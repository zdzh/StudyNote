# include <iostream>

using namespace std;


int main(int argc, char* argv[]){
	if(argc != 2){
		cout<<"./test6.cpp <num>"<<endl;
		exit(0);
	}
	int num = atoi(argv[1]);
	int one = 0;
	int length;
	length = sizeof(num) * 8;
	while(length){
		one += num&0x01;
		num>>= 1;
		length--;
	}
	cout<<one<<endl;
}
