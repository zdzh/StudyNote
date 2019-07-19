//输出倒数第k个节点
#include <iostream>

struct ListNode{
	int data;
	ListNode* next;	
};

ListNode* FindNode(ListNode* list, int k){
	ListNode* fp1=NULL, *fp2=NULL;
	if(list == NULL ||k < 1){
		return fp1;
	}
	fp2 = list;
	int i = 1;
	while(i < k && fp2!= NULL){
		fp2 = fp2->next;
		++i;
	}
	if(fp2 == NULL){
		return fp1;
	}
	fp1 = list;
	while(fp2->next!=NULL){
		fp2 = fp2->next;
		fp1 = fp1->next;
	}

	return fp1;
}



int main(int argc, char*argv[]){
	ListNode* list = NULL;
	int k = atoi(argv[1]);
	if( 2 < argc){
		list = new ListNode;
		list->data= atoi(argv[2]);
		list->next = NULL;
	}
	int i = 3;
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
	n = FindNode(list, k);
	if(n == NULL){
		std::cout<<"NULL"<<std::endl;
	}
	else
		std::cout<<n->data<<std::endl;

}
