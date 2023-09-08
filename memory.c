
void print_arena(memory_arena* arena) {
	for(int i=0; i<(arena->flags&ARENA_RESERVE?arena->commit:arena->size); ++i) {
		if(arena->address[i]) {
			if(arena->address[i] == '\n') {
				printf("\\n");
			} else {
				printf("%c", arena->address[i]);
			}
		} else {
			printf("_");
		}
		// fwrite(buffer+i, 1, 1, stdout);
	}
	putchar('\n');
}

void push_string(memory_arena* arena, char* str) {
	char* mem = m_push(arena, strlen(str)+1);
	sprintf(mem, str);
}

void print_freelist(memory_arena* arena) {
	putchar('\n');

	memory_block* block = arena->blocks.first;
	printf("blocks");
	while(block) {
		printf(" -> (l %li, s %li) ", (u8*)block-(u8*)arena->address, block->size);
		block = ((list_node*)block)->next;
	}
	putchar('\n');

	memory_block* free = arena->free.first;
	printf("free");
	while(free) {
		printf(" -> (l %li, s %li) ", (u8*)free-(u8*)arena->address, free->size);
		free = ((list_node*)free)->next;
	}
	putchar('\n');
}

void memory() {
	FILE* file = fopen("../africa.txt", "r");
	if(!file) {
		printf("cant open file\n");
		file = fopen("africa.txt", "r");
		if(!file) {
			printf("cant open file\n");
			return;
		}
	}
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	char* africa = malloc(size+1);
	memset(africa, 0, size+1);
	rewind(file);
	fread(africa, 1, size, file);
	fclose(file);

	u8 buffer[PAGE_SIZE] = {0};
	memory_arena stack;
	m_stack(&stack, buffer, sizeof(buffer));

	push_string(&stack, "hello world");
	push_string(&stack, "Good morning");
	push_string(&stack, africa);

	// print_arena(&stack);

	printf("align %li \n", align64(4500, PAGE_SIZE));
	printf("align %li \n", align64(4095, PAGE_SIZE));
	printf("align %li \n", align64(4000, PAGE_SIZE));
	printf("align %li \n", align64(8500, PAGE_SIZE));

	memory_arena dynStack;
	m_stack(&dynStack, 0, 0);
	m_reserve(&dynStack, GB(1), PAGE_SIZE);

	push_string(&dynStack, africa);
	push_string(&dynStack, africa);
	push_string(&dynStack, africa);
	push_string(&dynStack, africa);
	push_string(&dynStack, africa);
	// print_arena(&dynStack);
	// printf("commit size %li \n", dynStack.commit);

	// memory_arena allocator;
	// m_freelist(&allocator, 0, 0);
	// m_reserve(&allocator, GB(1), PAGE_SIZE);
	// m_alloc(&allocator, 2, GB(1));

	memory_arena allocator;
	u8 buffer2[PAGE_SIZE] = {0};
	m_freelist(&allocator, buffer2, sizeof(buffer2));
	m_alloc(&allocator, 64);
	m_alloc(&allocator, 128);
	m_alloc(&allocator, 256);

	print_freelist(&allocator);
	print_freelist(&allocator);

	// TODO test static freelists more
	// TODO include memory block header in size calculation and return
	// offset pointers
	// TODO dynamic sizing for freelists
}