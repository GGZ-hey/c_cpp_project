#include <stdio.h>
#include <stdlib.h>

void shell_sort(int array[], int length)
{  int i;  
   int j; 
   int m;  
   int gap; //gap是分组的步长也就是我们上面所述的增量  
   int temp; //用于实现直接插入排序的变量因为希尔排序是在直接排序上面演变而成 
   
   for(gap=length/2; gap>0; gap=gap/2)
   {   
       //用于实现增量的递减用一个循环来实现每次排序，gap减一次排序一次 
        for(i=0; i<gap; i++)
		{    
		// 用一个循环来实现每一个组的排序 一般gap是几我们就有几组 
		     
		     //下面就是对每一个组进行直接插入排序 我们可以在之前的公众号文章中看到详细的解释
			  
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
