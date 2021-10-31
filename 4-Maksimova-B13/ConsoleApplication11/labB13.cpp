
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "memallocator.h"
#pragma warning(disable: 4996)

#define TRUE 1
#define FALSE 0

#define SIZE (sizeof(header) + sizeof(int))


typedef struct header{
    int size;
    struct header* next;
    struct header* prev;
} header;


typedef struct MemSyst{
    int totalSize;
    header* bufBlock;
    header* curBlock;
} MemSyst;

MemSyst Mem = { 0, NULL, NULL };


int memgetminimumsize(void){
    return 2 * SIZE;
}

int memgetblocksize(void){
    return SIZE;
}


int meminit(void* block, int size){
    int minSize = memgetminimumsize();
    int blockSize = memgetblocksize();

    if (size >= minSize && block) 
    {
        Mem.bufBlock = (header*)block;
        Mem.totalSize = size;
        Mem.bufBlock->next = (header*)((char*)block + blockSize);
        Mem.bufBlock->prev = (header*)((char*)block + blockSize);
        Mem.bufBlock->size = 0;
        *(int*)(Mem.bufBlock + 1) = 0;
        Mem.bufBlock->next->next = Mem.bufBlock;
        Mem.bufBlock->next->prev = Mem.bufBlock;
        Mem.bufBlock->next->size = size - minSize;
        *(int*)((char*)block - sizeof(int) + size) = Mem.bufBlock->next->size;
        Mem.curBlock = Mem.bufBlock->next;
        return FALSE;
    }
    else
        return TRUE;
}

void* memalloc(int size){
    header* block;
    header* newBlock;
    void* buffer = NULL;
    int blockSize = memgetblocksize();

    if (Mem.bufBlock == NULL)
        return NULL;
    if (Mem.bufBlock) {
        block = Mem.curBlock;
        while (block == Mem.curBlock) 
        {
            if (block->size < size)
                block = block->next;
            else if (block->size < size + blockSize)
            {
                buffer = (void*)(block + 1);
                memset(buffer, 0, block->size);
                block->prev->next = block->next;
                block->next->prev = block->prev;
                Mem.curBlock = block->next;
                block->next = NULL;

                *(int*)((char*)(block + 1) + block->size) = block->size;

                break;
            }
            else
            {

                newBlock = (header*)((char*)block + blockSize + size);

                newBlock->prev = block->prev;
                newBlock->next = block->next;
                newBlock->next->prev = newBlock;
                newBlock->prev->next = newBlock;
                block->next = NULL;

                newBlock->size = block->size - blockSize - size;
                *(int*)((char*)(newBlock + 1) + newBlock->size) = newBlock->size;

                block->size = size;
                *(int*)((char*)(block + 1) + size) = size;

                buffer = (void*)(block + 1);
                memset(buffer, 0, size);
                Mem.curBlock = newBlock;
                break;
            }
        }
    }
    return buffer;
}

void memfree(void* point){
    int blockSize = memgetblocksize();
    header* block;
    header* nextBlock;
    header* prevBlock;
    header* end = (header*)((char*)Mem.bufBlock + Mem.totalSize);
    if (point != NULL && Mem.totalSize != 0 && (char*)point < (char*)Mem.bufBlock + Mem.totalSize) 
    {
        block = (header*)((char*)point - sizeof(header));
        nextBlock = (header*)((char*)point + sizeof(int) + block->size);
        prevBlock = (header*)((char*)block - *(int*)((char*)point - blockSize) - blockSize);
        if (nextBlock != end && nextBlock->next != NULL)
        {
            block->size = block->size + nextBlock->size + blockSize;
            if (nextBlock == Mem.curBlock)
                Mem.curBlock = nextBlock->next;
            nextBlock->prev->next = nextBlock->next;
            nextBlock->next->prev = nextBlock->prev;
            *(int*)((char*)(block + 1) + block->size) = block->size;
        }

        if (prevBlock != Mem.bufBlock && prevBlock->next != NULL)
        {
            prevBlock->size = prevBlock->size + block->size + blockSize;
            if (block == Mem.curBlock)
                Mem.curBlock = prevBlock;
            *(int*)((char*)(prevBlock + 1) + prevBlock->size) = prevBlock->size;
            return;
        }

        block->next = Mem.bufBlock->next;
        Mem.bufBlock->next->prev = block;
        block->prev = Mem.bufBlock;
        Mem.bufBlock->next = block;
    }
}



void memdone(void){
    Mem.totalSize = 0;
    Mem.bufBlock = NULL;
    Mem.curBlock = NULL;
}
