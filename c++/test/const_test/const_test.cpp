//const全局变量与一般全局变量一样默认全局可见
#include <iostream>

using namespace std;
extern int Non_const;
extern int Const_num;
int print();

void test1(){
    print();
    cout<< "2 Not const:"<<Non_const<<endl;
    cout<< "2 Const:   "<<Const_num<<endl;
}

int main(){
    cout<<"hello word"<<endl;
    test1();
}
