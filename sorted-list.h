#ifndef SORTED_LIST_H
#define SORTED_LIST_H
/*
 * sorted-list.h
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//-=-=-=-You must implement all the functions and definitions below-=-=-=-

//=====0: SortedList=====================================
//===0.1: List Definition, List Create/Destroy

/*
 * Structure that holds the record with file name and frequency of occurrence of token in the form of a linked list.
 */
struct node
{
	char *fname;
	int count;
	struct node *next;
};
/*
 * Structure that holds the name of the token, and the record of the token in a form of linked list.
 */
struct SortedList	
{
	char *w;
	struct node *n;
	struct SortedList *nex;
};

struct SL
{
	struct SortedList *l;
};



/*
 * SLInsert inserts a given data item 'newObj' into a SortedList while maintaining the
 *   order and uniqueness of list items.
 */

void SLInsert(struct SL *list, char *newObj, char *fname);

#endif
