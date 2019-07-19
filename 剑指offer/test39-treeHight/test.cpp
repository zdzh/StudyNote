//求二叉树高度
#include <iostream>


using namespace std;

struct BinarryTreeNode{
    int val;
    BinarryTreeNode* left;
    BinarryTreeNode* right;
}；


int getBinarryTreeHigh(BinarryTreeNode* T){
    int high = 0;
    if( T != NULL ){
        int leftHigh,rightHigh;
        leftHigh = getBinarryTreeHigh(T->left);
        rightHigh = getBinarryTreeHigh(T->right);
        high = 1 + ( leftHigh > rightHigh ? leftHigh:rightHigh);
    }
    return high;
}