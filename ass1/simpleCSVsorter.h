/* Project1.c
 *
 *  Created on: Sep 25, 2018
 *      Author: Joshua
 */


typedef struct Movie{
  char* hugeassstring;
  int type; //Determines whether data is float or stirng
  char* colData; //Column data if String
  float colValue; //Column data if numeric
}Movie;

typedef struct Node{
  Movie* movie;
  struct Node* next;
}Node;


// declare functions
char* column_cleaner(char*);
int column_finder(char*,char*);
char* column_reader(char*,int);
int isNumeric(char*);
int printList(Node *);
int end_insert(Node**,char*,char*);
char* row2(char*);

void merge_sort(Node**);
Node* sort(Node*, Node*);


//printer
//input: head, output: nothing
int printList(Node *head){
  while(head!=NULL){
    printf("%s",head->movie->hugeassstring);
    head = head->next;
  }
	return 0;
}

// cant figure out pointrs
//input row, output row
char* row2(char* row){
  //malloc row can Change
  char* rown = (char*) malloc (500);
  if(rown == NULL){
    fprintf(stderr,"%s","Malloc error");
  }
  strcpy(rown,row);
  return rown;
}

// inserts at the end
// points to linked list head and changes it
// input: head, column, and row, output: nothing
int end_insert(Node** head, char* col, char* row){
	// Make space for new node and movie
	Node *new_node = (Node *) malloc (sizeof(Node));
	if(new_node == NULL){
		fprintf(stderr,"%s","Malloc error");
	    	return(-1);
	}

	Movie *new_movie = (Movie* ) malloc (sizeof(Movie));
	if(new_movie == NULL){
		fprintf(stderr,"%s","Malloc error");
       	return(-1);
	}

  char * rown= row2(row);

	//fill in node
  if(col != NULL){
  	char* clean_col = column_cleaner(col);
    new_movie->type = isNumeric(clean_col);
    if(new_movie->type == 1){
      float value = atof(clean_col);
      new_movie->colValue = value;
    }
    else{
      new_movie->colData = clean_col;
    }
  }
  else{
    new_movie->type = 2;
    new_movie->colValue = -1.0;
    new_movie->colData = NULL;
  }

  new_movie->hugeassstring=rown;
	new_node->movie=new_movie;
	new_node->next=NULL;

	// if null make head
    if (*head == NULL){
    		*head = new_node;
		return 0;
    }
    // adds to end
    Node *end = *head;
    while(end->next!= NULL){
    		end = end->next;
    }
    end->next = new_node;
	return 0;
}

//checks if string is numeric
//returns 1 if numeric, 0 if non-numeric
int isNumeric(char* data){
  int i = 0;
  int isNum = 1; //set to 0 if not numeric
  int period = 0; //shouldnt be more than one period
  int length = (int)(strlen(data));
  for(i=0; i<length;i++){
    char c = data[i];
    if(c < '0' || c > '9'){
      if(c == '.')
        period++;
      else
        isNum = 0;
    if(period > 1)
      isNum = 0;
    }
  }
  return isNum;
}

// cleans column input
// leading whitespace
// leading zeros
// input: column string, output: cleaned column string
char* column_cleaner(char* column){
	// leading whitespace
	while( isspace( (unsigned char)*column))
		column++;

	// if the string is blank return NULL
	if(*column == 0)
	    return NULL;

	// leading zeros
	int i =0;
	while(column[i]==0){
		column++;
		i++;
	}
	return column;
}

// finds column number
// almost the same as column_reader
// instead column string is known and finds column number
// input:row and column string, output: column number
int column_finder(char* row, char* column){
	//searchs row for the column string
	char* pointer_tocolumn = strstr(row,column);
	// loop setup
	int position= (int) (pointer_tocolumn-row);
	int commas = 0;
	int inquotes = 0;
	int i= 0;

	//counts commas to find column number
	while(i<position){
		char c = row[i];
		// quote check
		if(c =='"'){
			if(inquotes ==0)
					inquotes--;
			else
				inquotes++;
		}
		// if in quotes do not count commas
		if(inquotes == 0){
			if(c == ',')
				commas++;
		}
		i++;
	}
	// There are 1 less comma than column number;
	return commas+1;
}


//Input: Column number and row string, Output: string in column
char* column_reader(char* row, int column){
	int commas = column; 	// There are 1 less comma than column number
	int diff=0; 	// Store beginning and end index
	int end;

	// If parenthesis for movie title, there is a comma in the title
	// using int as pseudo boolean. 0 for false 1 for true
	int inquotes = 0;
  int quoted=0;
  int last=0;
	// Setup for loop
	int i=0;

	while(commas>0){

		if(commas == 1){
			diff++;
      if(inquotes!=0){
        quoted++;
      }
		}
		char c = row[i];

    if(c=='\n'){
      last++;
      break;
    }

		// quote check
		if(c =='"'){
			if(inquotes ==0){
				inquotes--;
			}
			else{
				inquotes++;
			}
		}
		// if in quotes do not count commas
		if(inquotes == 0){
			if(c == ','){
				commas--;
			}
		}
		i++;
	}

  end= i-1;

	// includes the commas so +1 and -1 at the end
	int start = end-diff+1;
	diff--;
  //diff--;
  if(diff==0){
    return NULL;
  }
  if(last>0){
    start++;
    diff--;
  }
  if(quoted>0){
    start++;
    diff= diff-2;
  }
	// for storing the output


	char* column_string = (char*) malloc(diff*sizeof(char*));
  int x = 0;
  while (x<diff) {
    column_string[x]=row[start];
    x++;
    start++;
  }

  column_string[diff]='\0';

	return column_string;
}
