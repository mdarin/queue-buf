#include <assert.h>
#include "queue.h"


//-----------------------------------------------------------------------------
struct QUEUE* QCreate(struct QUEUE* Queue, int Tag, void* Object, size_t Size)
{
 	Queue= malloc(sizeof *Queue); 	
	if (NULL != Queue)
	{	
		struct SLLIST* List = malloc(sizeof *List);
		if (NULL != List)
		{
			Queue->HeadPtr = Queue->TailPtr = List;
			Queue->TailPtr->Tag = 1;
			Queue->NumItems = 1;	
			Queue->TailPtr->Size = Size;
			Queue->TailPtr->Object = malloc(Size);
			if (NULL != Queue->TailPtr->Object) 
			{
				memcpy(Queue->TailPtr->Object, Object, Size);		
			}
			else
			{
				free(Queue->TailPtr->Object);
				free(List);
				free(Queue);
				Queue = NULL;
			}
		}
		else
		{
			free(List);
			free(Queue);
			Queue = NULL;
		}	
	}
	else
	{
		free(Queue);
		Queue = NULL;
	}

	return Queue;	
}
//-----------------------------------------------------------------------------
int QEnqueue(QUEUE* Queue, int Tag, void* Object, size_t Size) 
{
	int Result = QUEUE_ADD_FAILURE;
	assert(Queue != NULL);
	assert(Queue->TailPtr != NULL || Queue->HeadPtr != NULL);
	assert(0 == Queue->CheckInit1 && 0 == Queue->CheckInit2);
	int ListResult = SLAdd(&Queue->TailPtr, Tag, Object, Size);
  if (SL_SUCCESS == ListResult)
	{
		if (0 == Queue->NumItems)
		{
			Queue->HeadPtr = Queue->TailPtr;
		} 
		else
		{
			Queue->TailPtr = Queue->TailPtr->Next;
		}

		++Queue->NumItems;
		Result = QUEUE_SUCCESS;

	}
	return Result;
}
//-----------------------------------------------------------------------------
int QDequeue(QUEUE* Queue, void* Object)
{
	size_t Size;
	//void* p;
  int Result = QUEUE_SUCCESS;
	assert(NULL != Queue);
	assert(0 == Queue->CheckInit1 && 0 == Queue->CheckInit2);
	if (Queue->NumItems > 0)
	{
		void* p = SLGetData(Queue->HeadPtr, NULL, &Size);
		if (NULL != p)
		{			
			if (NULL != Object)
			{
				memcpy(Object, p, Size);
			}
			else
			{
				Object = NULL;	
			}
		}
		else
		{
			Result = QUEUE_DEL_FAILURE;
		}

		Queue->HeadPtr = SLDeleteThis(Queue->HeadPtr);
		--Queue->NumItems;

		if (0 == Queue->NumItems)
		{
			Queue->TailPtr = NULL;
		}
	}
	else
	{
		Result = QUEUE_EMPTY;
	}
	return Result;
}
//-----------------------------------------------------------------------------
void * QGetData(QUEUE *Queue, int *Tag, size_t *Size)
{
	 assert(Queue != NULL );
	 assert(Queue->CheckInit1 == 0 || Queue->CheckInit2 == 0);
	 void* Data = SLGetData(Queue->HeadPtr, Tag, Size);
	 return Data;
}
//-----------------------------------------------------------------------------
size_t QCount(QUEUE *Queue)
{
	assert(Queue != NULL );
	assert(Queue->CheckInit1 == 0 || Queue->CheckInit2 == 0);
	return Queue->NumItems;
}
//-----------------------------------------------------------------------------
void QDestroy(QUEUE *Queue)
{
	assert(Queue != NULL );
	assert(Queue->CheckInit1 == 0 || Queue->CheckInit2 == 0);
	
	while(QCount(Queue) > 0)
  {
    QDequeue(Queue, NULL);
  }
  Queue->TailPtr = NULL;
  /*╡╩дэж╠╫ссцхГоб╡ывВё╛╩Атздз╢ФжпреаТйЩ╬щ
  SLDestroy(Queue->HeadPtr);*/
}

