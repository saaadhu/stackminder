#include <string>
#include <vector>
#include <map>
#include <iostream>

struct node
{
    std::string filename;
    std::string name;
    std::vector<struct node*> children;
    unsigned int stack_usage;
};

class graph
{
    public:
        
        bool exists(const std::string &filename, const std::string &name)
        {
            const std::string &key = make_key (filename, name);
            return names_to_nodes.find(key) != names_to_nodes.end();
        }
        
        void add_root(const std::string &filename, const std::string &name)
        {
            struct node *child = new node();
            child->filename = filename;
            child->name = name;
            child->stack_usage = 0;
            add(child);
            roots.push_back(child);
        }
        
        struct node* get_node(const std::string &filename, const std::string &name)
        {
            return names_to_nodes[make_key (filename, name)];
        }
        
        void add_child(const std::string &parent_filename, const std::string &parent_name, const std::string &child_filename, const std::string &name)
        {
            struct node *child = NULL;
            struct node *parent = NULL;

            if (!exists (child_filename, name))
            {
                struct node *temp = new node();
                temp->filename = child_filename;
                temp->name = name;
                temp->stack_usage = 0;
                add(temp);
            }
            child = get_node (child_filename, name);
            
            if (!exists (parent_filename, parent_name))
            {
                struct node *parent = new node();
                parent->filename = parent_filename;
                parent->name = parent_name;
                add(parent);
            }
            parent = get_node (parent_filename, parent_name);

            std::vector<struct node*>::const_iterator iter = parent->children.begin();

            bool parent_has_this_child = false;
            
            for (; iter != parent->children.end(); ++iter)
            {
                if (*iter == child)
                {
                    parent_has_this_child = true;
                    break;
                }
            }
            
            if (!parent_has_this_child)
            {
                parent->children.push_back(child);
            }
        }
        
        void print()
        {
            std::vector<struct node*>::const_iterator iter = roots.begin();

            for (; iter != roots.end(); ++iter)
            {
                print (*iter, 0, 0);
            }

            std::cout << std::endl << std::endl;
        }
    private:
        void print(const struct node* n, unsigned int indent_level, unsigned int stack_usage)
        {
            for (unsigned int i = 0; i<indent_level; ++i)
            {
                std::cout << "  ";
            }
            
            std::cout << n->name << " (" << n->filename << ") " <<  " : " << n->stack_usage << " : " << n->stack_usage + stack_usage << std::endl;
            
            std::vector<struct node*>::const_iterator iter = n->children.begin();
            
            for (; iter != n->children.end(); ++iter)
            {
                print (*iter, indent_level + 1, stack_usage + n->stack_usage);
            }
        }
        
        void add (struct node *n)
        {
            names_to_nodes[make_key(n->filename, n->name)] = n;
        }
        
        const std::string make_key (const std::string &filename, const std::string &name)
        {
            return filename + ":" + name;
        }
        
    private:
        std::vector<struct node*> roots;
        std::map<std::string, struct node *> names_to_nodes;
};
