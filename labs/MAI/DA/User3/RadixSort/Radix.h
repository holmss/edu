#ifndef _RADIX_SORT_
#define _RADIX_SORT_

#include <stdio.h>
#include <stdint.h>
#include<math.h>
#include "Vector.h"

int SetLogNum (int r);
void CountingSort(int, Vector&, uint64_t, int, int);
void RadixSort(Vector&, int);
int RoundUp(double);
int RoundDown(double);
uint64_t FindDigit(Item&, int, int);

#endif //_RADIX_SORT_