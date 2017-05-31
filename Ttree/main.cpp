#include <iostream>
#include <string>
using namespace std;

#define MaxSize 26
struct TNode
{
	TNode():isStr(false)
	{
		for(int i = 0; i < MaxSize; ++i)
		{
			Node[i] = NULL;
		}
	}
	bool isStr;
	TNode* Node[MaxSize];
};

class TreeNode
{
public:
	TreeNode():root(new TNode)
	{
	}
	~TreeNode()
	{
		if (root != NULL)
		{
			destroy(root);
			root = NULL;
		}
	}
	void insert(string str)
	{
		int size = str.size();
		TNode *p = root;
		for (int i = 0; i < size; ++i)
		{
			if (p->Node[str[i]-'a'])
			{
				p = p->Node[str[i]-'a'];
			}
			else
			{
				TNode *node = new TNode;
				p->Node[str[i]-'a'] = node;
				p = p = p->Node[str[i]-'a'];
			}
			p->isStr = true;
		}
	}
	bool serch(string str)
	{
		int size = str.size();
		TNode *p = root;
		for (int i = 0; i < size; ++i)
		{
			if(p->Node[str[i]-'a'])
			{
				p = p->Node[str[i]-'a'];
			}
			else
			{
				break;
			}
		}
		if (p->isStr)
		{
			return true;
		}
		return false;
	}
private:
	void destroy(TNode *&head)
	{
		for (int i = 0; i < MaxSize; ++i)
		{
			if (head->Node[i])
			{
				destroy(head->Node[i]);
			}
		}
		delete head;
		head = NULL;
	}
private:
	TNode *root;
};
int main()
{
	{
		TreeNode bt;
		int n;
		cin >> n;
		for (int i = 0;i < n; ++i)
		{
			string str;
			cin >> str;
			bt.insert(str);
		}
		cout<<"********insert success**********\n";
	}
	int n;
	cout<<"wait\n";
	cin>>n;
	cout<<"find str:\n";


	/*
	while(1)
	{
		string str;
		cin >> str;
		if(bt.serch(str))
			cout<<"find success\n";
		else
			cout<<"find error\n";
	}*/
}
