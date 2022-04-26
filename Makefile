NAME				=	ft_nm
AUTHOR				:=	gboucett

PATH_INC			:=	-I./include
PATH_SRCS			:=	src
PATH_OBJS			:=	objs

CC					:=	gcc
RM					:=	@rm -f
MKDIR				:=	@mkdir -p

CFLAGS				:=	-Wall -Werror -Wextra -g3 -gdwarf-2 -fdiagnostics-color=always
LDFLAGS				:=	-g3

ifeq ($(PLATFORM),32)
	NAME			= ft_nm_x86
	CFLAGS			+=	-m32
	LDFLAGS			+=	-m32
	PATH_OBJS		=	objs/32bits
else
	CFLAGS			+=	-m64
	LDFLAGS			+=	-m64
	PATH_OBJS		=	objs/64bits
endif

BASENAME			:=	main.c						\
						ft_nm.c						\
						help.c						\
						parse_args.c				\
						options/init.c				\
						options/get_option.c		\
						options/print_flags.c		\
						utils/printer.c				\
						utils/free_args.c			\
						utils/string.c				\
						core/core.c					\

SRCS				:=	$(addprefix $(PATH_SRCS)/, $(BASENAME))
OBJS				:=	$(addprefix $(PATH_OBJS)/, $(BASENAME:%.c=%.o))
DEPS				:=	$(addprefix $(PATH_OBJS)/, $(BASENAME:%.c=%.d))
# $(info $(DEPS))
# exit 1

#######################################################################################################################################################
#######################################################################################################################################################


PROGRESS			:=	0
NO_OF_FILES			:=	$(words $(SRCS))

COLOR_HEADER		= 	\033[1;31m
COLOR_DONE		= 	\033[1;32m
COLOR_HEADER_CONT	= 	\033[38;5;247m
COLOR_FILE			= 	\033[34m
COLOR_PERCENT		= 	\033[1;94m
CLEAR_COLOR			=	\033[m

NAME_PRINT			=	$(COLOR_HEADER)Name$(CLEAR_COLOR)
PROGRESS_BAR_CHAR	=	$(COLOR_PERCENT)▰$(CLEAR_COLOR)
REMAINING_BAR_CHAR 	=	$(COLOR_PERCENT)╍$(CLEAR_COLOR)

define show_git_infos =
	$(eval TMP := $(shell [ -d .git ] && echo "true"))
	$(eval __REPOSITORY_URL__ := $(if $(TMP),$(shell git remote get-url origin 2> /dev/null),Not a git repository))
	$(eval __BRANCH__ := $(if $(TMP), $(shell git branch --show-current 2> /dev/null), $(echo "Not a git repository")))
	$(eval __REPOSITORY__ := $(if $(__REPOSITORY_URL__), $(__REPOSITORY_URL__),Unknown repository))
	$(eval TMP_REPOS := $(COLOR_HEADER)Git repository$(CLEAR_COLOR):$(COLOR_HEADER_CONT)$(subst :,!,$(__REPOSITORY__))$(CLEAR_COLOR))
	$(eval TMP_BRANCH := $(if $(TMP),$(COLOR_HEADER)Git branch$(CLEAR_COLOR):$(COLOR_HEADER_CONT)$(__BRANCH__)$(CLEAR_COLOR)))
endef

define init_makefile =
	$(eval TMP_NAME = $(NAME_PRINT):$(COLOR_HEADER_CONT)$(NAME)$(CLEAR_COLOR))
	$(eval TMP_AUTHOR = $(COLOR_HEADER)Author$(CLEAR_COLOR):$(COLOR_HEADER_CONT)$(AUTHOR)$(CLEAR_COLOR))
	$(eval TMP_CC = $(COLOR_HEADER)Compiler$(CLEAR_COLOR):$(COLOR_HEADER_CONT)$(subst @,,$(CC))$(CLEAR_COLOR))
	$(eval TMP_FLAGS = $(COLOR_HEADER)Flags$(CLEAR_COLOR):$(COLOR_HEADER_CONT)$(CFLAGS)$(CLEAR_COLOR))
	$(eval TMP_LINKER = $(COLOR_HEADER)Linker flags$(CLEAR_COLOR):$(COLOR_HEADER_CONT)$(LDFLAGS)$(CLEAR_COLOR))
	$(show_git_infos)

	@if [ $(PROGRESS) -eq 0 ]; then \
		clear; \
		tput civis;\
		/bin/echo -e '$(TMP_NAME)\n$(TMP_AUTHOR)\n$(TMP_CC)\n$(TMP_FLAGS)\n$(TMP_LINKER)\n$(TMP_REPOS)$(if $(TMP_BRANCH),\n$(TMP_BRANCH))' \
		| sed -e 's/^ //' | column -t -s':' -o '       ' | tr '!' ':'; \
		echo ""; \
	fi
endef

define draw_bar =
	@for i in $(shell seq 1 $(1)); do \
		/bin/echo -en '$(PROGRESS_BAR_CHAR)'; \
	done
	@for i in $(shell seq $(1) 99); do \
		/bin/echo -en '$(REMAINING_BAR_CHAR)'; \
	done
	@echo
endef

define clear_line =
	if [ -d .git ]; then \
		tput cup 8 0; \
	else \
		tput cup 7 0; \
	fi; \
	tput el
endef

define show_progress =
	$(eval PROGRESS = $(shell expr $(PROGRESS) + 1))
	$(eval TMP := $(shell echo "scale=3;$(PROGRESS) / $(NO_OF_FILES) * 100" | bc))
	$(eval TMP := $(shell echo "$(TMP)" | sed 's/\..*//'))

	@$(clear_line)
	@printf "[$(COLOR_PERCENT)%4d %-2s$(CLEAR_COLOR)]%13s $(COLOR_FILE)$(subst objs/,,$@)$(CLEAR_COLOR)\n" $(TMP) % Compiling
	$(call draw_bar,$(TMP))
endef


#######################################################################################################################################################
#######################################################################################################################################################


$(PATH_OBJS)/%.o:	$(PATH_SRCS)/%.c
					$(init_makefile)
					$(show_progress)

					$(shell mkdir -p $(dir $@))
					$(eval TMP_COMP := $(shell $(CC) $(CFLAGS) $(PATH_INC) -MMD -c $< -o $@ 2> /tmp/compilation_error_$(subst /,_,$@) && echo 'true'))
					@if [ '$(TMP_COMP)' != 'true' ]; then \
						tput cnorm; \
						echo ""; \
						cat /tmp/compilation_error_$(subst /,_,$@); \
						exit 2; \
					fi
					@if [ $(PROGRESS) -eq $(NO_OF_FILES) ]; then \
						$(clear_line); \
						tput cnorm; \
					fi

all:				$(NAME)

-include $(DEPS)

$(NAME):			$(OBJS)
					$(init_makefile)
					@tput cnorm
					@echo "Linking $(NAME)..."
					@$(CC) $(LDFLAGS) $(OBJS) -o $@
					@$(clear_line)
					@/bin/echo -e "Compilation done $(COLOR_DONE)\xE2\x9C\x94$(CLEAR_COLOR)"

clean:
					$(RM) -r $(PATH_OBJS)

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

init:
					$(init_makefile)

.PHONY:				all clean fclean re
