#include <iostream>

#include "splay_tree.h"
using namespace std;

int main()
{
	CSplayTree<int> tree;
	tree.insert(3);
	tree.insert(2);
	tree.insert(1);
	tree.insert(4);

	tree.search(4);

	//tree.preOrder();
	/*cout<<tree.maximum()<<"\n";
	cout<<tree.minimum()<<"\n";
	
	tree.destory();
	cout<<"inorder\n";
	tree.inOrder();*/
	
	return 0;
}