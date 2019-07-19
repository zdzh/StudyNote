#include <iostream>
#include "CQueue.h"

using namespace std;

template<class T> CQueue<T>::CQueue():length(0){

}


template<class T> CQueue<T>::~CQueue(){

}

template<class T> void sendStack( stack<T>& stack1, stack<T>& stack2 ){
	while(stack1.size() > 0 ){
		T a;
		a = stack1.top(); 
		stack1.pop();
		stack2.push(a);
	}
}

template<class T> void CQueue<T>::appendTail(const T& node){	
	stack1.push(node);
	length = stack1.size();
}



template<class T> T CQueue<T>::deletHead(){
	T a;
	if( stack2.size() == 0){
		sendStack(stack1,stack2);
	}
	if( stack2.size() > 0 ){
		a = stack2.top();
		stack2.pop();
		length = stack2.size();
	}
	return a;
}

template<class T> int CQueue<T>::size(){
	return length;
}

int main(){
	CQueue<int> que;
	int i = 0;
	while( i < 10 ){
		que.appendTail(i);
		i++;
	}
	while(que.size()){
		cout<< que.deletHead() << " ";
	}
}


