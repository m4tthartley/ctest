typedef struct {
		list_node node;
		char* str;
	} item;

void print_list(list* l) {
	list_node* node = l->first;
	printf("list ");
	while(node) {
		item* i = (item*)node;
		printf("-> %s ", i->str);
		node = node->next;
	}
	putchar('\n');
}

int lists() {
	// list_node node;
	// list list = {0};
	// list_add(&list, &a);
	// list_remove(&list, &b);

	list strings = {0};
	item a = {.str="hello"};
	item b = {.str="world"};
	item c = {.str="testing"};
	item d = {.str="Matthew"};
	item e = {.str="BEGINNING"};
	item f = {.str="insert before"};
	item g = {.str="insert after"};

	list_add(&strings, &a);
	print_list(&strings);
	list_remove(&strings, &a);
	print_list(&strings);

	list_add(&strings, &a);
	list_add(&strings, &c);
	list_add(&strings, &d);
	list_add(&strings, &b);
	
	print_list(&strings);

	list_remove(&strings, &b);
	list_remove(&strings, &c);
	list_add_beginning(&strings, &e);
	list_add_before(&strings, &d, &f);
	list_add_after(&strings, &f, &g);

	print_list(&strings);
}