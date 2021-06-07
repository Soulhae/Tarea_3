#include <stdlib.h>
#include <assert.h>
#include "stack.h"

typedef struct n{
    void* data;
    struct n* next;
    struct n* prev;
} node;

struct List{
    node* first;
    node* last;
    node* current;
    int size;
};

int get_size(Lista* list){
    return list->size;
}

int is_empty(Lista* list){
    return (list->first==NULL);
}

void clean(Lista* list){
    while(is_empty(list)==0)
        pop(list);
}

Lista* createListS(){
   Lista* list=(Lista*) malloc(sizeof(Lista));
   list -> first = NULL;
   list -> last = NULL;
   list -> size = 0;
   return list;
}

Stack* createStack(){
    return createListS();
}

node* _createNode(void* data){
    node* t;
    t=(node*) malloc (sizeof(node));
    t -> data = data;
    t -> next = NULL;
    t -> prev = NULL;
    return t;
}

void popFrontS(Lista* list){
    if(!is_empty(list)){
        node *a = list->first;
        list->first=list->first->next;
        if(list->first!=NULL) list->first->prev=NULL;
        else list->last=NULL;
        free(a);
        list -> size--;
    }
}

void popBackS(Lista* list){
    if(!is_empty(list)){
        node *a = list->last;
        list->last=list->last->prev;
        if(list->last!=NULL) list->last->next=NULL;
        else list->first=NULL;
        free(a);
        list -> size-- ;
    }
}

void pushFrontS(Lista* list, void* data){
    node *a;
    a=_createNode(data);
    if(is_empty(list))
        list -> last = a;
    else
        list -> first -> prev = a;

    a -> next = list -> first;
    list -> first = a;
    list -> size++;
}

void pushBackS(Lista* list, void* data){
    node *a;
    a=_createNode(data);
    if(is_empty(list))
        list -> first = a;
    else
        list -> last -> next = a;

    a -> prev = list -> last;
    list -> last = a;
    list -> size++;
}

void pushCurrentS(Lista* list, void* data){
    if(!list->current) return;

    node* a=_createNode(data);
    a->next=list->current->next;
    list->current->next=a;
    if(a->next) a->next->prev=a;
    a->prev=list->current;
    if(list->current==list->last) list->last=a;

    list->current=a;
    list -> size++;
}

void popCurrentS(Lista* list){
    if(!list->current) return;

    if (list->current->prev) list->current->prev->next=list->current->next;
    if(list->current->next) list->current->next->prev=list->current->prev;
    if(list->first==list->current) list->first=list->current->next;
    if(list->last==list->current) list->last=list->current->prev;
    free(list->current);
    list -> size--; 
}


void pop(Stack* s){
  popBackS(s);
}


void* front(Lista* list){
    if(is_empty(list)) {
        return NULL;
    }
    list->current=list->first;
    if(list->first)
       return (list->first->data);
    else return NULL;
}



void* first(Lista* list){
    return front(list);
}

void* next(Lista* list){
    if(list->current)
       list->current=list->current->next;
    if(list->current)
       return list->current->data;
    else return NULL;
}

void* last(Lista* list){
    if(list->last){
        list->current=list->last;
        return list->last->data;
    }
    else return NULL;
}

void* top(Stack* s){
  return last(s);
}

void* prev(Lista* list){
    if(list->current)
       list->current=list->current->prev;
    if(list->current)
       return list->current->data;
    else return NULL;
}



void push(Stack* s, void* data){
  pushBackS(s,data);
}