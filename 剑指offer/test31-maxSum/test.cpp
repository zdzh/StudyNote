//
#include <iostream>

using namespace std;


bool  arraySumMax(int nums[],int n, int& max){
	if( nums == NULL || n < 1 ){
		return false;
	}
	max = nums[0];
	int now = nums[0];
	int i = 1;
	while( i < n ){
		if( now > 0 ){
			now += nums[i];
		}
		else{
			now = nums[i];
		}
		max = max > now ? max:now;
		++i;
	}
	return true;
}




int main(int argc, char* argv[]){
	int nums[argc-1];
	int i = 0;
	while( i < argc -1 ){
		nums[i] = atoi(argv[i]);
		i++;
	}
	for(i = 0; i < argc -1; ++i){
		cout<<nums[i]<<" ";
	}
	cout<<endl;
	int max;
	if( arraySumMax(nums,argc-1,max) ){
		cout<<"max sum:" <<max<<endl;
	}
	else
		cout<<"error";
}
