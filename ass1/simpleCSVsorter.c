#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simpleCSVsorter.h"



int main(int argc, char **argv){
	if(argc!=3){
	fprintf(stderr, "%s\n","Error: Does not have 3 parameters.");
	return -1;
	}
	if(strcmp((argv[1]),"-c")!=0){
	fprintf(stderr, "%s\n","Error: No -c argument.");
	return -1;
	}
char * buffer;
size_t len = 0;
Node *front=NULL;
Node * ptr = NULL;
long llength = 0;
while((getline(&buffer, &len, stdin)!=-1)){
	llength++;
	if(front == NULL){
		Node * current = (Node*)malloc(sizeof(Node));
		char * copystring = (char *)malloc(sizeof(char)*strlen(buffer));
		strcpy(copystring, buffer);
		current->data = copystring;
		current->next = NULL;
		front = current;
		ptr = front;

	}else{
		Node * current = (Node*)malloc(sizeof(Node));
		char * copystring = (char *)malloc(sizeof(char)*strlen(buffer));
		strcpy(copystring, buffer);
		current->data = copystring;
		ptr->next = current;
		ptr = ptr->next;
		
	}
}


	

	
	
	char * ind = (char*)malloc(sizeof(char)*strlen(front->data));
	char * potato = (char*)malloc(sizeof(char)*strlen(front->data));
	char * potato1 = (char*)malloc(sizeof(char)*strlen(front->data));
	
	ind = argv[2];				//index to sort by
	
	char * copystring1 = (char *)malloc(sizeof(char)*strlen(front->data));
	strcpy(copystring1, front->data);
	char * copystring2 = (char *)malloc(sizeof(char)*strlen(front->data));
	strcpy(copystring2, front->data);
	potato = copystring1;		//first line of categories
	potato1 = copystring2;
	
	
	//split commas
	int comma = 0; //first comma the relevant data is on
	int commamax = 0;
	char *found = (char*)malloc(sizeof(char)*strlen(front->data));
	char *found1= (char*)malloc(sizeof(char)*strlen(front->data));
	
	int notfound= 1;
	if(strstr(front->data,argv[2]))
	notfound=0;
	
	while(strsep(&potato1, ",")!=NULL){
	
	
		commamax++; //max commas
	}
	
	
	while((found = (strsep(&potato, ",")))!=NULL){
	if(strcmp(found,argv[2])==0){
	notfound = 0;
	break;
	}
		comma++;
	}
	if(comma==commamax)
	comma--;
	
	
	
	
	
	//add cat values
	Node * temp1 = (Node*)malloc(sizeof(Node));
	temp1 = front;
	char dumbo;
		int titlename = 0;
		int koo = 0;
	int i;
	int u;
	int fakecommas;
	int commacomma;
	int commacheck;
	int totalfakes;
	while(temp1!=NULL){
		char *find = (char*)malloc(sizeof(char)*strlen(temp1->data));
		char * copy = (char *)malloc(sizeof(char)*strlen(temp1->data));
		char * copycopy = (char *)malloc(sizeof(char)*strlen(temp1->data));
		
		strcpy(copy, temp1->data);
		strcpy(copycopy, temp1->data);
		
	
		int stupid = strlen(copy);
		commacheck = 0;
		fakecommas = 0;
		totalfakes = 0;
		titlename=0;
		//finding fake commas per category
		
		for(i=0;i<stupid;i++){
			dumbo=copy[i];
			
			if(dumbo==',')
			commacheck++;
				
			if(dumbo=='"'){
			titlename++;
			titlename=titlename%2;
		}
		if(titlename==1&&dumbo==',')
			fakecommas++;
			
		if(commacheck-fakecommas==comma)
		break;
		}
		// finding fake commas in total
		titlename=0;
		commacheck=0;
		for(i=0;i<stupid;i++){
			dumbo=copy[i];
			
			if(dumbo==',')
			commacheck++;
			
			if(dumbo=='"'){
			titlename++;
			titlename=titlename%2;
		}
		if(titlename==1&&dumbo==',')
			totalfakes++;

		}
		//printf("%d-%d-%d \n", commacheck,totalfakes,commamax);
		
		if(commacheck-totalfakes!=commamax-1){
		fprintf(stderr, "%s\n","Error: Bad formatting with commas.");
		return -1;
		}
		for(u=0;u<=(comma+fakecommas);u++){
				
			find = strsep(&copy, ",");
		}
	
		int k;
		
		while(find[0]==' '){
		
		if(strlen(find)==1)
		break;
		
		for(k=1;k<strlen(find);k++)
		find[k-1]=find[k];
		find[strlen(find)-1]= '\0';
		}
		if(find[strlen(find)-1]=='\n')
		find[strlen(find)-1]='\0';
		temp1->cat=find;
		

		temp1=temp1->next;
	}
	
	//exit
	if(notfound==1){
		fprintf(stderr, "%s\n","Error: Parameter not found.");
		return 0;
	}
	
	
	
	
	
	mergesort(&(front->next));
	double fatass;
	
	
	Node * temp = front;
	while (temp!=NULL){
		
		printf("%s", temp->data);
		temp = temp->next;
	}
	

	
	
	
	
	return 0;



}






