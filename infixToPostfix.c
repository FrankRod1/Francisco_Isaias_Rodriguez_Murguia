#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct strStack{
    int top;
    unsigned capacity;
    int* array;
}Stack;


struct Stack* createStack( unsigned capacity ){
    struct strStack* stack = (struct strStack*) malloc(sizeof(struct strStack));

    if (!stack)
        return NULL;

    stack->top = -1;
    stack->capacity = capacity;

    stack->array = (int*) malloc(stack->capacity * sizeof(int));

    if (!stack->array)
        return NULL;
    return stack;
}
int isEmpty(struct strStack* stack){
    return stack->top == -1 ;
}
char top(struct strStack* stack){
    return stack->array[stack->top];
}
char pop(struct strStack* stack){
    if (!isEmpty(stack))
        return stack->array[stack->top--] ;
    return '$';
}
void push(struct strStack* stack, char op){
    stack->array[++stack->top] = op;
}

int isOperand(char ch){
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int hasHigherPrecedence(char ch){
    switch (ch)
    {
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
int infixToPostfix(char* exp){
    int i, k;
    struct Stack* stack = createStack(strlen(exp));
    if(!stack){
        return -1 ;
    }
    for (i = 0, k = -1; exp[i]; ++i){
        if (isOperand(exp[i])){
            exp[++k] = exp[i];
        }
        else if (exp[i] == '('){
            push(stack, exp[i]);
        }
        else if (exp[i] == ')'){
            while (!isEmpty(stack) && top(stack) != '('){
                exp[++k] = pop(stack);
            }
            if (!isEmpty(stack) && top(stack) != '('){
                return -1;
            }
            else{
                pop(stack);
            }
        }
        else{
            while (!isEmpty(stack) && hasHigherPrecedence(exp[i]) <= hasHigherPrecedence(top(stack)))
                exp[++k] = pop(stack);
            push(stack, exp[i]);
        }
    }
    while (!isEmpty(stack))
        exp[++k] = pop(stack );

    exp[++k] = '\0';
    printf( "%s", exp );
    return 0;
}

int main(){
    char exp[50];
    printf("Ingrese la expresion:\n");
    scanf("%s",exp);
    printf("La expresion posfija es:\n");
    infixToPostfix(exp);

    return 0;
}
