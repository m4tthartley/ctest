#define GFX_VEC_CLASSIC_NAMES
#include <platform.h>
#include <im.h>

void game() {
	char* name = "Window Test";
	print(BLUF "Game %s \n", name);

	// core_window_t window = core_window(name, 800, 600, CORE_CENTERED);
	core_window_t window;
	core_window(&window, name, 800, 600, 0);
	printf("opengl start \n");
	core_opengl(&window);
	printf("opengl done \n");

	gfx_texture_t test_tex = gfx_create_null_texture(256, 256);

	for(;;) {
		core_window_update(&window);

		// sets the coordinate system for gfx im calls
		gfx_coord_system(800.0f/64.0f, 600.0f/64.0f); // nice

		// glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		// glClear(GL_COLOR_BUFFER_BIT);

		vec4_t c = vec4_create(0.0f, 0.0f, 1.0f, 1.0f);
		gfx_clear(c);

		// glColor4f(1, 0, 1, 1);
		// glBegin(GL_QUADS);
		// glVertex2f(-0.5f, -0.5f);
		// glVertex2f(0.5f, -0.5f);
		// glVertex2f(0.5f, 0.5f);
		// glVertex2f(-0.5f, 0.5f);
		// glEnd();

		gfx_color(vec4(0, 1, 0, 1));
		gfx_quad(vec3(10, 0, 0), vec2(1, 1));

		gfx_color(vec4(1, 1, 0, 1));
		gfx_quad(vec3(11, 9, 0), vec2(1, 1));

		gfx_color(vec4(0, 1, 0, 1));
		gfx_quad(vec3(-5, 0, 0), vec2(1, 1));

		gfx_circle(vec3(-5, 2, 0), 1, 10);

		gfx_color(vec4(1, 0, 0, 1));
		gfx_quad(vec3(0, 0, 0), vec2(1, 1));

		gfx_color(vec4(1, 1, 1, 1));
		gfx_texture(test_tex);
		gfx_sprite(vec2(5, 5), 0, 0, 128, 128, 2);
		gfx_sprite(vec2(5, -5), 0, 0, 64, 64, 2);
		// gfx_quad(vec3(5, 5, 0), vec2(1, 1));
		glDisable(GL_TEXTURE_2D);
		// gfx_quad();

		core_opengl_swap(&window);
	}
}
