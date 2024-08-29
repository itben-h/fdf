# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 18:52:45 by bhowe             #+#    #+#              #
#    Updated: 2024/07/26 14:02:04 by bhowe            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########## Files & Dirs ##########
NAME		:= fdf
SRC			:=	fdf.c \
				fdf_parse1.c \
				fdf_parse2.c \
				fdf_render1.c \
				fdf_render2.c \
				fdf_inits.c \
				fdf_utils1.c \
				fdf_utils2.c \
				project.c \
				project_matrix.c \
				mlx_image.c \
				mlx_keypress.c \
				e.c \

OBJ			:= $(SRC:.c=.o)
LIBFT_DIR	:= ./libft/
LIBFT		:= $(LIBFT_DIR)libft.a
LIBFT_D		:= $(LIBFT_DIR)libft.a
HEADER		:= fdf.h

########## Compilation ##########
CC			:= cc
CFLAG		:= -Wall -Werror -Wextra
LIB			:= -L$(LIBFT_DIR) -lft
MAKE		:= make -C

########## Minilibx ##########
MLX_DIR		:= ./minilibx-linux/
MLX			:= $(MLX_DIR)libmlx.a
MLX_LIB		:= -L$(MLX_DIR) -lmlx_Linux
INC_MLX		:= -I/usr/include -I$(MLX_DIR)
MLX_LINKS	:= -L/usr/lib -lXext -lX11 -lm -lz

########## Custom ##########
RM			:= rm -rf

COLOR_RED	:=\033[0;31m
COLOR_END	:=\033[0m

all: mlx libft $(NAME)

bonus: all

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	@echo "$(COLOR_RED)making fdf ...$(COLOR_END)"
	$(CC) $(CFLAG) $(OBJ) $(LIB) $(MLX_LIB) $(MLX_LINKS) -o $@

%.o: %.c $(HEADER)
	@echo "$(COLOR_RED)making obj ...$(COLOR_END)"
	$(CC) $(CFLAG) $(INC_MLX) -O3 -g -c $< -o $@

mlx:
	@if [ ! -d $(MLXDIR) ] || [ ! -f $(MLX) ]; then \
		echo "$(COLOR_RED)MLX not found. Cloning and building ...$(COLOR_END)"; \
		$(RM) $(MLX_DIR); \
		git submodule deinit -f $(MLX_DIR); \
		git submodule update --init $(MLX_DIR); \
		$(MAKE) $(MLX_DIR) all; \
	else \
		echo "$(COLOR_RED)MLX already exists. Skipping ...$(COLOR_END)"; \
	fi

libft:
	@echo "$(COLOR_RED)making libft ...$(COLOR_END)"
	@$(MAKE) $(LIBFT_DIR) all

clean:
	@echo "$(COLOR_RED)removing objs ...$(COLOR_END)"
	$(RM) $(OBJ)
	@$(MAKE) $(LIBFT_DIR) clean

fclean: clean
	@echo "$(COLOR_RED)removing all libs '&' execs ...$(COLOR_END)"
	$(RM) $(NAME)
	@$(MAKE) $(LIBFT_DIR) fclean
	@$(MAKE) $(MLX_DIR) clean

re: fclean all

.PHONY: all clean flcean re libft mlx
