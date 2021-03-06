#include <swa/swa.h>
#include <swa/key.h>
#include <dlg/dlg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include "shared.h"
#define CGLTF_IMPLEMENTATION
#include "cgltf.h"

// this is important as a msvc workaround: their gl.h header is
// broken windows.h has to be included first (which is pulled by stdlib.h)
// Thanks Bill!
#ifdef _WIN32
  #include <windows.h>
#endif

#ifdef __ANDROID__
  #include <GLES2/gl2.h>
#else
  #include <GL/gl.h>
#endif

#define GL_FRAMEBUFFER_SRGB 0x8DB9

static bool premult = false;

void load_models() {
	cgltf_options options = {0};
	cgltf_data* data = NULL;
	cgltf_result result = cgltf_parse_file(&options, "CPU.glb", &data);
	if (result == cgltf_result_success)
	{
		/* TODO make awesome stuff */
		// load vertices
		// load textures
		cgltf_free(data);
	}
}

void game_init() {
	load_models();
}

void io_init() {
	inpfd = shm_open(inpname, O_RDWR, S_IRUSR | S_IWUSR);
	if (inpfd == -1) {
        dlg_error("can't open shm %s\n", inpname);
    }
	shm = (struct SharedMem*)mmap(0, sizeof(struct SharedMem), PROT_READ|PROT_WRITE, MAP_SHARED, inpfd, 0); // somehow it works without shmopen
	if (shm == MAP_FAILED) {
        dlg_error("mmap failed\n");
    }
	shm->pids.graphics = getpid();
	dlg_info("grpid %d", shm->pids.graphics);
}

static void window_draw(struct swa_window* win) {

	float alpha = 0.1f;
	float mult = premult ? alpha : 1.f;

	glClearColor(mult * 0.8f, mult * 0.6f, mult * 0.3f, alpha);
	glClear(GL_COLOR_BUFFER_BIT);
	if(!swa_window_gl_swap_buffers(win)) {
		dlg_error("swa_window_gl_swap_buffers failed");
	}

	// for continous redrawing:
	swa_window_refresh(win);
}

static void window_close(struct swa_window* win) {
	shm->run = false;
}

static void window_mouse_button(struct swa_window* win,
		const struct swa_mouse_button_event* ev) {
	if(ev->pressed && ev->button == swa_mouse_button_left) {
		//dlg_debug("begin resize");
		swa_window_begin_resize(win, swa_edge_bottom_right);
	}
}

static void window_key(struct swa_window* win, const struct swa_key_event* ev) {
	//dlg_trace("key: %d %d, utf8: %s", ev->keycode, ev->pressed, ev->utf8 ? ev->utf8 : "<null>");
	if(ev->pressed && ev->keycode == swa_key_escape) {
		dlg_info("Escape pressed, exiting");
		shm->run = false;
	}
	if(ev->keycode == swa_key_a) {
		shm->input = inp_left;
	} else if(ev->keycode == swa_key_d) {
		shm->input = inp_right;
	}
}

static void window_surface_created(struct swa_window* win) {
	bool ret = swa_window_gl_make_current(win);
	dlg_assert(ret);
}

static const struct swa_window_listener window_listener = {
	.draw = window_draw,
	.mouse_button = window_mouse_button,
	.close = window_close,
	.key = window_key,
	.surface_created = window_surface_created
};

int main(int argc, char** argv, char** envp) {
	struct swa_display* dpy = swa_display_autocreate("swa example-gl");
	if(!dpy) {
		dlg_fatal("No swa backend available");
		return EXIT_FAILURE;
	}

	struct swa_cursor cursor;
	cursor.type = swa_cursor_right_pointer;

	struct swa_window_settings settings;
	swa_window_settings_default(&settings);
	settings.title = "swa-example-window";
	settings.listener = &window_listener;
	settings.cursor = cursor;
	settings.transparent = true;
	settings.surface = swa_surface_gl;
#ifdef __ANDROID__
	settings.surface_settings.gl.major = 2;
	settings.surface_settings.gl.minor = 0;
	settings.surface_settings.gl.api = swa_api_gles;
#else
	settings.surface_settings.gl.major = 4;
	settings.surface_settings.gl.minor = 0;
	settings.surface_settings.gl.api = swa_api_gl;
#endif
	// settings.surface_settings.gl.srgb = true;
	// settings.surface_settings.gl.debug = true;
	// settings.surface_settings.gl.compatibility = false;
	struct swa_window* win = swa_display_create_window(dpy, &settings);
	if(!win) {
		//dlg_fatal("Failed to create window");
		swa_display_destroy(dpy);
		return EXIT_FAILURE;
	}

	swa_window_set_userdata(win, dpy);

	if(!swa_window_gl_make_current(win)) {
		dlg_fatal("Could not make gl window current");
		return EXIT_FAILURE;
	}

	dlg_info("OpenGL version: %s", glGetString(GL_VERSION));
	glEnable(GL_FRAMEBUFFER_SRGB);

	inpname = argv[1];
	io_init();
	game_init();


	while(shm->run) {
		if(!swa_display_dispatch(dpy, true)) {
			break;
		}
	}

	dlg_info("exiting");

	swa_window_destroy(win);
	swa_display_destroy(dpy);
}
