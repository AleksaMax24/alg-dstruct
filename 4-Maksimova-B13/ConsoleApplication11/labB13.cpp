
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "memallocator.h"
#pragma warning(disable: 4996)


#define TRUE 1
#define FALSE 0

typedef struct header{
  struct header* next;
  struct header* prev;
  int size;
} header;


static struct{

  header* bufBlock;
  header* curBlock;
  int totalSize;

} MemSyst = { (header*)NULL, (header*)NULL, 0 };


int memgetminimumsize(void){
  return 2 * (sizeof(header) + sizeof(int));
}


int memgetblocksize(void){
  return sizeof(header) + sizeof(int);
}


int meminit(void* buf, int size){
  int minSize = memgetminimumsize();
  int blockSize = memgetblocksize();

  if (!buf || size < minSize)
    return FALSE;
  else
  {

    MemSyst.bufBlock = (header*)buf;
    MemSyst.totalSize = size;
    MemSyst.bufBlock->next = (header*)((char*)buf + blockSize);
    MemSyst.bufBlock->prev = (header*)((char*)buf + blockSize);
    MemSyst.bufBlock->size = 0;
    *(int*)(MemSyst.bufBlock + 1) = 0;

    MemSyst.bufBlock->next->next = MemSyst.bufBlock;
    MemSyst.bufBlock->next->prev = MemSyst.bufBlock;
    MemSyst.bufBlock->next->size = size - minSize;
    *(int*)((char*)buf + size - sizeof(int)) = MemSyst.bufBlock->next->size;
    MemSyst.curBlock = MemSyst.bufBlock->next;
    return TRUE;
  }
}

void* memalloc(int size){
  header* block;
  header* newblock;
  void* res = NULL;
  int blockSize = memgetblocksize();

  if (MemSyst.bufBlock) 
  {
    block = MemSyst.curBlock;
    do
    {
      if (block->size < size)
      {
        block = block->next;
      }
      else if (block->size < size + blockSize) 
      {

        res = (void*)(block + 1);
        memset(res, 0, block->size);
        block->prev->next = block->next;
        block->next->prev = block->prev;
        MemSyst.curBlock = block->next;
        block->next = NULL;

        *(int*)((char*)(block + 1) + block->size) = block->size;

        break;
      }
      else
      {

        newblock = (header*)((char*)block + size + blockSize);

        newblock->prev = block->prev;
        newblock->next = block->next;
        newblock->next->prev = newblock;
        newblock->prev->next = newblock;
        block->next = NULL;

        newblock->size = block->size - size - blockSize;
        *(int*)((char*)(newblock + 1) + newblock->size) = newblock->size;

        block->size = size;
        *(int*)((char*)(block + 1) + size) = size;

        res = (void*)(block + 1);
        memset(res, 0, size);
        MemSyst.curBlock = newblock;
        break;
      }
    } while (block != MemSyst.curBlock);
  }

  return res;
}


void memfree(void* pointer){
  int blockSize = memgetblocksize();
  header* block;
  header* nextblock;
  header* prevblock;
  header* end = (header*)((char*)MemSyst.bufBlock + MemSyst.totalSize);

  if (pointer != NULL)
  {
    block = (header*)((char*)pointer - sizeof(header));
    nextblock = (header*)((char*)pointer + block->size + sizeof(int));
    prevblock = (header*)((char*)block - blockSize - *(int*)((char*)pointer - blockSize));


    if (nextblock != end && nextblock->next != NULL)
    {
      block->size += nextblock->size + blockSize;
      if (nextblock == MemSyst.curBlock)
        MemSyst.curBlock = nextblock->next;
      nextblock->prev->next = nextblock->next;
      nextblock->next->prev = nextblock->prev;
      *(int*)((char*)(block + 1) + block->size) = block->size;
    }

    if (prevblock != MemSyst.bufBlock && prevblock->next != NULL) 
    {
      prevblock->size += block->size + blockSize;
      if (block == MemSyst.curBlock)
        MemSyst.curBlock = prevblock;
      *(int*)((char*)(prevblock + 1) + prevblock->size) = prevblock->size;

      return;
    }

    block->next = MemSyst.bufBlock->next;
    MemSyst.bufBlock->next->prev = block;
    block->prev = MemSyst.bufBlock;
    MemSyst.bufBlock->next = block;
  }
}


void memdone(void){
  header* block;
  int minSize = memgetminimumsize();

  block = MemSyst.bufBlock->next;
  if (MemSyst.totalSize != block->size + minSize) {
    fprintf(stderr, "Error\n");
  }
}
