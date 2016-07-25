#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "xmlx.h"
#include "xmlx_int.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

t_mlx_ctx *ctx;
t_xmlx_window *curr_win;

t_mlx_ctx *xmlx_init()
{
	if (ctx)
		return (ctx);
	if (!glfwInit())
		return (0);
	ctx = malloc(sizeof(*ctx));
	ctx->windows = init_vector(malloc(sizeof(t_vector)), sizeof(t_xmlx_window*));
	ctx->init = 0;
	return (ctx);
}

void xmlx_run_window(t_xmlx_window *win, t_callback cb, void *user_ptr)
{
	while (!glfwWindowShouldClose(win->internal_window))
	{
		cb(user_ptr);
		glfwPollEvents();
	}
}

void xmlx_destroy()
{
	t_xmlx_window **data = ctx->windows->data;
	int i = 0;

	while (i < ctx->windows->size)
		free_window(data[i++]);
	glDeleteShader(ctx->shader.vsh);
	glDeleteShader(ctx->shader.fsh);
	glDeleteProgram(ctx->shader.prog);
	glDeleteBuffers(3, &ctx->mesh.vao);
	ctx->init = 0;
	delete_vector(ctx->windows);
	free(ctx->windows);
	free(ctx);
	glfwTerminate();
}
