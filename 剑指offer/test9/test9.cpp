//反转链表
#include <iostream>

using namespace std;

struct ListNode{
	int data;
	ListNode* next;	
};


void printList(ListNode* list){
	ListNode* fp;
	fp = list;
	cout<<"list: ";
	while(fp){
		cout<<fp->data;
		fp = fp->next;
	}
	cout<<endl;

}

ListNode* reList(ListNode* list){
	if( list == NULL ){
		return NULL;
	}
	ListNode *behand, *mid, *next;
	behand = NULL;
	mid = list;
	while( mid ){
		next = mid->next;
		mid->next = behand;
		behand = mid;
		mid = next;
	}
	return behand;
}



int main(int argc, char*argv[]){
	ListNode* list = NULL;
	int k = atoi(argv[1]);
	if( 2 < argc){
		list = new ListNode;
		list->data= atoi(argv[1]);
		list->next = NULL;
	}
	int i = 2;
	ListNode* last = list;
	while( i < argc ){
		ListNode* node;
		node = new ListNode;
		last->next = node;
		node->data = atoi(argv[i]);
		node->next = NULL;
		last = node;
		i++;
	}
	ListNode* n;
	printList(list);
	n = reList(list);
	printList(n);

}
