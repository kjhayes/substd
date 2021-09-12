#ifndef SUBSTD_TREE_HPP
#define SUBSTD_TREE_HPP

#include<vector>

namespace ss
{

class Tree
{
    protected:
        Tree* parent;        
        
        std::vector<Tree*> children;

        ~Tree();

    public:
        Tree(Tree*);
        virtual void AddChild(Tree*);
        virtual void GiveChild(Tree*, const int&);
        virtual int IndexInParent();
        virtual void SetIndex(const int&);
        virtual void Destroy();
};

}

#endif