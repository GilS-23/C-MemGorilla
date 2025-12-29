#define MEM_TRACKER_IMPLEMENTATION
#include "mem_tracker.h"
#include <string.h>

int static totalAlloc = 0;
int static totalFree = 0;

typedef struct MemoryNode
{
    void* address;
    size_t size;
    char file[256];
    int line;
    struct MemoryNode* next;
} MemoryNode;

static MemoryNode* head = NULL;

static void add_node(void* addr, size_t size, const char* file, int line)
{
    MemoryNode* newNode = (MemoryNode*)malloc(sizeof(MemoryNode));
    if (!newNode)
    {
        return;
    }
    newNode->address = addr;
    newNode->size = size;
    newNode->line = line;
    strncpy(newNode->file, file, 255);
    newNode->next = head;
    head = newNode;
}

static int remove_node(void* addr)
{
    MemoryNode** current = &head;
    while (*current)
    {
        if ((*current)->address == addr)
        {
            MemoryNode* toDelete = *current;
            *current = (*current)->next;
            free(toDelete);
            return 1;
        }
        current = &((*current)->next);
    }
    return 0;
}

void* my_malloc(size_t size, const char* file, int line)
{
    void* ptr = malloc(size);
    if (ptr)
    {
        add_node(ptr, size, file, line);
        totalAlloc++;
    }
    else
    {
        printf("ERROR: Memory allocation failed in %s at line %d\n", file, line);
    }
    return ptr;
}

void* my_calloc(size_t nmemb, size_t size, const char* file, int line)
{
    void* ptr = calloc(nmemb, size);
    if (ptr)
    {
        add_node(ptr, nmemb * size, file, line);
        totalAlloc++;
    }
    else
    {
        printf("ERROR: Memory allocation failed in %s at line %d\n", file, line);
    }
    return ptr;
}

void* my_realloc(void* ptr, size_t size, const char* file, int line)
{   
    void* temp = ptr;
    void* newPtr = realloc(ptr, size);
    if (newPtr!= NULL)
    {
        if (temp != NULL)
        {
            remove_node(temp);
        }
        add_node(newPtr, size, file, line);
    }
    else
    {
        printf("ERROR: Memory allocation failed in %s at line %d\n", file, line);
        temp = NULL;
    }
    return newPtr;
}

void my_free(void* ptr)
{
    if (remove_node(ptr) == 0)
    {
        printf("ERROR: Attempted to free an invalid or already freed pointer: %p\n", ptr);
        return;
    }
    free(ptr);
    totalFree++;
}

void print_leak_report()
{
    MemoryNode* curr = head;
    if (!curr)
    {
        printf("\n>>> Memory Report: No leaks detected. Well done!\n");
        return;
    }
    printf("\n>>> MEMORY LEAK REPORT <<<\n");
    while (curr)
    {
        printf("Leak: %zu bytes at %p (File: %s, Line: %d)\n",curr->size, curr->address, curr->file, curr->line);
        curr = curr->next;
    }
    printf("\n>>> Statistics <<<\n");
    printf("Total allocations: %d\n",totalAlloc);
    printf("Total free: %d\n", totalFree);
    printf("--------------------------\n");
}