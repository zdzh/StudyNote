//求第n个丑数
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;


long getNum(int n){
	int nums[n];
	nums[0] = 1;
	int index2,index3,index5;
	index2 = index3 = index5 = 0;
	for( int i = 0; i < n; ){
		while( nums[index2]*2 < nums[i] || nums[index2]*2 == nums[i]){
			index2++;
		}
		while( nums[index3]*3 < nums[i] || nums[index3]*3 == nums[i] ){
			index3++;
		}
		while( nums[index5]*5 < nums[i] || nums[index5]*5 == nums[i] ){
			index5++;
		}
		int min;
		min = nums[index2]*2 < nums[index3]*3 ? nums[index2]*2 :nums[index3]*3;
		min = nums[index5]*5 < min ? nums[index5]*5 : min;
		nums[++i] = min;
	}
	return nums[n-1];
}



int main(int argc, char* argv[]){
	if( argc != 2 ){
		cout<<"取得第k个丑数"<<endl;
		cout<<"./test <num>"<<endl;
		exit(0);
	}


	int num;
	num =getNum(atoi(argv[1]));
	cout<<"the NO."<<argv[1]<<"is: "<<num<<endl;
  getchar();





}
