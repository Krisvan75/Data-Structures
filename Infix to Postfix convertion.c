#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
typedef struct Stack{
    void** array;
    int capacity;
    int tos;
    int nodeCount;
    void (*display)(void* arg);
} STACK;
void createStack(STACK** stack, int capacity, char* prompt, void
                 (*display)(void* arg));
void destroyStack(STACK* stack, char* prompt);
void push(STACK* stack, void* data);
void pop(STACK* stack, void** data);
void top(STACK* stack, void** data);
bool isEmpty(STACK* stack);
bool isFull(STACK* stack);
void printStack(STACK* stack);
void createStack(STACK** stack, int capacity, char* prompt, void
                 (*display)(void* arg)){
    printf("\nCreating a %s Stack of Size %d", prompt, capacity);
    *stack = malloc( sizeof(STACK));
    (*stack) -> array = calloc (capacity,sizeof(void*));
    (*stack) -> capacity = capacity;
    (*stack) -> tos = -1;
    (*stack) -> nodeCount= 0;
    (*stack) -> display = display;
    printf("\n%s Created Successfully\n", prompt);
    return;
}
void destroyStack(STACK* stack, char* prompt){
    int index;
    for( index = stack->nodeCount; index >=0; --index)
        free( stack-> array[index]);
    free( stack->array);
    free(stack);
    printf("\n%s Destroyed Successfully\n", prompt);
    return;
}
void push(STACK* stack, void* data) { //code to push data onto the stack
    stack-> array[ ++stack -> tos] = data;
    ++stack -> nodeCount;
    return;
}
void pop(STACK* stack, void** data){ //to remove element from the stack
    *data = stack -> array [ stack -> tos--];
    --stack -> nodeCount;
    return;
}
void top(STACK* stack, void** data) { //to retrieve the top most element from the stack.
    *data = stack -> array[ stack -> tos];
    return;
}
bool isEmpty(STACK* stack){
    return stack -> tos == -1;
}
bool isFull(STACK* stack){
    return stack -> tos == stack -> capacity - 1;
}
void printStack(STACK* stack){ //display stack elements.
    int index;
    printf("\nStack Elements are\n");
    for(index = stack -> tos; index >=0; --index)
        stack -> display(stack -> array[ index]);
    return;
}
bool isOperator(char token){
    if( token == '*' || token == '/' || token == '%' || token == '+' ||
       token == '-')
        return true;
    else
        return false;
}
int priority(char token){
    if( token == '*' || token == '/')
        return 2;
    else if(token == '+' || token == '-')
        return 1;
    return 0;
}
void displayInt(void* arg){
    printf("\n| %d |", *(int*) arg);
}
int main(void){
    STACK* charStack;
    char infix[81]={};
    char postfix[81] = {};
    char temp[2] = {};
    void* dataPtr;
    char token;
    int index = 0;
    createStack(&charStack, 81, "Character Stack", displayInt);
    printf("\n\nInfix to Postfix Conversion.........\n\n");
    printf("\nEnter an Infix Expression\n");
    scanf(" %[^\n]", infix);//reading infix expression.
    while( (token = infix[index++]) != '\0'){
        printf("\nToken = %c", token);
        if( token == ' ') //if space encountered goto next token
            continue;
        else if( token == '('){ //case 1 : if ( directly push onto the stack.
            dataPtr = malloc( sizeof(char));
            *(char*)dataPtr = token;
            push(charStack, dataPtr);
        }
        else if( token == ')'){ // case 2 : if ) the pop all elements until ( is encountered.
            pop(charStack, &dataPtr);
            while(*(char*)dataPtr != '('){
                temp[0] = *(char*)dataPtr;
                strcat(postfix, temp);
                pop(charStack, &dataPtr);
            }
        }
        else if( isOperator(token)){ // case 3 : if operator then check for priority with top token on stack. If priority is more     //push other wise pop elements from stack until priority becomes more than the top token.
            top(charStack, &dataPtr);
            while( !isEmpty(charStack) && priority(token) <=
                  priority(*(char*)dataPtr)){
                pop(charStack, &dataPtr);
                temp[0] = *(char*) dataPtr;
                strcat(postfix, temp);
                top(charStack, &dataPtr);
            }
            dataPtr = malloc( sizeof(void*));
            *(char*)dataPtr = token;
            push(charStack, dataPtr);
        }
        else{ // case 4: token is a operand directly append it to the postfix string.
            temp[0] = token;
            strcat(postfix, temp);
        }
    }
    while( !isEmpty(charStack)){
        pop(charStack, &dataPtr);
        temp[0] = *(char*)dataPtr;
        strcat(postfix, temp);
    }
    printf("\nInfix Expression : %s", infix);
    printf("\nPostfix Expression : %s", postfix);
    printf("\n\n");
    return 0;
}
