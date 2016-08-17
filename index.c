#include "index.h"

struct node* SortedMerge(struct node *x, struct node *y){
	struct node *ans = NULL;
 
	
	if(x == NULL){	//if x list of split record list is empty then function returns y list of split record list
		return y;
	}else if(y == NULL){	//vice versa
		return x;
	}
	if (x->count >= y->count){		//if count of record x is greater than count of record y than
		ans = x;
		ans->next = SortedMerge(x->next, y);
	}else{
		ans = y;
		ans->next = SortedMerge(x, y->next);
	}
	return ans;
}
/*
 * Splits record linked list into two different lists
 */
void Split(struct node *head, struct node **f, struct node **b){
	struct node *fast;
	struct node *slow;
	if (head == NULL || head->next==NULL){		//if the records list has less than two items then it returns the head of the input record list
		*f = head;
		*b = NULL;
	}else{						//if the records list has two or more items then it peforms the split operations
		slow = head;
		fast = head->next;
 
		while (fast != NULL){			//the fast pointer jumps two nodes ahead while the slow pointer jumps one node ahead
			fast = fast->next;
			if (fast != NULL){
				slow = slow->next;
				fast = fast->next;
			}
		}

		*f = head;					//slow is pointed at the node before the midpoint so the record list is split 
		*b = slow->next;
		slow->next = NULL;
	}
}
/*
 * Sorts record linked list through recursive call of mergeSort. 
 */
struct node* mergeSort(struct node **head){
	struct node *h = *head;
	struct node *x;
	struct node *y;
 
	
	if ((h == NULL) || (h->next == NULL)){		//if there are only 1 or no item(s) in the record linked list then the list is already sorted
		return h;
	}
 
	Split(h, &x, &y); 	//splits the record linked list into two different lists
 
	x = mergeSort(&x);			//these two calls recursively sorts the split linked list
	y = mergeSort(&y);
 
	*head = SortedMerge(x, y);	//merges the split record linked list
	return *head;
}

/*
 * The printItem function goes through the sorted list and prints the token and records associated with the token in to the file specified by FILE *i.
 * index file follows the JSON (JavaScript Object Notation).
 */
void printItem(struct SL *head, FILE *i){
	struct SortedList *tokenptr = head->l;
	struct node *recordptr;
	struct SortedList *h;
	struct node *m;
	fprintf(i,"{\"list\" : [\n");
	while(tokenptr != NULL){		//loops through all the token items
		fprintf(i,"\t{\"%s\" : [\n", tokenptr->w);
		free(tokenptr->w);
		recordptr = tokenptr->n;
		while(recordptr != NULL){	//loops through all the record items
			fprintf(i,"\t\t{\"%s\" : %d}", recordptr->fname, recordptr->count);
			m = recordptr;
			recordptr = recordptr->next;
			if(recordptr != NULL){
				fprintf(i,",\n");
			}else{
				fprintf(i,"\n");
			}
			free(m);
		}
		fprintf(i,"\t]}");
		h = tokenptr;
		tokenptr = tokenptr->nex;
		if(tokenptr!= NULL){
			fprintf(i, ",\n");
		}else{
			fprintf(i, "\n");
		}
		free(h);
	}
	fprintf(i,"]}\n");
}
/*
 * The sortFile function takes in a file, filename, and head of a sorted list. This function iterates through the file and stores the tokenized 
 * string into a sorted linked list. This function returns the head of the sorted list.
 */
struct SL *sortFile(FILE *fi, char *name, struct SL *head){
		struct T *item = (struct T*) malloc(sizeof(*item));
		char *x = (char *) malloc(1024);
		char *word;
		char *pname = (char *) malloc(sizeof(*pname));
		strcpy(pname,name);
		while(fgets(x, 1024, fi) != NULL){		//gets string from FILE fi until it reaches EOF
			item->w = x;
			while(item->w[0] != '\0'){		//iterates through string until it reaches end of string
				word = TKGetNextToken(item);	//calls tokenizer function
				if(word == NULL){		//if tokenizer function returns a null string then the function continues
					continue;
				}
				SLInsert(head, word, pname);	//once the token is obtained, it is added onto the sorted linked list.	
			}
		};
		free(x);
		free(item);					
	return head;
}
/*
 * This function takes in a directory and head of a sorted list. This function sorts each item in a directory recursively. 
 * It returns the head of the sorted list. 
 */	
struct SL *sortDir(DIR *di, char *dname, struct SL *head){

	struct dirent *d;
	DIR *x;
	FILE *p;	
	char *pname = (char *) malloc(sizeof(*pname));
	memset(pname, 0,sizeof(pname));
	while((d = readdir(di)) != NULL){	//loops through all the items in a directory	
		if(strcmp(d->d_name,".") == 0 || strcmp(d->d_name, "..") == 0){		//skips items that are name "." or ".."
			continue;
		}
		strcpy(pname,dname);	//the following three lines allow me to prepend the pathname.
		strcat(pname, "/");
		strcat(pname, d->d_name);
		if(d->d_type == DT_REG){	//if the item is a file then the file is passed onto the sortFile function
			p = fopen(d->d_name, "r");
			if(p){
				head = sortFile(p, pname, head);
				fclose(p);
			}else{
				continue;
			}
		}else if(d->d_type == DT_DIR){	//if the item is another directory then the item passed into sortDir again (recursive call).
			x = opendir(d->d_name);
			chdir(d->d_name);
			head = sortDir(x, pname, head);
			closedir(x);
			chdir("..");
		}
	};
	return head;
}
