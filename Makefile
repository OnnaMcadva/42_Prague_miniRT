# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: annavm <annavm@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 21:47:07 by annavm            #+#    #+#              #
#    Updated: 2024/12/12 21:33:07 by annavm           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
DEF_COLOR   = \033[0;39m
GRAY        = \033[0;90m
RED         = \033[0;91m
GREEN       = \033[0;92m
YELLOW      = \033[0;93m
BLUE        = \033[0;94m
MAGENTA     = \033[0;95m
CYAN        = \033[0;96m
WHITE       = \033[0;97m
ORANGE      = \033[38;5;222m
GREEN_BR    = \033[38;5;118m
YELLOW_BR   = \033[38;5;227m
PINK_BR     = \033[38;5;206m
BLUE_BR     = \033[38;5;051m
PINK_BRR     = \033[38;5;219m

# Text styles
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLINK       = \033[5m

# Project
NAME        = minirt
CC          = gcc
CFLAGS      = -Werror -Wextra -Wall -O3
CDEBUG      = -g3 -fsanitize=address
NORM        = norminette
AR          = ar
ARFLAGS     = rcs
RM          = rm -rf

# Directories
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = incs
LIBFT_DIR   = libft
MLX_DIR     = minilibx-linux

# Files
SRC_FILES     = $(wildcard ./src/minirt.c) \
 				$(wildcard ./src/common/*.c) \
				$(wildcard ./src/hook_handle/*.c) \
				$(wildcard ./src/math/*.c) \
				$(wildcard ./src/parsing/*.c) \
				$(wildcard ./src/ray_tracing/*.c)

OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
DEV_SRCS    = $(patsubst %/minirt.c, %/dev.c, $(SRC_FILES))
DEV_OBJS    = $(DEV_SRCS:.c=.o)

# Libraries
LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a

# Includes
INCLUDES    = -I $(INC_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR)

# MLX Flags
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11
LDFLAGS += -L/usr/lib/x86_64-linux-gnu -lX11 -lXpm -lXext

# Math Flags
MATH_FLAGS  = -lm
CPPFLAGS += -I/usr/include/X11

# Rules
all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "$(BOLD)$(YELLOW_BR)\n   Building $(NAME)\n$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) $(MATH_FLAGS) -o $(NAME)
	@echo "$(BOLD)$(GREEN_BR)$(NAME) is ready!$(DEF_COLOR)"
	@echo "$(BOLD)$(GREEN_BR)		Use hot keys please	😸	\n$(DEF_COLOR)"
	@echo "$(BLUE_BR)😸	L --- antialiasing$(DEF_COLOR)"
	@echo "$(BLUE_BR)😸	W --- move_camera_forward$(DEF_COLOR)"
	@echo "$(BLUE_BR)😸	S --- move_camera_backward$(DEF_COLOR)"
	@echo "$(BLUE_BR)😸	A --- move_camera_left$(DEF_COLOR)"
	@echo "$(BLUE_BR)😸	D --- move_camera_right$(DEF_COLOR)"
	@echo "$(BLUE_BR)😸	R --- move_camera_up$(DEF_COLOR)"
	@echo "$(BLUE_BR)😸	F --- move_camera_down$(DEF_COLOR)"
	@echo "$(BLUE_BR)🎄	C or X --- Easter_egg$(DEF_COLOR)"
	@echo "$(BLUE_BR)😸	Q --- rotate_camera_left$(DEF_COLOR)"
	@echo "$(BLUE_BR)😸	E --- rotate_camera_right$(DEF_COLOR)"
	@echo "$(BLUE_BR)😸	arrows --- light_moving$(DEF_COLOR)"
	@echo "$(BLUE_BR)😸	NP4...NP9 --- light_color_change$(DEF_COLOR)"
	@echo "$(BLUE_BR)😸	-/+ --- bright_change$(DEF_COLOR)"
	@echo "$(BLUE_BR)😸	Mouse --- move_object\n$(DEF_COLOR)"

$(LIBFT):
	@echo "$(BOLD)$(BLUE_BR)Getting libft ready!$(DEF_COLOR)"
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX):
	@echo "$(BOLD)$(PINK_BRR)\n  Building minilibx...     $(DEF_COLOR)"
	@echo "$(BOLD)$(YELLOW_BR)      ⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⠤⢤⡀⠀             $(DEF_COLOR)"
	@echo "$(BOLD)$(YELLOW_BR)      ⠀⠀⠀⠀⠀⠀⠀⢀⠎⠀⠀⠀⠘⣦⠀            $(DEF_COLOR)"
	@echo "$(BOLD)$(YELLOW_BR)      ⠀⠀⠀⠀⠀⠀⢠⣾⡖⢦⣰⣿⢲⠸⡇⠀⠀⠀        $(DEF_COLOR)"
	@echo "$(BOLD)$(YELLOW_BR)      ⠀⠀⠀⠀⠀⠀⢨⠻⢷⣟⠙⠿⠞⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀ $(DEF_COLOR)"
	@echo "$(BOLD)$(YELLOW_BR)       ⠀⠀⠀⠀⠀⢸⠦⠤⠷⠶⠶⠂⠀⢸⠀⠀⠀⠀⠀⠀⢀⢀⠀ $(DEF_COLOR)"
	@echo "$(BOLD)$(YELLOW_BR)      ⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⡆⡄⢸⠀⠀⠀⠀⠀⢠⠃⢸⠀⠀$(DEF_COLOR)"
	@echo "$(BOLD)$(YELLOW_BR)      ⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⡇⡇⢸⣇⡀⠀⠀⡠⠁⢠⠃⠀⠀$(DEF_COLOR)"
	@echo "$(BOLD)$(YELLOW_BR)      ⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⣸⠃⢻⠈⠈⠉⢙⣳⣥⣄⣀⠔⠀ $(DEF_COLOR)"
	@echo "$(BOLD)$(YELLOW_BR)      ⠀⠀⠀⠀⠀⠀⠸⡆⠀⠀⠰⣧⣶⠌⠂⠀⠀⠉⠁⠀⠀⠉⠳⡄⠀$(DEF_COLOR)"
	@echo "$(BOLD)$(YELLOW_BR)      ⠀⠀⠀⠀⠀⠀⠀⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀$(DEF_COLOR)"
	@echo "$(BOLD)$(YELLOW_BR)      ⠀⠀⠀⠀⠀⠀⠀⠹⢦⣀⣀⣀⡀⠀⢀⣀⣀⡀⠀⢀⣀⡠⠚⠀⠀$(DEF_COLOR)"
	@echo "$(BOLD)$(YELLOW_BR)      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠉⡹⠉⠉⠉⠉⢉⠇⢠⠃⠀     $(DEF_COLOR)"
	@echo "$(BOLD)$(YELLOW_BR)      ⠀⠀⠀⠀⠀⠀⠰⡉⠑⠁⢠⠃⠀⠀⣟⠓⠋⢠⠃⠀      $(DEF_COLOR)"
	@echo "$(BOLD)$(YELLOW_BR)      ⠀⠀⠀⠀⠀⠀⠀⠈⠛⠒⠁⠀⠀⠀⠈⠓⠒⠁⠀       $(DEF_COLOR)"
	@$(MAKE) -s -C $(MLX_DIR)

clean:
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(MLX_DIR) clean
	@$(RM) $(OBJ_DIR)
	@echo "$(UNDERLINE)$(PINK_BR)Cleaned object files$(DEF_COLOR)"

fclean: clean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(UNDERLINE)$(ORANGE)Removed all binaries$(DEF_COLOR)"

re: fclean all

run:
	./$(NAME) $(SCENE)

norm:
	$(NORM) $(INC_DIR) $(SRCS_DIR) $(LIBFT_DIR)

dev: CFLAGS += $(CDEBUG)
dev: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT_FLAGS) $(MLX_FLAGS) -L $(LIBFT_DIR) -L $(MLX_DIR) -o $(NAME)
	$(MAKE) run

valgrind:
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re