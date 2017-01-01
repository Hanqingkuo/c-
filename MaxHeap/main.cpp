/*************************************************************************
	> File Name:main.cpp
	> Author: Hanqingkuo
	> Mail: 18829897801@163.com
	> Created Time: Sat 31 Dec 2016 11:20:42 AM CST
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

typedef vector<int>::iterator Iterator;

// first method
/*
template <typename RandomAccessIterator>
void adjustHeap(RandomAccessIterator first,int holeIndex, int len)
{
    int value = *(first+ holeIndex);
    int topIndex = holeIndex;
    int sendIndex = 2 * holeIndex + 2;
    while(sendIndex < len)
    {
        if(*(first+sendIndex-1) > *(first+sendIndex))
        {
            --sendIndex;
        }
        if(value < *(first+sendIndex))
        {
            *(first+holeIndex) = *(first+sendIndex);
        }
        else
        {
            value = *(first + sendIndex);
        }
        holeIndex = sendIndex;
        sendIndex = (sendIndex+1) * 2;
    }
    if(sendIndex == len)
    {
        if(value < *(first+sendIndex-1))
        {
            *(first+holeIndex) = *(first+sendIndex-1);
        }
        holeIndex = sendIndex-1;
    }
    *(first+holeIndex) = value;
}
template <typename RandomAccessIterator>
void makeHeap(RandomAccessIterator first,RandomAccessIterator last)
{
    if(last - first < 2)
    {
        return;
    }
    int len =  last - first;
    int parent = (len-2)/2;
    while(true)
    {
        adjustHeap(first,parent,len);
        if(parent == 0)
        {
            return ;
        }
        parent--;
    }

}
*/


void push_heap(Iterator first,int topIndex,int holeIdex,int value)
{
    int parent = (holeIdex-1)/2;
    while(holeIdex > topIndex && *(first+parent) < value)
    {
        *(first+holeIdex) = *(first+parent);
        holeIdex = parent;
        parent = (parent-1)/2;
    }
    *(first+holeIdex) = value;
}
void pushHeap(Iterator first,Iterator last)
{
    int  len = last - first;
    push_heap(first,0,len-1,*(last-1));
}
void adjustHeap(Iterator first,int holeIndex,int len,int value)
{
    int topIndex = holeIndex;
    int sendIndex = holeIndex * 2 + 2;
    while(sendIndex < len)
    {
        if(*(first + sendIndex -1) > *(first + sendIndex))
        {
            --sendIndex;
        }
        *(first + holeIndex) = *(first + sendIndex);
        holeIndex = sendIndex;
        sendIndex = (sendIndex+1)*2;
    }
    if(sendIndex == len)
    {
        *(first+holeIndex) = *(first + sendIndex-1);
        holeIndex = sendIndex-1;
    }
   push_heap(first,topIndex,holeIndex,value);
}
void popHeap(Iterator first,Iterator last)
{
    int value = *(last-1);
    *(last-1) = *(first);
    adjustHeap(first,0,last-first-1,value);
}
void makeHeap(Iterator first,Iterator last)
{
    int len =  last - first;
    if(len < 2)
    return;
    int parent = (len-2)/2;
    while(true)
    {
        adjustHeap(first,parent,len,*(first+parent));
        if(parent == 0)
        {
            return;
        }
        parent--;
    }
    
}
int main()
{
    vector<int> ve{0,1,2,3,4,5,6,7,8,9};
    //makeHeap<vector<int>::iterator>(ve.begin(),ve.end());
    makeHeap(ve.begin(),ve.end());
    cout<<ve[0]<<"\n";
    ve.push_back(10);
    pushHeap(ve.begin(),ve.end());
    cout<<ve[0]<<"\n";
    popHeap(ve.begin(),ve.end());
    cout<<ve.back()<<"\n";
}

