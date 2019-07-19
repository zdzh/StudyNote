#include <iostream>
#include <vector>
using namespace std;


int merge(std::vector<int>& num1,std::vector<int>& num2,vector<int>& nums){
    std::vector<int>::iterator iter1,last1;
    std::vector<int>::iterator iter2, last2;
    vector<int>::iterator nums_iter;
    int count = 0;
    iter1 = num1.begin();
    iter2 = num2.begin();
    last1 = num1.end();
    last2 = num2.end();
    nums_iter = nums.begin();

    while( iter1 < last1 && iter2 < last2 ){
      if( *iter1 > *iter2 ){
        *nums_iter = *iter1;
        ++iter1;
	++nums_iter;
        count += last2-iter2;
      }
      else{
        *nums_iter= *iter2;
        ++iter2;
	++nums_iter;
      }
    }
    while( iter1 < last1 ){
      *nums_iter = *iter1;
      ++iter1;
      ++nums_iter;
    }
    while( iter2 < last2 ){
      *nums_iter= *iter2;
      ++iter2;
      ++nums_iter;
    }
    return count;
}

int getrenum(vector<int>&nums){
  int count = 0;

  if( nums.size() > 1 ){
    vector<int>::iterator mid;
     mid = nums.begin() + nums.size()/2;
      vector<int> num1(nums.begin(),mid);
      vector<int> num2(mid, nums.end());

      count += getrenum(num1);
      count += getrenum(num2);
      count += merge(num1,num2,nums);
   }
   return count;
}


int main(int argc, char* argv[]){
	if( argc < 2 ){
		cout<<"求数组中的逆序对"<<endl;
		cout<<"./test <num1><nums2>……"<<endl;
		exit(0);
	}
  vector<int>nums;
  for(int i = 1; i < argc; ++i ){
      nums.push_back(atoi(argv[i]));
  }
 
  for(int i = 0; i < argc-1; ++i ){
  	cout<<nums[i];
  }

  cout<<endl; int count;
  count = getrenum(nums);
  cout<<count<<endl;

  for(int i = 0; i < argc-1; ++i ){
  	cout<<nums[i];
  }
  cout<<endl;
 




}
