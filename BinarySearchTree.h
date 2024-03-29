// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Amrita Kohli
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
	private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
   
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
   
	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
   
	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
   
	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* nodePtr, const ItemType & target) const;

	//returns smallest node
	BinaryNode<ItemType>* findSmallest(BinaryNode<ItemType>* nodePtr, const ItemType &item) const;

	// returns largest node
	BinaryNode<ItemType>* findLargest(BinaryNode<ItemType>* nodePtr, const ItemType &item) const;
   
	public:  
	// insert a node at the correct location
    bool insert(const ItemType & newEntry);
	// remove a node if found
	bool remove(const ItemType & anEntry);
	// find a target node
	bool getEntry(const ItemType & target, ItemType & returnedItem) const;
	// stores the smallest item
	void theSmallest(ItemType &item);
	//stores the largest item
	void theLargest(ItemType &item);
};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>:: insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	return true;
}  

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	return isSuccessful; 
}  

/* getEntry returns true if key entered in anEntry is found in the binary search tree and stores the item data in returnedItem */
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType &returnedItem) const
{
	bool isSuccessful = false;

	BinaryNode<ItemType>* entry;
	entry = findNode(this->rootPtr, anEntry);

	if (entry)
	{
		returnedItem = entry->getItem();
		isSuccessful = true;
	}

	return isSuccessful;
}  

/* Stores the smallest node's data in item. */
template<class ItemType>
void BinarySearchTree<ItemType>::theSmallest(ItemType &item)
{
	BinaryNode<ItemType>* small;
	small = findSmallest(this->rootPtr, item);
	item = small->getItem();
}

/* Stores the largest node's data in item. */
template<class ItemType>
void BinarySearchTree<ItemType>::theLargest(ItemType &item)
{
	BinaryNode<ItemType>* large;
	large = findLargest(this->rootPtr, item);
	item = large->getItem();
}


//////////////////////////// private functions ////////////////////////////////////////////

//Used to insert nodes in the tree in order
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNodePtr) 
{
	if (nodePtr == 0)
		return newNodePtr;

	else if (nodePtr->getItem() > newNodePtr->getItem())
		{
			nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr)); //going left
		}

	else
		{
			nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
		}

	return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success)
{
	if (nodePtr == 0)                   
	{
		success = false;
		return 0;
	}

	if (nodePtr->getItem() > target)		 
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));

	else if (nodePtr->getItem() < target)	 
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));

	else		
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}      

	return nodePtr;   
}  

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())				
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)  
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0) 
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;      
	}
	else                                  
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}  
}  

template<class ItemType> 
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else 
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}       
}

/* findNode searches the tree for target and returns nodePtr when found */
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr, const ItemType &target) const 
{
	while (nodePtr != 0) //iterative
	{
		if (nodePtr->getItem() == target)			  
			return nodePtr;
		else if (nodePtr->getItem() < target)		  
			nodePtr = nodePtr->getRightPtr();	//going right
		else
			nodePtr = nodePtr->getLeftPtr();	// going left
	}

	return 0;
}

/* Finds the smallest node and returns its pointer. */
template<class ItemType>
BinaryNode<ItemType>*  BinarySearchTree<ItemType>::findSmallest(BinaryNode<ItemType>* nodePtr, const ItemType &item) const
{
	if (nodePtr != 0)
	{
		if (nodePtr->isLeaf())
			return nodePtr;
		
		else
			return findSmallest(nodePtr->getLeftPtr(), item);
	}

	return 0;
}

template<class ItemType>
BinaryNode<ItemType>*  BinarySearchTree<ItemType>::findLargest(BinaryNode<ItemType>* nodePtr, const ItemType &item) const
{
	if (nodePtr != 0)
	{
		if (nodePtr->isLeaf())
			return nodePtr;

		else
			return findLargest(nodePtr->getRightPtr(), item);
	}

	return 0;
}

#endif
