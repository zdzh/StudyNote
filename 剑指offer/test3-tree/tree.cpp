#include<iostream>
#include "doubletree.h"

using namespace std;


MyTree::MyTree(){
	

}

MyTree::Mytree(tree* other=NULL){
	if(other == NULL){
		root = NULL;
	}
	else{
		root = cpyTree(other);
	}
}

tree* MyTree::cpyTree(tree* old_tree){
	tree* new_tree= NULL;
	if(second != NULL){
		new_tree = new tree;
		new_tree->data = old_tree.data;
		new_tree->left = cpyTree(old.left);
		new_tree->right = cpyTree(old.right);
	}
	return new_tree;
}



