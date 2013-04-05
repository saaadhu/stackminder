#include <string>
#include <vector>
#include <map>
#include <iostream>

struct node
{
    std::string name;
    std::vector<struct node*> children;
    unsigned int stack_usage;
};

class graph
{
    public:
        bool exists(const std::string &name)
        {
            return names_to_nodes.find(name) != names_to_nodes.end();
        }
        
        void add_root(const std::string &name)
        {
            struct node child;
            child.name = name;
            child.stack_usage = 0;
            names_to_nodes[name] = child;

            roots.push_back(&names_to_nodes[name]);
        }
        
        struct node* get_node(const std::string &name)
        {
            return &names_to_nodes[name];
        }
        
        void add_child(const std::string &parent_name, const std::string &name)
        {
            struct node *child = NULL;

            if (!exists (name))
            {
                struct node temp;
                temp.name = name;
                temp.stack_usage = 0;
                names_to_nodes[name] = temp;
            }
            child = &names_to_nodes[name];
            
            if (!exists (parent_name))
            {
                struct node parent;
                parent.name = parent_name;
                names_to_nodes[parent_name] = parent;
            }
            
            names_to_nodes[parent_name].children.push_back(child);
        }
        
        void print()
        {
            std::vector<struct node*>::const_iterator iter = roots.begin();

            for (; iter != roots.end(); ++iter)
            {
                print (*iter, 0, 0);
            }
        }

        void print(const struct node* n, unsigned int indent_level, unsigned int stack_usage)
        {
            for (unsigned int i = 0; i<indent_level; ++i)
            {
                std::cout << "  ";
            }
            
            std::cout << n->name << " : " << n->stack_usage << " : " << n->stack_usage + stack_usage << std::endl;
            
            std::vector<struct node*>::const_iterator iter = n->children.begin();
            
            for (; iter != n->children.end(); ++iter)
            {
                print (*iter, indent_level + 1, stack_usage + n->stack_usage);
            }
        }
        
    private:
        std::vector<struct node*> roots;
        std::map<std::string, struct node> names_to_nodes;
};
