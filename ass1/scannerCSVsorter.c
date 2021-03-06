#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <sys/mman.h>
#include "scannerCSVsorter.h"


int PRINT = 1;

int main(int argc, char *argv[]){
	// Check for good arguments example below
	// ./sorter -c movie_title -d thisdir -o thatdir
	
	// More descriptive error messages for bad flags
	char* sorting_column = NULL;
	char* sorting_directory = NULL;
	sorting_directory = "./";
	char* output_directory = NULL;
	switch (argc) {
			// "Bad" Input Args
			// Returns descriptive error message
		case 0 :
		case 1 :
			fprintf(stderr,"%s\n","Not enough input arguments");
			return -1;
		case 2 :
			if(strcmp(argv[1],"-c") == 0)
				fprintf(stderr,"%s\n","Missing Sorting Column");
			else
				fprintf(stderr,"%s\n","Bad input arguments");
			return -1;
		case 4 :
			if(strcmp(argv[3],"-d") == 0)
				fprintf(stderr,"%s\n","Missing Sorting Directory");
			else
				fprintf(stderr,"%s\n","Bad input arguments");
			return -1;
		case 6 :
			if(strcmp(argv[5],"-o") == 0)
				fprintf(stderr,"%s\n","Missing Output Directory");
			else
				fprintf(stderr,"%s\n","Bad input arguments");
			return -1;
			
			// "Good" input args
			// Runs the code below each case
			// each case below is a subset
		case 7 :
			if(strcmp(argv[5],"-o") != 0){
				fprintf(stderr,"%s\n","Bad '-o' flag");
				return -1;
			}
			output_directory= argv[6];
		case 5:
			if(strcmp(argv[3],"-d") != 0){
				fprintf(stderr,"%s\n","Bad '-d' flag");
				return -1;
			}
			sorting_directory= argv[4];
		case 3 :
			if(strcmp(argv[1],"-c") != 0){
				fprintf(stderr,"%s\n","Bad '-c' flag");
				return -1;
			}
			sorting_column = argv[2];
			break;
			// check if sorting column is in list.
			
			// Bad input if over 7 args
		default:
			fprintf(stderr,"%s\n","Too many input arguments");
			return -1;
	}
	// Get origninal PID
	int parent_pid= getpid();
	
	// Print Statements for output
	if(PRINT ==1 || PRINT ==3 ){
		
		
		printf("Initial PID: %d\n",parent_pid);
		char message[]  = "PIDS of all child processes: \0";
		printf("%s",message);
		
		
	}

	// Start sorting process
	int i = 0;
	int * count;
	count = &i;
	int  x = directory_crawler(sorting_directory, sorting_column, output_directory,count);
	printf("\nTotal number of processes: %d\n", *count);
	return x;
}


int directory_crawler(char * sorting_directory,char * sorting_column, char * output_directory, int * count){
	DIR *directory;
	struct dirent *dirent;
	directory = opendir(sorting_directory);
	if( !directory){
		fprintf(stderr,"Cannot open directory: %s\n", strerror (errno));
		return -1;
	}
	int t= 0;
	while(t==0){

		const char * d_name;
		dirent = readdir (directory);
		if (! dirent) {
			t= 1;
			break;
		}
		d_name = dirent->d_name;
		if(PRINT==0|| PRINT ==3){
			printf ("%s\n",  d_name);
		}
		if (dirent->d_type & DT_DIR) {
			if (strcmp (d_name, "..") != 0 && strcmp (d_name, ".") != 0) {
				if(PRINT == 3)
					printf("DIRECTORY\n");
				int directorylen= (int) strlen(sorting_directory);
				int d_namelen= (int) strlen(d_name);
				char* new_directory = malloc(directorylen+d_namelen+1);
				strcpy(new_directory, sorting_directory);
				strcat(new_directory, d_name);
				strcat(new_directory, "/");
				if(PRINT==0){
					printf("New directory: %s\n", new_directory);
				}
				pid_t child = fork();
				fflush(stdout);
				int pid = getpid();
				int status = 0;
				if(child ==0){
					if( PRINT==1 ||PRINT == 3){
						printf("%d,",pid);
					}
					exit(1);
				}else{
					while ((pid = wait(&status)) > 0);
					if(PRINT == 0)
						printf("Count is: %d",*count);
					*count= *count +1;
					directory_crawler(new_directory,sorting_column,output_directory,count);
				}
				
			}
			
		}else{
			pid_t child = fork();
			fflush(stdout);
			int pid = getpid();
			int status = 0;
			if(child ==0){
				if( PRINT==1 ||PRINT == 3){
					printf("%d,",pid);
				}
				exit(1);
			}else{
				while ((pid = wait(&status)) > 0);
				if(PRINT ==  0)
					printf("Count is: %d",*count);
				*count = *count +1 ;
				sortCSV(sorting_column,(char*) d_name, output_directory, sorting_directory);
			}
			
		}
	}
	return 0;
}

//Where argv is what we're sorting by , file, output directory
int sortCSV(char *argv, char* ffile, char* ddir, char* idir){
	// checks to see if ffile is already sorted or not
	char* sortedd = (char*) malloc(sizeof(char*)*10);
	sortedd = "-sorted-";
	if(strstr(ffile,sortedd)!=NULL){
		if(PRINT ==3){
			printf("Already Sorted\n");
		}
		return -1;
	}
	
	//file + directory
	char * fffile;
	fffile = (char*) malloc(sizeof(char*) * (strlen(idir) + strlen(ffile)) );
	
	
	//Checking directory
	struct stat stt = {0};
	
	//Appends idir to beginning of ffile name if input directory exists
	if(stat(idir, &stt)!= -1){
		strcpy(fffile,idir);
		strcat(fffile,ffile);
	}
	else{
		strcpy(fffile,ffile);
	}
	
	//check if file exists
	if(PRINT ==2){
		printf("FILE PATH is: %s\n", fffile);
	}
FILE *fp;
fp = fopen(fffile,"r");

if(fp==NULL){
	fprintf(stderr,"File DNExist\n");
	//fileDoesNotExist
	return -1;
}else{
	//printf("open success\n");
	
}

//check last 4 letters .csv
//check if extension is csv file
char end[5] = "";
int z=0;
int h=0;
for(z=(int)strlen(ffile)-4;z< (int)strlen(ffile);z++){
end[h]=ffile[z];
h++;
}
if(strcmp(end,".csv")!=0){
	if(PRINT ==0|| PRINT ==3)
		printf("notcsv\n");
	fclose(fp);
	if(PRINT == 0 || PRINT ==3)
		printf("one\n");
	return -1;
}else{
	if(PRINT == 2 || PRINT == 0){
		printf("File is a csv\n");
		printf("File is : %s\n", ffile);
		printf("idir is  : %s\n", idir);
	}
}

//not CSV files...

//Therefore we know we are working with csv file which exists

char * buffer = (char *)malloc(sizeof(char)*5000);
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
		char * copystring = (char *)malloc(sizeof(char)*strlen(buffer)+3);
		strcpy(copystring, buffer);
		//for last input which ends in EOF
		if(copystring[strlen(copystring)-1]!='\n')
			copystring[strlen(copystring)] = '\n';
		copystring[strlen(copystring)] = '\0';
		current->data = copystring;
		ptr->next = current;
		ptr = ptr->next;
		
	}
}
	// fix length kill extra
	long llength1 =llength;
	Node *extra = front;
	Node *t;
	//printf("length: %ld\n",llength1);
	while (llength1>0){
		t=extra;
		extra = extra->next;
		llength1--;
		//printf("length: %ld\n",llength1);
		if( llength1==0){
			t->next=NULL;
			break;
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
	//char *found1= (char*)malloc(sizeof(char)*strlen(front->data));
	
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
		//int koo = 0;
	int i;
	int u;
	int fakecommas;
	//int commacomma;
	int commacheck;
	int totalfakes;
	//long llength2 =llength;
	while(temp1!=NULL){
		
		if(temp1->data == NULL){
			fprintf(stderr,"blank column\n");
			return -1;
		}
		/*
		printf("start one\n");
	
		printf("start two\n");
		printf("Temp data is: %s", temp1->data);
		printf("Size of malloc is: %lu\n",sizeof(char)*strlen(temp1->data));
		
		*/
		char *find = (char*)malloc(sizeof(char)*strlen(temp1->data));
		char * copy = (char *)malloc(sizeof(char)*strlen(temp1->data));
		
		
		strcpy(copy, temp1->data);
		
	
		int stupid = (int) strlen(copy);
		int commacheck = 0;
		int fakecommas = 0;
		int totalfakes = 0;
		int titlename=0;
		int firsty = 0;
		int fraud = 0;
		int quotes=0;
		int openingcomma=0;
		int closingcomma=0;
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
			
			//if comma-- ==commacheck - fakecommas take keep both indices and take string between them to use in cat
			//if I am 1 commas away I will
			
			
			if((commacheck-fakecommas)==comma&&firsty==0){
				firsty=1;
			}
			
			if(firsty==1&&dumbo=='"'&&quotes==0){
				if(PRINT == 4){
					printf("opening:%d\t",i);
				}
				openingcomma = i;
				quotes=1;
			}
			if(quotes>0)
				quotes++;
			
			if(quotes>2&&dumbo=='"')
				fraud=1;
			
			
			if(fraud==1){
				if(PRINT == 4){
					printf("closing: %d\n",i);
				}
				closingcomma=i;
				break;
			}
			
			
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
			fprintf(stderr, "%s\n","Error: Inconsistent commas between rows.");
			fclose(fp);
			return -1;
		}
		//THERE WERE COMMAS IN PARENTHESES
		u=0;
		
		if(fraud==1){
			if(PRINT == 4)
				printf("fraud\n");
			for(i=openingcomma+1;i<=closingcomma-1;i++){
				find[u]=copy[i];
				u++;
			}
			if(PRINT == 4)
				printf("%s\n",find);
		}
		else{
			
			for(u=0;u<=(comma+fakecommas);u++){
				
				find = strsep(&copy, ",");
			}
		}
		int k;
		
		while(find[0]==' '){
		
			if(strlen(find)==1)
			break;
			
			for(k=1;k<strlen(find);k++)
			find[k-1]=find[k];
		
			find[strlen(find)-1]= '\0';
		}
		
		while(find[strlen(find)-1]==' '){
			find[strlen(find)-1]='\0';
		}
		if(find[strlen(find)-1]=='\n'){
			find[strlen(find)-1]='\0';
		}
		temp1->cat=find;
		//printf("end one\n");
		
		temp1=temp1->next;
		//llength2--;
		
		//printf("end two\n");
	}
	//printf("out\n");
	//exit
	if(notfound==1){
		//ignore
		fprintf(stderr, "%s\n","Error: Parameter not found.");
		fclose(fp);
		if(PRINT == 0 || PRINT ==3 )
			printf("three\n");
		return -1;
	}
	
	//Checking directory
	struct stat st = {0};
	
	//Creates directory if it DNE
	if(ddir!=NULL&&stat(ddir, &st)== -1){
		//mkdir(ddir, 0700);
		//fclose(fp);
		//if(PRINT == 0)
		fprintf(stderr, "%s\n","Error: Invalid Output Directory.");
		return(-1);
	}
	
	
	//creating new CSV file 
	
	char* fileStub = (char*)malloc(strlen(ffile)*sizeof(char));
	strcpy(fileStub,ffile);
	
	for(i=0;i<4;i++)
	fileStub[strlen(fileStub)-1] = '\0';
	 
	char* newFileName = (char*) malloc((strlen(argv)+strlen(fffile)+ 10)*sizeof(char));
	if(ddir!=NULL){
		if(PRINT!= 1){
			printf("ddir is not null\n");
			printf("ddir is: %s\n", ddir);
			printf("idir is: %s\n", idir);
		}
		strcpy(newFileName,ddir);
		strcat(newFileName,fileStub);
	}else{
		if(PRINT!= 1){
			printf("ddir is: %s\n", ddir);
			printf("idir is: %s\n", idir);
		}
		strcpy(newFileName,idir);
		strcat(newFileName,fileStub);
	}
	strcat(newFileName,"-sorted-");
	strcat(newFileName,argv);
	strcat(newFileName,".csv");
	if(PRINT== 0 || PRINT ==3 )
		printf("%s\n",newFileName);

	fclose(fp);
	
	FILE *new;
	new = fopen(newFileName, "w+");
	mergesorter(&(front->next));
	
	Node * temp = front;
	//long llength3 =llength;
	while (temp!=NULL){
		fprintf(new,"%s", temp->data);
		temp = temp->next;
		//llength3--;
	}
	
	fclose(new);
	if(PRINT == 0 || PRINT ==3 )
		printf("five\n");
	/*
	free(potato);
	free(potato1);
	free(copystring1);
	free(copystring2);
	free(found);
	free(fileStub);
	free(newFileName);
	free(buffer);
	free(temp1);
	free(temp);
	free(front);
	 */
	return 0;

}

