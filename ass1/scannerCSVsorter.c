#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "scannerCSVsorter.h"


//Where argv is what we're sorting by , file, directory
int sortCSV(char *argv, char* ffile, char* ddir){
	
	/*	error checks from PA0	
	if(argc!=3){
	fprintf(stderr, "%s\n","Error: Does not have 3 parameters.");
	return -1;
	}
	if(strcmp((argv[1]),"-c")!=0){
	fprintf(stderr, "%s\n","Error: No -c argument.");
	return -1;
	}
	*/

//check if file exists


FILE *fp;
fp = fopen(ffile,"r"); 

if(fp==NULL){
	printf("DNExist\n");
//fileDoesNotExist
return -1;
}

/*
//checks if directory
DIR* directory = opendir(ffile);
if(directory!=NULL){
closedir(directory);
//isDirectory
return -2;
}

*/

//check last 4 letters .csv
//check if extension is csv file
char end[5] = "";
int z=0;
int h=0;
for(z=strlen(ffile)-4;z<strlen(ffile);z++){
end[h]=ffile[z];
h++;
}
printf("%s  %s\n",end,ffile);
if(strcmp(end,".csv")!=0){
	printf("notcsv\n");
fclose(fp);
return -1;
}

//not CSV files...

//Therefore we know we are working with csv file which exists

char * buffer;
size_t len = 0;
Node *front=NULL;
Node * ptr = NULL;
long llength = 0;
while((getline(&buffer, &len, fp)!=-1)){
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
	
	ind = argv;				//index to sort by
	
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
	if(strstr(front->data,argv))
	notfound=0;
	
	while(strsep(&potato1, ",")!=NULL){
	
	
		commamax++; //max commas
	}
	
	
	while((found = (strsep(&potato, ",")))!=NULL){
	if(strcmp(found,argv)==0){
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
			//ignore formatted incorrectly
		//fprintf(stderr, "%s\n","Error: Bad formatting with commas.");
		fclose(fp);
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
		//ignore
		fprintf(stderr, "%s\n","Error: Parameter not found.");
		fclose(fp);
		return 0;
	}
	//Checking directory
	struct stat st = {0};
	
	//Creates directory if it DNE
	if(stat(ddir, &st)== -1){
	mkdir(ddir, 0700);	
	}
	
	
	//creating new CSV file 
	
	char* fileStub = (char*)malloc(strlen(ffile)*sizeof(char));
	strcpy(fileStub,ffile);
	
	for(i=0;i<4;i++)
	fileStub[strlen(fileStub)-1] = '\0';
	 
	printf("fuck you bitch\n");
	char* newFileName = malloc((strlen(argv)+strlen(ffile))*sizeof(char));
	if(ddir!=NULL)
	strcpy(newFileName,ddir);
	
	strcat(newFileName,fileStub);
	strcat(newFileName,"-sorted-");
	strcat(newFileName,argv);
	strcat(newFileName,".csv");
	printf("%s\n",newFileName);

	//FILE *fd;
	int fz = open(newFileName,O_WRONLY | O_CREAT, 0644);
	//fd=fopen(newFileName,"w");
	dup2(fz,1);
	
	mergesort(&(front->next));
	
	
	Node * temp = front;
	while (temp!=NULL){
		
		printf("%s", temp->data);
		temp = temp->next;
	}
	

	
	
	
	fclose(fp);
	return 0;



}


/* you fool

int potato(int argc, char **argv){
	//size 3 5 or 7 because one mandatory flag and 2 optional
	if(argc!=7||argc!=5||argc!=3){
	fprintf(stderr, "%s\n", "Does not have correct number of arguments");
	return -1;
	}
	
	if(strcmp((argv[1]),"-c")!=0){
	fprintf(stderr, "%s\n","Error: No -c argument.");
	return -1;
	}
	
	
	if(strcmp((argv[3]),"-d")==0){
	//check to see if argv[4] is valid directory
	
	//if not
	fprintf(stderr, "%s\n", "Directory in argv[4] not found");
		//otherwise
	//search from this directory @ argv[4]
	}
	else {
	//search current directory
	}
	
	
	if(strcmp((argv[5]),"-o")==0||strcmp((argv[3]),"-o")==0){
		
		if(strcmp((argv[3]),"-o")==0)
		//Check to see if argv[4] is valid directory
		
		//if not
		fprintf(stderr, "%s\n", "Directory in argv[4] not found");
		//otherwise
	// output to this directory argv[4]
	
		if(strcmp((argv[5]),"-o")==0)
	//Check to see if argv[6] is valid directory
	
	//if not
	fprintf(stderr, "%s\n", "Directory in argv[6] not found");
		//otherwise
	// output to this directory argv[6]
	]
	else{
	//Output same directory as source file
	}
	
	
	

return 0;
}

*/

int main(int argc, char **argv){
	
	//index to sort by
	
	char* a = malloc(sizeof(char)*20);
	char* b = malloc(sizeof(char)*20);
	char* c = malloc(sizeof(char)*30);
	a="movie_title";
	b="test.csv";
	c="franciscolivesinhismother'sbasement/";
	sortCSV(a,b,c);
	
	return 0;
}

























