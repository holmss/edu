#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <stdlib.h>
#include <stdint.h>

typedef struct{
uint64_t key;
uint64_t value;
} Item;
typedef struct {
  Item* data;
  uint64_t size;
} Vector;
void Create(Vector&, int);
bool Empty(Vector&);
int Size(Vector&);
Item &Load(const Vector&, int);
void Save(Vector&, int, Item);
void Resize(Vector&, int);
bool Equal(Vector&, Vector&);
void Destroy(Vector&);
#endif // _VECTOR_H_