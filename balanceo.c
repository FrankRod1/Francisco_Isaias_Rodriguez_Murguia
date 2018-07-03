#include<stdio.h>
#include<stdlib.h>
#define bool int


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
bool symbolMatch(char character1, char character2){
   if (character1 == '(' && character2 == ')')
     return 1;
   else if (character1 == '{' && character2 == '}')
     return 1;
   else if (character1 == '[' && character2 == ']')
     return 1;
   else
     return 0;
}

bool BalancedBrackets(char exp[])
{
   int i = 0;
   struct strNode *stack = NULL;
   while (exp[i]){
      if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[')
        push(&stack, exp[i]);
      if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']'){
         if (stack == NULL){
           return 0;
      }
         else if ( !symbolMatch(pop(&stack), exp[i]) ){
           return 0;
         }
      }
      i++;
   }
   if (stack == NULL){
        return 1;
   }
   else{
     return 0;
   }
}

int main(){
  char exp[500];
  scanf("%s", &exp);
  if (BalancedBrackets(exp)){
    printf("La ecuacion esta balanceada \n");
  }
  else{
    printf("La ecuacion no esta balanceada \n");
  }
  return 0;
}
