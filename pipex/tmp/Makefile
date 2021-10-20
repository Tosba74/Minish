# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/11 11:23:45 by bmangin           #+#    #+#              #
#    Updated: 2021/07/23 21:07:30 by bmangin          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = pipex

override PATH_L		:= libft
override PATH_I		:= includes
override PATH_S		:= srcs
override PATH_B		:= .bin

override FILES		:= main.c pipex.c tool.c

SRCS		= ${addprefix ${PATH_S}/, ${FILES}}
OBJS		= ${addprefix ${PATH_B}/, ${FILES:.c=.o}}

VPATH		= ${PATH_S} ${PATH_I} ${PATH_B} ${PATH_L}

H_FILES		:= pipex.h
HEADER		= ${addprefix ${PATH_I}/, ${H_FILES}}

LIBFT_NAME	:= ${PATH_L}.a
LIBFT		= ${addprefix ${PATH_L}/, ${LIBFT_NAME}}

CC			:= clang
FLAGS		:= -Wall -Wextra -Werror
#INC			:= -I${PATH_I}
INC			:= -I${PATH_I} -I${PATH_L}/${PATH_I}
FS			:= -g3 -fsanitize=address
FLIB		:= -L${PATH_L}
LFT			:= -lft
MAKE		:= make -C
CP			:= cp 
RM			:= rm -rf
NORME		:= norminette

# Entry point
all: $(NAME)

# Compiles ls
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)

# Compiles libft/libft.a
# It's a prerequisite to compile ft_ls
$(LIBFT):
	$(MAKE) ./$(PATH_L)

# Creates obj/ directory
# It's a prerequisite to compile any OBJ
$(PATH_B):
	mkdir $@

# Adds the dependency to create the directory
# before to compile an object
$(OBJS): | $(PATH_B)

# Compiles all the src/*.c into obj/*.o
$(PATH_B)/%.o:$(PATH_S)/%.c $(HEADER)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

# /!\ Dirty workaround /!\
# If make on the libft directory should rebuild something then PHONY the rule
# libft to build it. Otherwise it relink.
#	ifeq ($(shell $(MAKE) --question -C ./$(LIBFT_PATH) ; echo $$?), 1)
#	.PHONY: $(LIBFT_PATH)/$(LIBFT_PATH).a
#	endif


.PHONY: clean
clean:
	$(MAKE) ./$(PATH_L) clean
	$(RM) $(PATH_B)

fclean: clean
	$(MAKE) ./$(PATH_L) fclean
	$(RM) $(NAME) 
	$(RM) $(NAME).dSYM

re: fclean
	$(MAKE) all

.PHONY: norm
norm:
	norminette $(SRC)
	norminette $(PATH_I)
	norminette $(PATH_L)/*.c
	norminette $(PATH_L)/*.h

normal:
	norminette $(SRC)
	norminette $(PATH_I)
	$(MAKE) ./${PATH_L} norm