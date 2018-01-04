#include <stdio.h>

extern int mm_init (void);
extern void *mm_malloc (size_t size);
extern void mm_free (void *ptr);

// Extra credit
extern void* mm_realloc(void* ptr, size_t size);

// Garbage collector extra credit
extern void mm_garbage_collect(void * rootPtrs[], int numRoots);
