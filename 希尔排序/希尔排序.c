#include <stdio.h>
#include <stdlib.h>

void shell_sort(int array[], int length)
{  int i;  
   int j; 
   int m;  
   int gap; //gap�Ƿ���Ĳ���Ҳ����������������������  
   int temp; //����ʵ��ֱ�Ӳ�������ı�����Ϊϣ����������ֱ�����������ݱ���� 
   
   for(gap=length/2; gap>0; gap=gap/2)
   {   
       //����ʵ�������ĵݼ���һ��ѭ����ʵ��ÿ������gap��һ������һ�� 
        for(i=0; i<gap; i++)
		{    
		// ��һ��ѭ����ʵ��ÿһ��������� һ��gap�Ǽ����Ǿ��м��� 
		     
		     //������Ƕ�ÿһ�������ֱ�Ӳ������� ���ǿ�����֮ǰ�Ĺ��ں������п�����ϸ�Ľ���
			  
			 for(j=i; j<length; j=j+gap)
			 {    
				         temp = array[j]; 
				         m=j-gap;
				         while(m>=0 && array[m]>temp)
						 {       
						     array[m + gap] = array[m];       
							 m = m - gap;      
						}      
						array[m + gap] = temp;    
				  
			}  
	   }  
  } 
}

int main()
{
	int m=0;
	int a[]={9,2,0,3,7,1,5,9,4,5 };
    int len = 10; 
    shell_sort(a,len);
    for(m=0;m<len;m++){
    	
    	printf("%d ",a[m]);
    }
   
}
