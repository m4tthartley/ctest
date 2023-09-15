
void strings() {
	printf("strings \n");

	u8 buffer[PAGE_SIZE];
	ZeroMemory(buffer, sizeof(buffer));
	string_pool pool;
	s_create_pool(&pool, buffer, sizeof(buffer));
	s_pool(&pool);
	string str = s_create("hello");
	s_append(&str, " world \n");
	s_prepend(&str, "Good morning, ");
	printf(str);

	char* fmt = s_format("Hello, The number is %i, by %s \n", 7, "Matt");
	printf(fmt);
	char* copy = s_copy(fmt);
	s_insert(&fmt, 5, " Computer");
	s_create("Good Morning \n");

	s_replace(&fmt, "number", "very important number");
	printf(fmt);
	
	char* find = NULL;
	s_find(fmt, "7", &find);
	printf("found: %s \n", find);

	string a = s_create(africa_short);
	s_replace(&a, "Africa", "AAFFRRIICCAA");
	printf(a);
	s_replace_single(&a, "AAFFRRIICCAA", "ENGLAND");
	printf(a);
	s_lower(&a);
	printf(a);
	s_upper(&a);
	printf(a);

	print_arena(&pool);
}