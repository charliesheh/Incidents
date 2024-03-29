// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Amrita Kohli
 
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree) { rootPtr = copyTree(tree.rootPtr); }
	virtual ~BinaryTree() { destroyTree(rootPtr); }
	BinaryTree & operator = (const BinaryTree & sourceTree);
   
	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
	void levelOrder(void visit(ItemType &)) const { _levelorder(visit, rootPtr); }
	void indentPrint(void visit(ItemType &), int level) { _indentprint(visit, rootPtr, level); } //wrapper function for printing w/ indentation

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0; 
	virtual bool remove(const ItemType & data) = 0; 
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;
	virtual void theSmallest(ItemType &item) = 0;
	virtual void theLargest(ItemType &item) = 0;

private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _levelorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;

	// prints tree with indentation based on their level
	void _indentprint(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int level);
}; 

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr) 
{
	BinaryNode<ItemType>* newNodePtr = 0; 

	if (nodePtr != 0)
	{
		newNodePtr = new BinaryNode<ItemType>(nodePtr->getItem());
		newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
		newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
	}
   
    return newNodePtr;
}  

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != 0)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	} 
}  

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item);		
	}
}  

template<class ItemType> 
void BinaryTree<ItemType>::_levelorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{	//prints tree in level order (breadth first)
	if (nodePtr != 0)
	{
		Queue<BinaryNode<ItemType>*> Q;
		Q.enqueue(rootPtr);
		while (Q.isEmpty() == false)
		{
			BinaryNode<ItemType>* newNodePtr;
			Q.queueFront(newNodePtr);
			ItemType item = newNodePtr->getItem();
			visit(item);
			Q.dequeue(newNodePtr);

			if (newNodePtr->getLeftPtr() != 0)
				Q.enqueue(newNodePtr->getLeftPtr());

			if (newNodePtr->getRightPtr() != 0)
				Q.enqueue(newNodePtr->getRightPtr());
		}
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_indentprint(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int level)
{	//prints tree with indentation based on level
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();

		for (int indent = 0; indent < level; indent++)
		{
			cout << "\t";
		}

		cout << ++level << ". ";
		visit(item);
		cout << endl;

		_indentprint(visit, nodePtr->getRightPtr(), level);
		_indentprint(visit, nodePtr->getLeftPtr(), level);

		level--;
	}
}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
	copyTree (sourceTree->rootPtr);
	return *this;
} 


#endif

