NAME = libxmlx.a

SRCS = shader.c  vector.c  xmlx_init.c  xmlx_win_callbacks.c  xmlx_window.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Iinclude -Ofast

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJS) Makefile
	ld -r $(OBJS) -o $(NAME)
.PHONY: clean fclean re
