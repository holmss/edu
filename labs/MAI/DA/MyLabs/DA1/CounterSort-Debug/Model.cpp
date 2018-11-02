//
// Created by Maxim Spiridonov on 29.09.17.
//

#include "Model.h"

TPair::TPair () {
    Key = 0;
    Value = TString();
}

TPair::TPair (const TPair &that) {
    Key = that.Key;
    Value = that.Value;
}

TPair::TPair (int key, TString value) {
    Key = key;
    Value = value;
}

TPair &TPair::operator = (const TPair &that) {
    if (this != &that) {
        this->Key = that.Key;
        this->Value = that.Value;
    }
    return *this;
}

TPair::~TPair () {
}