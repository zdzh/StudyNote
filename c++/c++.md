# c++

## const

### 指针与const

- 指向const对象的指针必须具有const特性，即

```c++
const int i;
int *ptr = &i;			//error
const int *cptr = &i;			//ok
```

- 允许将非const对象赋值给const指针

```c++
int val;
const int *cptr = &val;    //ok
```

### const成员函数

- const对象、指向const对象的指针或引用只能调用其const成员函数，不能调用非const成员函数  *(L38)*
- const成员函数可以被对应的具有相同形参列表的非const成员函数重载
- const成员函数可以访问非const对象的非const数据成员，const数据成员，也可以访问const对象内的所有数据成员；
- 非const成员函数只可以访问非const对象的任意的数据成员（不能访问const对象的任意数据成员）

```c++
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
```



## 面向对象编程
### 继承
#### 访问控制
**派生类继承基类的所有成员包括private成员，但派生类不能直接访问private成员**
```c++ 	
// 继承和访问控制
#include <iostream>

using namespace std;

class base{
	int pri_data;
	protected:
	int pro_data;
	public:
	int publi_data;
	base():pri_data(1),pro_data(2),publi_data(3){}
	int getPri_data(){ return pri_data;}
	void setPri_data(int set){pri_data = set;}
	
};

class publicitem :public base{
	public:
		void print();
};
void publicitem::print(){
//	cout<< "pri_data "<<pri_data<<endl;  //error
	cout<<"pro_data" << pro_data <<endl;
	cout<<"publi_data"<<publi_data<<endl;
	setPri_data(10);
        cout<<"getpridata"<<getPri_data()<<endl;  //ok
}


int main(){
	base a;
	publicitem b;
	b.print();
	int temp = a.getPri_data();
	cout<<"a "<<temp<<endl;
}
```
- 派生类中的成员函数不会重载基类中的成员函数

#### 构造函数、复制控制
> 构造函数和复制控制成员不能继承

### 虚函数

- 在实现多态时，当一个类被作为基类并且该基类对派生类的对象进行操作，在析构时防止只析构基类而不析构派生类的状况发生。把基类的析构函数设计为虚函数可以在基类的指针指向派生类对象时，用基类的指针删除派生类对象，避免内存泄漏。  

- 在构造函数或析构函数中调用虚函数，运行的是构造函数或析构函数自身类型定义的版本

[Q&A](#虚函数)

## Q&A

#### 虚函数

- [ ] 在什么情况下需要虚析构函数

  > **在实现多态时，当一个类被作为基类并且该基类对派生类的对象进行操作，在析构时防止只析构基类而不析构派生类的状况发生。把基类的析构函数设计为虚函数可以在基类的指针指向派生类对象时，用基类的指针删除派生类对象，避免内存泄漏。** 

- [ ] 虚函数在基类中如何记录


