//求数字在数组中的次数
#include <iostream>

using namespace std;

int getNumFrist(int nums[], int l,int r, int k){
	int s;
	int frist=r;
	while(l < r ){
		s = (r-l)/2;
		if( nums[s] < k ){
			l = s+1;
		}
		else if( nums[s] > k ){
			r = s-1;
		}
		else if( s == l || nums[s-1] != k){
			frist = s;
			break;
		}
	}	
	return frist;
}

int getNumLast(int nums[], int l,int r, int k){
	int s;
	int last=l-1;
	while(l < r ){
		s = (r-l)/2;
		if( nums[s] < k ){
			l = s+1;
		}
		else if( nums[s] > k ){
			r = s-1;
		}
		else if( s == r || nums[s+1] != k){
			last = s;
			break;
		}
	}	
	return last;
}


int getNumCount(int nums[],int n, int k){
	int l, r, s;
	int frist, last;
	frist = -1;
	last = -1;
	l = 0;
	r = n;
	while(l < r ){
		s = (r-l)/2;
		if( nums[s] < k ){
			l = s+1;
		}
		else if( nums[s] > k ){
			r = s-1;
		}else{
			frist = getNumFrist(nums,l,s,k);
			last = getNumLast(nums,s,r,k);
			break;	
		}
		
		
		
	}
	return last-frist+1;
}


int main(int argc, char* argv[]){
	int nums[argc-2];
	int i = 0;
	int k;
	k = atoi(argv[1]);
	while( i < argc -2 ){
		nums[i] = atoi(argv[i+2]);
		i++;
	}
	cout<<"arry: "<<endl;
	for(i = 0; i < argc -2; ++i){
		cout<<nums[i]<<" ";
	}
	cout<<endl;
	int count;
	count = getNumCount(nums,argc-2,k);
	cout<<count<<endl;
	
	
}
