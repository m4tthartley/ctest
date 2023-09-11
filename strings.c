
void strings() {
	printf("strings \n");

	u8 buffer[1024];
	string_pool pool;
	s_create_pool(&pool, buffer, sizeof(buffer));
	s_pool(&pool);
	string str = s_create("hello");
	s_append(&str, " world");
	s_append(&str, " cool");
	printf(str);
}