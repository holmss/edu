//
// Created by Maxim Spiridonov on 29.09.17.
//

#ifndef MODEL_H
#define MODEL_H

#include <cstdlib>
#include "TString.h"

class TPair {
public:
    TPair ();

    TPair (const TPair &that);

    TPair (int key, TString value);

    TPair &operator = (const TPair &that);

    ~TPair ();

    int Key;

    TString Value;
};

#endif //MODEL_H
