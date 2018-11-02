//
// Created by Maxim Spiridonov on 29.09.17.
//

#ifndef MODEL_H
#define MODEL_H

#include <cstdlib>
#include "String.h"

class TPair {
public:
    TPair (const TPair &that);

    TPair (unsigned long long key, TString value);

    explicit TPair (int charBufferSize = 0);

    TPair &operator = (const TPair &that);

    virtual ~TPair () = default;

    unsigned long long Value;

    TString Key;
private:
    int const DEFAULT_INT_VALUE = 0;
};

#endif //MODEL_H
