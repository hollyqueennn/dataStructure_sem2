#include <stdio.h>
#include <stdlib.h>

//untuk struct node
struct node{
	int data;
	struct node *parent; 
	struct node *right;
	struct node *left;
};

struct node *root = NULL;

//insert bst
struct node *bst(struct node *traversal, struct node *temp){
    if(traversal == NULL){
        return temp;
    }
	
    if(temp->data < traversal->data){
	    traversal -> left = bst(traversal -> left, temp);
	    traversal -> left-> parent = traversal;
    }
    else if(temp -> data > traversal -> data){
	    traversal -> right = bst(traversal -> right, temp);
	    traversal -> right-> parent = traversal;
    }
	return traversal;
}

//rotasi kanan
void rightRotate(struct node *temp){
    struct node *left = temp -> left;
    temp -> left = left -> right;
    
    if (temp -> left){
	    temp -> left -> parent = temp;
	    left -> parent = temp -> parent;
    }		
    if (!temp -> parent){
		root = left;
    }
    else if(temp == temp -> parent -> left){
	    temp -> parent -> left = left;
    }
    else{
	    temp -> parent -> right = left;
	    left -> right = temp;
	    temp -> parent = left;
    }
}

//rotasi kiri
void leftRotate(struct node *temp){
    struct node *right = temp -> right;
    temp -> right = right -> left;

    if(temp -> right){
	    temp -> right -> parent = temp;
	    right -> parent = temp -> parent;
    }
    if(!temp->parent){
	    root = right;
    }
		
    else if(temp == temp -> parent -> left){
	    temp -> parent -> left = right;
    }
    else{
	    temp -> parent -> right = right;
	    right -> left = temp;
	    temp -> parent = right;
    }
}

//print inorder transversal
void inorder(struct node *traversal){
    if(traversal == NULL){
	    return;
    }

    inorder(traversal -> left);
    inorder(traversal -> right);
    printf("%d ", traversal -> data);
}


int main(){
    int i = 0; 
    int n = 10;
    int a[] = {41, 22, 5, 51, 48, 29, 18, 21, 45, 3};
 
    for(i = 0; i < n; i++){
        struct node *temp = (struct node*)malloc(sizeof(struct node));
        temp -> right = NULL;
        temp -> left = NULL;
        temp -> parent = NULL;
        temp -> data = a[i];
        root = bst(root, temp);
    }
    printf("Inorder Traversal of Created Tree\n");
    inorder(root);

    return 0;
}
