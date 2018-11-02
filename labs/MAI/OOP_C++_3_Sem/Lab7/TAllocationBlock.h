#ifndef TALLOCATIONBLOCK_H
#define TALLOCATIONBLOCK_H

#include <cstdlib>

class TAllocationBlock {
public:
    TAllocationBlock (size_t size, size_t count);

    void *allocate ();

    void *allocateSome(size_t count);

    void deallocate (void *pointer);

    void deallocateSome (void *pointer, size_t count);

    bool has_free_blocks ();

    virtual ~TAllocationBlock ();

private:
    size_t _size;
    size_t _count;

    char *_used_blocks;
    void **_free_blocks;

    size_t _free_count;
};


#endif //PROG_TALLOCATIONBLOCK_H
