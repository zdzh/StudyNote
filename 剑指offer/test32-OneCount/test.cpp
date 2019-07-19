//1到n中1出现的个数
#include <iostream>

using namespace std;

int ArryOneCount(int num){
	int i, temp;
	i = 1;
	int count = 0;
	while( i < num || i == num ){
		int before,now,after;
		before = num /(i*10);
		after = num %i;
		now = num / i % (i * 10);
		
		if( now == 0 ){
			count += before*i;
		}
		else if( now == 1){
			count += before*i + after + 1;
		}
		else{
			count += (before+1)*i;
		}
		i  *= 10;
	}
	return count;
}


int main(int argc, char** argv){
	if(argc != 2){
		cout<<"./test <num>"<<endl;
		exit(0);
	}
	int num;
	num = atoi(argv[1]);
	int count = ArryOneCount(num);
	cout<<"count of 1:"<<count<<endl;

}

