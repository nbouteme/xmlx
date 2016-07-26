SYSTEM = $(shell uname)

ifeq ($(SYSTEM),Linux)

define redout
$(shell echo -e '\033[0;31m'$1'\033[0m')
endef

define blueout
$(shell echo -e '\033[0;34m'$1'\033[0m')
endef

define greenout
$(shell echo -e '\033[0;32m'$1'\033[0m')
endef

endif

src_from_modules = $(shell find $1 -type f | grep -v '/\.' | grep '.c$$')
nsrc_from_modules = $(shell find $1 -type f | grep -v '/\.' | grep '.c$$' | wc -l)
file_exist = $(shell test -e $1 && echo "exist")
make_dep = $(shell make -C $(CURNAME))
eq = $(and $(findstring $(1),$(2)),$(findstring $(2),$(1)))
get_val_in_file =	$(if $(call file_exist,$1),\
						$(shell cat $1  | sed -n "s/$2.=.\(.*\)/\1/p"))
int_length = $(shell echo "(l($1) / l(10)) + 1" | bc -l | head -c 1)

length = $(shell echo $1 | wc -c)
per = $(shell echo $1 / $2 \* 100 | bc)
div = $(shell echo $1 / $2 | bc)
add = $(shell echo $1 + $2 | bc)

generate_header = $(shell \
	LEN=$(call length,$1); \
	LEN2=`echo $$LEN / 2 | bc`;\
	LEN3=`echo 27 - $$LEN2 | bc`;\
	LEN4=`echo $$LEN3 % 2 | bc`;\
	printf "%*s" $$LEN3 "" | tr ' ' '-';\
	printf "%s" $1 ;\
	printf "%*s" $$LEN3 "" | tr ' ' '-';\
	printf "%*s" $$LEN4 "" | tr ' ' '-';\
)

BUILD_CFG := $(shell ls ./config/build_cfg.mk 2> /dev/null)
LINK_CFG := $(shell ls ./config/link_cfg.mk 2> /dev/null)
SUBFOLDERS := $(shell find `pwd` -maxdepth 1 -type d ! -path `pwd` ! -path `pwd`/config ! -path `pwd`/build  | grep -v '/\.')

CURDIR := $(shell pwd)

ifeq ($(RUNDIR),)
	RUNDIR := $(CURDIR)
else
	SUBFOLDERS += $(shell find $(RUNDIR) -maxdepth 1 -type d ! -path $(RUNDIR) ! -path $(RUNDIR)/config | grep -v '/\.')
endif

ifeq ($(BUILD_CFG),)
$(error $(call redout,Missing build config file))
endif

ifeq ($(LINK_CFG),)
$(error $(call redout,Missing link config file))
endif

PKG_DIR = .

include $(BUILD_CFG)

ifeq ($(NAME),)
$(error $(call redout,Missing project name))
endif

ifeq ($(OUTPUT),)
$(error $(call redout,Missing project output))
endif

ifeq ($(MODULES),)
$(error $(call redout,Missing project modules))
endif

ifeq ($(TYPE),)
$(error $(call redout,Missing project type))
endif

CUR_NAME := $(NAME)
CUR_INCLUDE_DIRS := $(INCLUDE_DIRS)
CUR_OPTS := $(OPTS)
CUR_TYPE := $(TYPE)
CUR_DEPS := $(DEPS)
CUR_OUTPUT := $(OUTPUT)
CUR_MODULES := $(MODULES)

LFLAGS_ACC := $(LFLAGS)
CFLAGS_ACC := $(addprefix -I,$(INCLUDE_DIRS)) $(CFLAGS)

S_FLAGS_ACC := $(SFLAGS_$(SYSTEM))

all: print_head $(CUR_OUTPUT) 

print_head:
	$(info $(call redout,$(call generate_header,[Building\ $(CUR_NAME)...])))

define GEN_DEP_RULE
$1:
	make -C $2 RUNDIR=$(RUNDIR)
endef

$(foreach dep,$(CUR_DEPS), \
	$(foreach dir,$(SUBFOLDERS), \
		$(eval CURNAME:=$(call get_val_in_file,$(dir)/config/build_cfg.mk,NAME))\
		$(if $(call file_exist,$(dir)/config/build_cfg.mk),\
			$(eval \
				CURNAME=$(call get_val_in_file,$(dir)/config/build_cfg.mk,NAME)\
				$(if $(call eq,$(CURNAME),$(dep)), \
					$(if $(shell make -q -C $(CURNAME) RUNDIR=$(RUNDIR) &> /dev/null || echo "not_updated"),\
						$(shell make -C $(CURNAME) RUNDIR=$(RUNDIR)))\
					$(eval $(dep)_FOUND=true) \
					$(eval PKG_DIR=$(dir)) \
					$(eval include $(dir)/config/link_cfg.mk)\
					$(eval LFLAGS_ACC += $(LFLAGS))\
					$(eval CFLAGS_ACC += $(CFLAGS))\
					$(eval SFLAGS_ACC += $(SFLAGS_$(SYSTEM))))\
					$(eval include $(dir)/config/build_cfg.mk)\
					$(eval DEP_ACC += $(OUTPUT))\
					$(eval $(call GEN_DEP_RULE,$(OUTPUT),$(dir)))\
			)\
		)\
		$(if $($(dep)_FOUND),,$(error Dependency $(dep) not found.))\
	)\
)

SRCS := $(call src_from_modules, $(CUR_MODULES))
NSRCS := $(call nsrc_from_modules, $(CUR_MODULES))
PNSRCS := 0
OBJS := $(SRCS:.c=.o)
BUILD_DEPS = build

build:
	$(info $(call blueout,Building temporary build directory hierachy...))
	@mkdir -p build

get_n = $(PNSRCS)
inc_n = $(eval PNSRCS=$(call add,$(PNSRCS),1))

define BUILD_DIR_RULE
build/$1: build
	@mkdir -p build/$1

build/$1/%.o: $1/%.c
	$$(call inc_n)
	@printf "\e[32m[%*s/%s]\e[0m Compiling \e[34m%-31.31s\e[0m" $(call int_length,$(NSRCS)) $$(call get_n) $(NSRCS) $(notdir $$@)...
	@$(CC) $$(CFLAGS_ACC) -c $$^ -o $$@ $$(SFLAGS_ACC)
	@printf "\e[32m[✓]\e[0m\n"
endef

$(foreach mod,$(CUR_MODULES),\
	$(eval BUILD_DEPS += build/$(mod))\
	$(eval $(call BUILD_DIR_RULE,$(mod)))\
)

$(CUR_OUTPUT): $(BUILD_DEPS) $(DEP_ACC) $(addprefix build/,$(OBJS))
	@printf "\e[31m------------------------------------------------------\e[0m\n"
	@printf "\e[34mLinking %s..." $(CUR_OUTPUT)
ifeq ($(CUR_TYPE),prog)
	@$(CC) $(addprefix build/,$(OBJS)) -o $(CUR_OUTPUT) $(LFLAGS_ACC) $(SFLAGS_ACC)
else
	@ld -r $(addprefix build/,$(OBJS)) -o $(OUTPUT)
endif
	@printf "\e[32m✓\e[0m\n"

.PHONY: clean fclean re all print_head

clean:
	@/bin/rm -rf $(addprefix build/,$(OBJS))

fclean: clean
	@/bin/rm -rf $(CUR_OUTPUT) build

re: fclean all
