#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "xmlx.h"
#include "xmlx_int.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern t_mlx_ctx *ctx;
extern t_xmlx_window *curr_win;

void xmlx_bind_window(t_xmlx_window *win)
{
	curr_win = win;
	glfwMakeContextCurrent(win->internal_window);
}

t_image *xmlx_new_image(int width, int height, int format)
{
	unsigned long buf_size;

	t_image *ret = malloc(sizeof(*ret));
	buf_size = width * height;
	if (format == INTEGER || format == FLOAT3)
		buf_size *= 3;
	else
		buf_size *= 4;
	if (format == FLOAT3 || format == FLOAT4)
		buf_size *= 4;
	ret->buffer = memset(malloc(buf_size), 0, buf_size);
	ret->type = format == INTEGER ? GL_UNSIGNED_BYTE : GL_FLOAT;
	ret->width = width;
	ret->height = height;
	ret->format = format;
	glGenTextures(1, &ret->tex_id);
	glBindTexture(GL_TEXTURE_2D, ret->tex_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	return (ret);
}

void xmlx_set_win_callbacks(t_xmlx_window *win);

t_xmlx_window *xmlx_new_window(int width, int height,
							   const char *name, int fb_format)
{
	t_xmlx_window *ret = calloc(1, sizeof(*ret));

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	ret->internal_window = glfwCreateWindow(width, height, name, NULL, NULL);
	glfwSetWindowUserPointer(ret->internal_window, ret);
	xmlx_set_win_callbacks(ret);
	xmlx_bind_window(ret);
	if (!ctx->init)
	{
		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
			exit(42);
		ctx->mesh = gen_screen();
		ctx->shader = gen_shader();
	}
	ret->framebuffer = xmlx_new_image(width, height, fb_format);
	vector_pushback(ctx->windows, &ret);
	return (ret);
}

void xmlx_draw(t_xmlx_window *win)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, win->framebuffer->tex_id);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glfwSwapBuffers(win ? win->internal_window : curr_win->internal_window);
}

void xmlx_present(t_xmlx_window *win)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, win->framebuffer->tex_id);
	glTexImage2D(GL_TEXTURE_2D, 0,
				win->framebuffer->type == GL_FLOAT ?
				 (win->framebuffer->format == FLOAT3 ? GL_RGB : GL_RGBA32F)
				 : GL_RGBA8,
				win->framebuffer->width,
				win->framebuffer->height, 0,
				win->framebuffer->type == GL_FLOAT ?
				 (win->framebuffer->format == FLOAT3 ? GL_RGB : GL_RGBA)
				 : GL_BGRA,
				win->framebuffer->type,
				win->framebuffer->buffer);
	xmlx_draw(win);
}

void xmlx_destroy_window(t_xmlx_window *win)
{
	if (win && !win->destroyed)
	{
		glfwDestroyWindow(win->internal_window);
		free(win->framebuffer->buffer);
		free(win->framebuffer);
		glDeleteTextures(1, &win->framebuffer->tex_id);
		win->destroyed = 1;
	}
}
