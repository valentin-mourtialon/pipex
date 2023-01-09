# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmourtia <vmourtia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 16:16:53 by valentin          #+#    #+#              #
#    Updated: 2023/01/09 10:51:53 by vmourtia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =		mandatory/main.c \
			mandatory/init.c \
			mandatory/free.c \
			mandatory/close.c \
			mandatory/child.c \
			mandatory/alert.c

STDLIB  =	mandatory/stdlib/ft_split.c \
			mandatory/stdlib/ft_strlen.c \
			mandatory/stdlib/ft_strjoin.c \
			mandatory/stdlib/ft_strncmp.c

OBJS = 		${SRCS:c=o} ${STDLIB:c=o}

NAME =		pipex

CC =		gcc

CFLAGS =	-Wall -Werror -Wextra

INC =		-I./includes/

RM =		rm -f

all :		${NAME}

%.o : %.c
			${CC} ${CFLAGS} ${INC} -c $< -o $@ -g


${NAME} :	${OBJS}
			${CC} ${OBJS} -o ${NAME}

clean :
			${RM} ${OBJS}

fclean :	clean
			${RM} ${NAME}

re :		fclean all

.PHONY :	all clean fclean re

