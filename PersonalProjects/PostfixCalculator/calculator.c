#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define SIZEMAX 100

// ______________Stack Definition and Methods______________
// Defining type struct node with char val and next pointer (nodeChar)
typedef struct node
{
    char val; // Value of the node
    struct node* next; // Pointer to next node
} nodeChar;

int isEmpty(nodeChar * head);
void push(nodeChar * head, char val);
char pop(nodeChar * head);
char peek(nodeChar * head);
void printLinkedList(nodeChar * head);

int isEmpty(nodeChar * head)
{
    nodeChar* currentNode = head;
    if (currentNode->next == NULL)
    {
        return 1;
    } else {
        return 0;
    }
}

void push(nodeChar * head, char val)
{
    // Setting pointer type node to head
    nodeChar * currentNode = head;
    // iterating through the list
    while (currentNode->next != NULL) 
    {
        currentNode = currentNode->next;
    }

    //Creating node at end of list
    currentNode->next = (nodeChar *) malloc(sizeof(nodeChar));
    currentNode->next->val = val;
    currentNode->next->next = NULL;
}

// Method to pop top of list
char pop(nodeChar * head)
{
    // Setting currentNode to head
    nodeChar * currentNode = head;
    char returnChar;
    // Iterating through nodes through to end
    if(currentNode->next != NULL) {
        while (currentNode->next->next != NULL)
        {
            currentNode = currentNode->next;
        }
        returnChar = currentNode->next->val;
        currentNode->next = NULL;
    } else {
        printf("Stack is empty\n");
    }
    // Returning value of node at end
    
    return returnChar;
}

char peek(nodeChar* head)
{
    nodeChar * currentNode = head;
    while(currentNode->next != NULL)
    {
        currentNode = currentNode->next;
    }
    return currentNode->val;
}

// Print whole linked list
void printLinkedList(nodeChar * head)
{
    nodeChar * currentNode = head;
    
    // Iterate through list and print each value
    int index = -1;
    while (currentNode != NULL)
    {
        printf("Index: %d = %c\n", index, currentNode->val);
        currentNode = currentNode->next;
        index++; 
    }
}

// ______________StackInt Definition and Methods______________

long stackLong[SIZEMAX];
int topLong = -1;

// Method to check if the stackLong is empty
int isEmptyInt()
{
    if(topLong == -1)
    {
        return 1;
    } 
    
    else 
    {
        return 0;
    }
}

// Method to check if the stackLong is full
int isFullInt()
{
    if(topLong == SIZEMAX)
    {
        return 1;
    } 
    
    else 
    {
        return 0;
    }
}

// Method to push a character to stackLong
void pushLong(long data)
{
    if(!isFullInt())
    {
        topLong++;
        stackLong[topLong] = data;
    } 
    
    else 
    {
        printf("StackInt is full\n");
    }
}

// Method to pop a character from stackLong
long popLong()
{
    long data;
    
    if(!isEmptyInt())
    {
        data = stackLong[topLong];
        topLong = topLong - 1;
        return data;
    } 
    
    else 
    {
        printf("StackInt is empty\n");
    }
}

int peekInt()
{
    return stackLong[topLong];
}

//______________Infix/Postfix Methods______________

// Method to determine if the next symbol in the infixExpression is an operand
int isOperand(char sym)
{
    // Determining if passed symbol is one of the following non-operands '(', ')', '+', '*', '/', '^'
    if(sym == '(' || sym == ')' || sym == '+' || sym == '-' || sym == '*' || sym == '/' || sym == '^')
    {
        return 0;
    } 
    else 
    {
        return 1;
    }
}

// Method to determine the precedence of the operator
int operatorPrecedence(char operator) 
{
    // Determining precedence of each operator assigned to values 3, 2, 1, and 0
    if (operator == '+' || operator == '-') 
    {
        return 1;
    } 
    else if (operator == '*' || operator == '/')
    {
        return 2;
    } 
    else if (operator == '^')
    {
        return 3;
    } 
    else 
    {
        return 0;
    }
}

// Method to convert infix to postfix expression
void infixToPostfix(char infixExpression[SIZEMAX], char postfix[SIZEMAX], nodeChar* head) {
    int i = 0;
    int j = 0;
    //Iterating infix to postfix rules across infix expression
    while (infixExpression[i] != '\0')
    {
        char infixSym = infixExpression[i];
        if(isOperand(infixSym)) // Rule 2
        {
            // Passing operand to postfixExpression
            char operand = infixSym;
            postfix[j] = operand;
            j++;
        } 
        else if (infixSym == '+' || infixSym == '-' || infixSym == '*' || infixSym == '/' || infixSym == '^') // Rule 2
        {
            // Part I: Determining precedence and popping equal or higher precedence operators from the stack   
            int precedenceInfix = operatorPrecedence(infixSym);
            if (peek(head) != '(') // Checking for left parenthesis
            {
                while(precedenceInfix <= operatorPrecedence(peek(head))) 
                {
                    char operator = pop(head);
                    postfix[j] = operator;
                    j++;
                }
            }
            // Part II: Pushing new operator to stack
            char operator = infixSym;
            push(head, operator);
        } 
        else if (infixSym == '(') // Rule 4
        {
            // Pushing left parenthesis to stack
            char leftParenthesis = infixSym;
            push(head, leftParenthesis);
        } 
        else if (infixSym == ')') // Rule 5
        {
            // Popping all symbols from stack until left parenthesis
            while(peek(head) != '(') {
                postfix[j] = pop(head);
                j++;
            }
            char discard = pop(head);
            discard = '\0';
        }
        i++;
    }

    // Flushing stack to end of postfix expression
    while(!isEmpty(head)) 
    {
        char operatorsLeft = pop(head);
        postfix[j] = operatorsLeft;
        j++;
    }
    
}

//______________Postfix Evaluator______________
long postfixEval(char postfixExpression[SIZEMAX])
{
    long finalResult;
    int i = 0;
    // Looping postfix evaluation
    while(postfixExpression[i] != '\0')
    {
        char postfixSym = postfixExpression[i];
        if (isOperand(postfixSym)) // Pushing operands to stack
        {
            char operand = postfixSym;
            pushLong(operand);
        } 
        else // Operator encountered
        {
            // Defining result, operand1, and operand2
            long result;
            long operand2 = popLong();
            long operand1 = popLong();
            operand1 = operand1 - '0';
            operand2 = operand2 - '0';

            // Evaluating operand1, operator, operand2 combination
            if (postfixSym == '^') 
            {
                result = pow(operand1, operand2);
            } 
            else if (postfixSym == '*')
            {
                result = operand1 * operand2;                
            } 
            else if (postfixSym == '/')
            {
                result = operand1 / operand2;
            } 
            else if (postfixSym == '+')
            {
                result = operand1 + operand2;
            } 
            else if (postfixSym == '-')
            {
                result = operand1 - operand2; 
            }
            // Pushing result to stack
            pushLong(result);
        }
        i++;
    }
    // Popping final result from stack
    finalResult = popLong();
    return finalResult;
}

//______________Main Method______________
int main (void)
{
    // Defining infix and postfix char arrays
    char infixExpression[SIZEMAX];
    char postfixExpression[SIZEMAX];
    long resultPostfix;

    nodeChar* head = (nodeChar *) malloc(sizeof(nodeChar));
    if (head == NULL) {
        return 1;
    }
    head->val = '\0';
    head->next = NULL;

    // Printing and scanning for infix input
    printf("Enter infix expression:\n");
    scanf("%s", infixExpression);
    infixToPostfix(infixExpression, postfixExpression, head);
    printf("Postfix expression: %s\n", postfixExpression);
    resultPostfix = postfixEval(postfixExpression);
    printf("Result = %ld\n", resultPostfix);
    
    return 0;
}