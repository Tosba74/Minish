# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/22 23:19:50 by bmangin           #+#    #+#              #
#    Updated: 2021/07/24 11:49:50 by bmangin          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# ******************************************************* #
# *********************   VARIABLES   ******************* #
# ******************************************************* #

NAME		:= pipex

PATH_L		:= libft
PATH_I		:= includes
PATH_S		:= srcs
PATH_B		:= .bin

VPATH	= ${PATH_I} ${PATH_S} ${PATH_B} ${PATH_L}

FILES		= main.c pipex.c tools.c

SRCS		= ${addprefix ${PATH_S}/, ${FILES}}
OBJS		= ${FILES:.c=.o}
BIN			= ${addprefix ${PATH_B}/, ${OBJS}}

H_FILES		:= pipex.h
HEADER		= ${addprefix ${PATH_I}/, ${H_FILES}}

LIBFT_NAME	:= ${PATH_L}.a
LIBFT		= ${addprefix ${PATH_L}/, ${LIBFT_NAME}}

# ******************************************************* #
# *******************   COMMANDES   ********************* #
# ******************************************************* #

CC			:= clang
FLAGS		:= -Wall -Wextra -Werror
CCF			:= ${CC} ${FLAGS}
INC			:= -I${PATH_I} -I${PATH_L}/${PATH_I}
FS			:= -g3 -fsanitize=address
FLIB		:= -L${PATH_L}
LFT			:= -lft
MAKE		:= make -C
CP			:= cp 
MKDIR		:= mkdir -p
RM			:= rm -rf
NORM		:= norminette

# ******************************************************* #
# *******************   MAKE SHIT   ********************* #
# ******************************************************* #

all:	${NAME}

lib:		crea_b
		${MAKE} ./${PATH_L}

${PATH_B}/%.o:	${PATH_S}/%.c ${HEADER}
		${CCF} ${INC} -c $< -o $@

${NAME}:	lib ${BIN}
		${CCF} ${FLIB} ${BIN} -o $@ ${LFT}

fs:	${BIN} ${HEADER}
		${CCF} ${FS} ${FLIB} ${BIN} -o $@ ${LFT}

crea_b :
	${shell mkdir -p ${PATH_B}}

clean:
	$(MAKE) ./$(PATH_L) clean
	$(RM) $(PATH_B)

fclean: clean
	$(MAKE) ./$(PATH_L) fclean
	$(RM) $(NAME) $(NAME).dSYM

re: fclean all

seg: fclean fs

norm:
	${NORM} ${SRCS} ${HEADER}
	$(MAKE) ./$(PATH_L) norm
	
.PHONY:		all lib crea_b bonus clean fclean re seg norm