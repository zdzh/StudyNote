#include <iostream>
#include <vector>

using namespace std;

typedef vector<int>::iterator vec_iter;


void sortQ(vec_iter frist, vec_iter second){
	int mid;
	if(second - frist < 2 ){
		return;
	}
	mid = *frist;	
	vec_iter i,j;
	i = frist;
	j = second-1;
	int temp;
	while( i < j ){
		while(i < j && *i < mid) i++;
		while(i < j && *j > mid) j--;
		
		if(i < j){
			temp = *i;
			*i = *j;
			*j = temp;
		}
	}

	temp = *i;
	*i = *j;
	*j= *i;
	
	sortQ(frist, i);
	sortQ(i+1, second);
}

void qucikSort(vector<int>& vec){
	if(vec.size() > 1){
		sortQ(vec.begin(), vec.end());
	}
}
