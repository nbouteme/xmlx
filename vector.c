#include <stdlib.h>
#include <string.h>
#include "vector.h"

t_vector	*init_vector(t_vector *self, unsigned long e_size)
{
	self->data = malloc(2 * e_size);
	self->capacity = 2;
	self->size = 0;
	self->e_size = e_size;
	return (self);
}

void		resize_vector(t_vector *self, unsigned long new_cap)
{
	void *tmp;

	if (new_cap < self->size)
		self->size = new_cap;
	tmp = self->data;
	free(self->data);
	self->data = malloc(new_cap * self->e_size);
	memcpy(self->data, tmp, self->capacity * self->e_size);
	self->capacity = new_cap;
}

void		vector_pushback(t_vector *self, void *new_elem)
{
	if (self->size >= self->capacity)
		resize_vector(self, self->capacity * 2);
	memcpy(self->data + (self->e_size * self->size), new_elem, self->e_size);
	++self->size;
}

void		delete_vector(t_vector *self)
{
	free(self->data);
}
