# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/20 23:13:34 by ilevy             #+#    #+#              #
#    Updated: 2025/02/23 03:26:42 by ilevy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name:

NAME:= cube3D
NAME_BONUS:= cube4D

# CC and CFLAGS:

CC:= cc
CFLAGS:= -Wall -Werror -Wextra

# Directories:

C_DIR:= c_files/
H_DIR:= h_files/
LIBFT:= libft/
O_DIR:= o_files/
SUBS:= exec/ init/ parsing/ free/ main/ utils/
O_DIR_SUBS:= $(addprefix $(O_DIR), $(SUBS))

# Sub-Directory and files:

PARSING_DIR:= parsing/
PARSING:= ft_parse.c ft_parse1.c ft_parse2.c

INIT_DIR:= init/
INIT:= ft_init.c

UTILS_DIR:= utils/
UTILS:= ft_parse1_utils.c ft_parse1_utils_2.c

FREE_DIR:= free/
FREE:= ft_free.c

EXEC_DIR:= exec/
EXEC:=

MAIN_DIR:= main/
MAIN:= main.c

# Source files relative to c_files:

SRC_FILES+= $(addprefix $(PARSING_DIR), $(PARSING))
SRC_FILES+= $(addprefix $(FREE_DIR), $(FREE))
SRC_FILES+= $(addprefix $(UTILS_DIR), $(UTILS))
SRC_FILES+= $(addprefix $(INIT_DIR), $(INIT))
SRC_FILES+= $(addprefix $(MAIN_DIR), $(MAIN))
SRC_FILES+= $(addprefix $(EXEC_DIR), $(EXEC))

# Source files relative to Makefile:

SRC:= $(addprefix $(C_DIR), $(SRC_FILES))
OBJ:= $(addprefix $(O_DIR), $(SRC_FILES:.c=.o))
SRC_BONUS:= $(addprefix $(C_DIR), $(BONUS_FILES))
OBJ_BONUS:= $(addprefix $(O_DIR), $(BONUS_FILES:.c=.o))

# Rules:

all:	$(NAME)

$(NAME):	$(O_DIR_SUBS) $(OBJ)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) -I $(H_DIR) -o $(NAME) $(OBJ) -L $(LIBFT) -lft
	@echo "Compiled $(NAME)"

$(O_DIR)%.o:	$(C_DIR)%.c
	$(CC) $(CFLAGS) -I $(H_DIR) -c $< -o $@

$(O_DIR_SUBS):	$(O_DIR)
	mkdir -p $(O_DIR_SUBS)

$(O_DIR):
	mkdir -p $(O_DIR)

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJ)
	rm -rf $(O_DIR)

fclean:	clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT)

re:	fclean all

bonus:	$(NAME_BONUS)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) -I $(H_DIR) -o $(NAME_BONUS) $(OBJ_BONUS) -L $(LIBFT) -lft
	@echo "Compiled $(NAME_BONUS)"

.PHONY: re all fclean clean bonus