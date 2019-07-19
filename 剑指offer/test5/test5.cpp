#include <iostream>
#include <vector>


using namespace std;

typedef vector<int>::iterator vec_iter;
int find(const vector<int>& vec){
	vector<int>::const_iterator iter, frist, second;
	frist = vec.begin();
	second = vec.end();
	int res;
	if(*frist < *second){
		res = *frist;
	}
	else{
		while(frist!=second){
			iter = frist+(second-frist)/2;
			if(*iter > *frist ){
				frist = iter;
			}
			else if( *iter < *second ){
				second = iter;
			}
			else{              //三者相等
				vector<int>::const_iterator  next = frist;
				while(frist < iter){
					next = frist+1;
					if(*next < *frist){
						break;
					}
					++frist;
				}
				if(*next < *frist){
					res = *next;
					break;
				}
			}
		}
		if(frist == second ){
			res = *frist;
		}	
	}
	return res;
	
}

void xuanzhuan(vec_iter frist, vec_iter second, int k){
	vec_iter iter1, iter2;
	k = k %(second - frist);	
	iter1 = frist + k-1;
	iter2 = frist;
        while(iter2 < iter1){
		int temp;
		temp = *iter2;
		*iter2 = *iter1;
		*iter1 = temp;
		iter2++;
		iter1--;
	} 
	iter1 = frist+k;
	iter2 = second-1;
        while(iter2 > iter1){
		int temp;
		temp = *iter2;
		*iter2 = *iter1;
		*iter1 = temp;
		iter2--;
		iter1++;
	}
	iter1 = frist;
	iter2 = second-1;
        while(iter2 > iter1){
		int temp;
		temp = *iter2;
		*iter2 = *iter1;
		*iter1 = temp;
		iter2--;
		iter1++;
	}

}


int main( int argc, char** argv){
	vector<int> vec;
	if(argc < 3){
		cout<<"./test5 <nums>"<<endl;
		exit(0);
	}
	int i = 2;
	while(i < argc){
		vec.push_back(atoi(argv[i]));
		i++;
	}
	for(i = 0; i < vec.size(); i++ ){
		cout <<vec[i]<< " ";
	}
	cout<<endl;
	int k = atoi(argv[1]);
	if(k > vec.size() || k == vec.size() )
	 	k = vec.size()/2;
	xuanzhuan(vec.begin(), vec.end(),k);
        int rest;
	rest = find(vec);
	cout<<k<<": "<<rest<<endl;
	for(i = 0; i < vec.size(); ++i ){
		cout<<vec[i]<<" ";
	}	

}
