#include <stdio.h> 
#include <stdlib.h>
#define MAX_SIZE 10

void swap(int arr[], int start, int end)
{
	int temp = arr[start];
	arr[start] = arr[end];
	arr[end] = temp;
}
void HeapAdjust(int a[],int i, int n)
{
	int s,temp = a[i];
	
	for(s = i * 2; s <= n; s *= 2)
    {
    	if(a[s] < a[s+1] && s < n)
	       s++;
	    if(temp > a[s])  
           break;
        a[i] = a[s];
        i = s;
	}
	a[i] = temp;
}

void HeapSort(int a[],int n)
{
	for(int i = n / 2; i > 0; i--)
	{
		HeapAdjust(a,i,n);
	}
	for(int i = n; i > 1; i--)
	{
		swap(a,1,i);  
		HeapAdjust(a,1,i-1);
	}
}



void SelectSort(int arr[],int n)
{
	for(int i = 0; i < n-1; i++)
	{
		int min = i;
		for(int j = i + 1; j < n; j++)
		{
			if(arr[min] > arr[j])
		        min = j;
		}
		if(i != min)
		{
			int temp = arr[i];
			arr[i] = arr[min];
	        arr[min] = temp;
		}
	} 
}  


void InsertSort(int arr[],int n)
{
	int temp,j;
	for( int i = 0; i < n - 1; i++ )
	{
		if(arr[i+1] < arr[i])
		{
			temp = arr[i+1];
			for(j = i; j >= 0 && arr[j] > temp;j-- )
		    {
	    		arr[j+1] = arr[j];
		    }			
		    arr[j+1] = temp;
		}

	}
}



void ShellSort(int arr[],int n)
{
	int gap = n,min,temp,j;
	do{
	   gap = gap / 3 + 1;
	   for(int i = 0; i < n; i++)
	   {
	   	    if(arr[i] > arr[i+gap])
	        {
	        	temp = arr[i+gap];
        		for(j = i; arr[j] > temp; j-=gap)
        		{
		        	arr[j+gap] = arr[j];
		        }
		        arr[j+gap] = temp;
        	}
   	   }	
		
	}while(gap > 1);
}

//QuickSort
int patition(int* arr,int low, int high)
{
	 int pivot = arr[low];
	 while(low < high)
	 {
 		while(low < high && arr[high] >= pivot)
            high--;
        arr[low] = arr[high];
        while(low < high && arr[low] <= pivot)
            low++;
        arr[high] = arr[low];
 	 }
 	 arr[low] = pivot;
 	 return low;
}

void QuickSorting(int *arr, int low, int high)
{
	int pivot;
	if(low < high)
	{
		pivot = patition(arr,low,high);
	    QuickSorting(arr,low,pivot-1);
        QuickSorting(arr,pivot+1,high);
	}
}

void QuickSort(int arr[], int low, int high)
{
	QuickSorting(arr,low,high);
}
//End of QuickSort


//Merge
void Merge(int *arr1,int end1,int *arr2,int end2)  //µÝ¹é°æ 
{
	int i = 0,j = 0,temp[MAX_SIZE],k=0;
	while(i < end1 && j < end2)
	{
		if(arr1[i] > arr2[j])
		{
			temp[k++] = arr2[j++];
		}
		else
		{
			temp[k++] = arr1[i++];
		}
	}
	while(i < end1)
	{
		temp[k++] = arr1[i++];
	}
	while(j < end2)
	{
		temp[k++] = arr2[j++];
	}
	for(int m = 0; m < (end1+end2); m++)
	{
		arr1[m] = temp[m];
	}
}

void MergeSort(int *arr,int n)
{
	if(n > 1)
	{
	    int *arr1 = arr,*arr2,end1,end2;
	    end1 = n/2;
     	arr2 = arr1 + end1;
        end2 = n - end1;
        MergeSort(arr1,end1);
        MergeSort(arr2,end2);
        Merge(arr1,end1,arr2,end2);
	}
}


void MergeSort2(int *k,int n)
{
	int i,left_min,left_max,right_min,right_max,next;
	int *temp = (int *)malloc(sizeof(int) * MAX_SIZE);
	for(i = 1; i < n; i *= 2)
	{
		for(left_min = 0;left_min < n - i;left_min = right_max)
		{
			right_min = left_max = left_min + i;
			right_max = left_max + i;
			if(right_max > n)
			{
				right_max = n;
			}
			next = 0;
			while(left_min < left_max && right_min < right_max)
			{
				if(k[left_min] < k[right_min])
				{
					temp[next++] = k[left_min++];
				}
				else
				{
					temp[next++] = k[right_min++];
				}
			}
			while(left_min < left_max)
			{
				k[--right_min] = k[--left_max];
			}
			while(next > 0)
                k[--right_min] = temp[--next];
		}
	}
}




int main(int argc, char *argv[])
{
	int arr[MAX_SIZE] = { 1,5,7,8,12,2,9,13,4,90};
	
	       

//    SelectSort(arr,10);
//	printf("start SelectSorting: ");
//	for(int i = 0; i < 10; i++)
//	    printf("%d ",arr[i]);
//
//	 
//
//	HeapSort(arr,10);    
//   	printf("start HeapSorting: ");
//	for(int i = 0; i < 10; i++)
//	    printf("%d ",arr[i]);
//		
//	InsertSort(arr,10);
//   	printf("start InsertSorting: ");
//	for(int i = 0; i < 10; i++)
//	    printf("%d ",arr[i]);	
//	 
//    ShellSort(arr,10);
//  	printf("start ShellSorting: ");
//	for(int i = 0; i < 10; i++)
//	    printf("%d ",arr[i]);
	    
//    QuickSort(arr,0,9);
//  	printf("start QuickSorting: ");
//	for(int i = 0; i < 10; i++)
//	    printf("%d ",arr[i]);	


    MergeSort2(arr,10);
  	printf("start MergeSorting: ");
	for(int i = 0; i < 10; i++)
	    printf("%d ",arr[i]);		
		    
	printf("\n\n");              
	return 0;      
}
