#include<substd/graph.hpp>

namespace ss
{

Tree::Tree(Tree* parent):parent(parent)


Tree::~Tree()


void Tree::AddChild(Tree* child)


void Tree::GiveChild(Tree* other, const int& index)


int Tree::IndexInParent()


void Tree::SetIndex(const int& index)


}//namespace ss;