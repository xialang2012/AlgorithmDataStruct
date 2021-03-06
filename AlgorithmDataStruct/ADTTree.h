#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <math.h>
#include <limits>

const int MAX_INT = std::numeric_limits<int>::max();

// node class
template<typename T>
class Node
{
public:
	Node() : left(nullptr), right(nullptr) {};
	
	T data;
	Node *left;
	Node *right;

	virtual ~Node() {};

private:

};

// operations of tree
template<typename T>
class ADTTree
{
public:
	Node<T>* root = nullptr;

	void Create(int depth = 3); // creat an tree with default depth of 3
	void PrintPreorder(); // print the tree in preorder
	
	void PrintLevelOrder(); // print the tree in levelorder

	void PrintInOrder(); // print the tree in inorder

	virtual ~ADTTree();

private:

};

template<typename T>
void ADTTree<T>::Create(int depth)
{
	std::cout << "create an tree..." << std::endl;
	this->root = new Node<int>();
	this->root->data = 0;
	std::cout << "top data: " << this->root->data << std::endl;

	std::queue<Node<T> *> s;
	s.push(this->root);
	for (int i=1; i<=pow(2, depth-1)-1; ++i)
	{
		Node<T> *mode = s.front();
		s.pop();

		mode->left = new Node<int>();
		mode->left->data = i;
		mode->right = new Node<int>();
		mode->right->data = i+1;

		std::cout << "left data: " << mode->left->data << ", right data: " << mode->right->data << std::endl;

		s.push(mode->left);
		s.push(mode->right);
	}
	std::cout << "create trees finished!" << std::endl;
	/*
	0
	6        5
	2   7    9    4
	*/
	/*
	std::cout << "create an tree..." << std::endl;
	ADTTree<T> *root = new ADTTree<int>();
	root->left = new ADTTree<int>();
	root->right = new ADTTree<int>();
	root->data = 0;

	root->left->left = new ADTTree<int>();
	root->left->right = new ADTTree<int>();
	root->left->data = 6;
	root->left->left->left = nullptr;
	root->left->left->right = nullptr;
	root->left->left->data = 2;
	root->left->right->left = nullptr;
	root->left->right->right = nullptr;
	root->left->right->data = 7;

	root->right->left = new ADTTree<int>();
	root->right->right = new ADTTree<int>();
	root->right->data = 5;
	root->right->left->left = nullptr;
	root->right->left->right = nullptr;
	root->right->left->data = 9;
	root->right->right->left = nullptr;
	root->right->right->right = nullptr;
	root->right->right->data = 4;
	*/
}

template<typename T>
void ADTTree<T>::PrintPreorder()
{
	std::cout << "Preorder Search" << std::endl;
	std::stack<Node<T> *> s;
	if (root == nullptr)
	{
		std::cout << "empty tree" << std::endl;
		return;
	}
	else
	{
		if (root != nullptr) s.push(root);
	}

	while (!s.empty())
	{
		Node<T> *node = s.top();
		s.pop();
		std::cout << node->data << ", ";
		if (node->right != nullptr) s.push(node->right);
		if (node->left != nullptr) s.push(node->left);		
	}
	std::cout << std::endl;
}

template<typename T>
void ADTTree<T>::PrintLevelOrder()
{
	std::cout << "Level Order Search" << std::endl;
	std::queue<Node<T> *> s;
	if(root == nullptr) 
	{
		std::cout << "empty tree" << std::endl;
		return;
	}
	else
	{
		//std::cout << root->data << std::endl;
		if (root!= nullptr) s.push(root);
		//if (root->right != nullptr) s.push(root->right);
	}

	while (!s.empty())
	{
		Node<T> *node = s.front();
		s.pop();
		std::cout << node->data << ", ";
		if (node->left != nullptr) s.push(node->left);
		if (node->right != nullptr) s.push(node->right);
	} 
	std::cout << std::endl;
}

template<typename T>
void ADTTree<T>::PrintInOrder()
{
	std::cout << "Inorder Search" << std::endl;
	std::stack<Node<T> *> s;
	if (root == nullptr)
	{
		std::cout << "empty tree" << std::endl;
		return;
	}

	Node<T> *node = root;
	while (!s.empty() || node != nullptr)
	{
		if (node != nullptr)
		{
			s.push(node);
			node = node->left;
		}
		else
		{
			node = s.top();
			s.pop();
			std::cout << node->data << ", ";
			node = node->right;
		}
		/*Node<T> *node = s.top();
		s.pop();
		std::cout << node->data << ", ";
		if (node->right != nullptr) s.push(node->right);
		if (node->left != nullptr) s.push(node->left);*/
	}
	std::cout << std::endl;
}

template<typename T>
ADTTree<T>::~ADTTree()
{
	std::cout << "Destory all the resources" << std::endl;
	std::queue<Node<T> *> s;
	if (root == nullptr)
	{
		std::cout << "empty tree" << std::endl;
		return;
	}
	else
	{
		if (root != nullptr) s.push(root);
	}

	while (!s.empty())
	{
		Node<T> *node = s.front();
		s.pop();		
		if (node->left != nullptr) s.push(node->left);
		if (node->right != nullptr) s.push(node->right);
		
		std::cout << "deleted tree with data, " << node->data << std::endl;
		delete node;
	}
	std::cout << "resources clean done!" << std::endl;
}


// binray sort tree
template<typename T>
class ADTBSTree : public ADTTree<T>
{
public:

	ADTBSTree() : ADTTree() {};

	void Create();
	void Insert(const std::vector<T>& add);
	void Delete();

	bool Search(const T& value, Node<T>* posNode);

	~ADTBSTree() {};

private:

};

template<typename T>
bool ADTBSTree<T>::Search(const T& value, Node<T>* posNode)
{
	if (root == nullptr)
	{
		std::cout << "empty tree" << std::endl;
		return false;
	}

	Node<T>* node = root;
	while (node != nullptr)
	{
		posNode = node;
		if (node->data == value)
		{
			posNode = node;
			return true;
		}
		else if (node->data > value)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
		
	}
	return false;
}

template<typename T>
void ADTBSTree<T>::Create()
{

}

template<typename T>
void ADTBSTree<T>::Delete()
{

}

template<typename T>
void ADTBSTree<T>::Insert(const std::vector<T>& add)
{
	Node<T> *node = new Node<T>();
	for each(auto var in add)
	{
		if (this->Search(var, node))
		{
			std::cout << "value already existed in Binary Tree, continue" << std::endl;
			continue;
		}

		Node<T> *nodeNew = new Node<T>();
		nodeNew->data = var;
		if (node->data > var)  // insert to left
		{			
			nodeNew->left = nodeNew;			
		}
		else
		{
			nodeNew->right = nodeNew;  // or to right
		}
	}

	delete node;
}

