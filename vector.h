#ifndef VECTOR_H
# define VECTOR_H

typedef struct	s_vector
{
	void *data;
	unsigned long capacity;
	unsigned long size;
	unsigned long e_size;
}				t_vector;

void		delete_vector(t_vector *self);
void		resize_vector(t_vector *self, unsigned long new_cap);
t_vector	*init_vector(t_vector *self, unsigned long e_size);
void		vector_pushback(t_vector *self, void *new_elem);

#endif
