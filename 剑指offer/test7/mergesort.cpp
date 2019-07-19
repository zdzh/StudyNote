#include <iostream>


using namespace std;


void mergeSort(vector<int>::iterator frist, vector<int>::iterator second){
	if(vec.size() > 1){
		auto iter;
		iter = frist + (second-frist)/2;
		mergeSort(frist, iter);
		mergeSort(iter+1, second);
	}	
	merge(frist, iter,iter+1, second);

}


void merge(vector<int>::iterator fristBegin, vector<int>::iterator fristEnd,
		vector<int>::iterator secondBegin, vector<int>::iterator secondEnd){
	
}
