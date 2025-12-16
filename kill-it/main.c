/* nagnu/kill-it
 * main.c
 * Ruzen42
 */
#define NK_IMPLEMENTATION
#define NK_XLIB_IMPLEMENTATION

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDART_IO
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

#include <nuklear.h>
#include <nuklear_xlib.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define WIDTH 300
#define HEIGHT 120

void 
handle_do_it(void)
{
	system("shutdown now");
}

int
main(int argc, char *argv[])
{
	const char *first_arg = argv[0];
	if (argc > 1) {
		if (strcmp(first_arg, "--help") == 0) {
			printf("Use: %s [--version|--help]\n", argv[0]);
			return 0;
		}
		else if (strcmp(first_arg, "--version") == 0) {
			puts("0.1");
			return 0;
		}
	}

	Display *dpy = XOpenDisplay(NULL);
	
	if (!dpy) {
		fprintf(stderr, "kill-it: I can`t open display - goodbye\n");
		return 1;
	}

	int screen = DefaultScreen(dpy);
	Window root = RootWindow(dpy, screen);
	
	Window win = XCreateSimpleWindow(
		dpy,
		root,
		200, 200,
		WIDTH, HEIGHT,
		1,
		BlackPixel(dpy, screen),
		WhitePixel(dpy, screen)
	);

	XStoreName(dpy, win, "Kill it");
	XSelectInput(dpy, win, ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | StructureNotifyMask);
	XMapWindow(dpy, win);
	struct XFont *font = nk_xfont_create(dpy, "fixed");
	struct nk_context *ctx = nk_xlib_init(
			font,
			dpy,
			screen,
			win,
			WIDTH,
			HEIGHT
	);

	bool running = true;

	while (running) {
		XEvent evt;
		nk_input_begin(ctx);
		while (XPending(dpy)) {
			XNextEvent(dpy, &evt);
			nk_xlib_handle_event(dpy, screen, win, &evt);
		}

		nk_input_end(ctx);

		if (nk_begin(
			ctx,
			"dialog",
			nk_rect(0, 0, WIDTH, HEIGHT),
			NK_WINDOW_NO_SCROLLBAR)) {
			
			nk_layout_row_dynamic(ctx, 30, 1);
			nk_label(ctx, "Kill it?", NK_TEXT_CENTERED);

			nk_layout_row_dynamic(ctx, 30, 2);
			if (nk_button_label(ctx, "Do it")) {
				handle_do_it();
				running = 0;
			}	

			if (nk_button_label(ctx, "Cancel")) {
				running = 0;
			}	
		}
		nk_end(ctx);

		nk_xlib_render(win, nk_rgb(240,240,240));
		XFlush(dpy);

		usleep(16000);
	}

	nk_xlib_shutdown();
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);

	return 0;
}
