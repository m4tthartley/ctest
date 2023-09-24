#define GFX_VEC_CLASSIC_NAMES
#include <platform.h>
#include <im.h>
#include <file.h>

// TODO window resizing option

float sprite_frame = 0.0f;
float timer = 0.0f;
float timer2 = 0.0f;

/* 
 *	TODO
 *	- Embedded font
 *	- Audio
 *	- Wav loading
 *	- Dynarrays
 *	- Hot reloading
 *	- Remote reloading
 *	- Exe packer
 *	- VSYNC NOT WORKING
 *
 *	- Build asteroids with Nathan
 *	- Decide who's making art
 * */
void game() {
	char* name = "Window Test";
	print(BLUF "Game %s \n", name);

	// core_window_t window = core_window(name, 800, 600, CORE_CENTERED);
	core_window_t window;
	core_window(&window, name, 800, 600, WINDOW_CENTERED);
	printf("opengl start \n");
	core_opengl(&window);
	printf("opengl done \n");

	gfx_texture_t test_tex = gfx_create_null_texture(256, 256);
	memory_arena assets;
	m_freelist(&assets, 0, 0);
	m_reserve(&assets, GB(1), PAGE_SIZE);
	bitmap_t* bitmap = f_load_bitmap(&assets, "texture1.bmp");
	// gfx_texture_t texture2 = gfx_create_null_texture(256, 256);
	gfx_texture_t texture2 = gfx_create_texture(bitmap);
	// gfx_texture_t texture2 = gfx_create_texture(bitmap->data, bitmap->width, bitmap->height);

	wave_t* sound1 = f_load_wave(&assets, "star_wars.wav");
	wave_t* sound2 = f_load_wave(&assets, "example.wav");
	wave_t* sound3 = f_load_wave(&assets, "cantina_band.wav");
	wave_t* sound4 = f_load_wave(&assets, "dunkadunka.wav");
	wave_t* sound5 = f_load_wave(&assets, "dunkadunka22050.wav");
	wave_t* sound6 = f_load_wave(&assets, "dunkadunka8000.wav");
	wave_t* sound7 = f_load_wave(&assets, "dunkadunka8000mono.wav");
	wave_t* sound8 = f_load_wave(&assets, "dunkadunka22050mono.wav");

	wave_t* sound9 = f_load_wave(&assets, "examplesmall.wav");

	core_init_audio(CORE_DEFAULT_AUDIO_MIXER_PROC, 0);
	core_play_sound(sound9, 0.1f);
	core_play_sound(sound4, 0.1f);

	u8 block_buffer[PAGE_SIZE*2];
	// m_arena block_arena;
	// m_stack(&block_arena, block_buffer, PAGE_SIZE);
	// m_dynarr_t blocks = m_dynarr(&block_arena, sizeof(vec2_t));

	// m_dynarr_t blocks = m_dynarr_static(block_buffer, sizeof(block_buffer), sizeof(vec2_t));
	// m_dynarr_t blocks = dynarr_reserve(GB(1), sizeof(block_buffer), sizeof(vec2_t));
	dynarr_t blocks = dynarr(sizeof(vec2_t));

	for(;;) {
		core_window_update(&window);

		// if(window.keyboard['A'].pressed) {
		// 	printf("a \n");
		// }

		if(window.keyboard[KEY_ESC].released) {
			exit(0);
		}

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
		gfx_texture(&test_tex);
		gfx_sprite(vec2(5, 5), 0, 0, 128, 128, 2);
		gfx_sprite(vec2(5, -5), 0, 0, 64, 64, 4);
		// gfx_quad(vec3(5, 5, 0), vec2(1, 1));
		// glDisable(GL_TEXTURE_2D);
		// gfx_quad();

		sprite_frame += 0.0001f;
		
		gfx_sprite_t sprite;
		sprite.texture = &texture2;
		sprite.tile_size = 64;
		sprite.scale = 4;
		gfx_sprite_tile(sprite, vec2(-5, 5), (int)sprite_frame);

		gfx_line(vec2(0, 0), vec2(5, 5));

		{
			timer += window.dt;
			timer2 += window.dt;
			if(timer > 0.01f) {
				timer = 0.0f;
				vec2_t v = vec2(r_float()*20 - 10, r_float()*20 - 10);
				dynarr_push(&blocks, &v);
			}
			if(timer2 > 0.1f) {
				timer2 = 0.0f;
				dynarr_pop(&blocks, r_int_range(0, blocks.count));
			}
		}

		for(int i=0; i<blocks.count; ++i) {
			vec2_t* b = dynarr_get(&blocks, i);
			gfx_color(vec4(1, 1, 1, 1));
			gfx_quad(vec3(b->x, b->y, 0), vec2(0.2f, 0.2f));
		}

		core_opengl_swap(&window);
	}
}
