#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "math.c"
#include "../core/core.h"
#include "../core/terminal.h"

char* africa = NULL;
char* africa_short = NULL;

#include "list.c"
#include "arrays.c"
#include "memory.c"
#include "strings.c"

void vectors() {
	vec3 vec1 = {1, 2, 3};
	vec3 vec2 = {4, 5, 6};
	sumVec3(vec1, vec2);
}

void inPlaceSwap() {
	int a = 3;
	int b = 7;
	printf("a=%i, b=%i \n", a, b);
	b = b-a;
	a = b+a;
	b = a-b;
	printf("a=%i, b=%i \n", a, b);
}

void hashing() {
	printf("hash %u \n", murmur3("hello world"));
	printf("hash %u \n", murmur3("test"));
	printf("hash %u \n", murmur3("main.c"));
	printf("hash %u \n", murmur3("core.h"));
	printf("hash %u \n", murmur3("this"));
	printf("hash %u \n", murmur3("is"));
	printf("hash %u \n", murmur3("a"));
	printf("hash %u \n", murmur3("test"));
	printf("hash %u \n", murmur3("test"));
	printf("hash %u \n", murmur3("test"));
}

int main() {
	{
		FILE* file = fopen("africa.txt", "r");
		if(!file) {
			printf("cant open file\n");
		}
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		africa = malloc(size+1);
		memset(africa, 0, size+1);
		rewind(file);
		fread(africa, 1, size, file);
		fclose(file);
	}

	{
		FILE* file = fopen("africa_short.txt", "r");
		if(!file) {
			printf("cant open file\n");
		}
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		africa_short = malloc(size+1);
		memset(africa_short, 0, size+1);
		rewind(file);
		fread(africa_short, 1, size, file);
		fclose(file);
	}

#if 0
	typedef enum {
		ARENA_STATIC,
		ARENA_DYNAMIC,
	} ARENA_TYPE;
	typedef struct {
		memory_block_header* next;
		memory_block_header* prev;
		int size;
	} memory_block_header;
	typedef struct {
		void* memory;
		int size;
		int stack;
		ARENA_TYPE type;
	} memory_arena;

	u8 buffer[1024];
	memory_arena arena;
	arenaInitStatic(&arena, buffer, sizeof(buffer));
	pushMemory(&arena, 64);

	memory_arena arena2;
	arenaInitDynamic(&arena2, 4);
	allocateMemory(&arena2, 64);

	typedef struct {
		u8 buffer[1024*1024];
	} string_pool;

	string_pool strings;
	useStringPool(&strings);
	char* str = sintern("hello world");
	clearStringPool(&strings); // at end of frame
#endif

#if 0
	u8 buffer[64];
	memory_arena stack = memoryStackInit(buffer, sizeof(buffer), ARENA_STATIC);

	memory_arena dynStack = memoryStackInit(0, 2, ARENA_DYNAMIC);

	u8 buffer2[64];
	memory_arena freelist = memoryFreelistInit(buffer2, sizeof(buffer2), ARENA_STATIC);

	memory_arena virtualStack = memoryInit(0, 2, ARENA_RESERVE|ARENA_STACK, 0);
	memory_arena virtualFreelist = memoryInit(0, 2, ARENA_RESERVE|ARENA_FREELIST, 0);
	u8 basicBuffer[64];
	memory_arena basic = memoryInit(basicBuffer, sizeof(basicBuffer), ARENA_STATIC|ARENA_STACK, 0);
#endif

	// u8 buffer[64];
	// memory_arena stack;
	// m_stack(&stack, buffer, sizeof(buffer));
	// char* str = m_push(&stack, 64);

	// memory_arena dynStack;
	// m_stack(&dynStack, 0, 0);
	// m_reserve(&dynStack, GB(1), 2);

	// memory_arena allocator;
	// m_freelist(&allocator, 0, 0);
	// m_reserve(&allocator, GB(1), 2);

	// m_alloc(&allocator, 2, GB(1));
	putchar('\n');

	// SYSTEM_INFO systemInfo;
	// GetSystemInfo(&systemInfo);
	// int pageSize = systemInfo.dwPageSize;
	// printf("page size %i \n", pageSize);

	// lists();
	// memory();
	strings();

	putchar('\n');
}