#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>

using namespace std;
//冒泡排序
#if 0
void swap(int *a,int *b)
{
    int tmp = *a;
    *a = *b;
    *b =  tmp;
}
void BubbleSort(int *arr,int n)
{
    if(arr == NULL || n <= 1)
    {
        return;
    }
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n-i-1; ++j)
        {
            if(arr[j] > arr[j+1])
            {
                swap(arr+j,arr+j+1);
            }
        }
    }
}

#endif

//选择排序
#if 0
void swap(int *a,int *b)
{
    int tmp = *a;
    *a = *b;
    *b =  tmp;
}

void SelectSort(int *arr, int n)
{
    if(arr == NULL || n <= 1)
        return;
    for(int i = 0; i < n-1; ++i)
    {
        int index = i;
        for(int j = i+1; j < n; ++j)
        {
            if(arr[index] > arr[j])
            {
                index = j;
            }
        }
        if(i != index)
        {
            swap(arr+i,arr+index);
        }
    }
}
#endif

//插入排序

#if 0
void InsertSort(int *arr,int n)
{
    if(arr == NULL || n <= 1)
        return ;
    for(int i = 1; i < n; ++i)
    {
        int target = arr[i];
        int j = i;
        while(j > 0 && arr[j-1] > target)
        {
            arr[j] = arr[j-1];
            --j;
        }
        arr[j] = target;
    }
}
#endif

//快速排序 O(nlgn)
#if 0 
void swap(int *a,int *b)
{
    int tmp = *a;
    *a = *b;
    *b =  tmp;
}
/*
int partition(int *arr,int beg,int end)
{
    int small = beg-1;
    for(int index = beg; index < end; ++index)
    {
        if(arr[index] < arr[end])
        {
            ++small;
            if(index != small)
            {
                swap(arr+small,arr+index);
            }
        }
    }
    ++small;
    swap(arr+small,arr+end);
    return small;
}
*/
int partition(int *arr,int beg,int end)
{
    int tmp = arr[beg];
    while(beg < end)
    {
        while(beg < end && arr[end] >= tmp)
        {
            --end;
        }
        arr[beg] = arr[end];
        while(beg < end && arr[beg] <= tmp)
        {
            ++beg;
        }
        arr[end] = arr[beg];
    }
    arr[beg] = tmp;
    return beg;
}
void QuckSort(int *arr,int beg,int end)
{
    int mid = partition(arr,beg,end);
    if(mid > beg)
        QuckSort(arr,beg,mid-1);
    if(mid < end)
        QuckSort(arr,mid+1,end);
}
#endif


#if 0
//归并排序
 void merge(int *arr,int left,int mid,int right)
 {
     int *tmp = (int*)malloc(sizeof(int)*(right-left+1));
     int beg = left;
     int end = mid+1;
     int k = 0;
     while(beg <= mid && end <= right)
     {
        if(arr[beg] < arr[end])
         {
            tmp[k++] = arr[beg++];
         }
         else
         {
             tmp[k++] = arr[end++];
         }
     }
     while(beg <= mid)
     {
         tmp[k++] = arr[beg++];
     }
     while(end <= right)
     {
         tmp[k++] = arr[end++];
     }
     for(int i = 0; i < k; ++i)
     {
        arr[left+i] = tmp[i];
     }
 }
void mSort(int *arr,int left,int right)
{
    if(left >= right)
        return;
    int mid = (left+right)/2;
    mSort(arr,left,mid);
    mSort(arr,mid+1,right);
    merge(arr,left,mid,right);
}
void MergeSort(int* arr,int len)
{
    if(arr == NULL && len <= 1)
        return;
    mSort(arr,0,len-1);
}
#endif

//堆排序
#if 0 
void swap(int *a,int *b)
{
    int tmp = *a;
    *a = *b;
    *b =  tmp;
}
 void createMaxHeap(int *arr,int point,int len)
 {
     if(arr == NULL)  return;
     while((2*point+1) < len)
     {
        int mpoint = 2*point+1;
         if(mpoint + 1 < len)
         {
             if(arr[mpoint] < arr[mpoint+1])
             {
                 mpoint += 1;
             }
         }
         if(arr[point] < arr[mpoint])
         {
             swap(arr+point,arr+mpoint);
             point = mpoint;
         }
         else
         {
             break;
         }
     }
 }
mZvoid heapSort(int *arr,int len)
{
    if(arr == NULL)
    {
        return ;
    }
    for(int i = len/2-1; i >= 0; i--)
    {
        createMaxHeap(arr,i,len);
    }
    for(int i = len -1; i > 0; i--)
    {
        swap(arr,arr+i);
        createMaxHeap(arr,0,i);
    }

}
#endif

// 基数排序

int  getLen(int *arr,int size)
{
    if(arr == NULL)
        return -1;
    int m = 0;
    for(int i = 0; i < size; ++i)
    {
        int tmp = 0;
        int data = arr[i];
        while(data)
        {
            data /= 10;
            tmp++;
        }
        if(tmp > m)
        {
            m = tmp;
        }
    }

    return m;
}

int main()
{
    queue<int> queArr[10];
    int arr[] = {126,127,120,34,26,7,9};
    int size = sizeof(arr)/sizeof(arr[0]);
    int max = getLen(arr,size);
    int mod = 0;
    for(int i = 0; i < max; ++i)
    {
        int k = 0;
        if(i == 0)
        {
            mod = 1;
        }
        else
        {
            mod *= 10;
        }
        for(int j = 0; j < size; ++j)
        {
            int n = arr[j]/mod - ((arr[j]/(mod*10))*10);
            queArr[n].push(arr[j]);
        }
        for(int j = 0; j < 10; ++j)
        {
            while(!queArr[j].empty())
            {
                arr[k++] = queArr[j].front();
                queArr[j].pop();
            }
        }
    }
    for(int i = 0; i < size; ++i)
    {
        cout<<arr[i]<<" ";
    }
    cout<<"\n";
    return 0;

}








