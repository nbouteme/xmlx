INCLUDE_DIRS = $(PKG_DIR)/include
LFLAGS = -L$(PKG_DIR) -lxmlx -ldl
LFLAGS_Darwin = -framework OpenGL -framework AppKit -lglfw3
LFLAGS_Linux = -lGL -lglfw
CFLAGS = $(addprefix -I,$(INCLUDE_DIRS))
