//bst = binary search tree

#include <stdio.h>


typedef struct node{
    int number;
    struct node* left;
    struct node* right;
} node;

int main(void){
    //building a balance binary tree is possible but difficult. 
    //assuming the tree is built, we can implement binary search as below
}

int search(node* tree, int n){
    if (tree == NULL){
        return 0;
    }
    else if (tree->number == n){
        return 1;
    }
    else if (n < tree->number){
        return search(tree->left, n);
    }
    else{
        return search(tree->right, n);
    }
}