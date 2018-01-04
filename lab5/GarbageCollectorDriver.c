#include "mm.h"
#include "memlib.h"

#include <stdio.h>

int verbose = 0;        /* global flag for verbose output */
#define WORD_SIZE sizeof(void*)
#define TAG_USED 1

#define NUM_ROOTS 3

typedef struct obj_1 {
  void * ptr1;
  void * ptr2;
  void * ptr3;
} obj_1;

typedef struct obj_2{
  int a;
  void * ptr1;
  int b;
  double d;
  void * ptr2;
} obj_2;

typedef struct obj_3{
  void * ptr1;
} obj_3;

static void initialize_blocks(void);
static void validate_garbage_collect(void);
static int is_free(void * payloadPtr);

static obj_1 * block1;
static obj_2 * block2;
static obj_3 * block3;
static obj_3 * block4;
static obj_2 * block5;
static obj_1 * block6;
static obj_3 * block7;
static obj_3 * block8;
static obj_3 * block9;
static obj_1 * block10;

void * roots[NUM_ROOTS];

int main(){
    /* Initialize the simulated memory system in memlib.c */
    /* Call the mm package's init function */
    mem_init();
    mem_reset_brk();

    /* Call the mm package's init function */
    if (mm_init() < 0) {
	    printf("Error in mm_init\n");
	    return -1;
    }

    initialize_blocks();
    mm_garbage_collect(roots, NUM_ROOTS);
    validate_garbage_collect();

    /*Free the remaining memory*/
    mem_deinit();
    return 0;
}

static void initialize_blocks(void){
  //Reachable fork
  block1 = mm_malloc(sizeof(obj_1));
  block2 = mm_malloc(sizeof(obj_2));
  block3 = mm_malloc(sizeof(obj_3));

  block1->ptr1 = block2;
  block1->ptr2 = block3;
  block1->ptr3 = (void *) 1;

  block2->a = 1;
  block2->ptr1 = (void *) 2;
  block2->b = 999999999;
  block2->d = 1.1;
  block2->ptr2 = NULL;

  block3->ptr1 = NULL;  

  roots[0] = (void *) block1;

  //single reachable block
  block4 = mm_malloc(sizeof(obj_3));

  block4->ptr1 = NULL;

  roots[1] = (void *) block4;

  //This makes an unreachable loop
  block7 = mm_malloc(sizeof(obj_3));
  block8 = mm_malloc(sizeof(obj_3));
  block9 = mm_malloc(sizeof(obj_3));

  block7->ptr1 = block8;
  block8->ptr1 = block9;
  block9->ptr1 = block7;

  //Unreachable self-pointing block
  block10 = mm_malloc(sizeof(obj_1));

  block10->ptr1 = NULL;
  block10->ptr2 = block10;
  block10->ptr3 = NULL;

  //This is just a chain of two that are reachable
  block5 = mm_malloc(sizeof(obj_2));
  block6 = mm_malloc(sizeof(obj_1));

  block5->a = 1393294;
  block5->ptr1 = (void *) 333;
  block5->b = 5;
  block5->d = 1.1;
  block5->ptr2 = block6;

  block6->ptr1 = NULL;
  block6->ptr2 = (void *) 7777;
  block6->ptr3 = NULL;

  roots[2] = (void *) block5;
}

static void validate_garbage_collect(void){
  //block[1-6] should still be allocated
  //block[7-10] should be freed
  int wasError = 0;

  if (is_free(block1) || is_free(block2) || is_free(block3)
      || is_free(block4) || is_free(block5) || is_free(block6))
  {
    printf("ERROR: A block that was reachable was freed!\n");
    wasError = 1;
  }

  if (!is_free(block7) || !is_free(block8) || !is_free(block9) || !is_free(block10)){
    printf("ERROR: A block that was not reachable was not freed\n");
    wasError = 1;
  }

  if (!wasError){
    printf("Success! The garbage collector passed all of the tests\n");
  }
}

static int is_free(void * payloadPtr){
  size_t sizeAndTags = *((size_t*) ( ((char *) payloadPtr) - WORD_SIZE));
  return !(sizeAndTags & TAG_USED);
}


