//
// Created by Maxim Spiridonov on 19.11.2017.
//

#include "TAllocationBlock.h"
#include <iostream>

TAllocationBlock::TAllocationBlock (size_t size, size_t count) : _size(size), _count(count) {
    _used_blocks = (char *) malloc(_size * _count);
    _free_blocks = (void **) malloc(sizeof(void *) * _count);

    for (size_t i = 0; i < _count; i++) {
        _free_blocks[i] = _used_blocks + i * _size;
    }
    _free_count = _count;
    std::cout << "TAllocationBlock: Memory init" << std::endl;
}

void *TAllocationBlock::allocate () {
    void *result = nullptr;

    if (has_free_blocks()) {
        result = _free_blocks[_free_count - 1];
        _free_count--;
        //std::cout << "TAllocationBlock: Allocate " << (_count - _free_count) << " of " << _count << std::endl;
    } else {
        //std::cerr << "TAllocationBlock: No memory exception :-)" << std::endl;
    }

    return result;
}

void *TAllocationBlock::allocateSome (size_t count) {
    void *result = nullptr;
    void *first = nullptr;
    for (int i = 0; i < count; ++i) {
        result = allocate();

        if (result != nullptr && i == 0) {
            first = result;
        }
    }
    if(has_free_blocks()) {
        std::cout << "TAllocationBlock: Allocate " << (_count - _free_count) << " of " << _count << std::endl;
    }else{
        std::cerr << "TAllocationBlock: No memory exception :-)" << std::endl;
    }
    return first;
}

void TAllocationBlock::deallocate (void *pointer) {

    if(_free_count<_count){
        _free_blocks[_free_count] = pointer;
        _free_count++;

    }
    else{
        //std::cerr << "TAllocationBlock: Failed Deallocate block " << std::endl;
    }

}

bool TAllocationBlock::has_free_blocks () {
    return _free_count > 0;
}

TAllocationBlock::~TAllocationBlock () {

    if (_free_count < _count) std::cout << "TAllocationBlock: Memory leak?" << std::endl;
    else std::cout << "TAllocationBlock: Memory freed" << std::endl;
    delete _free_blocks;
    delete _used_blocks;
}

void TAllocationBlock::deallocateSome (void *pointer, size_t count) {
    for (int i = 0; i < count; ++i) {
        deallocate(pointer);
    }
    std::cout << "TAllocationBlock: Deallocate blocks ["<<count<<"] " << std::endl;
}
