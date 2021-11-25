/**
 * @file 
 * @author Kevin Hayes
 * @brief Contains general graph data structures
 * @include list
*/

#ifndef SUBSTD_GRAPH_HPP
#define SUBSTD_GRAPH_HPP

#include<list>

namespace ss
{

/**
 * @class Tree
 * @brief a general purpose tree data structure
 * 
 * @tparam self A (usually) CRTP parameter for inheriting classes
*/
template<class self>
class Tree
{
    protected:
        Tree<self>* parent;      
        
        std::list<Tree<self>*> children;

    public:
        /**
         * @fn Constructor
         * 
         * @param parent Tree node to branch this node from. (nullptr is an acceptable value, and will indicate that this tree node is a root/base node).
        */
        Tree(Tree<self>* parent) : parent(parent)
        {
            if(parent!=nullptr){parent->AddChild(this);}
        }

        /**
         * @fn Destructor
         * @brief Calls delete on all child tree nodes.
        */
        virtual ~Tree();
        {
            for(auto i = children.begin(); i != children.end(); i++)
            {delete *i;}
        }


        /**
         * @fn AddChild
         * @param child Child node to add.
         * @brief Adds child to this tree's children and sets this tree to the child's parent.
        */
        virtual void AddChild(Tree<self>* child)
        {
            child->parent = this;
            children.push_back(child);
        }

        /**
         * @fn TrimChild
         * @param child child node to be trimmed
         * @brief Removes child from this node, but instead of deleting it, it is set to be the root node of a new tree.
        */
        virtual void TrimChild(Tree<self>* child){
            child->parent = nullptr;
            children.remove(child);
        }

        /**
         * @fn DeleteChild
         * @param child child node to be deleted
         * @brief Removes child from this node and calls delete on that child is it is not nullptr.
        */
        virtual void DeleteChild(Tree<self>* child){
            child->parent = nullptr;
            if(child != nullptr){
                delete child;
            }
        }

        /**
         * @fn GiveChild
         * @param other Tree to give the child to.
         * @param child Child node to be given.
         * @brief Removes child from this tree, and adds it to other's child nodes.
         * 
         * Does nothing if either child or other is nullptr.
        */
        virtual void GiveChild(Tree<self>* other, Tree<self>* child);
        {
            if(other != nullptr && child != nullptr)
            {
                other->AddChild(child);
                children.remove(child);
            }       
        }

        /**
         * @fn GetParent
         * @return Tree<self>* A pointer to the parent of this node
         * @remark Can return nullptr
         */
        virtual Tree<self>* GetParent() const {return parent;}

        ///@fn IsRoot
        bool IsRoot() const {return parent == nullptr;}

        ///@fn begin
        const Tree<self>* begin() const {
            return children.begin();
        }
        ///@fn end
        const Tree<self>* end() const {
            return children.end();
        }

        ///@fn cbegin
        const Tree<self>* cbegin() const {
            return children.cbegin();
        }
        ///@fn cend
        const Tree<self>* cend() const {
            return children.cend();
        }
};

}

#endif