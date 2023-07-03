# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/22 08:46:09 by gkintana          #+#    #+#              #
#    Updated: 2022/08/10 20:37:25 by gkintana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_M		=	cub3D
NAME_B		=	cub3D_bonus

LIBFT_DIR	=	libft
LIBFT		=	libft.a

ifeq ($(shell uname -s), Linux)
	MLX_DIR		=	minilibx_linux
	MLX			=	libmlx_Linux.a
	LINK_MLX	=	-I$(MLX_DIR) -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
endif

ifeq ($(shell uname -s), Darwin)
	MLX_DIR		=	minilibx_mac
	MLX			=	libmlx.a
	LINK_MLX	=	-L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

INC_DIR		=	include
SRC_DIR		=	sources/mandatory
BONUS_DIR	=	sources/bonus
OBJ_DIR		=	objects

SRCS		=	main.c \
				floor_and_ceiling.c \
				init.c \
				init1.c \
				init2.c \
				keyboard.c \
				parse_utils.c \
				parse.c \
				parse0.c \
				parse1.c \
				parse2.c \
				parse3.c \
				parse4.c \
				parse5.c \
				player_calculations.c \
				player_initialization.c \
				raycast_textures.c \
				raycast.c \
				utils.c
OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRCS:%c=%o))

BONUS		=	main_bonus.c \
				draw_functions_bonus.c \
				floor_and_ceiling_bonus.c \
				init_bonus.c \
				init1_bonus.c \
				init2_bonus.c \
				keyboard_bonus.c \
				minimap_check_bonus.c \
				minimap_utils_bonus.c \
				minimap_bonus.c \
				mouse_bonus.c \
				parse_utils_bonus.c \
				parse_bonus.c \
				parse0_bonus.c \
				parse1_bonus.c \
				parse2_bonus.c \
				parse3_bonus.c \
				parse4_bonus.c \
				parse5_bonus.c \
				player_calculations_bonus.c \
				player_initialization_bonus.c \
				player_representation_bonus.c \
				raycast_textures_bonus.c \
				raycast_bonus.c \
				utils_bonus.c
OBJS_BONUS	=	$(addprefix $(OBJ_DIR)/, $(BONUS:%c=%o))

CC			=	gcc
CFLAGS		=	-g -Wall -Wextra -Werror
LIB_AR		=	ar rcs
RM			=	rm -rf

DEFAULT		=	"\033[0m"
RED			=	"\033[0;31m"
GREEN		=	"\033[1;32m"
YELLOW_BU	=	"\033[1;4;33m"
PURPLE		=	"\033[3;35m"
CYAN		=	"\033[3;36m"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
			@mkdir -p $(OBJ_DIR)
			@printf $(CYAN)
			@printf "\033[A\033[2K\r"
			$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR) -I$(MLX_DIR) -O3 -c $< -o $@

$(OBJ_DIR)/%.o : $(BONUS_DIR)/%.c
			@mkdir -p $(OBJ_DIR)
			@printf $(CYAN)
			@printf "\033[A\033[2K\r"
			$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR) -I$(MLX_DIR) -O3 -c $< -o $@

all:		$(NAME_M)

$(NAME_M):	$(MLX) $(LIBFT) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFT) $(LINK_MLX) -o $@

$(NAME_B):	$(MLX) $(LIBFT) $(OBJS_BONUS)
			@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT_DIR)/$(LIBFT) $(LINK_MLX) -o $@

$(LIBFT):
			@printf $(DEFAULT)
			@make -C $(LIBFT_DIR) all

$(MLX):
			@printf $(DEFAULT)
			@make -C $(MLX_DIR) all

bonus:		$(NAME_B)

clean:
			@make -C $(LIBFT_DIR) fclean
			@make -C $(MLX_DIR) clean
			@$(RM) $(OBJ_DIR)
			@echo $(RED)"Deleted cub3D object files & folder"$(DEFAULT)

fclean:		clean
			@$(RM) $(NAME_M) $(NAME_B)
			@echo $(RED)"Deleted cub3D executable/s"$(DEFAULT)

norm:
			@make -C $(LIBFT_DIR) norm
			@echo $(DEFAULT)$(YELLOW_BU)"cub3D .c files"$(DEFAULT)$(CYAN)
			@norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*.c
			@echo $(DEFAULT)$(YELLOW_BU)"cub3D_bonus .c files"$(DEFAULT)$(CYAN)
			@norminette -R CheckForbiddenSourceHeader $(BONUS_DIR)/*.c
			@echo $(DEFAULT)$(YELLOW_BU)"cub3D .h files"$(DEFAULT)$(CYAN)
			@norminette -R CheckDefine $(INC_DIR)/*.h

re:			fclean all

.PHONY:		all clean fclean re bonus
