#include <iostream>  
#include <ctime>  
#include <fstream>  
//#include "ExternSort.h"  
using namespace std;  
  
//ʹ�ö�·�鲢�������������  
//ExternSort.h  
  
/* 
 * �������������� 
 * ��·�鲢���� 
 * ��ǧ��������С��������Ϊ�� 
 * һ���Ƚϼ򵥵����ӣ�û�н����ڴ滺���� 
 */  
  
#ifndef EXTERN_SORT_H  
#define EXTERN_SORT_H  
  
#include <cassert>  
//#define k 5  
#define MIN -1//���￪ʼ��ʱ�������һ��BUG����������MIN���ڵ��ڴ����������������㷨���ִ���
#define MAX 10000000//���ֵ�������ڹ鲢�ļ���β
typedef int* LoserTree;
typedef int* External;

class ExternSort  
{  
public:  
    void sort()  
    {  
        time_t start = time(NULL);  
          
        //���ļ����ݷֿ����ڴ������򣬲��ֱ�д����ʱ�ļ�  
        k = memory_sort();  //
          
        //�鲢��ʱ�ļ����ݵ�����ļ�  
        //merge_sort(file_count); 
        ls=new int[k];
        b=new int[k+1];
        K_Merge();
        delete []ls;
        delete []b;
          
        time_t end = time(NULL);  
        printf("total time:%f\n", (end - start) * 1000.0/ CLOCKS_PER_SEC);  
    }  
      
    //input_file:�����ļ���  
    //out_file:����ļ���  
    //count: ÿ�����ڴ����������������  
    ExternSort(const char *input_file, const char * out_file, int count)  
    {  
        m_count = count;  
        m_in_file = new char[strlen(input_file) + 1];  
        strcpy(m_in_file, input_file);  
        m_out_file = new char[strlen(out_file) + 1];  
        strcpy(m_out_file, out_file);  
    }  
    virtual ~ExternSort()  
    {  
       delete [] m_in_file;  
       delete [] m_out_file;  
    }  
      
private:  
    int m_count; //���鳤��  
    char *m_in_file;   //�����ļ���·��  
    char *m_out_file; //����ļ���·��  
    int k;//�鲢������������Ҫ������֮����ܵõ������������ls��b��ֻ�ܶ���Ϊָ��(ע�����������)
    LoserTree ls;//�����Ϊָ�룬֮��̬��������
    External b;//�����Ϊָ�룬�ڳ�Ա�����п��԰�����������ʹ��
    //int External[k];
protected:  
    int read_data(FILE* f, int a[], int n)  
    {  
        int i = 0;  
        while(i < n && (fscanf(f, "%d", &a[i]) != EOF)) i++;  
        printf("read:%d integer\n", i);  
        return i;  
    }  
    void write_data(FILE* f, int a[], int n)  
    {  
        for(int i = 0; i < n; ++i)  
            fprintf(f, "%d ", a[i]);  
        fprintf(f,"%d",MAX);//�����д��һ�����ֵ
    }  
    char* temp_filename(int index)  
    {  
        char *tempfile = new char[100];  
        sprintf(tempfile, "temp%d.txt", index);  
        return tempfile;  
    }  
    static int cmp_int(const void *a, const void *b)  
    {  
        return *(int*)a - *(int*)b;  
    }  
      
    int memory_sort()  
    {  
        FILE* fin = fopen(m_in_file, "rt");  
        int n = 0, file_count = 0;  
        int *array = new int[m_count];  
          
        //ÿ����m_count�����������ڴ�����һ�����򣬲�д����ʱ�ļ�  
        while(( n = read_data(fin, array, m_count)) > 0)  
        {  
            qsort(array, n, sizeof(int), cmp_int);     
            //��������˿⺯�������ڵ��Ľڵ�cʵ������ٵ���qsort��  
            char *fileName = temp_filename(file_count++);  
            FILE *tempFile = fopen(fileName, "w");  
            free(fileName);  
            write_data(tempFile, array, n);  
            fclose(tempFile);  
        }  
          
        delete [] array;  
        fclose(fin);  
          
        return file_count;  
    }  

    void Adjust(int s)
    {//�ش�Ҷ�ӽڵ�b[s]�����ڵ�ls[0]��·������������
        int t=(s+k)/2;//ls[t]��b[s]��˫�׽ڵ�
        while(t>0)
        {
            if(b[s]>b[ls[t]])//���ʧ�ܣ���ʧ����λ��s���£�sָ���µ�ʤ����
            {
                int tmp=s;
                s=ls[t];
                ls[t]=tmp;
            }
            t=t/2;
        }
        ls[0]=s;//ls[0]��ŵ���������ֵ��λ��
    }

    void CreateLoserTree()
    {
        b[k]=MIN;//����Ĵ洢һ����Сֵ
        for(int i=0;i<k;i++)ls[i]=k;//�ȳ�ʼ��Ϊָ����Сֵ����������ĵ���������ȷ��
                                    //�����ܱ�֤��Ҷ�ӽڵ㶼�������еġ������֡�
        for(i=k-1;i>=0;i--)
            Adjust(i);//���δ�b[k-1],b[k-2]...b[0]��������������
    }

    void K_Merge()
    {//���ð�������k������鲢�ι鲢���������
        //b��ǰk���������k��������е�ǰ��¼��Ԫ��
        //�鲢��ʱ�ļ�  
        FILE *fout = fopen(m_out_file, "wt");  
        FILE* *farray = new FILE*[k];  
        int i;  
        for(i = 0; i < k; ++i)  //������k·�����ļ�
        {  
            char* fileName = temp_filename(i);  
            farray[i] = fopen(fileName, "rt");  
            free(fileName);  
        }  
          
        for(i = 0; i < k; ++i)  //��ʼ��ȡ
        {  
            if(fscanf(farray[i], "%d", &b[i]) == EOF)//��ÿ���ļ��ĵ�һ������data����  
            {
                printf("there is no %d file to merge!"��k);
                return;
            }
        }  
    //    for(int i=0;i<k;i++)input(b[i]);

        CreateLoserTree();
        int q;
        while(b[ls[0]]!=MAX)//
        {
            q=ls[0];//q�����洢b����Сֵ��λ�ã�ͬʱҲ��Ӧһ·�ļ�
            //output(q);
            fprintf(fout,"%d ",b[q]);
            //input(b[q],q);
            fscanf(farray[q],"%d",&b[q]);
            Adjust(q);
        }
        //output(ls[0]);
        fprintf(fout,"%d ",b[ls[0]]);
        //delete [] hasNext;  
        //delete [] data;  
          
        for(i = 0; i < k; ++i)  //������
        {  
            fclose(farray[i]);  
        }  
        delete [] farray;  
        fclose(fout);  
    }
    /*
    void merge_sort(int file_count)  
    {  
        if(file_count <= 0) return;  
          
        //�鲢��ʱ�ļ�  
        FILE *fout = fopen(m_out_file, "wt");  
        FILE* *farray = new FILE*[file_count];  
        int i;  
        for(i = 0; i < file_count; ++i)  
        {  
            char* fileName = temp_filename(i);  
            farray[i] = fopen(fileName, "rt");  
            free(fileName);  
        }  
          
        int *data = new int[file_count];//�洢ÿ���ļ���ǰ��һ������  
        bool *hasNext = new bool[file_count];//����ļ��Ƿ����  
        memset(data, 0, sizeof(int) * file_count);  
        memset(hasNext, 1, sizeof(bool) * file_count);  
          
        for(i = 0; i < file_count; ++i)  //��ʼ��ȡ
        {  
            if(fscanf(farray[i], "%d", &data[i]) == EOF)//��ÿ���ļ��ĵ�һ������data����  
                hasNext[i] = false;  
        }  
          
        while(true)  //ѭ����ȡ�������ѡ����С���ķ����Ǽ򵥱���ѡ��
        {  
            //��data�п��õ���С�����֣�����¼��Ӧ�ļ�������  
            int min = data[0];  
           int j = 0;  
              
            while (j < file_count && !hasNext[j])  //˳�������Ѷ�ȡ��ϵ��ļ�
                j++;  
              
            if (j >= file_count)  //û�п�ȡ�����֣���ֹ�鲢  
                break;  
              
              
            for(i = j +1; i < file_count; ++i)  //ѡ����С��������Ӧ����i=j�ɣ��������һ���ģ�
            {  
                if(hasNext[i] && min > data[i])  
                {  
                    min = data[i];  
                    j = i;  
                }  
            }  
              
            if(fscanf(farray[j], "%d", &data[j]) == EOF) //��ȡ�ļ�����һ��Ԫ��  
                hasNext[j] = false;  
            fprintf(fout, "%d ", min);  
              
        }  
          
        delete [] hasNext;  
        delete [] data;  
          
        for(i = 0; i < file_count; ++i)  
        {  
            fclose(farray[i]);  
        }  
        delete [] farray;  
        fclose(fout);  
    }  
    */
};  
  
#endif  
  
  
//�����������ļ�  
/* 
 * ���ļ����� 
 * ���ݲ���һ����ȫ��װ���ڴ� 
 * �����ļ����ж������������֮���ÿո���� 
 */  
const unsigned int count = 10000000; // �ļ������ݵ�����  
const unsigned int number_to_sort = 100000; //���ڴ���һ�����������  
const char *unsort_file = "unsort_data.txt"; //ԭʼδ������ļ���  
const char *sort_file = "sort_data.txt"; //��������ļ���  
void init_data(unsigned int num); //������������ļ�  
  
int main(int argc, char* *argv)  
{  
    srand(time(NULL));  
    init_data(count);  
    ExternSort extSort(unsort_file, sort_file, number_to_sort);  
    extSort.sort();  
    system("pause");  
    return 0;  
}  
  
void init_data(unsigned int num)  
{  
    FILE* f = fopen(unsort_file, "wt");  
    for(int i = 0; i < num; ++i)  
        fprintf(f, "%d ", rand());  
    fclose(f);  
}  
