#include "sorted-list.h"
/*
 * SLInsert creates a new node object to store the new value in. The function then searches through the linked 
 * list of "list" to determine where it should be placed. The function also checks and updates the record in the sorted list.
 */
void SLInsert(struct SL *list, char *newObj, char *name){

	struct SortedList *new = (struct SortedList *) malloc(sizeof(*new)); 	
	new->w = newObj;
	new->n = NULL;
	new->nex = NULL;

	struct node *ne = (struct node *) malloc(sizeof(*ne));
	ne->fname = name;
	ne->count = 1;
	ne->next = NULL;
	if(list->l == NULL){
		new->n = ne;			//If the list is empty then the start of list will point to new.
		new->nex = list->l;
		list->l = new;
		return;
	}

	struct SortedList *fake = list->l;
	struct SortedList *prev = NULL;
	struct node *ptr = NULL;	
	while((fake != NULL) && (strcmp(newObj, fake->w) > -1)){ 	//Iterates through the linked list of tokens to determine where new should be placed.
		if(strcmp(newObj, fake->w) == 0){			//If the same value is already in the linked list then the function loops through the record 
									//nodes to search for the record corresponding to the file name in the parameter
			ptr = fake->n;
			while(ptr != NULL){				//loops through the records to search if the newObj in file "name" is in records for token
				if(strcmp(ptr->fname, name) == 0){	//if there is already a record for the token then the count for record gets incremented
					ptr->count++;
					free(newObj);
					free(ne);
					free(new);
					return;
				}
				ptr = ptr->next;
			}
			ne->next = fake->n;				//if there is no record for this token in file "name" then a new record is created
			fake->n = ne;
			free(newObj);
			free(new);
			return;
		}
		if(fake->nex == NULL){
			break;
		}
		prev = fake;
		fake = fake->nex;
	}
	new->n = ne;
	if(strcmp(newObj, fake->w) < 0){
		if(prev == NULL){			//If the item to be added is in the first node
			new->nex = list->l;
			list->l = new;
		}else{					//If the item to be added is in the middle of the list
			new->nex = fake;
			prev->nex = new;
			fake = new;
		}
	}else if((fake->nex == NULL) && (strcmp(newObj, fake->w) > 0)){	//if the item to be added is in the end of the list
		fake->nex = new;
	}
	
	return;
	
}
