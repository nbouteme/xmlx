#ifndef XMLX_INT_H
# define XMLX_INT_H

# include "xmlx.h"
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

t_mesh gen_screen();
t_shader gen_shader();


#endif
