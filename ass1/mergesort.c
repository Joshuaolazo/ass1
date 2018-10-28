#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ScannerCSVsorter.h"


void merge_sort(Node** head)
{
	Node* headPtr = *head;
	//if list is empty
	if(headPtr == NULL)
		return;
	//if list of size 1
	if(headPtr->next == NULL)
		return;
	
	Node* end = headPtr;
	Node* temp = headPtr->next;
	while(temp != NULL){
		temp = temp->next;
		if(temp != NULL){
			end = end->next;
			temp = temp->next;
		}
	}
	Node* list1 = headPtr;
	Node* list2 = end->next;
	end->next = NULL;
	
	merge_sort(&list1);
	merge_sort(&list2);
	*head = sort(list1, list2);
}

Node* sort(Node* list1, Node* list2)
{
	Node* sorted = NULL;
	if (list1 == NULL)
		return(list2);
	else if (list2==NULL)
		return(list1);
	
	if(list1->movie->type == 1){ //Handles case of input being numeric
		if ((list1->movie->colValue - list2->movie->colValue) < 0.0)
		{
			sorted = list1;
			sorted->next = sort(list1->next, list2);
		}
		else
		{
			sorted = list2;
			sorted->next = sort(list1, list2->next);
		}
	}
	else if(list1->movie->type == 0){ //handles case of input being string
		int s = strcmp(list1->movie->colData, list2->movie->colData);
		
		if (s < 0)
		{
			sorted = list1;
			sorted->next = sort(list1->next, list2);
		}
		else
		{
			sorted = list2;
			sorted->next = sort(list1, list2->next);
		}
	}
	
	return(sorted);
}
