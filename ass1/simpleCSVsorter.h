#ifndef _simpleCSVsorter_c
#define _simpleCSVsorter_c

typedef struct _Node{
	char* data;
	char* cat;
	struct _Node * next;
}Node;

Node* merge(Node* one, Node* two); 
void half( Node* base, Node** first,  Node** last); 
void mergesort(Node** front);


#endif
