# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbelle <hbelle@student.42angouleme.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 17:52:23 by hbelle            #+#    #+#              #
#    Updated: 2024/01/27 16:26:38 by hbelle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRCS	=	main.c \
	utils_ext/ft_isdigit.c \
	utils_ext/ft_atoi.c \
	srcs/parse/check_arg.c \
	srcs/utils/time_handle.c \
	srcs/utils/printf_handle.c \
	srcs/data/init.c \
	srcs/data/free_end.c \
	srcs/algo/monitor_death.c \
	srcs/algo/fork_handle.c \
	srcs/data/create_data.c \
	srcs/algo/routine.c \
	srcs/algo/eat_sleep_think.c \
	
OBJ_DIR = .o
OBJTS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

RM	=	rm -f
HEADER =	-I includes

CFLAGS = -Wall -Wextra -Werror -g

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@cc $(CFLAGS) $(HEADER) -c  $< -o $@
	@if test -s $*.c; then\
			echo "\033[01m\033[35mCompiling ⌛\033[00m\
			\033[36m$*.c\033[032m  [OK] ✅ \033[00m";\
			else \
			echo "\033[01m\033[33mCompiling \033[00m\
			\033[36m$*.c\033[00m\  [Error] ❌ \033[00m"; fi

$(NAME): $(OBJTS)
	@cc -o $(NAME) $(OBJTS) $(CFLAGS) $(HEADER)
	@echo "\033[01m\033[4;33mCompilation done\033[00m\033[1;31m ✒▶\033[00m\033[1;32m ./${NAME}\033[00m"


all:	${NAME}

clean:
	@${RM} -r $(OBJ_DIR)
	@echo "\033[01m\033[31mRemoving objects ...\033[00m"

fclean:	clean
	@${RM} ${NAME}
	@echo "\033[01m\033[31mRemoving exec : ${NAME} ...\033[00m"

re:	fclean all

.PHONY: all clean fclean re