//
//  ScannerCSVsorter.c
//  l,m,
//
//  Created by Joshua Olazo on 10/20/18.
//  Copyright © 2018 Joshua Olazo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include "ScannerCSVsorter.h"
#include <dirent.h>

int directory_crawler(char*);
int dummy(void);

int PRINT = 0;

int main(int argc, char *argv[]){
	// Check for good arguments example below
	// ./sorter -c movie_title -d thisdir -o thatdir

	// More descriptive error messages for bad flags
	char* sorting_column = NULL;
	char* sorting_directory = NULL;
	sorting_directory = "./";
	char* output_directory = NULL;
	output_directory = "./";
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
	int parent_pid= getpid();
	printf("Initial PID: %d\n",parent_pid);
	printf("PIDS of all child processes: ");
	int  x = directory_crawler(sorting_directory);
	return x;
}


int directory_crawler(char * sorting_directory){
	DIR *directory;
	struct dirent *dirent;
	if( strlen(sorting_directory) == 0){
		sorting_directory =".";
	}
	directory = opendir(sorting_directory);
	if( !directory){
		fprintf(stderr,"Cannot open directory: %s\n", strerror (errno));
		return -1;
	}
	while(1){
		const char * d_name;
		dirent = readdir (directory);
		if (! dirent) {
			/* There are no more entries in this directory, so break
			 out of the while loop. */
			break;
		}
		d_name = dirent->d_name;
		/* Print the name of the file and directory. */
		if(PRINT==0){
			printf ("%s\n",  d_name);
		}
		if (dirent->d_type & DT_DIR) {
			//printf("memes");
			// Check that the directory is not "d" or d's parent.
			if (strcmp (d_name, "..") != 0 && strcmp (d_name, ".") != 0) {
				// Recursively call "list_dir" with the new path.
				int directorylen= (int) strlen(sorting_directory);
				int d_namelen= (int) strlen(d_name);
				char* new_directory = malloc(directorylen+d_namelen+1);
				strcpy(new_directory, sorting_directory);
				strcat(new_directory, d_name);
				strcat(new_directory, "/");

				if(PRINT==0){
					printf("New directory: %s\n", new_directory);
				}
				int child = fork();
				fflush(stdout);
				int pid = getpid();
				if(child ==0 && PRINT > 0){
					printf("%d,",pid);
					exit(1);
				}
				
				directory_crawler(new_directory);
				
			}
			
		}else{
			int child = fork();
			fflush(stdout);
			int x = dummy();
			x++;
			int pid = getpid();
			if(child ==0 && PRINT >0){
				printf("%d,",pid);
				exit(1);
			}
		
		}
	}
	return 0;
}

int dummy(){
	//printf("Not a directory\n");
	return 0;
}
