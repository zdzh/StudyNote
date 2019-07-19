#include <iostream>

class one{
	private: 
		static int test;
		one(){test++;}
		static one e;

	public:
		static one get();
		void print(){std::cout<<test<<std::endl;}
};

int one::test = 0;
int one::e;
one one::get(){

	return e;
}
int main(){
        one a = one::get();
	one b = one::get();
	a.print();
	b.print();
	
	
}
