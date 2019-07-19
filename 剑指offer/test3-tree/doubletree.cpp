
//根据前序数组和中序数组输出二叉树
#include <iostream>
#include <vector>
#include <queue>
#include "doubletree.h"

using namespace std;
typedef vector<int>::iterator vecIntIter;

vecIntIter findRoot(const vecIntIter frist, const vecIntIter second, int target){
	vecIntIter iter;
	iter = frist;
	while(iter < second ){
		if(*iter == target ){
		break;
		}
		iter++;
	}
	return iter;
}



tree* getTree(const vecIntIter head_frist,const vecIntIter head_second, 
		const vecIntIter mid_frist,const vecIntIter mid_second){
	tree* root = NULL;
	if(mid_frist == mid_second|| mid_frist > mid_second){
		return root;
	}
	root = new tree;
	root->data = *head_frist;
	vecIntIter inder;
	inder = findRoot(mid_frist, mid_second, *head_frist);
	root->left = getTree(head_frist+1,head_second,mid_frist,inder);
	vecIntIter begin;
	begin = head_frist + (inder- mid_frist)+1;
	root->right = getTree(begin, head_second,inder+1,mid_second);
	return root;
}


void printTree(tree* root){
	if(root != NULL){
   		queue<tree*> que;
		que.push(root);
		while(!que.empty() ){
			int count = que.size();
			tree* temp;
			while(count){
				temp = que.front(); 
				que.pop();
				count--;
				if( temp == NULL ){
					cout<<"* ";
				}
				else{
					cout <<temp->data<<" ";
					que.push(temp->left);
					que.push(temp->right);
				}
				
			}
			cout<<endl;
		}
	}
}



int main(){
	cout<<"input head sort of tree. "<<endl;
	vector<int> headsort;
	int in;
	while( (cin >> in)){
		headsort.push_back(in);
	}
	cin.clear();
	cin.sync();
	cin.ignore(1000,'\n');
	cout<<"input middle sort of tree." << endl;
	vector<int>midsort;
	
	while( (cin >> in)){
		midsort.push_back(in);
	}
	cout<< "1"<<endl;
	tree* root;
	root = getTree(headsort.begin(),headsort.begin(),midsort.begin(),midsort.end());
        cout<< "2"<<endl;
	printTree(root);
	cout<<"finish"<<endl;
}

