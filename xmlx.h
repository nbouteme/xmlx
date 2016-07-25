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
}				t_xmlx_window;

typedef void(*t_callback)();

enum
{
	INTEGER = 1,
	FLOAT = 4
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
#endif
