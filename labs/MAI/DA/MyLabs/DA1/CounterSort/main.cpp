//
// Created by Maxim Spiridonov on 29.09.17.
//

#include "TVector.h"

void Print (TVector &inp) {
    for (int i = 0; i < inp.Capacity(); ++i) {
        printf("%d\t%s\n", inp[i].Key, inp[i].Value.GetCharArray());
    }
}

int main (int argc, char **argv) {
    TVector myVector(32);
    int tempInt = 0;
    char *bufStr = new char[2048];
    TPair tPair;
    while (scanf("%d", &tempInt) != EOF) {
        scanf("%s", bufStr);
        tPair.Key = tempInt;
        tPair.Value = bufStr;

        myVector.FastPushBack(tPair);
    }
    if (myVector.Capacity() != 0) {
        myVector.CountingSort();
        Print(myVector);
    }
    delete[] bufStr;
    return 0;
}