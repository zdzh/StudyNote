//合并递增链表
#include <iostream>

using namespace std;

struct ListNode{
	int data;
	ListNode* next;	
	ListNode(int value = 0):data(value), next(NULL){}
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

ListNode* MergeList(ListNode* L1, ListNode* L2){
	ListNode* head;
	if( L1 == NULL ){
		return L2;
	}
	if( L2 == NULL ){
		return L1;
	}
	if( L1->data < L2->data ){
		head = L1;
		L1 = L1->next;
	}
	else{
		head = L2;
		L2 = L2->next;
	}
	ListNode* node;
	node = head;
	while(L1 != NULL && L2!= NULL ){
		if(L1->data < L2->data ){
			node->next = L1;
			node = node->next;
			L1 = L1->next;
		}
		else{
			node->next = L2;
			node  = node->next;
			L2 = L2->next;
		}
	}
	while( L1 != NULL ){
		node->next  = L1;
		node = node->next;
		L1 = L1->next;
	}
	while( L2 != NULL ){
		node->next  = L2;
		node = node->next;
		L2 = L2->next;
	}
	return head;
}


ListNode* GetNewList(){
	ListNode* list= NULL, *node = NULL;
	cout<< "input list"<<endl;
  	cin.clear();

	int temp;
	while( cin >> temp ){
		if(list == NULL){
			list = new ListNode(temp);
			node = list;
		}
		else{
			node->next = new ListNode(temp);
			node = node->next;
		}
	}
	return list;
}


int main(int argc, char*argv[]){
	ListNode* l1, *l2;
	l1 = GetNewList();
	l2 = GetNewList();
	ListNode* n;
	printList(l1);
	printList(l2);
	n = MergeList(l1, l2);
	printList(n);
}
