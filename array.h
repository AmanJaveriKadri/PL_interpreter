#ifndef ARRAY_H_
#define ARRAY_H_

typedef array *array;

array new_array();

void free_array(array ray);

void *get_at(array ray, int i);
void put_at(array ray, void *val, int i);
void push(array ray, void *val);
void *pop(array ray, void *val);




#endif