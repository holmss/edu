//Project Radix_sort

#include "TData.h"
#include "TVector.h"
using namespace std;
int main() {
    TVector in;
    TData t;
    while (t.InputStream()) {
        in.Push_back(t);
    }
    //TVector out;
    in.RadixSort(/*out*/);
    //for (int i = 0; i < in.Size(); i++)
    //    out[i].Print();
    return 0;
}

