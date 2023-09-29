
#include "platform.h"
#include "im.h"

int main() {
	core_window_t window;
	core_window(&window, "Window", 800, 600, 0);
	core_opengl(&window);
	for (;;) {
		core_window_update(&window);
		gfx_clear(vec4(1, 0, 0, 1));
		core_opengl_swap(&window);
	}
}
