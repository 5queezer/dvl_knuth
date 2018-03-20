/*****************************************************************************/
/*                      Doppelt verkettete Liste                             */
/*                      Christian Pojoni 29.05.2015                          */
/*****************************************************************************/

#pragma warning(disable:4996)		
#include <stdio.h>  // printf
#include <stdlib.h> // system
#include <string.h>

typedef struct node {
	char data[20];
	struct node *prev, *next;
}Node;

typedef Node* Nodeptr;
Nodeptr list_search(Nodeptr, char []);
void list_insert_after(Nodeptr, char[]);
void list_insert(Nodeptr, char []);
void list_delete(Nodeptr);
void get_input(char *, char*);
void print_list(Nodeptr);
void cleanup(Nodeptr);

int main(int argc, char **argv){
	Node sentinel; // Wächterknoten
	Nodeptr result;
	char op;
	char txtBuf[20];
	sentinel.next = sentinel.prev = &sentinel;
	sentinel.data[0] = '\0';

	do
	{
		system("cls");
		printf("(a) Einfuegen\n");
		printf("(b) Suchen\n");
		printf("(c) Loeschen\n");
		printf("(d) Anzeige\n");
		printf("(e) Beenden\n");
		scanf("%c", &op); fflush(stdin);
		switch (op)
		{
		case 'a':
			get_input("Neuen Begriff eingeben: ", txtBuf);
			list_insert(&sentinel, txtBuf);
			system("pause");
			break;
		case 'b':
			get_input("Suchbegriff eingeben: ", txtBuf);
			result = list_search(&sentinel, txtBuf);
			if (result != &sentinel)
				printf("Begriff gefunden.\n");
			else
				printf("Begriff nicht gefunden.\n");
			system("pause");
			break;
		case 'c':
			get_input("Den zu loeschenden Knoten eingeben: ", txtBuf);
			result = list_search(&sentinel, txtBuf);
			if (result != &sentinel)
			{
				list_delete(result);
				printf("Knoten geloescht.\n");
			}
			else
			{
				printf("Begriff nicht gefunden.\n");
			}
			system("pause");
			break;
		case 'd':
			print_list(&sentinel);
			system("pause");
			break;
		}
	} while (op != 'e');
	cleanup(&sentinel);
	system("pause");
	return EXIT_SUCCESS;
}

Nodeptr list_search(Nodeptr sentinel, char key[])
{
	Nodeptr x = sentinel->next;
	while (x != sentinel && strcmp(x->data, key) != 0)
	{
		x = x->next;
	}
	return x;
}

void list_insert_after(Nodeptr prev_node, char key[])
{
	Nodeptr x = (Nodeptr)malloc(sizeof(Node));
	if (!x) 
	{
		fprintf(stderr, "Speicherzugriffsfehler\n");
		exit(EXIT_FAILURE);
	}
	strcpy(x->data, key);
	x->next = prev_node->next;
	prev_node->next->prev = x;
	prev_node->next = x;
	x->prev = prev_node;
}

void list_insert(Nodeptr sentinel, char key[])
{
	Nodeptr x;
	for (x = sentinel; x->next != sentinel && strcmp(x->next->data, key) < 0; x = x->next);
	list_insert_after(x, key);
}

void list_delete(Nodeptr x)
{
	x->prev->next = x->next;
	x->next->prev = x->prev;
}

void get_input(char *message, char *dest)
{
	printf("%s\n", message);
	fgets(dest, 20, stdin);
	fflush(stdin);
	dest[strlen(dest) - 1] = '\0'; 
}

void print_list(Nodeptr sentinel)
{
	Nodeptr x;
	int i = 0;
	for (x = sentinel->next; x != sentinel; x = x->next)
		printf("% 2d. %s\n", ++i, x->data);
}

void cleanup(Nodeptr sentinel)
{
	Nodeptr x = sentinel->next;
	Nodeptr temp;
	int i = 0;
	while (x != sentinel)
	{
		temp = x->next;
		printf("% 2d. Knoten \"%s\" an der Adresse %X loeschen...\n", ++i, x->data, &x);
		free(x);
		x = temp;
	}
}