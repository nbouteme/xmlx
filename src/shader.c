#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "xmlx_int.h"

#include <stdlib.h>
#include <stdio.h>

const char *vshader =
	"#version 150\n"
	"in vec2 position;\n"
	"in vec2 itexco;\n"
	"out vec2 otexco;\n"
	"void main()\n"
	"{\n"
	"	otexco = itexco;\n"
	"    gl_Position = vec4(position, 0.0, 1.0);\n"
	"}\n";

const char *fshader =
	"#version 150\n"
	"in vec2 otexco;\n"
	"out vec4 ocol;\n"
	"uniform sampler2D tex;\n"
	"void main()\n"
	"{\n"
	"    ocol = texture(tex, otexco);\n"
	"}\n";

t_shader gen_shader()
{
	t_shader ret;

	ret.vsh = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(ret.vsh, 1, &vshader, NULL);
	glCompileShader(ret.vsh);
	ret.fsh = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(ret.fsh, 1, &fshader, NULL);
	glCompileShader(ret.fsh);
	GLint isCompiled = 0;
	glGetShaderiv(ret.fsh, GL_COMPILE_STATUS, &isCompiled);
	if (!isCompiled)
	{
		GLint maxLength = 0;
		glGetShaderiv(ret.fsh, GL_INFO_LOG_LENGTH, &maxLength);
		char *n = calloc(1, maxLength);
		glGetShaderInfoLog(ret.fsh, maxLength, 0, n);
		exit(1);
	}
	ret.prog = glCreateProgram();
	glAttachShader(ret.prog, ret.vsh);
	glAttachShader(ret.prog, ret.fsh);
	glBindFragDataLocation(ret.prog, 0, "ocol");
	glLinkProgram(ret.prog);
	GLint isLinked = 0;
	glGetProgramiv(ret.prog, GL_LINK_STATUS, &isLinked);
	if (!isLinked)
	{
		GLint maxLength = 0;
		glGetProgramiv(ret.prog, GL_INFO_LOG_LENGTH, &maxLength);
		char *n = malloc(maxLength);
		glGetProgramInfoLog(ret.prog, maxLength, 0, n);
		exit(1);
	}
	glUseProgram(ret.prog);
	GLint posAttrib = glGetAttribLocation(ret.prog, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 16, 0);
	glEnableVertexAttribArray(posAttrib);
	GLint texAttrib = glGetAttribLocation(ret.prog, "itexco");
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 16, (void*)8);
	glEnableVertexAttribArray(texAttrib);
	return (ret);
}

t_mesh gen_screen()
{
	t_mesh ret;
	float vertices[] = {
		-1.0f,	1.0f, 0.0f, 0.0f,
		1.0f,	1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 1.0f
	};
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };
	glGenVertexArrays(1, &ret.vao);
	glGenBuffers(1, &ret.vbo);
	glBindVertexArray(ret.vao);
	glBindBuffer(GL_ARRAY_BUFFER, ret.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glGenBuffers(1, &ret.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	return (ret);
}
