#include <GLFW/glfw3.h>
#include "xmlx_int.h"

void win_key_input(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	t_xmlx_window *self = glfwGetWindowUserPointer(win);
	(void)scancode;
	if (self->on_key)
		self->on_key(self, key, action, mods);
}

void win_mouse_button(GLFWwindow* win, int button, int action, int mods)
{
	t_xmlx_window *self = glfwGetWindowUserPointer(win);
	if (self->on_mouse_button)
		self->on_mouse_button(self, button, action, mods);
}

void win_scroll(GLFWwindow* win, double x, double y)
{
	t_xmlx_window *self = glfwGetWindowUserPointer(win);
	if (self->on_mouse_scroll)
		self->on_mouse_scroll(self, x, y);
}

void win_mouse_move(GLFWwindow* win, double x, double y)
{
	t_xmlx_window *self = glfwGetWindowUserPointer(win);
	if (self->on_mouse_move)
		self->on_mouse_move(self, x, y);
}

void xmlx_set_win_callbacks(t_xmlx_window *win)
{
	glfwSetKeyCallback(win->internal_window, win_key_input);
	glfwSetCursorPosCallback(win->internal_window, win_mouse_move);
	glfwSetMouseButtonCallback(win->internal_window, win_mouse_button);
	glfwSetScrollCallback(win->internal_window, win_scroll);
}
