#ifndef TREEMAP_h
#define TREEMAP_h

typedef struct TreeMap TreeMap;

TreeMap * createTreeMap(double (*lower_than_double) (void* key1, void* key2));

void insertTreeMap(TreeMap * tree, void* key, void * value);

void eraseTreeMap(TreeMap * tree, void* key);

void * searchTreeMap(TreeMap * tree, void* key);

void * upperBound(TreeMap * tree, void* key);

void * firstTreeMap(TreeMap * tree);

void * nextTreeMap(TreeMap * tree);

#endif /* TREEMAP_h */
