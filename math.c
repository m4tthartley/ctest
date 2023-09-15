
typedef struct {
	float x;
	float y;
	float z;
} vec3;

int sum(int a, int b) {
	int result = a + b;
	return result;
}

vec3 sumVec3(vec3 a, vec3 b) {
	vec3 result = {
		sum(a.x, b.x),
		sum(a.y, b.y),
		sum(a.z, b.z),
	};
	return result;
}