#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class CMyString{
	private:
		char* data;
	public:
		CMyString(const char* d);
		CMyString(const CMyString& other){ data = other.data;}
		~CMyString();
    		void  print(){cout<< *data<<endl;}
		CMyString& operator =(const CMyString& str);
};
CMyString(const char* d){
	data = new char[sizeof(d)/sizeof(*d)];
	strcpy(data,d);
}

CMyString& CMyString::operator =(const CMyString& str ){
	if(this != str ){
		data = str.data;
	}
	return *this;
}

int main(){
	CMyString a;
	CMyString b = a;
	b.print();
}
