# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/14 19:07:44 by bmangin           #+#    #+#              #
#    Updated: 2021/10/15 03:06:35 by bmangin          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# ******************************************************* #
# *******************   VARIABLES   ********************* #
# ******************************************************* #

NAME = minishell

override PATH_L		:= libft
override PATH_I		:= includes
override PATH_S		:= srcs
override PATH_O		:= .bin
override PATH_P		:= parsing
override PATH_E		:= engine
override PATH_B		:= builtins

override VPATH		:= ${addprefix ${PATH_S}/, ${PATH_P}} \
					${addprefix ${PATH_S}/, ${PATH_E}} \
					${addprefix ${PATH_S}/, ${PATH_B}} \
					${PATH_S}

override FILES_P	:= parser.c lexer.c init_env.c \
					pars_tools.c env_tools.c history.c \
					tokenizator.c
override FILES_E	:= exec.c pipe_tools.c
override FILES_B	:= b_env.c b_history.c b_echo.c b_cd.c b_exit.c \
					b_export.c b_pwd.c b_unset.c
override FILES_M	:= prompt.c debug.c debug_tools.c error.c main.c

FILES		= ${addprefix ${PATH_P}/, ${FILES_P}} \
			${addprefix ${PATH_E}/, ${FILES_E}} \
			${addprefix ${PATH_B}/, ${FILES_B}} \
			${FILES_M}

SRCS		= ${addprefix ${PATH_S}/, ${FILES}}
OBJS		= ${addprefix ${PATH_O}/, ${notdir ${SRCS:.c=.o}}}

HEADER	 	:= error.h tools.h minish.h 
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
CCF			:= ${CC} -Wall -Wextra -Werror -g 
CF_FS		:= ${CCF} -g3 -fsanitize=address
CF_DB		:= ${CCF} -glldb -fsanitize=address
LLFT		:= -L${PATH_L}
LFT			:= -lft -lreadline
INCS		:= -I${PATH_I} -I${LIBFT_H}
MAKE		:= make -C
CP			:= cp 
RM			:= rm -rf
NORM		:= norminette

# ******************************************************* #
# *********************   COLOR!!   ********************* #
# ******************************************************* #

.SILENT:

_BLACK	= \x1b[30m
_R		= \x1b[31m
_G		= \x1b[32m
_Y		= \x1b[33m
_B		= \x1b[34m
_P		= \x1b[35m
_C		= \x1b[36m
_E		= \x1b[0m

# ******************************************************* #
# ********************   MAKE SHIT   ******************** #
# ******************************************************* #

all:		lib ${NAME} minish

lib:		crea_b
		${MAKE} ${PATH_L}

${PATH_O}/%.o:	%.c ${INC} ${INC_LFT}
		${CCF} ${INCS} -c $< -o $@
		printf "\e[?35l${_Y}$< >>> ${_G}$@${_E} \e[0m%20s\r" " "

${NAME}:	${OBJS} ${INC} ${INC_LFT}
		${CCF} ${INCS} ${LLFT} ${OBJS} -o $@ ${LFT}
		printf "\n"
		clear

fs:			${OBJS} ${INC} ${INC_LFT}
		${CF_FS} ${INCS} ${LLFT} ${OBJS} -o ${NAME} ${LFT}

db:			${OBJS} ${INC} ${INC_LFT} 
		${CF_DB} ${INCS} ${LLFT} ${OBJS} -o ${NAME} ${LFT}
		lldb ${NAME}

crea_b :
		${shell mkdir -p ${PATH_O}}
	
clean:
		${RM} ${PATH_O}

fclean:		clean
		${MAKE} ${PATH_L} fclean
		${RM} ${LIBFT}
		${RM} ${NAME}

re:			fclean all minish

seg:		fclean lib fs minish

lldb:		fclean lib db minish

op:			fclean lib opti minish

fast:		fclean lib speed minish

norm :
			${NORM} ${SRCS}
			${NORM} ${INC}
			
minish:
		printf "\n"
		printf "\n"
		printf "${_C}        :::   :::  :::::::::: ::::    ::: :::::::: ::::::::: :::    ::: ${_E}\n"
		printf "${_C}      :+:+: :+:+:     :+:    :+:+:   :+:    :+:   :+:   :+: :+:    :+:  ${_E}\n"
		printf "${_C}    +:+ +:+:+ +:+    +:+    :+:+:+  +:+    +:+   +:+       +:+    +:+   ${_E}\n"
		printf "${_C}   +#+  +:+  +#+    +#+    +#+ +:+ +#+    +#+   +#++:++#+ +#++:++#++    ${_E}\n"
		printf "${_C}  +#+       +#+    +#+    +#+  +#+#+#    +#+         +#+ +#+    +#+     ${_E}\n"
		printf "${_C} #+#       #+#    #+#    #+#   #+#+#    #+#   #+#   #+# #+#    #+#      ${_E}\n"
		printf "${_C}###       #################    ############# ######### ###    ###       ${_E}\n"
		printf "${_B}                                                           is ready !!!${_E}\n"
		printf "\n"
	
.PHONY: all lib fsanit fs db lldb clean fclean re bonus norm minish
