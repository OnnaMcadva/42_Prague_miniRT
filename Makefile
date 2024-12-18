# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: annavm <annavm@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 21:47:07 by annavm            #+#    #+#              #
#    Updated: 2024/12/18 23:17:31 by annavm           ###   ########.fr        #
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
NAME = miniRT
UNAME = $(shell uname -s)
INC_DIR     = incs
CC = @gcc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address 
HEADERS = $(wildcard incs/*.h)
MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
RM = @rm -rf

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11
INCLUDES = -I $(INC_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR)

FILES = minirt \
		common/exit_error \
		common/free_func \
		common/lights_manag \
		common/object_manag \
		common/str_convert \
		common/str_type_check \
		hook_handle/cam_moving \
		hook_handle/hook_init \
		hook_handle/light_moving \
		hook_handle/manage_fig \
		hook_handle/mouse_moving \
		math/geometry_norms \
		math/quadr_roots \
		math/vector_arithm \
		math/vector_re_re \
		math/vector_vector \
		parsing/open_file \
		parsing/pars_extra \
		parsing/pars_general \
		parsing/pars_object \
		parsing/parse_textures \
		parsing/parse_utils \
		parsing/primary_parse \
		ray_tracing/anti_alias \
		ray_tracing/color_effects \
		ray_tracing/color_utils \
		ray_tracing/complex_intersec \
		ray_tracing/loading_bar \
		ray_tracing/mlxwin_init \
		ray_tracing/primit_intersec \
		ray_tracing/ray_casting \
		ray_tracing/ray_intersec \
		ray_tracing/refle_refra \
		ray_tracing/render \
		ray_tracing/textures \
		ray_tracing/transition_matrix

SRCS_DIR = ./src/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./obj/
OBJ_DIRS = $(OBJS_DIR)common $(OBJS_DIR)hook_handle $(OBJS_DIR)math $(OBJS_DIR)parsing $(OBJS_DIR)ray_tracing
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

INCFLAGS = $(INCLUDES)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJ_DIRS)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCFLAGS)

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	@echo "$(BOLD)$(YELLOW_BR)\n   Building $(NAME)\n$(DEF_COLOR)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) -lm $(LIBFT_LIB)
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
	@echo "$(BLUE_BR)😸	Mouse --- move_object$(DEF_COLOR)"
	@echo "$(BLUE_BR)😸	Mouse/1,2,3 --- change_object\n$(DEF_COLOR)"
	
$(LIBFT_LIB):
	@echo "$(BOLD)$(BLUE_BR)Getting libft ready!$(DEF_COLOR)"	
	@make -s -C $(LIBFT_DIR)


$(MLX_LIB):
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
	@make --quiet -C $(MLX_DIR)

clean:
	$(RM) $(OBJS_DIR) $(NAME)
	@echo "$(UNDERLINE)$(PINK_BR)Cleaned object files$(DEF_COLOR)"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@echo "$(UNDERLINE)$(ORANGE)Removed all binaries$(DEF_COLOR)"

re: clean $(NAME)

fre: fclean $(NAME)

norm: $(NAME)
	@norminette $(SRCS) $(HEADERS)

.PHONY: all clean fclean re fre norm
