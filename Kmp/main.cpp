#include <iostream>
#include <string>
using namespace std;

void getNext(string str,int *next)
{
	if (str.empty())
	{
		return;
	}
	int size = str.size();
	int i = 0;
	int j = -1;
	next[0] = -1;
	while(i < size-1)
	{
		if(j == -1 || str[j] == str[i])
		{
			i++;
			j++;
			next[i] = j;	
		}
		else
		{
			j = next[j];
		}
	}
}

void getNextVal(string str,int *next)
{
	if (str.empty())
	{
		return;
	}
	int size = str.size();
	int i = 0;
	int j = -1;
	next[0] = -1;
	while(i < size-1)
	{
		if(j == -1 || str[j] == str[i])
		{
			i++;
			j++;
			if(next[i] == next[j])
			    next[i] = next[j];
			else
				next[i] = j;
		}
		else
		{
			j = next[j];
		}
	}
}
int indexKmp(string str,string src,int pos)
{
	if(str.empty()|| pos < 0 || src.empty())
	{
		return -1;
	}
	int strSize = str.size();
	int srcSize = src.size();
	int *next = new int[srcSize];
	getNextVal(src,next);
	int i = pos-1;
	int j = -1;
	while(i < strSize &&  j < srcSize)
	{
		if(j == -1 || str[i] == src[j])
		{
			++i;
			++j;
		}
		else
		{
			j = next[j];
		}
	}
	delete []next;
	if(j >= srcSize)
	{
		return i-srcSize+1;
	}
	else
	{
		return -1;
	}

}

int main()
{
	cout<<indexKmp("adadeadcadcfg","adcadcfg",0)<<"\n";
}