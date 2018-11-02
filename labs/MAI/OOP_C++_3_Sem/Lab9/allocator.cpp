#include "allocator.h"

#include <iostream>

using namespace std;

TAllocBlock::TAllocBlock(size_t size, size_t count) //Constructor of allocator. Free blocks are full.
{
	_used_blocks = (char *)malloc(size * count);
	_free_blocks = (void **)malloc(sizeof(void *) * count);
	for (size_t i = 0; i < count; i++) {
		_free_blocks[i] = _used_blocks + i * size;
	}
	_free_count = count;
	cout << "TAllocBlock: Memory init" << endl;
}

void *TAllocBlock::allocate() // allocation of memory. Decrement of free blocks
{
	void *result = nullptr;
	if (_free_count > 0) {
		result = _free_blocks[_free_count - 1];
		_free_count--;
		cout << "TAllocBlock: Allocate" << endl; // it's ok
	}
	else {
		cout << "TAllocBlock: no memory exception" << endl; //if _free_count is 0, that means malloc returned nullptr
	}
	return result;
}

void TAllocBlock::deallocate(void *pointer) //deallocating. Increment of free blocks
{
	cout << "TAllocBlock: Deallocation" << endl;
	_free_blocks[_free_count] = pointer;
	_free_count++;
}
bool TAllocBlock::has_free_blocks()
{
	return _free_count > 0;
}

TAllocBlock::~TAllocBlock() //if incremented free is lower than all elems, that means not all free blocks are deallocated
{
	if (_free_count < count) {
		cout << "TAllocBlock: Memory leaked" << endl;
	}
	else {
		cout << "TAllocBlock: Memory freed" << endl;
	}
	delete _free_blocks;
	delete _used_blocks;
}