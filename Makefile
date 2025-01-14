# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lolaparr <lolaparr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 20:10:20 by lolaparr          #+#    #+#              #
#    Updated: 2023/10/16 20:10:20 by lolaparr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
SRC_DIR		:= src
BUILD_DIR:= .build
SRCS		:=  builtins/cd.c \
				builtins/echo.c \
				builtins/env.c \
				builtins/export.c \
				builtins/pwd.c \
				builtins/unset.c \
				error/error.c \
				error/exit.c \
				error/free.c \
				exec/builtin.c \
				exec/exec.c \
				main/exec_main.c \
				main/main.c \
				main/parsing_main.c \
				parsing/arg.c \
				parsing/does_it.c \
				parsing/heredoc.c \
				parsing/init.c \
				parsing/parsing.c \
				parsing/qparsing.c \
				signal/signal.c \
				utils/env_utils.c \
				utils/export_utils.c \
				utils/export_variable_utils.c \
				utils/export_very_utils.c \
				utils/filter.c \
				utils/free_utils.c \
				utils/gestion_memory.c \
				utils/utils_builtin.c \
				utils/utils_does_it.c \
				utils/utils_exec.c \
				utils/utils_parsing.c \
				utils/utils.c \

SRCS		:= $(SRCS:%=$(SRC_DIR)/%)
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

CC			:= cc -g3
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -MMD -MP -I include
RM			:= rm -rf
MAKEFLAGS	+= --no-print-directory
DIR_DUP		= mkdir -p $(@D)
LIBRARIES	:= -L libft -lft
INCLUDES	:= -Ilibft/include

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(OBJS) $(LIBRARIES) -lreadline -o $(NAME)
	$(info CREATED $(NAME))
	clear

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< -o $@
	$(info CREATED $@)

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)
	make -C libft clean
	clear

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean
	clear

re: clean all

.PHONY: all re clean fclean
.SILENT:
