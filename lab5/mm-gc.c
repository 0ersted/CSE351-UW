/**
 * UW CSE 351 Spring 2016 Lab 5
 *
 * Extra credit: implementing garbage collection
 *
 * This requires mm_malloc and mm_free to be working correctly, so
 * don't start on this until you finish mm.c.
 */
#include "mm.c"

/* The tag to indicate that a block is marked. */
#define BLOCK_MARKED 4

/* Forward function declarations */
static void sweep(void);
static int is_pointer(void * ptr);
static void mark(void * ptr);

/** A modified version of examine_heap() to include BLOCK_MARKED. */
static void examine_heap_gc() {
  BlockInfo *block;

  /* print to stderr so output isn't buffered and not output if we crash */
  fprintf(stderr, "FREE_LIST_HEAD: %p\n", (void *)FREE_LIST_HEAD);

  for(block = (BlockInfo *)UNSCALED_POINTER_ADD(mem_heap_lo(), WORD_SIZE); /* first block on heap */
      SIZE(block->sizeAndTags) != 0 && (void *) block < mem_heap_hi();
      block = (BlockInfo *)UNSCALED_POINTER_ADD(block, SIZE(block->sizeAndTags))) {

    /* print out common block attributes */
    fprintf(stderr, "%p: %ld %ld %ld %ld\t",
    (void *)block,
    SIZE(block->sizeAndTags),
    block->sizeAndTags & BLOCK_MARKED,
    block->sizeAndTags & TAG_PRECEDING_USED,
    block->sizeAndTags & TAG_USED);

    /* and allocated/free specific data */
    if (block->sizeAndTags & TAG_USED) {
      fprintf(stderr, "ALLOCATED\n");
    } else {
      fprintf(stderr, "FREE\tnext: %p, prev: %p\n",
      (void *)block->next,
      (void *)block->prev);
    }
  }
  fprintf(stderr, "END OF HEAP\n\n");
}

/*
 * This will determine if the given pointer points to the beginning
 * of the payload of a block which is allocated.
 */
static int is_pointer(void * ptr){
  size_t * curBlock = (size_t*) UNSCALED_POINTER_ADD(mem_heap_lo(), WORD_SIZE);
  size_t * heapFooter = (size_t*) UNSCALED_POINTER_SUB(mem_heap_hi(), WORD_SIZE - 1);

  while(curBlock < heapFooter){
    size_t sizeAndTags = *curBlock;
    void * payloadPtr = UNSCALED_POINTER_ADD(curBlock, WORD_SIZE);
    size_t allocated = sizeAndTags & TAG_USED;

    if (payloadPtr == ptr && allocated){
      return 1;
    }
    curBlock = (size_t *) UNSCALED_POINTER_ADD(curBlock, SIZE(sizeAndTags));
  }
  return 0;
}

/*
 * Mark the block pointed to by ptr. The argument ptr will point to the beginning
 * of the payload of the block. Use the tag BLOCK_MARKED to signify that a block is
 * reachable. Next go and mark all other blocks that are pointed to by pointers in this block.
 */
static void mark(void * ptr){
  size_t * blockHeader = (size_t *) UNSCALED_POINTER_SUB(ptr, WORD_SIZE);

  // ** YOUR CODE HERE **//

}

/*
 * This goes through the all of the allocated blocks in the heap and frees all that are
 * unreachable (i.e., there is no BLOCK_MARKED tag).
 */
static void sweep(){
  size_t * curBlock = (size_t*) UNSCALED_POINTER_ADD(mem_heap_lo(), WORD_SIZE);
  size_t * heapFooter = (size_t*) UNSCALED_POINTER_SUB(mem_heap_hi(), WORD_SIZE - 1);

  // ** YOUR CODE HERE **//

}

void mm_garbage_collect(void * rootPtrs[], int numRoots){
  int i;
  for (i = 0; i < numRoots; i++){
    void * root = rootPtrs[i];
    mark(root);
  }
  sweep();
}
