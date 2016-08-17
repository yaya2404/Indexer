#include "index.h"
int main(int argc, char **argv) {

	DIR *d;
	if(argv[2] == NULL || argv[1] == NULL){
		printf("Error: Empty inputs\n");
		return 1;
	}
	d = opendir(argv[2]);
	FILE *index, *fd;
	index = fopen(argv[1], "r");		//checks if index file already exists
	
	char *yn = (char *) malloc(sizeof(*yn));
	char *dfile = (char *) malloc(sizeof(*dfile));
	dfile = argv[2];	
	if(index){		//if index exists then user is asked whether or not to rewrite file	
		printf("This index already exists. Would you like to rewrite this index?\n");
		printf("y for yes.\nn for no.\n");
		scanf("%s", yn);
		if(yn[0] == 121 || yn[0] == 89){		//if input is yes then index file is written over
			index = fopen(argv[1], "w");
		}else if(yn[0] == 78 || yn[0] == 110){		//if input is no then index file is appended
			index = fopen(argv[1], "a");
		}else{						//if input is not yes or no then program exits
			printf("Error: invalid input\n");
			fclose(index);
			return 1;
		}
		
	}else{			//if index does not exist then new index is created
		index = fopen(argv[1], "w");
	}

	struct SL *head = (struct SL*) malloc(sizeof(*head));
	if(d){
		chdir(dfile);	
		sortDir(d, dfile,head);
		chdir("..");
		closedir(d);
	}else{	
		fd = fopen(dfile, "r");
		if(!fd){			
			printf("Error: directory or file does not exist\n");
			fclose(index);
			return 1;
		}else{
			head = sortFile(fd, dfile, head);
		}
		fclose(fd);
	}
	struct SortedList *h = head->l;
	struct node *wah;
	while(h != NULL){
		wah = h->n;
		h->n = mergeSort(&wah);
		h = h->nex;
	}
	printItem(head, index);
	free(head);
	fclose(index);	
  	return 0;
}
