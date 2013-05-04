
void record_callgraph(void *gcc_data, void *user_data);
unsigned int save_stack_usage (void);
void dump_data (void *gcc, void *user_data);

#include "gmp.h"
#include <stdio.h>
extern "C"
{
#include "gcc-plugin.h"
#include "tree-pass.h"
#include "cgraph.h"
#include "tree.h"
}

#include "graph.h"
graph callgraph;

extern "C"
{
    int plugin_is_GPL_compatible;
    
    struct rtl_opt_pass pass=
    {
        {
            RTL_PASS,
            "read_stack_usage",				/* name */
            NULL,                        /* optinfo_flags */
            save_stack_usage,			/* execute */
            NULL,                                 /* sub */
            NULL,                                 /* next */
            0,                                    /* static_pass_number */
            TV_EXPAND,				/* tv_id */
            0,
            0,                             /* properties_provided */
            0,		/* properties_destroyed */
            0,
            0
        }
    };

    struct register_pass_info pass_info = 
    {
        (struct opt_pass *) &pass,
        "pro_and_epilogue",
        0,
        PASS_POS_INSERT_AFTER
    };


    int plugin_init (struct plugin_name_args *info,
            struct plugin_gcc_version *v)
    {
        register_callback ("stackminder", PLUGIN_ALL_IPA_PASSES_END,
                record_callgraph, NULL);
        
        register_callback ("stackminder", PLUGIN_PASS_MANAGER_SETUP,
                NULL, &pass_info);
        
        register_callback ("stackminder", PLUGIN_FINISH,
                dump_data, &pass_info);
        return 0;
    }
}

unsigned int save_stack_usage(void)
{
    if (cfun)
    {
        const char *name = IDENTIFIER_POINTER (DECL_NAME (cfun->decl));
        const char *filename = DECL_SOURCE_FILE (cfun->decl);
        callgraph.get_node( filename, name)->stack_usage = cfun->machine->stack_usage;
    }
    return 0;
}

void record_callgraph(void *gcc_data, void *user_data)
{
    cgraph_node_ptr node_ptr = NULL;
    struct cgraph_edge *callees_ptr = NULL;
    
    FOR_EACH_FUNCTION_WITH_GIMPLE_BODY(node_ptr)
    {
        const char *name = IDENTIFIER_POINTER(DECL_NAME(node_ptr->decl));
        const char *filename = DECL_SOURCE_FILE (node_ptr->decl);
        
        if (!node_ptr->callers)
            callgraph.add_root (filename, name);
        
        callees_ptr = node_ptr->callees;
        while (callees_ptr)
        {
            const char* callee_name =  IDENTIFIER_POINTER(DECL_NAME(callees_ptr->callee->decl));
            const char* callee_filename = DECL_SOURCE_FILE(callees_ptr->callee->decl);
            
            callgraph.add_child(filename, name, callee_filename, callee_name);
            callees_ptr = callees_ptr->next_callee;
        }
    }
}

void dump_data(void *gcc_data, void *user_data)
{
    callgraph.print();
}

