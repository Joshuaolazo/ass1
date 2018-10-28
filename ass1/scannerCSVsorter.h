#ifndef _scannerCSVsorter_c
#define _scannerCSVsorter_c

typedef struct _Node{
	char* data;
	char* cat;
	struct _Node * next;
}Node;

Node* merge(Node* one, Node* two); 
void half( Node* base, Node** first,  Node** last); 
void mergesorter(Node** front);
int directory_crawler(char*,char*,char*);
int sortCSV(char *, char* , char* ,char*);
int isNumeric(char*);


#endif
