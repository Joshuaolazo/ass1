#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simpleCSVsorter.h"

 void mergesort(Node** front) {
 Node* one;
 Node* two;
 Node* head = *front;
  
if(head->next == NULL||head == NULL) 
   return;
  
half(head, &one, &two);  


mergesort(&one); 
mergesort(&two); 

*front = merge(one,two); 
} 
  
 Node* merge(Node* one,  Node* two) {
 	 
 Node* esp = NULL; 
  
if (one == NULL) 
    return two; 
else if (two==NULL)
    return one; 
    
  //fix this later
if((isdigit(one->cat[0])||one->cat[0]=='-')&&isdigit(two->cat[0])||two->cat[0]=='-'){
double aa, bb;
sscanf(one->cat, "%lf", &aa);
sscanf(two->cat, "%lf", &bb);
if (aa<=bb) { 
    esp = one; 
    esp->next = merge(one->next, two); 
} 
else{ 
    esp = two; 
    esp->next = merge(one, two->next); 
} 
}
else{
if (strcmp(one->cat,two->cat)<=0) { 
    esp = one; 
    esp->next = merge(one->next, two); 
} 
else{ 
    esp = two; 
    esp->next = merge(one, two->next); 
} 
}
return esp; 
} 
  

void half( Node* base, Node** first,  Node** last) 
{ 
         Node* fast;
         Node* slow;
    slow = base; 
    fast = base->next; 

    while (fast != NULL) 
        { 
    fast = fast->next; 
    if (fast != NULL) { 
        slow = slow->next; 
        fast = fast->next; 
    } 
    } 
  

    *first = base; 
    *last = slow->next; 
    slow->next = NULL; 
} 