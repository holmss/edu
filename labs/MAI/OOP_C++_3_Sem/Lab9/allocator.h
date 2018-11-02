#ifndef TALLOCATOR_H
#define TALLOCATOR_H

#include <cstdlib>

class TAllocBlock {
public:
	TAllocBlock(size_t size, size_t count);
	void *allocate();
	void deallocate(void *pointer);
	bool has_free_blocks();

	virtual ~TAllocBlock();
private:
	size_t size;
	size_t count;
	char *_used_blocks;
	void **_free_blocks;
	size_t _free_count;
};

#endif