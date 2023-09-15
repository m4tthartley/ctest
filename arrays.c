int _array_size(int totalSize, int itemSize) {
	assert(totalSize != sizeof(void*));
	return totalSize / itemSize;
}
#define array_add(array, item) if(array##Count < array_size(array)) array[array##Count++] = item;

typedef struct {
	int type;
	int size;
	int count;
	void* array;
} array_state;
void init_array_state(array_state* state, void* loc, int ts, int s) {
	state->array = loc;
	state->type = ts;
	state->size = s;
	state->count = 0;
}
void array_state_add(array_state* state, void* item) {
	if(state->count < (state->size/state->type)) {
		void* newLoc = ((char*)state->array) + state->count*state->type;
		memcpy(newLoc, item, state->type);
		++state->count;
	}
}

#define array_define(type, name, size) \
	struct {\
		int typeSize;\
		int count;\
		type array;\
	} name##_state;

#define generate_array_type(NAME, TYPE, SIZE) \
	typedef struct { \
		TYPE data[SIZE]; \
		int count; \
	} NAME; \
	void NAME##_add(NAME* array, TYPE item) { \
		if(array->count < SIZE) { \
			array->data[array->count++] = item; \
		} \
	} \
	TYPE* NAME##_get(NAME* array, int index) { \
		return array->data + index; \
	}

typedef struct {
	int x;
	int y;
} entity;

generate_array_type(entity_array, entity, 4);

typedef struct {
	int shaders[64];
	int nshaders;

	char* msgs[4]; int msgsCount;

	// array_define(int, codes, 4);
	int _codes[4];
	array_state codes;

	entity_array entities;
} state;

void addShader(state* s, int shader) {
	if(s->nshaders < sizeof(s->shaders)/sizeof(s->shaders[0])) {
		
	}
}

void arrays() {
	// Simple macros
	state s = {0};
	array_add(s.msgs, "Hello world");
	array_add(s.msgs, "How are you?");
	array_add(s.msgs, "Are you well?");
	array_add(s.msgs, "Have all your dreams come true?");
	array_add(s.msgs, "Are you happy?");

	for(int i=0; i<s.msgsCount; ++i) {
		printf("%s \n", s.msgs[i]);
	}

	// Array state type
	init_array_state(&s.codes, s._codes, sizeof(int), sizeof(s._codes));
	int num = 1;
	array_state_add(&s.codes, &num);
	num = 2;
	array_state_add(&s.codes, &num);
	num = 3;
	array_state_add(&s.codes, &num);
	num = 4;
	array_state_add(&s.codes, &num);
	num = 5;
	array_state_add(&s.codes, &num);

	for(int i=0; i<s.codes.count; ++i) {
		printf("%i \n", s._codes[i]);
	}

	// Just an array
	if(s.nshaders < array_size(s.shaders)) {
		s.shaders[s.nshaders++] = 10;
	}
	if(s.nshaders < array_size(s.shaders)) {
		s.shaders[s.nshaders++] = 9;
	}
	if(s.nshaders < array_size(s.shaders)) {
		s.shaders[s.nshaders++] = 8;
	}
	if(s.nshaders < array_size(s.shaders)) {
		s.shaders[s.nshaders++] = 7;
	}

	for(int i=0; i<s.nshaders; ++i) {
		printf("shader %i \n", s.shaders[i]);
	}

	// Generator macro
	entity e;
	e.x = 5;
	e.y = 10;
	entity_array_add(&s.entities, e);
	entity_array_add(&s.entities, e);
	entity_array_add(&s.entities, e);
	entity_array_add(&s.entities, e);
	entity_array_add(&s.entities, e);

	for(int i=0; i<s.entities.count; ++i) {
		// entity* e = &s.entities.data[i];
		// entity* e = entity_array_get(&s.entities, i);
		entity* e = (entity*)(&s.entities) + i;
		printf("entity x%i y%i \n", e->x, e->y);
	}
}