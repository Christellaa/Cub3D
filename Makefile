# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/20 23:13:34 by ilevy             #+#    #+#              #
#    Updated: 2025/03/13 11:59:24 by cde-sous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name:

NAME:= cub3D
NAME_BONUS:= cub4D

# CC and CFLAGS:
CC:= cc
CFLAGS:= -Wall -Werror -Wextra -g3

# Directories:
C_DIR:= c_files/
H_DIR:= h_files/
LIBFT:= libft/
MLX:= minilibx-linux/
O_DIR:= o_files/
SUBS:= exec/ init/ parsing/ free/ main/ utils/
O_DIR_SUBS:= $(addprefix $(O_DIR), $(SUBS))

# Sub-Directory and files:
PARSING_DIR:= parsing/
PARSING:= ft_parse.c ft_parse1.c ft_parse2.c ft_parse3.c

INIT_DIR:= init/
INIT:= ft_init.c ft_init_2.c

UTILS_DIR:= utils/
UTILS:= ft_parse1_utils.c ft_parse1_utils_2.c ft_parse3_utils.c \
        ft_parse3_utils_2.c ft_flood_fill_util.c ft_utils.c ft_hooks.c \
		ft_moves.c ft_moves_utils.c

FREE_DIR:= free/
FREE:= ft_free.c ft_free_utils.c

EXEC_DIR:= exec/
EXEC:= ft_window.c ft_raycaster.c draw_ceiling_floor.c draw_wall.c

MAIN_DIR:= main/
MAIN:= main.c

# Source files relative to c_files:
SRC_FILES+= $(addprefix $(PARSING_DIR), $(PARSING))
SRC_FILES+= $(addprefix $(FREE_DIR), $(FREE))
SRC_FILES+= $(addprefix $(UTILS_DIR), $(UTILS))
SRC_FILES+= $(addprefix $(INIT_DIR), $(INIT))
SRC_FILES+= $(addprefix $(MAIN_DIR), $(MAIN))
SRC_FILES+= $(addprefix $(EXEC_DIR), $(EXEC))

# Object files:
SRC:= $(addprefix $(C_DIR), $(SRC_FILES))
OBJ:= $(addprefix $(O_DIR), $(SRC_FILES:.c=.o))

# Libraries:
LIBMLX:= -L$(MLX) -lmlx -lX11 -lXext -lm
LIBFT_FLAG:= -L$(LIBFT) -lft

# Rules:
all: $(NAME)

$(NAME): $(O_DIR_SUBS) $(OBJ)
	make -C $(LIBFT)
	make -C $(MLX)
	$(CC) $(CFLAGS) -I $(H_DIR) -I $(MLX) -o $(NAME) $(OBJ) $(LIBFT_FLAG) $(LIBMLX)
	@echo "Compiled $(NAME)"

$(O_DIR)%.o: $(C_DIR)%.c | $(O_DIR_SUBS)
	$(CC) $(CFLAGS) -I $(H_DIR) -I $(MLX) -c $< -o $@

$(O_DIR_SUBS): $(O_DIR)
	mkdir -p $(O_DIR_SUBS)

$(O_DIR):
	@wget https://cdn.intra.42.fr/document/document/31613/minilibx-linux.tgz
	@tar -xpf minilibx-linux.tgz
	@rm -rf minilibx-linux.tgz
	mkdir -p $(O_DIR)

clean:
	rm -rf $(OBJ)
	rm -rf $(O_DIR)
	make clean -C $(LIBFT)
	make clean -C $(MLX)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT)
	make clean -C $(MLX)

re: fclean all

bonus: $(NAME_BONUS)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) -I $(H_DIR) -o $(NAME_BONUS) $(OBJ_BONUS) $(LIBFT_FLAG)
	@echo "Compiled $(NAME_BONUS)"

.PHONY: re all fclean clean bonus

