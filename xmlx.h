#ifndef XMLX_H
# define XMLX_H

# include "vector.h"

typedef struct	s_shader
{
	unsigned vsh;
	unsigned fsh;
	unsigned prog;
}				t_shader;

typedef struct	s_mesh
{
	unsigned vao;
	unsigned vbo;
	unsigned ebo;
}				t_mesh;

typedef struct	s_mlx_ctx
{
	t_vector	*windows;
	t_shader	shader;
	t_mesh		mesh;
	int			init;
}				t_mlx_ctx;

typedef struct	s_xmlx_image
{
	void		*buffer;
	unsigned	tex_id;
	int			type;
	int			width;
	int			height;
}				t_image;

typedef struct	s_xmlx_window
{
	void		*internal_window;
	t_image		*framebuffer;
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

void die_error();
void xmlx_present(t_xmlx_window *win);
void xmlx_run_window(t_xmlx_window *win, t_callback cb, void *user_ptr);


#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)

#endif
