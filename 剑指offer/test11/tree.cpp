//根据后序遍历判断是否为搜索树
#include <iostream>
#include <vector>
#include <queue>
#include "doubletree.h"

using std::vector;
using std::cout;
using std::endl;
using std::cin;
using std::queue;
typedef vector<int>::iterator vecIntIter;

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

bool IsFindBinaryTree(vector<int>::iterator frist, vector<int>::iterator second){
	if(second - frist < 1){
		return false;
	}
	int root = *(second -1);
	vector<int>::iterator iter1, iter2;
	iter1 = frist;
	while( iter1 < second ){
		if(*iter1 > root || *iter1 == root ){
			break;
		}
		iter1++;
	}
	iter2 = iter1;
	while(iter2 < second ){
		if( *iter2 < root ){
			return false;
		}
		++iter2;
	}
	bool status = true;
	if(iter1 > frist)
		status = IsFindBinaryTree(frist, iter1);
	if(status == false){
		return status;
	}
	if( iter1 < second - 1 ){
		status = IsFindBinaryTree(iter1, second-1);
	}
	return status;
}

int main(){
	cout<<"input sort of tree./end with @"<<endl;
	vector<int> headsort;
	int in;
	while( (cin >> in)){
		headsort.push_back(in);
	}
	bool status = false;
	status = IsFindBinaryTree(headsort.begin(), headsort.end());
	cout<< "answer:" <<status<<endl;
	cout<<"finish"<<endl;
}



