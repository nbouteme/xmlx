#ifndef XMLX_H
# define XMLX_H

typedef struct	s_mlx_ctx t_mlx_ctx;

typedef struct	s_xmlx_image
{
	void		*buffer;
	int			width;
	int			height;
	unsigned	tex_id;
	int			type;
	int			format;
}				t_image;

typedef struct	s_xmlx_window t_xmlx_window;

typedef void(*t_key_input_func)(t_xmlx_window* win,
								int key,
								int action,
								int mods);

typedef void(*t_mouse_button_f)(t_xmlx_window* win,
								int button,
								int action,
								int mods);

typedef void(*t_mouse_move_fun)(t_xmlx_window* win,
								double x, double y);

typedef void(*t_mouse_scroll_f)(t_xmlx_window* win,
								double x, double y);

typedef struct	s_xmlx_window
{
	void			*internal_window;
	t_key_input_func on_key;
	t_mouse_button_f on_mouse_button;
	t_mouse_move_fun on_mouse_move;
	t_mouse_scroll_f on_mouse_scroll;	
	t_image			*framebuffer;
	int stop;
	int destroyed;
}				t_xmlx_window;

typedef void(*t_callback)();

enum
{
	INTEGER,
	FLOAT3,
	FLOAT4
};

t_mlx_ctx *xmlx_init();
t_xmlx_window *xmlx_new_window(int width, int height,
							const char *name, int fb_format);
void xmlx_present(t_xmlx_window *win);
void xmlx_run_window(t_xmlx_window *win, t_callback cb, void *user_ptr);
void xmlx_bind_window(t_xmlx_window *win);
void xmlx_destroy_window(t_xmlx_window *win);
void xmlx_destroy();
void xmlx_get_mouse_pos(double *x, double *y);
void xmlx_draw(t_xmlx_window *win);

# define XMLX_KEY_UNKNOWN            -1
# define XMLX_KEY_ESCAPE             256
# define XMLX_KEY_ENTER              257
# define XMLX_KEY_TAB                258
# define XMLX_KEY_BACKSPACE          259
# define XMLX_KEY_INSERT             260
# define XMLX_KEY_DELETE             261
# define XMLX_KEY_RIGHT              262
# define XMLX_KEY_LEFT               263
# define XMLX_KEY_DOWN               264
# define XMLX_KEY_UP                 265
# define XMLX_KEY_PAGE_UP            266
# define XMLX_KEY_PAGE_DOWN          267
# define XMLX_KEY_HOME               268
# define XMLX_KEY_END                269
# define XMLX_KEY_CAPS_LOCK          280
# define XMLX_KEY_SCROLL_LOCK        281
# define XMLX_KEY_NUM_LOCK           282
# define XMLX_KEY_PRINT_SCREEN       283
# define XMLX_KEY_PAUSE              284
# define XMLX_KEY_F1                 290
# define XMLX_KEY_F2                 291
# define XMLX_KEY_F3                 292
# define XMLX_KEY_F4                 293
# define XMLX_KEY_F5                 294
# define XMLX_KEY_F6                 295
# define XMLX_KEY_F7                 296
# define XMLX_KEY_F8                 297
# define XMLX_KEY_F9                 298
# define XMLX_KEY_F10                299
# define XMLX_KEY_F11                300
# define XMLX_KEY_F12                301
# define XMLX_KEY_F13                302
# define XMLX_KEY_F14                303
# define XMLX_KEY_F15                304
# define XMLX_KEY_F16                305
# define XMLX_KEY_F17                306
# define XMLX_KEY_F18                307
# define XMLX_KEY_F19                308
# define XMLX_KEY_F20                309
# define XMLX_KEY_F21                310
# define XMLX_KEY_F22                311
# define XMLX_KEY_F23                312
# define XMLX_KEY_F24                313
# define XMLX_KEY_F25                314
# define XMLX_KEY_KP_0               320
# define XMLX_KEY_KP_1               321
# define XMLX_KEY_KP_2               322
# define XMLX_KEY_KP_3               323
# define XMLX_KEY_KP_4               324
# define XMLX_KEY_KP_5               325
# define XMLX_KEY_KP_6               326
# define XMLX_KEY_KP_7               327
# define XMLX_KEY_KP_8               328
# define XMLX_KEY_KP_9               329
# define XMLX_KEY_KP_DECIMAL         330
# define XMLX_KEY_KP_DIVIDE          331
# define XMLX_KEY_KP_MULTIPLY        332
# define XMLX_KEY_KP_SUBTRACT        333
# define XMLX_KEY_KP_ADD             334
# define XMLX_KEY_KP_ENTER           335
# define XMLX_KEY_KP_EQUAL           336
# define XMLX_KEY_LEFT_SHIFT         340
# define XMLX_KEY_LEFT_CONTROL       341
# define XMLX_KEY_LEFT_ALT           342
# define XMLX_KEY_LEFT_SUPER         343
# define XMLX_KEY_RIGHT_SHIFT        344
# define XMLX_KEY_RIGHT_CONTROL      345
# define XMLX_KEY_RIGHT_ALT          346
# define XMLX_KEY_RIGHT_SUPER        347
# define XMLX_KEY_MENU               348

#endif
