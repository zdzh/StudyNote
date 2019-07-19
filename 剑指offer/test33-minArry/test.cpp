//将数组排成最小的数
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

bool minNumCmp(int a, int b){
	int m, n;
	
	m =0;
	n = 0;
	for(int temp = b; temp; temp /=10 ){
		n++;
	}
	for(int k = a; k; k/=10 ){
		m++;
	}
	if( m > n && n >  0){
		int temp;
		temp = a;
		for(int i = 0; i < n; ++i ){
		 	temp = temp / 10;	
		}
		for(int i = 0; i < m - n; ++i ){
			b *=10;
		}
		b = b+temp;
	}
	else if( m < n && m > 0){
		int temp;
		temp = b;
		for(int i = 0; i < m; ++i){
			temp /= 10;
		}
		for(int i = 0; i < n-m; ++i){
			a *= 10;
		}
		a +=temp;
	}
	return a < b;
} 


void sort( int nums[], int n){
	for(int i = 0; i < n-1; i++ ){
		int min = i;
		for( int j = i+1; j < n; j++ ){
			if( !minNumCmp(nums[min],nums[j]) ){
				min = j;
			}
		}
		int temp;
		temp  = nums[min];
		nums[min] = nums[i];
		nums[i] = temp;
	}
}



char* getMinNum(int nums[], int n, char*s){
	sort(nums, n);
	char*ptr;
	ptr = s;	
	for(int i=0; i < n; ++i){
		sprintf(ptr,"%d",nums[i]);
		ptr += strlen(ptr);
	}
	return s;
}


int main(int argc, char* argv[]){
	int nums[argc-1];
	int i = 0;
	int count = 1;
	while( i < argc -1 ){
		nums[i] = atoi(argv[i+1]);
		i++;
		count += strlen(argv[i]);
	}
	for(i = 0; i < argc -1; ++i){
		cout<<nums[i]<<" ";
	}
	cout<<endl;
	char *s;
	s = (char*)malloc(sizeof(char)*count);
	s = getMinNum(nums,argc -1,s);
	cout<<s<<endl;
	
}
