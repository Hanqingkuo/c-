#include <set>
#include <queue>
#include <iostream>
#include <vector>
#include <bitset>
#include <stack>
#include <algorithm>
using namespace std;

struct DataType
{
	DataType(char c=0):ch(c), cnt(1), weight(0.0){}

	bool operator<(const DataType &src)const
	{ return ch < src.ch; }

	char ch;
	int cnt;
	double weight;
	vector<int> encode;
};

class CAnalyze
{
public:
	void analyzeBuffer(char *buffer);
	void showResult()
	{
		set<DataType>::iterator it = dataSet.begin();
		for(; it!=dataSet.end(); ++it)
		{
			cout<<it->ch<<" cnt:"<<it->cnt<<" weight:"<<it->weight<<endl;
		}
	}
private:
	set<DataType> dataSet;
	friend class CHuffmanTree;
};
void CAnalyze::analyzeBuffer(char *buffer)
{
	char *p = buffer;
	int size = 1;
	DataType data;
	for(; *p != '\0'; ++p, ++size)   // "hello"
	{
		data.ch = *p;
		set<DataType>::iterator it = dataSet.find(data);
		if(it != dataSet.end())
			it->cnt++;
		else
			dataSet.insert(data);
	}

	set<DataType>::iterator it = dataSet.begin();
	for(; it!=dataSet.end(); ++it)
	{
		it->weight = it->cnt/(double)size;
	}
}
const int N = 5000;
class CHuffmanTree
{
public:
	CHuffmanTree(CAnalyze &a):_analyze(a)
	{
		set<DataType>::iterator it = _analyze.dataSet.begin();
		for(; it!=_analyze.dataSet.end(); ++it)
		{
			_queue.push(*it);
		}
	}
	~CHuffmanTree()
	{

	}
	void makeTree()
	{
		while(_queue.size() > 1)
		{
			HuffmanNode *ptmp1 = NULL;
			HuffmanNode *ptmp2 = NULL;
			HuffmanNode node1 = _queue.top();
			_queue.pop();
			HuffmanNode node2 = _queue.top();
			_queue.pop();
			
			HuffmanNode node;
			node._data.weight = node1._data.weight + node2._data.weight;

			ptmp1 = new HuffmanNode(node1);
			if(ptmp1->_pleft != NULL)
			{
				ptmp1->_pleft->_parent = ptmp1;
				ptmp1->_pright->_parent = ptmp1;
			}
			node._pleft = ptmp1;

			ptmp2 = new HuffmanNode(node2);
			if(ptmp2->_pleft != NULL)
			{
				ptmp2->_pleft->_parent = ptmp2;
				ptmp2->_pright->_parent = ptmp2;
			}
			node._pright = ptmp2;

			_queue.push(node);

		}
		
		HuffmanNode &node = _queue.top();
		if(node._pleft != NULL)
			node._pleft->_parent = &node;
		if(node._pright != NULL)
			node._pright->_parent = &node;
	}
	void showEncode()
	{
		HuffmanNode *pnode = &_queue.top();
		vector<int> bitvec;
		int level = -1;
		showEncode(pnode, bitvec, level);
	}
	void showEncode(char *buffer)
	{
		encodeBitSetCnt = 0;
		char *p = buffer;
		for(;*p != '\0'; ++p)
		{
			DataType data(*p);
			set<DataType>::iterator it = _analyze.dataSet.find(data);
			if(it != _analyze.dataSet.end())
			{
				vector<int>::iterator vit = it->encode.begin();
				for(; vit!=it->encode.end(); ++vit)
				{
					//encodeBuf[cnt++] = *vit;
					encodeBitset.set(encodeBitSetCnt++, *vit);
				}
			}
			else
			{
				cout<<*p<<"编码失败!"<<endl;
			}
		}
		//bitset<32> mybit;
		//FILE *pf = fopen("encode.txt", "w");
		for(int i=0; i<encodeBitSetCnt; ++i)
		{
			cout<<encodeBitset.at(i);
		}
		cout<<endl;
	}

	void decode()
	{
		HuffmanNode *pnode = &_queue.top();
		for(int i=0; i<encodeBitSetCnt; ++i)
		{
			if(encodeBitset[i] == 0)
			{
				pnode = pnode->_pleft;
			}
			else
			{
				pnode = pnode->_pright;
			}

			if(pnode->_pleft == NULL)
			{
				cout<<pnode->_data.ch;
				pnode = &_queue.top();
			}
		}
		cout<<endl;
	}
private:
	struct HuffmanNode
	{
		HuffmanNode(DataType data=DataType()):_data(data),_pleft(NULL), _pright(NULL), _parent(NULL){}
		HuffmanNode(const HuffmanNode &src):_data(src._data),_pleft(src._pleft),_pright(src._pright),_parent(src._parent){}
		bool operator>(const HuffmanNode &src)const
		{return _data.weight > src._data.weight;}
		DataType _data;
		HuffmanNode *_pleft;
		HuffmanNode *_pright;
		HuffmanNode *_parent;
	};
	typedef priority_queue<HuffmanNode, vector<HuffmanNode>, greater<HuffmanNode>> QUEUE_TYPE;
	void showEncode(HuffmanNode *pnode, vector<int> &vec, int level)
	{
		level++;
		if(pnode == NULL)
		{
			return;
		}
		else 
		{
			if(pnode->_parent != NULL)
			{
				if(pnode == pnode->_parent->_pleft)
					vec.push_back(0);
				else
					vec.push_back(1);
			}
		}

		showEncode(pnode->_pleft, vec, level);
		if(pnode->_pleft == NULL)
		{
			DataType data(pnode->_data.ch);
			set<DataType>::iterator it = _analyze.dataSet.find(data);
			if(it != _analyze.dataSet.end())
				it->encode = vec;

			cout<<pnode->_data.ch<<" ";
			copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
			cout<<endl;
			vec.pop_back();
		}
		else
		{
			while(level < vec.size())
			{
				vec.pop_back();
			}
		}
		showEncode(pnode->_pright, vec, level);
	}

	CAnalyze &_analyze;
	QUEUE_TYPE _queue;
	bitset<N> encodeBitset;
	int encodeBitSetCnt;
};

int main(int argc, char* argv[])
{
	char inputBuffer[1000]={0};

	cout<<"请输入原始的字符串:"<<endl;
	cin.getline(inputBuffer, 1000);

	cout<<"开始分析数据..."<<endl;
	CAnalyze analyze;
	analyze.analyzeBuffer(inputBuffer);
	analyze.showResult();

	cout<<"开始生成哈夫曼树..."<<endl;
	cout<<"输出原始字符编码压缩序列..."<<endl;
	CHuffmanTree huffman(analyze);
	huffman.makeTree();
	//huffman.writeEncode();
	huffman.showEncode();

	cout<<"显示原始字符的的编码序列:"<<endl;
	huffman.showEncode(inputBuffer);

	cout<<"开始解码程序生成解码字符序列:"<<endl;
	huffman.decode();

	return 0;
}


