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


int main(int argc, char *argv[]){
	// Check for good arguments example below
	// ./sorter -c movie_title -d thisdir -o thatdir

	// More descriptive error messages for bad flags
	char* sorting_column = NULL;
	char* sorting_directory = NULL;
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
	printf("column is: %s\n",sorting_column);
	
	printf("directory is: %s\n", sorting_directory);
	printf("output is: %s\n",output_directory);
	/* Go to starting dir, if null then start at parent dir
	DIR *startdir;
	struct dirent *startdirent;
	if( strlen(sorting_directory) == 0){
		sorting_directory =".";
	}
	startdir = opendir(sorting_directory);
	if( !startdir){
		fprintf(stderr,"Cannot open directory: %s\n", strerror (errno));
		return -1;
	}
	*/
	return 0;
	 
}
