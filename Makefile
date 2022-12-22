# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 00:32:16 by tliangso          #+#    #+#              #
#    Updated: 2022/12/22 14:24:58 by tliangso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIRSRC	=	./

SRC		= ft_printf.c

BONUS	=

EXTRA	=

SRCS	= ${addprefix ${DIRSRC}, ${SRC}}

BONUS_SRCS = ${addprefix ${DIRSRC}, ${BONUS}}

EXTRA_SRCS = ${addprefix ${DIRSRC}, ${EXTRA}}

OBJS	= ${SRCS:.c=.o}

BONUS_OBJS = ${BONUS_SRCS:.c=.o}

EXRTA_OBJS = ${EXTRA_SRCS:.c=.o}

HEAD	= .

NAME	= libftprintf.a

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c -I ${HEAD} $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}

bonus:		${OBJS} ${BONUS_OBJS}
			ar rc ${NAME} ${OBJS} ${BONUS_OBJS}

extra:	${OBJS} ${BONUS_OBJS} ${EXRTA_OBJS}
			ar rc ${NAME} ${OBJS} ${BONUS_OBJS} ${EXRTA_OBJS}

clean:
			${RM} ${OBJS} ${BONUS_OBJS} ${EXRTA_OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean	all

.PHONY:		all	clean	fclean	re
