NAME = xmlx
TYPE = lib

CFLAGS = -Wall -Wextra -Werror -O3 -Iinclude
MODULES = src

INCLUDE_DIRS = $(PKG_DIR)/includes

OUTPUT = $(PKG_DIR)/libxmlx.a
