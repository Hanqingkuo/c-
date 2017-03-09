#include<iostream>
#include<cstring>
#include<assert.h>
#include<cstdlib>
#include<string>
#include<cstdio>
#include<algorithm>
#include<ctime>
using namespace std;

const int num=100000000;
const int memory=2500000;

int read_data(FILE* fp,int *space)
{
    int local_num=0;
    while(local_num < memory && fscanf(fp,"%d ",&space[local_num]) != EOF)
    {
        ++local_num;
    }
    return local_num;
}

void write_data(FILE* fp,int* space,int size)
{
    int local_index=0;
    while(local_index < size)
    {
        fprintf(fp, "%d ", space[local_index]);
        ++local_index;
    }
}

int compare(const void *first_num, const void *second_num)
{
    return *(int *)first_num - *(int *)second_num;
}

void new_file_name(string &name,int count)
{
   // string name;
    sprintf((char*)name.c_str(),"data%d.txt",count);
    //return name;
}

int memory_sort()
{
    FILE* fp=fopen("data.txt","r");
    assert(fp!=NULL);
    int count=0;
    while(true)
    {
		int *space = new int[memory];
		assert(space);
        int num=read_data(fp,space);
        if(num==0)
        {
            break;
        }
        qsort(space, num, sizeof(int), compare);
        string file_name;
		new_file_name(file_name,++count);
		cout<<file_name<<"\n";
        FILE* fp1=fopen((const char*)file_name.c_str(),"w");
        assert(fp1!=NULL);
        write_data(fp1,space,num);
        fclose(fp1);
        delete []space;
    }
    fclose(fp);
    return count;
}
void merge_sort(int file_num)
{
    assert(file_num>0);
    FILE* fp2=fopen("resule.txt","w");
    assert(fp2!=NULL);
    FILE** fp3=new FILE*[file_num];
    for (int i = 0; i < file_num; ++i)
    {
        string file_name;
		new_file_name(file_name,i+1);
        fp3[i]=fopen(file_name.c_str(),"r");
        assert(fp3[i]!=NULL);
    }
    int *fssek=new int[file_num];
    bool* finish=new bool[file_num];
    memset(finish,false,sizeof(bool)*file_num);
    for(int i=0;i<file_num;i++)
    {
        fscanf(fp3[i], "%d ", &fssek[i]);
    }
    while(true)
    {
        int index=0;
        while(index<file_num && finish[index])
        {
            ++index;
        }
        if(index>=file_num)
            break;
        int min_data=fssek[index];
        for(int i=index+1;i<file_num;i++)
        {
			if(finish[i] == true)
			{
				continue;
			}
            if(min_data > fssek[i])
            {
                min_data=fssek[i];
				index = i;
            }
        }
        fprintf(fp2, "%d ",min_data);
        if(fscanf(fp3[index],"%d ",&fssek[index])==EOF)
        {
            finish[index]=true;
        }
    }
    fclose(fp2);
    delete []fssek;
    delete []finish;
    for(int i=0;i<file_num;i++)
    {
        fclose(fp3[i]);
    }
    delete []fp3;
}
int main(int argc, char *argv[])
{
    clock_t start_memory_sort = clock();
    int file_number= memory_sort();
    clock_t end_memory_sort = clock();
    cout << "The time needs in memory sort: " << end_memory_sort - start_memory_sort <<" ms"<< endl;
    clock_t start_memger_sort=clock();
    merge_sort(file_number);
    clock_t end_meger_sort=clock();
    cout<<"the merge sort total time:  "<<end_meger_sort-start_memger_sort<<" ms"<<endl;
    return 0;
}
