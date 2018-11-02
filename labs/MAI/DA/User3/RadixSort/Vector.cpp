#include "Vector.h"

void Create(Vector& v, int sz) {
  v.size = sz;
  v.data = (Item*)malloc(sizeof(Item) * v.size);
}

bool Empty(Vector& v) { return v.size == 0; }

int Size(Vector& v) { return v.size; }

Item &Load(const Vector& v, int i) { return v.data[i]; }

void Save(Vector& v, int i, Item item) {
 // if ((i >= 0) && (i < v->size)) {
    v.data[i] = item;
  //}
}

void Resize(Vector& v, int sz) {
  v.size = sz;
  v.data = (Item*)realloc(v.data, sizeof(Item) * v.size);
}

bool Equal(Vector& l, Vector& r) {
  bool isEqual = false;
  if (l.size != r.size) {
    isEqual = false;
  } else {
    for (int i = 0; i < l.size; i++) {
      if (l.data[i].key != r.data[i].key) {
        isEqual = false;
      } else {
        isEqual = true;
      }
    }
  }
  return isEqual;
}

void Destroy(Vector& v) {
  v.size = 0;
  free(v.data);
}