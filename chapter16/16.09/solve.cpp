/*
 * TASK: Implement align_malloc and align_free functions which allocate and
 *       free memory respectively that is always aligned to some address which
 *       is divisible by a specified power of 2. As an example, given a power
 *       of 2, say 8, the memory allocated by align_malloc begins at an address
 *       which is divisible by 8, and align_free frees that memory segment.
 */

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

/**
 * @brief Allocates a memory block with the requested number of bytes and such
 *        that the memory block begins at an address which is divisible by a
 *        specified alignment value.
 * @note The memory layout is as follows: [ ... <mem> <data> ... ], where ...
 *       represents overhead due to the alignment constraint, mem is the
 *       address of the actual memory block allocated and data marks the
 *       beginning of the aligned memory segment with the number of bytes
 *       requested by the user; the user gets the address of this segment, not
 *       the one from the entire allocated block (i.e., data, not mem).
 */
void* align_malloc(const size_t bytes, const size_t alignment)
{
    /*
     * memory overhead due to the alignment constraint plus mem: we need
     * space to store the address mem of the entire memory block which we
     * allocate; also, alignment-1 is the minimum amount of memory we need
     * to make sure that the address returned to the user is divisible by
     * alignment
     */
    size_t overhead = sizeof(size_t) + (alignment - 1);

    size_t mem = (size_t)malloc(overhead + bytes);
    if ((void*)mem == nullptr)
    {
        return nullptr;
    }

    /*
     * data is the largest multiple of alignment which is less than or
     * equal to (mem + overhead); it marks the location of the aligned
     * memory block which is returned to the user
     */
    size_t data = (mem + overhead) & (~(alignment - 1));

    /* make sure we have space for storing the address mem right before data */
    assert(data - mem >= sizeof(mem));

    /* write the address mem right before the data segment (for freeing) */
    memcpy((void*)(data - sizeof(mem)), &mem, sizeof(mem));

    return (void*)data;
}

/**
 * @brief Frees memory allocated by align_malloc.
 */
void align_free(void* data)
{
    size_t mem = *((size_t*)data - 1);
    free((void*)mem);
}

int main()
{
    std::vector<void*> data_ptrs;

    for (size_t bytes = 0; bytes <= 10000; ++bytes)
    {
        for (size_t alignment = 1; alignment <= 256; alignment *= 2)
        {
            void* data = align_malloc(bytes, alignment);

            /* make sure data has the requested alignment */
            assert((size_t)data % alignment == 0);

            /* this should not corrupt anything */
            memset(data, 0xff, bytes);

            data_ptrs.push_back(data);
        }
    }

    for (void* data : data_ptrs)
    {
        align_free(data);
    }

    std::cout << "passed all tests" << std::endl;

    return EXIT_SUCCESS;
}
