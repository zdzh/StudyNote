#ifndef CQUEUE_H
#define CQUEUE_H
#include <stack>
template<class T> class CQueue{
	private:
		std::stack<T> stack1;
		std::stack<T> stack2;
		int length;
	public:
		CQueue(void);
		~CQueue(void);
		void appendTail(const T& node);
		T deletHead();
		int size();
};

#endif
