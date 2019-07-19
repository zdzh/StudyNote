#include <iostream>
#include <vector>

using namespace std;

void qucikSort(vector<int>& vec);


void printVec(const vector<int>& vec){
	vector<int>::const_iterator frist,last;
	frist = vec.begin();
	last = vec.end();
	while(frist != last ){
		cout << *frist<<" ";
		++frist;
	}
	cout <<endl;
}

int main(int argc, char* argv[]){

	if(argc < 2){
		cout<<"./sort <num,num,....>"<<endl;
		exit(0);
	}
	vector<int> vec1,vec2;
	int i = 1;
	while(i < argc ){
		int temp = atoi(argv[i]);
		vec1.push_back(temp);
		vec2.push_back(temp);
		++i;
	}
	cout<<"input:"<<endl;
	printVec(vec1);
	qucikSort(vec1);
	cout<<"quickSort:"<<endl;
	printVec(vec1);
	
}

