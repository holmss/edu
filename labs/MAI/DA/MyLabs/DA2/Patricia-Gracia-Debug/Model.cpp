//
// Created by Maxim Spiridonov on 29.09.17.
//

#include "Model.h"

TPair::TPair (int charBufferSize) {
    Key = TString(charBufferSize);
    Value = DEFAULT_INT_VALUE;
}

TPair::TPair (const TPair &that) {
    Key = that.Key;
    Value = that.Value;
}

TPair::TPair (unsigned long long value, TString key) {
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
