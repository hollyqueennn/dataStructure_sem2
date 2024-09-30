//library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX 1001

//declare struct untuk stack
struct Stack{
	int top;
	int maxSize;
	int* array;
};

//fungsi alokasi memori menggunakan malloc
struct Stack* create(int max){
	struct Stack *stack = (struct Stack*)malloc (sizeof(struct Stack)); 
	stack->maxSize = max; 
	stack->top = -1; 
	stack->array = (int *) malloc (stack->maxSize * sizeof(int));
return stack;
}

//untuk cek stack full atau empty dan akan dilooping terus sampai selesai
int isFull(struct Stack* stack){
	if (stack->top == stack->maxSize - 1){ 
		printf("\n Tidak dapat memasukkan data");
	}
	return stack->top == stack->maxSize - 1; 
}

int isEmpty(struct Stack* stack){
	return stack->top == -1; 
}

//melakukan push
void push (struct Stack* stack, int item){
	if (isFull(stack)){ 
		return;
	}
	stack->array[++stack->top] = item; 
}

//melakukan pop
int pop(struct Stack* stack){
	if (isEmpty(stack)){ 
		return INT_MIN;
	}
	return stack->array[stack->top--]; 
}

//melihat yang paling atas
int peek(struct Stack* stack){
	if (isEmpty(stack)){ 
		return INT_MIN;
	}
	return stack->array[stack->top];  
}

//mengubah data char menjadi operand
int checkIfOperand(char ch){
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'); 
}

//mengurutkan atau menghitung data yang akan dimasukan/dibaca lebih dulu di postfix
int precedence(char ch){
	switch (ch){
		case '+':
		case '-':
			return 1; 
		case '*':
		case '/':
			return 2; 
		case '^':
			return 3; 
	}
	return -1;
}

//menghapus spasi pada string
void removeSpaces(char* str){ 
    int i, j;                                       
    for (i = 0, j = 0; str[i] != '\0'; i++){       
        if (str[i] != ' ') {                        
            str[j] = str[i];                        
            j++;                                   
        }
    }
    str[j] = '\0';     
}

//memutar string
void reverseString(char* str){ 
    int i, j;                                               
    char temp;                                             
    for (i = 0, j = strlen(str) - 1; i < j; i++, j--){     
        temp = str[i];                                     
        str[i] = str[j];                                 
        str[j] = temp;                                     
    }
}

//proses mengubah infix menjadi prefix
void convertInfixToPrefix(char* infix, char* prefix){ 
    struct Stack* stack = create(strlen(infix));          
    if (!stack){
    	return;
	}
	
    int i, j = 0;
    for (i = strlen(infix) - 1; i >= 0; i--) {               
        if (checkIfOperand(infix[i]))                            
            prefix[j++] = infix[i];                       
        else if (infix[i] == ')')                          
            push(stack, infix[i]);                      
        else if (infix[i] == '(') {                         
            while (!isEmpty(stack) && peek(stack) != ')')    
                prefix[j++] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != ')')       
                return;
            else
                pop(stack);           
        } else {                       
            while (!isEmpty(stack) && precedence(infix[i]) < precedence(peek(stack)))    
                prefix[j++] = pop(stack);
            push(stack, infix[i]);    
        }
    }
    while (!isEmpty(stack)){
    	prefix[j++] = pop(stack);
	}           
        
    prefix[j] = '\0';                  

    reverseString(prefix);             
}

//proses mengubah infix menjadi postfix
void convertInfixToPostfix(char* infix, char* postfix){ 
    int i, j;
    struct Stack* stack = create(strlen(infix));   
    if (!stack){
    	return;
	}   

    for (i = 0, j = 0; infix[i] != '\0'; i++){       
        if (checkIfOperand(infix[i])){                  
            postfix[j++] = infix[i];                 
        } else if (infix[i] == '('){               
            push(stack, infix[i]);                   
        } else if (infix[i] == ')'){                
            while (!isEmpty(stack) && peek(stack) != '('){     
                postfix[j++] = pop(stack);
            }
            if (!isEmpty(stack) && peek(stack) != '('){        
                printf("Infix expression invalid!\n");
                return;
            } else{
                pop(stack);     
            }
        } else{                
            while (!isEmpty(stack) && precedence(infix[i]) <= precedence(peek(stack))){   
                postfix[j++] = pop(stack);
            }
            push(stack, infix[i]);     
        }
    }

    while (!isEmpty(stack)){         
        postfix[j++] = pop(stack);
    }

    postfix[j] = '\0';    
}


int main(){
    
	char infixExpression[] = "A + B / C - D * E + F";
	char prefixExpression[MAX], postfixExpression[MAX];
	removeSpaces(infixExpression);
	convertInfixToPrefix(infixExpression, prefixExpression);
	convertInfixToPostfix(infixExpression, postfixExpression);
	
    //menampilkan expression A
	printf("Expression A :\n");
	printf("Infix : %s\n", infixExpression);
	printf("Prefix : %s\n", prefixExpression);
	printf("Postfix : %s\n\n", postfixExpression);
	
	char infixExpression2[] = "X + 5 * C / E + Y - Z";
	char prefixExpression2[MAX], postfixExpression2[MAX];
	removeSpaces(infixExpression2); 
	convertInfixToPrefix(infixExpression2, prefixExpression2);
	convertInfixToPostfix(infixExpression2, postfixExpression2);
	
    //menampilkan expression B
	printf("Expression B :\n");
	printf("Infix : %s\n", infixExpression2);
	printf("Prefix : %s\n", prefixExpression2);
	printf("Postfix : %s\n", postfixExpression2);
	
	return 0;
}

