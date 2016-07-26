INCLUDE_DIRS = $(PKG_DIR)/include
LFLAGS = -L$(PKG_DIR) -lxmlx -ldl -lGL -lglfw
CFLAGS = $(addprefix -I,$(INCLUDE_DIRS))
