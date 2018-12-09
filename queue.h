#ifndef QUEUE_H__
#define QUEUE_H__

#include "sllist.h"

#define QUEUE_SUCCESS       0
#define QUEUE_ADD_FAILURE   1
#define QUEUE_DEL_FAILURE   2
#define QUEUE_EMPTY         3
#define QUEUE_NO_MEM			  SL_NO_MEM

typedef struct QUEUE
{
#ifndef NDEBUG
  int CheckInit1;
#endif

  SLLIST* HeadPtr;
	SLLIST* TailPtr; 
	size_t NumItems;

#ifndef NDEBUG
  int CheckInit2;
#endif
} QUEUE;

QUEUE* QCreate(QUEUE* Queue, int Tag, void* Object, size_t Size);
int QEnqueue(QUEUE* Queue, int Tag, void* Object, size_t Size);
int QDequue(QUEUE* Queue, void* Object);
void * QGetData(QUEUE* Queue, int *Tag, size_t *Size);
size_t QCount(QUEUE* Queue);
void QDestroy(QUEUE *Queue);

#endif //QUEUE_H__

