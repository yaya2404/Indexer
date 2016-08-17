#ifndef INDEX_H
#define INDEX_H

#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"
#include "sorted-list.h"
#include <dirent.h>
#include <unistd.h>

struct node* SortedMerge(struct node *x, struct node *y);

void Split(struct node *head, struct node **f, struct node **b);

struct node* mergeSort(struct node **head);

void printItem(struct SL *head, FILE *i);

struct SL *sortFile(FILE *fi, char *name, struct SL *head);

struct SL *sortDir(DIR *dir, char *dname, struct SL *head);

#endif 
