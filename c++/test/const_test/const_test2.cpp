//
#include <iostream>

using namespace std;

class constTestbase{
    public:
    int a;
    const int const_a;
    constTestbase():a(1),const_a(1){}
    int func1() const{
        cout<<"func1"<<endl;
        cout<<"a:"<<a<<endl;    //调用非const成员
        cout<<"const_a: "<<const_a<<endl;        //调用const成员
    }
    int func2() const{
        cout<<"func2"<<endl;
        //the object has type qualifiers that are not compatible with the member function "constTestbase::func3" -- object type is: const constTestbase
        //func3();      //error,const成员函数调用非const成员函数 
    }
    int func3(){
        cout<<"func3"<<endl;
        func1();                     //非const成员函数调用const成员函数
        cout<<"a:"<<a<<endl;         //调用非const成员
        cout<<"const_a: "<<const_a<<endl;        //调用const成员
    }
};

int main(){
    constTestbase a;
    const constTestbase b;

    a.func1();
    a.func2();
    a.func3();
    b.func1();
    b.func2();
    //b.func3();          //error,const对象调用非const成员函数
 
    constTestbase *ptr;
    const constTestbase *cptr;    
}