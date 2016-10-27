/***************************************************************/
/*P0 assignment                                                */
/*Samuel Akerman, COSI21, 2016                                 */
/*   Run it: ./AkermanSamuel                                   */
/****************************************************************/
#include <stdio.h>
#include <stdlib.h>


/* vertex, TypeVertex, allocateVertex definitions were taken from the COSI21 handouts provided on the web of the course*/
/***********************************************************************************************************************/

/*Define a vertex to be a structure with two fields. Code provided on COSI21 website*/
typedef struct vertex {
	struct vertex *next;
	int data;
} TypeVertex;

/*Define a singly-linked list to be a pointer to a vertex. Code provided on COSI21 website*/
typedef TypeVertex *TypeList;

/*Function to allocate memory for a new vertex. Code provided on COSI21 website*/
TypeVertex *allocateVertex() {
	TypeVertex *p = malloc(sizeof(struct vertex));
	if (p==NULL) {printf("Malloc failed."); exit(1);}
	return p;
}
/***********************************************************************************************************************/
/***********************************************************************************************************************/

/*this function creates a new vertex and inserts it in the appropriate position within a list*/
void InsertSorted(int i, TypeList * X) {
  int exit = 0; /*boolean variable used to signal whether the vertex was inserted to the list*/

  TypeVertex *w = allocateVertex();
  w -> data = i;

  TypeVertex *v; /* these are used to locate where to put new vertex w*/
  TypeVertex *u;

  if (*X == NULL) { /* List is empty*/

    w -> next = NULL; *X = w;

  } else { /*Place element in its proper position within the list*/
    v = *X;

    while (exit == 0) {
      u = v->next;
      if ((w->data > v->data) && (u == NULL)) { /*should w be placed at the end of the list?*/

        v->next = w;
        w->next = u;
        exit = 1;

      } else if (((w-> data > v-> data) && (w-> data <= u->data))) { /*should w be placed between v and u?*/

        v-> next = w;
        w-> next = u;
        exit = 1;

      } else if (w->data < v->data) { /*if new value is the smallest than all in the list it will enter here*/

        w-> next = v; *X = w;
        exit = 1;

      } else {
        v = v-> next; /*none of the previous options, let's move forward within the list*/
      }

    }
  }
}
/*This function prints a list in the same order it is being presented*/
void PrintList(TypeList X) {

	if (X == NULL) {
		printf("List is empty.\n");
	}
	else {

		TypeVertex *v;
		v = X;
		int out;

		do {
			out = v->data;
			printf("%d\n",out);
			v = v->next;
		} while (v != NULL);

		printf("\n");
	}
}


/*This function keeps prompting the user until 'y' or 'n' are keyed*/
char yesorno(){
	char repeat;
	printf("Do it again? (y/n)\n");
	do {
	scanf("%c", &repeat );
	if ((repeat != 'n') && (repeat != 'y'))
	{
		printf("Option not valid. Enter 'y' or 'n'\n");
	}

} while ((repeat != 'n') && (repeat != 'y'));
return repeat;

} 


int main() {

	char repeat;
	char string[100]; /*string of chars read to be converted into integers. Done this way so I can read blank lines*/
	int input;			/*input contains the integer entered by the user after transforming from char*/

	printf("\nHello!\n");
	do {
	/*defining the list pointer L within the while loop will reset it with every iteration*/	
	/*this way, lists from different user tries will not mix*/	
	TypeList L = NULL;          
	printf("INPUT LIST (one integer per line followed by an empty line):\n");
	fgets(string, 100, stdin);

	while (string[0] != '\n')   /*blank line?*/
	{
		input = atoi(string);
		InsertSorted(input,&L);
		fgets(string, 100, stdin);
	}

	printf("Sorted list:\n");
	PrintList(L);

	repeat = yesorno();
	fgets(string, 100, stdin);      /*clear stdin*/
} while (repeat == 'y');

	printf("Goodbye\n");
	return 0;
}
