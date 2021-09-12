#include<substd/tree.hpp>

namespace ss
{

Tree::Tree(Tree* parent):parent(parent)
{
    if(parent!=nullptr){parent->AddChild(this);}
}

Tree::~Tree()
{
    for(auto i = children.begin(); i != children.end(); i++)
    {delete *i;}
}

void Tree::AddChild(Tree* child)
{
    child->parent = this;
    children.push_back(child);
}

void Tree::GiveChild(Tree* other, const int& index)
{
    if(other!=nullptr)
    {
    other->AddChild(children[index]);
    children.erase(children.begin()+index);
    }       
}

int Tree::IndexInParent()
{
    int index = 0;
    for(auto i = parent->children.begin(); i != parent->children.end(); i++)
    {
        if((*i)==this)
        {
            return index;
        }
        else{index++;}
    }
    return -1;
}

void Tree::SetIndex(const int& index)
{
    parent->children.erase(parent->children.begin()+IndexInParent());
    parent->children.insert(parent->children.begin()+index, this);
}

void Tree::Destroy()
{
    parent->children.erase(parent->children.begin()+IndexInParent());
    delete this;
}

}//namespace gly;