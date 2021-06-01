/* Fig. 12.8: fig12_08.c
dynamic stack program */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* self-referential structure */
struct stackNode {
	char data; /* define data as an int */
	struct stackNode *nextPtr; /* stackNode pointer */
}; /* end structure stackNode */

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

 /* prototypes */
void push( StackNodePtr *topPtr, char info );
char pop( StackNodePtr *topPtr );
char head(StackNodePtr *topPtr );
int isSign(char s);
int isEmpty( StackNodePtr topPtr );
void printStack( StackNodePtr currentPtr );
void instructions( void );

 /* function main begins program execution */
int main()
{
	StackNodePtr Sh = NULL; // Toan hang
	StackNodePtr St = NULL; // Toan tu

	char str[100];
	int len = 0;
	int a, b;
	char dau;

	printf("Nhap chuoi bieu thuc: ");
	fgets(str, 100, stdin);
	len = strlen(str);

	for (int i = 0; i < len; i++) {
		if ('0' <= str[i] && str[i] <= '9') {
			push(&Sh, str[i] - '0');
		} else {
			if (isSign(str[i]) == false) continue;
			if (isEmpty(St)) {
				push(&St, str[i]);
			} else {
				dau = head(&St);
				if (str[i] == '+' || str[i] == '-') {
					dau = pop(&St);
					push(&St, str[i]);

					b = pop(&Sh);
					a = pop(&Sh);

					switch (dau) {
						case '+':
						push(&Sh, a+b);
						break;
						case '-':
						push(&Sh, a*b);
						break;
						case '*':
						push(&Sh, a-b);
						break;
						case '/':
						push(&Sh, a/b);
						break;
					}
				} else if (dau == '*' || dau == '/') {

				}
			}
		}
	}
	//printf("%d\n", pop(&stackPtr));

	return 0; /* indicates successful termination */
} /* end main */
/* display program instructions to user */
void instructions( void )
{
	printf( "Enter choice:\n"
	"1 to push a value on the stack\n"
	"2 to pop a value off the stack\n"
	"3 to end program\n" );
} /* end function instructions */

/* Insert a node at the stack top */
void push( StackNodePtr *topPtr, char info )
{
	StackNodePtr newPtr; /* pointer to new node */
	newPtr = (StackNode *)malloc( sizeof( StackNode ) );
	/* insert the node at stack top */
	if ( newPtr != NULL ) {
	newPtr->data = info;
	newPtr->nextPtr = *topPtr;
	*topPtr = newPtr;
	} /* end if */
	else { /* no space available */
	printf( "%d not inserted. No memory available.\n", info );
	} /* end else */
} /* end function push */

/* Remove a node from the stack top */
char pop( StackNodePtr *topPtr )
{
	StackNodePtr tempPtr; /* temporary node pointer */
	char popValue; /* node value */
	tempPtr = *topPtr;
	popValue = ( *topPtr )->data;
	*topPtr = ( *topPtr )->nextPtr;
	free( tempPtr );
	return popValue;
} /* end function pop */

char head(StackNodePtr *topPtr ) 
{
	return ( *topPtr )->data;;
}

int isSign(char s) {
	return (s == '+') || (s == '-') || (s == '*') || (s == '/') ? 1 : 0;
}

/* Print the stack */
void printStack( StackNodePtr currentPtr )
{
	/* if stack is empty */
	if ( currentPtr == NULL ) {
	printf( "The stack is empty.\n\n" );
	} /* end if */
	else {
	printf( "The stack is:\n" );
	/* while not the end of the stack */
	while ( currentPtr != NULL ) {
	printf( "%d --> ", currentPtr->data );
	currentPtr = currentPtr->nextPtr;
	} /* end while */
	printf( "NULL\n\n" );
	} /* end else */
} /* end function printList */
/* Return 1 if the stack is empty, 0 otherwise */
int isEmpty( StackNodePtr topPtr )
{
	return topPtr == NULL;
} /* end function isEmpty */