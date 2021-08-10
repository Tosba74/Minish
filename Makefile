# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/11 11:23:45 by bmangin           #+#    #+#              #
#    Updated: 2021/04/24 22:24:46y bmangin          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# ******************************************************* #
# *******************   VARIABLES   ********************* #
# ******************************************************* #

NAME = minishell

override PATH_L		:= libft
override PATH_I		:= includes
override PATH_S		:= srcs
override PATH_B		:= .bin

FILES		= error.c main.c

SRCS		= ${addprefix ${PATH_S}/, ${FILES}}
OBJS		= ${addprefix ${PATH_B}/, ${notdir ${SRCS:.c=.o}}}

HEADER	 	:= error.h minish.h
INC			= ${addprefix ${PATH_I}/, ${HEADER}}

LIBFT_NAME	= ${PATH_L}.a
LIBFT_INC	= ${PATH_L}.h
LIBFT_H		= ${addprefix ${PATH_L}/, ${PATH_I}}
LIBFT		= ${addprefix ${PATH_L}/, ${LIBFT_NAME}}
INC_LFT		= ${addprefix ${LIBFT_H}/, ${LIBFT_INC}}

# ******************************************************* #
# *******************   COMMANDES   ********************* #
# ******************************************************* #

CC			:= clang
CFLAGS		:= ${CC} -Wall -Wextra -Werror
CFLAGS_FS	:= ${CC} -Wall -Wextra -Werror -g3 -fsanitize=address
LLFT		:= -L${PATH_L}
LFT			:= -lft
INCS		:= -I${PATH_I} -I${LIBFT_H}
MAKE		:= make -C
CP			:= cp 
RM			:= rm -rf

# ******************************************************* #
# ********************   MAKE SHIT   ******************** #
# ******************************************************* #

all:		lib ${NAME}

lib:		crea_b
		${MAKE} ${PATH_L}

${PATH_B}/%.o:	${PATH_S}/%.c ${INC} ${INC_LFT}
		${CFLAGS} ${INCS} -c $< -o $@

${NAME}:	${OBJS} ${INC} ${INC_LFT}
		${CFLAGS} ${INCS} ${LLFT} ${OBJS} -o $@ ${LFT}

fs:			${SRCS} ${INC} ${INC_LFT} 
		${CFLAGS_FS} ${INCS} ${LLFT} ${OBJS} -o ${NAME} ${LFT}

crea_b :
		${shell mkdir -p ${PATH_B}}
	
clean:
		${RM} ${PATH_B}

fclean:		clean
		${MAKE} ${PATH_L} fclean
		${RM} ${LIBFT}
		${RM} ${NAME}

re:			fclean all

seg:		fclean lib fs

op:			fclean lib opti

fast:		fclean lib speed

.PHONY: all lib op opti fast speed fsanit fs clean fclean re bonus
