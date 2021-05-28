#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 100

struct Node {
	char name[LIMIT];
	int salary;

	Node *next;
};

typedef Node *NodePtr;

 /* prototypes */
void Insert(NodePtr* p, char _name[LIMIT], int _salary);
void ShowSalary(NodePtr p, char _name[LIMIT]);
void PrintList(NodePtr p);

int IsEmpty(NodePtr p);
void instructions(void);

int main()
{
	NodePtr m_List = NULL;
	int choice, N; /* user's choice */
	char nv_name[LIMIT];
	int nv_salary;

	instructions(); /* display the menu */
	printf( "? " );
	scanf( "%d", &choice );

 	/* loop while user does not choose 4 */
	while ( choice != 4 ) {

 		switch ( choice ) {

 			case 1:
				printf( "Enter a name:");
				scanf("%d *[^\n]", &N);
				fgets(nv_name, LIMIT, stdin);

				printf(	"Enter salary: ");
				scanf("%d", &nv_salary);

				Insert(&m_List, nv_name, nv_salary);
			break;

			case 2:
				PrintList(m_List);
			break;

			case 3:
				printf( "Enter a name: ");
				scanf("%d *[^\n]", &N);
				fgets(nv_name, LIMIT, stdin);
				ShowSalary(m_List, nv_name);
			break;

			default:
				printf( "Invalid choice.\n\n" );
				instructions();
			break;

 		} /* end switch */

 		printf( "? " );
		scanf( "%d", &choice );
	} /* end while */

 	printf( "End of run.\n" );

 	return 0; /* indicates successful termination */
} /* end main */

 /* display program instructions to user */
void instructions( void )
{
	printf( "Enter your choice:\n"
		" 1 to insert an element into the list.\n"
		" 2 to print the list.\n"
		" 3 to find people.\n" 
		" 4 to end.\n");
} /* end function instructions */

void Insert(NodePtr* p, char _name[LIMIT], int _salary)
{
	NodePtr newNode;
	NodePtr prev;
	NodePtr cur;

	newNode = (Node*)malloc(sizeof(Node));
	if ( newNode == NULL ) return; /* is space available */

	strcpy(newNode->name, _name);
	newNode->salary = _salary;
	newNode->next = NULL;

	prev = NULL;
	cur  = *p;

	 /* loop to find the correct location in the list */
	while ( cur != NULL && strcmp(cur->name, _name) < 0) {
		prev = cur; /* walk to ... */
		cur = cur->next; /* ... next node */
	} /* end while */

	 /* insert newPtr at beginning of list */
	if ( prev == NULL ) {
		newNode->next = *p;
		*p = newNode;
	} /* end if */
	else { /* insert newPtr between previousPtr and currentPtr */
		prev->next = newNode;
		newNode->next = cur;
	} /* end else */
}

void ShowSalary(NodePtr p, char _name[LIMIT])
{
	NodePtr cur = p;

	 /* loop to find the correct location in the list */
	while ( cur != NULL && strcmp(cur->name, _name) ) {
		cur = cur->next; /* ... next node */
	} /* end while */

	if (cur != NULL) {
		printf( "Name: %sSalary: %d\n\n", cur->name, cur->salary);
	} else {
		printf("Not found!\n\n");
	}
}

void PrintList(NodePtr p)
{
	/* if list is empty */
	if (IsEmpty(p)) {
		printf( "List is empty.\n\n" );
	} else {
		printf( "The list is:\n" );

		 /* while not the end of the list */
		while ( p != NULL ) {
			printf( "Name: %sSalary: %d\n\n", p->name, p->salary);
			p = p->next;
		} /* end while */
	}
}

int IsEmpty(NodePtr p)
{
	return p == NULL;
}