#include <iostream>
using namespace std;


template <typename T>
class CSplayTreeNode
{
public:
	CSplayTreeNode(T data = T()):key(data){
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	T key;
	CSplayTreeNode *left;
	CSplayTreeNode *right;
	CSplayTreeNode *parent;
};

template <typename T>
class CSplayTree
{
private:
	CSplayTreeNode<T> *m_Root;

public:
	CSplayTree():m_Root(NULL){}
	~CSplayTree(){ destory();}
	void preOrder();
	void inOrder();
	void postOrder();
	CSplayTreeNode<T> *search(T key);
	T minimum();
	T maximum();
	void insert(T key);
	bool remove(T key);
	void destory();	
private:
	void destory(CSplayTreeNode<T> *tree);
	void preOrder(CSplayTreeNode<T> *tree)const;
	void inOrder(CSplayTreeNode<T> *tree)const;
	void postOrder(CSplayTreeNode<T> *tree)const;
	void splay(CSplayTreeNode<T> *tree);
	CSplayTreeNode<T> *search(CSplayTreeNode<T> *tree, T key)const;
	void insert(CSplayTreeNode<T> * tree,T key);
	void leftRotate(CSplayTreeNode<T>* tree);
	void rightRotate(CSplayTreeNode<T>* tree);
	void deleteOneNode(CSplayTreeNode<T>*pre,CSplayTreeNode<T>*cur);
};
template<typename T>
void CSplayTree<T>::preOrder(CSplayTreeNode<T> *tree)const
{
	if(tree == NULL)
		return;
	cout<<tree->key<<" ";
	preOrder(tree->left);
	preOrder(tree->right);
}
template<typename T>
void CSplayTree<T>::preOrder()
{
	preOrder(m_Root);
	cout<<"\n";
}
template <typename T>
void CSplayTree<T>::inOrder(CSplayTreeNode<T> *tree)const
{
	if(tree == NULL)
	{
		return;
	}
	inOrder(tree->left);
	cout<<tree->key<<" ";
	inOrder(tree->right);
}
template <typename T>
void CSplayTree<T>::inOrder()
{
	inOrder(m_Root);
	cout<<"\n";
}
template <typename T>
void CSplayTree<T>::postOrder(CSplayTreeNode<T> *tree)const
{
	if(tree == NULL)
		return ;
	postOrder(tree->left);
	postOrder(tree->right);
	cout<<tree->key<<" ";
}
template <typename T>
void CSplayTree<T>::postOrder()
{
	postOrder(m_Root);
	cout<<"\n";
}

template <typename T>
CSplayTreeNode<T> *CSplayTree<T>::search(CSplayTreeNode<T> *tree, T key)const
{
	if(tree != NULL)
	{
		if(tree->key > key)
		{
			return search(tree->left,key);
		}
		else if(tree->key < key)
		{
			return search(tree->right,key);
		}
		else
		{
			return tree;
		}
	}
	return tree;

}

template <typename T>
CSplayTreeNode<T> *CSplayTree<T>::search(T key)
{
	CSplayTreeNode<T> *p = search(m_Root,key);
	if(p != NULL)
	splay(p);
	return p;
}

template <typename T>
void CSplayTree<T>::insert(CSplayTreeNode<T> * tree,T key)
{
	CSplayTreeNode<T> *p = NULL;
	try{
		p = new CSplayTreeNode<T>(key);
	}catch(...){
		cout<<"new error\n";
		destory(tree);
		return ;
	}
	if(tree == NULL)
	{
		m_Root = p;
		return;
	}	
	CSplayTreeNode<T> *pre,*cur;
	pre = NULL;
	cur = tree;
	while(cur != NULL)
	{
		if(cur->key > key)
		{
			pre = cur;
			cur = cur->left;
		}
		else if(cur->key < key)
		{
			pre = cur;
			cur = cur->right;
		}
		else
		{
			return;
		}
	}
	if(pre->key > p->key) 
		pre->left = p;
	else
		pre->right = p;
	p->parent = pre;
	splay(p);
	
}
template <typename T>
void CSplayTree<T>::insert(T key)
{
	insert(m_Root,key);
}
template <typename T>
T CSplayTree<T>::minimum()
{
	CSplayTreeNode<T> *p = m_Root;
	if(p != NULL)
	{
		while(p->left != NULL)
		{
			p = p->left;
		}
		return p->key;
	}
}
template <typename T>
T CSplayTree<T>::maximum()
{
	CSplayTreeNode<T> *p = m_Root;
	if(p != NULL)
	{
		while(p->right != NULL)
		{
			p = p->right;
		}
		return p->key;
	}
}
template <typename T>
void CSplayTree<T>::splay(CSplayTreeNode<T> *tree)
{
	while(tree != NULL && tree->parent != NULL)
	{
		if(tree->parent->left == tree)
		{
			rightRotate(tree->parent);
		}
		else 
		{
			leftRotate(tree->parent);
		}

	}
}
template <typename T>
void CSplayTree<T>::leftRotate(CSplayTreeNode<T>* tree)
{
	CSplayTreeNode<T> *grand = tree->parent;
	CSplayTreeNode<T> *child = tree->right;
	if(grand != NULL)
	{
		if(grand->left == tree)
		{
			grand->left = child;
		}
		else
		{
			grand->right = child;
		}
	}
	tree->right = child->left;
	if(child->left != NULL)
	{
		child->left->parent = tree;
	}
	child->left = tree;
	tree->parent = child;
	child->parent = grand;
	if (child->parent == NULL)
	{
		m_Root = child;
	}
}
template <typename T>
void CSplayTree<T>::rightRotate(CSplayTreeNode<T>* tree)
{
	CSplayTreeNode<T> *grand = tree->parent;
	CSplayTreeNode<T> *child = tree->left;
	if(grand != NULL)
	{
		if(grand->left == tree)
		{
			grand->left = child;
		}
		else
			grand->right = child;
	}
	tree->left = child->right;
	if(child->right != NULL)
	{
		child->right->parent = tree;
	}
	child->right = tree;
	tree->parent = child;
	child->parent = grand;
	if(child->parent == NULL)
	{
		m_Root = child;
	}

}
template <typename T>
bool CSplayTree<T>::remove(T key)
{
	CSplayTreeNode<T> *pre = NULL,*cur = m_Root;
	while (cur != NULL)
	{
		if(cur->key == key)
			break;	
		else
		{
			pre = cur;
			if(cur->key > key)
				cur = cur->left;
			else
				cur = cur->right;
		}
	}
	if(cur == NULL)
		return false;
	if(cur->left == NULL || cur->right == NULL)
	{
		deleteOneNode(pre,cur);
		splay(pre);
	}
	else
	{
		CSplayTreeNode<T>* rPre = cur,rCur = cur->right;
		while(rCur->left != NULL)
		{
			rPre = rCur;
			rCur = rCur->left;
		}
		cur->key = rCur->key;
		deleteOneNode(rPre,rCur);
		splay(rPre);
	}
	return true;
}

template <typename T>
void CSplayTree<T>::deleteOneNode(CSplayTreeNode<T>*pre,CSplayTreeNode<T>*cur)
{
	if(cur->left == NULL && cur->right == NULL)
	{
		if(pre == NULL)
			m_Root = NULL;
		else if(pre->left == cur)
			pre->left = NULL;
		else
			pre->right = NULL;
	}
	else if(cur->left == NULL)
	{
		if(pre == NULL)
		{
			cur->right->parent = pre;
			m_Root = cur->right;
		}
		if(pre->left == cur)
			pre->left = cur->right;
		else
			pre->right = cur->right;
		cur->right->parent = pre;
	}
	else
	{
		if(pre == NULL)
		{
			cur->left->parent = pre;
			m_Root = cur->left;
		}
		if(pre->left == cur)
			pre->left = cur->left;
		else
			pre->right = cur->left;
		cur->left->parent = pre;
	}
	delete cur;
}
template <typename T>
void CSplayTree<T>::destory(CSplayTreeNode<T> *tree)
{
	if(tree == NULL)
	{
		return;
	}
	destory(tree->left);
	destory(tree->right);
	if(tree->parent == NULL)
	{
		m_Root = NULL;
	}
	delete tree;
}
template <typename T>
void CSplayTree<T>::destory()
{
	destory(m_Root);	
}


