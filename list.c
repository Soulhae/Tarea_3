#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    const void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List * lista;
  lista = (List *)malloc(sizeof(List));
  lista->head = NULL;
  lista->tail=NULL;
  lista->current=NULL;
     return lista;
}

void * firstList(List * list) {
  if(!list->head)return NULL;
  Node *primer_nodo = list->head;
  list->current = primer_nodo;
    return (void *)primer_nodo->data;
}

void * nextList(List * list) {
  Node * nodo_actual = list->current;
  if(!nodo_actual) return NULL;
  if(!nodo_actual->next){
    list->current = list->head;
    return (void *)list->current->data;       
  } 
  list->current = nodo_actual->next;
    return (void *)list->current->data;
}

void * lastList(List * list) {
   if(!list->tail)return NULL;
  Node *ultimo_nodo = list->tail;
  list->current = ultimo_nodo;
    return (void *)ultimo_nodo->data;
}

void * prevList(List * list) {
  Node * nodo_actual = list->current;
  if(!nodo_actual || !nodo_actual->prev) return NULL;
  list->current = nodo_actual->prev;
    return (void *)list->current->data;
}

void pushFront(List * list, const void * data) {
  Node * nuevo_head = createNode(data);
  Node * antiguo_head = list->head;
  if(!antiguo_head){
    list->head = nuevo_head;
    list->current = nuevo_head;
    list->tail = nuevo_head;
  }
  else{
		nuevo_head = NULL;
    nuevo_head->next = antiguo_head;
    antiguo_head->prev = nuevo_head;
    list->head = nuevo_head;
  }
  
}

void pushBack(List * list, const void * data) {
    if(list->head == NULL)pushFront(list,data);
    else{
        list->current = list->tail;
        pushCurrent(list,data);
    }
}

void pushCurrent(List * list, const void * data) {
  Node * nodo_nuevo = createNode(data);
  Node * nodo_actual = list->current;
  list->current = nodo_nuevo;
  if(!nodo_actual->next){
    list->tail = nodo_nuevo;
    nodo_actual->next = nodo_nuevo;
    nodo_nuevo->prev = nodo_actual;
  }
  else{
    nodo_nuevo->next = nodo_actual->next;
    nodo_nuevo->next->prev = nodo_nuevo;
    nodo_actual->next = nodo_nuevo;
    nodo_nuevo->prev = nodo_actual;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  Node * nodo_eliminar = list->current;
  const void* data = nodo_eliminar->data;
  if(!nodo_eliminar)  return NULL;
  else if(!nodo_eliminar->next){
    list->tail = nodo_eliminar->prev;
    list->current = nodo_eliminar->prev;
    nodo_eliminar->prev->next = NULL;
  }
  else if(!nodo_eliminar->prev){
    list->head = nodo_eliminar->next;
    list->current = nodo_eliminar->next;
    nodo_eliminar->next->prev = NULL;
  }
  else{
    list->current=nodo_eliminar->next;
    Node * nodo_anterior = nodo_eliminar->prev;
    nodo_anterior->next = nodo_eliminar->next;
    nodo_eliminar->next->prev = nodo_anterior;
  }
  free(nodo_eliminar);
  return (void *)data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}