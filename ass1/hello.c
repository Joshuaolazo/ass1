 void mergesort(Node** front) {
 Node* one, two; Node* head = *front;
  
if(head->next == NULL||head == NULL) 
   return;
  
half(head, &one, &two);  


mergesort(&one); 
mergesort(&two); 

*front = merge(one, two); 
} 
  
  
  
 Node* merge(Node* one,  Node* two) {
 	 
 Node* esp = NULL; 
  
if (one == NULL) 
    return two; 
else if (two==NULL)
    return one; 
    
  //fix this later
if(isdigit(one->cat[0])&&isdigit(two->cat[0])){
	
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
  


void half( Node* base, Node** first,  Node** back) 
{ 
         Node* sub, sub2;
     sub = base->next; 
    sub2 = base; 

    while (sub != NULL){ 
    sub = sub->next; 
    if (sub != NULL) {
    	sub = sub->next;  
        sub2 = sub2->next; 
    }
    
     
    } 
 
    *back = sub2->next; 
    
    
    
    *first = base; 
    sub2->next = NULL; 
    
} 