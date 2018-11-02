//Project Radix_sort

#include "TData.h"
#include "TVector.h"
using namespace std;
int main() {
    TVector in(1);
    TData t;
    while (t.InputStream()) {
        in.Push_back(t);
    }

    //TVector out;
    if(in.Capacity()>0){
        in.RadixSort(/*out*/);
    }
    //for (int i = 0; i < in.Size(); i++)
    //    out[i].Print();
    return 0;
}

