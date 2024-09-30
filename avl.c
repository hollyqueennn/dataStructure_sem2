#include <stdio.h>
#include <stdlib.h>

//untuk struct node
struct Node{
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

//mencari nilai max
int max(int a, int b){
    return(a > b) ? a : b;
}

//menghitung tinggi dari node
int height(struct Node* N){
    if(N == NULL)
        return 0;
    return N->height;
}

//membuat node baru
struct Node* newNode(int key){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

//rotasi kanan
struct Node* rightRotate(struct Node* y){
    struct Node* x = y->left;
    struct Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

//rotasi kiri
struct Node* leftRotate(struct Node* x){
    struct Node* y = x->right;
    struct Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

//untuk membuat node seimbang
int getBalance(struct Node* N){
    if(N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

//insert node baru
struct Node* insertNode(struct Node* node, int key){
    if(node == NULL) 
        return (newNode(key));
    if(key < node->key) 
        node->left = insertNode(node->left, key);
    else if(key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;
    
    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if(balance > 1 && key < node->left->key)
        return rightRotate(node);
    if(balance < -1 && key > node->right->key)
        return leftRotate(node);
    if(balance > 1 && key > node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if(balance < -1 && key < node->right->key){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}

//mencari nilai min node
struct Node* minValueNode(struct Node* node){
    struct Node* current = node;

    while(current->left != NULL)
        current = current->left;

    return current;
}

// mencari nilai max node
struct Node* maxValueNode(struct Node* node){
    struct Node* current = node;

    while(current->right != NULL)
        current = current->right;
        
	return current;
}

//print transversal preorder
void printPreOrder(struct Node* root){
	if(root != NULL){
		printf("%d ", root->key);
		printPreOrder(root->left);
		printPreOrder(root->right);
	}
}

//print transversal inorder
void printInOrder(struct Node* root){
	if(root != NULL){
		printInOrder(root->left);
		printf("%d ", root->key);
		printInOrder(root->right);
	}
}

//print transversal postorder
void printPostOrder(struct Node* root){
	if(root != NULL){
		printPostOrder(root->left);
		printPostOrder(root->right);
		printf("%d ", root->key);
	}
}

//mencari nilai node
struct Node* searchNode(struct Node* root, int key){
	if(root == NULL || root->key == key)
		return root;
		
	if(key < root->key)
   		return searchNode(root->left, key);
   		
	else
    	return searchNode(root->right, key);
}

//menghapus node
struct Node* deleteNode(struct Node* root, int key){
	if(root == NULL)
		return root;
		
	if(key < root->key)
    	root->left = deleteNode(root->left, key);

	else if(key > root->key)
    	root->right = deleteNode(root->right, key);

	else{
    	if((root->left == NULL) || (root->right == NULL)){
        	struct Node* temp = root->left ? root->left : root->right;

        if(temp == NULL){
            temp = root;
            root = NULL;
        } 
		else
            *root = *temp;
        	free(temp);
		} 
		else{
        	struct Node* temp = minValueNode(root->right);
				root->key = temp->key;
        		root->right = deleteNode(root->right, temp->key);
    	}
	}
	if(root == NULL)
    	return root;

		root->height = 1 + max(height(root->left), height(root->right));

int balance = getBalance(root);

//ada 4 kasus saat penghapusan node
//kasus LL
	if(balance > 1 && getBalance(root->left) >= 0)
	    return rightRotate(root);
//kasus LR
	if(balance > 1 && getBalance(root->left) < 0){
    	root->left = leftRotate(root->left);
    	
    return rightRotate(root);
    }
//kasus RR
	if(balance < -1 && getBalance(root->right) <= 0)
   		return leftRotate(root);

//kasus RL
	if(balance < -1 && getBalance(root->right) > 0){
    	root->right = rightRotate(root->right);
    	
    return leftRotate(root);
    }
	return root;
}

int main(){
    struct Node* root = NULL;
    int choice;
    int value;
    
    while (choice != 4){
        printf("1. Insertion\n");
        printf("2. Deletion\n");
        printf("3. Traversal\n");
        printf("4. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                printf("Insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                break;
            case 2:
                printf("Delete: ");
                scanf("%d", &value);
                struct Node* deletedNode = searchNode(root, value);
                if (deletedNode == NULL){
                    printf("Data not found\n");
                } else{
                    printf("Data found\n");
                    root = deleteNode(root, value);
                    printf("Value %d was deleted\n", value);
                }
                break;
            case 3:
                printf("Preorder: ");
                printPreOrder(root);
                printf("\n");
                printf("Inorder: ");
                printInOrder(root);
                printf("\n");
                printf("Postorder: ");
                printPostOrder(root);
                printf("\n\n");
                break;
            case 4:
                printf("Thank you\n\n");
                break;
            default:
                printf("Invalid choice\n\n");
                break;
        }
        printf ("\n");
    }

    return 0;
}
