/*
 * Project1.c
 *
 *  Created on: Sep 25, 2018
 *      Author: Joshua
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "simpleCSVsorter.h"


// 
int main(int argc, char *argv[]){
	// Input in form ./simpleCSVsorter -c food
	if(argc<3){
		fprintf(stderr,"%s","Incorrect input arguments");
		return -1;
	}
	// reads the last arg as the column to sort by
	char* sorting_column = argv[2];
	int count=0;

	// reads first row
	char row[5000];
	fgets(row,5000,stdin);
	count++;
	
	printf("%s",row);
	// finds column num
	int column_number = column_finder(row,sorting_column);

	// dont know if i should malloc
	char* col = (char*) malloc (500);
	if(col == NULL){
		fprintf(stderr,"%s","Malloc error");
        	return(-1);
	}

	// Head of Linked lists
	Node* head_valued = NULL;
	Node* head_null = NULL;

	// INPUT
	// Puts all rows into movie struct and makes a linked list of them
	// doesnt sort NULL columns
	while(fgets(row,sizeof(row),stdin)){
		
		count++;
		//printf("row number is: %d\n", count);
		col = column_reader(row,column_number);


		if(col != NULL){
			end_insert(&head_valued,col,row);
		}
		else{
			end_insert(&head_null,col,row);
		}
	}


	//SORTING
	merge_sort(&head_valued);

	//OUTPUT
	// prints the null list in order then the valued list
	printList(head_null);
	printList(head_valued);

	return column_number;
}
