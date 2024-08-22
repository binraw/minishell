NAME = minishell


SRCS_FILE = pipe/main.c pipe/utils.c pipe/error.c mini/print.c mini/lst_pipe.c builtins/command_cd.c  mini/redir.c mini/pipe_utils.c \
mini/env.c mini/utils_node.c builtins/export.c builtins/unset.c mini/utils_node_cmd.c parse/init_parsing.c parse/redir_get_last.c \
parse/utils_lst_redir.c parse/fill_redirs.c parse/ft_strtok.c parse/cmd_manage_env.c mini/rdocs.c mini/signal.c builtins/command_env.c \
builtins/echo.c parse/manage_quotes.c parse/parsing_error.c mini/road_builtin.c builtins/exit.c mini/get_next_line.c mini/get_next_line_utils.c \
mini/free_alloc.c builtins/utils_export.c builtins/more_export.c builtins/utils_cd.c builtins/assets_cd.c builtins/command_pwd.c \
mini/open_redir.c mini/value_redir.c mini/redir_one_child.c mini/process_builtins.c mini/utils_builtins.c mini/utils_signal.c \
mini/assets_pipe.c mini/process_pipe.c


CC = cc
MD = mkdir -p
CFLAGS = -Wall -Wextra -Werror -g


DIR_SRC = src/
DIR_OBJ = .object/


LIBFT = ./lib/libft/libft.a

OBJS = $(patsubst %.c, ${DIR_OBJ}%.o, ${SRCS})
SRCS = $(addprefix ${DIR_SRC},${SRCS_FILE})
OBJS_BONUS = $(patsubst %.c, ${DIR_OBJ_BONUS}%.o, ${SRCS_BONUS})


RM = rm -Rf

all: libft ${NAME}

${NAME}: ${OBJS} ${LIBFT}
	$(CC) $(OBJS) $(LIBFT) -lreadline  -o $(NAME)


${DIR_OBJ}%.o: %.c ${DIR_SRC}/pipe/pipex.h Makefile ${LIBFT}
	mkdir -p $(shell dirname $@)
	$(CC) ${CFLAGS} -c $< -o $@


libft: 
	${MAKE} -C ./lib/libft all

clean:
	${MAKE} -C ./lib/libft clean
	${RM} ${DIR_OBJ}

fclean: clean
	${MAKE} -C ./lib/libft fclean
	${RM} ${NAME}

re: fclean all



.PHONY: all clean fclean re 
