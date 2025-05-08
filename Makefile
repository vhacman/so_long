# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 11:35:07 by vhacman           #+#    #+#              #
#    Updated: 2025/04/10 11:35:07 by vhacman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================
# === COMANDI DISPONIBILI =======
# ================================
# make            → Compila il progetto (mandatory)
# make bonus      → Compila la versione bonus
# make re         → Pulisce tutto e ricompila
# make clean      → Rimuove solo gli oggetti compilati
# make fclean     → Rimuove oggetti + eseguibile

# =======================
# === COMPILING RULE=====
# =======================

CC          = cc
CFLAGS      = -g -Wall -Wextra -Werror \
              -Iinclude -Ilibft/includes -Iminilibx-linux -Iso_long_bonus/include

# =======================
# === DIRECTORY =========
# =======================

SRC_DIR     = src
BONUS_DIR   = so_long_bonus/src
OBJ_DIR     = obj
LIBFT_DIR   = libft
MLX_DIR     = minilibx-linux

# =======================
# === BONARY NAME  ======
# =======================

NAME        = so_long

# =======================
# === SRC FILES =========
# =======================

SRC = \
	$(SRC_DIR)/event_handling/clean_up.c \
	$(SRC_DIR)/event_handling/validate_map.c \
	$(SRC_DIR)/init_window/init_window.c \
	$(SRC_DIR)/event_handling/clean_up2.c \
	$(SRC_DIR)/main/main.c \
	$(SRC_DIR)/event_handling/handle_key.c \
	$(SRC_DIR)/game_loop/render.c \
	$(SRC_DIR)/image_loading/exit.c \
	$(SRC_DIR)/map_parsing/check_path.c \
	$(SRC_DIR)/event_handling/image_loading_utils.c \
	$(SRC_DIR)/image_loading/player.c \
	$(SRC_DIR)/map_parsing/check_path_utils.c \
	$(SRC_DIR)/event_handling/load_map.c \
	$(SRC_DIR)/image_loading/background.c \
	$(SRC_DIR)/image_loading/wall.c \
	$(SRC_DIR)/event_handling/move_player.c \
	$(SRC_DIR)/image_loading/collectible.c \
	$(SRC_DIR)/image_loading/win_lost.c

SRC_BONUS = \
	$(BONUS_DIR)/event_handling/clean_up.c \
	$(BONUS_DIR)/event_handling/clean_up2.c \
	$(BONUS_DIR)/event_handling/handle_key.c \
	$(BONUS_DIR)/event_handling/image_loading_utils.c \
	$(BONUS_DIR)/event_handling/load_map.c \
	$(BONUS_DIR)/event_handling/move_player.c \
	$(BONUS_DIR)/event_handling/validate_map.c \
	$(BONUS_DIR)/game_loop/animations.c \
	$(BONUS_DIR)/game_loop/render.c \
	$(BONUS_DIR)/game_loop/update_enemy.c \
	$(BONUS_DIR)/image_loading/background.c \
	$(BONUS_DIR)/image_loading/collectible.c \
	$(BONUS_DIR)/image_loading/enemy.c \
	$(BONUS_DIR)/image_loading/enemy_helper.c \
	$(BONUS_DIR)/image_loading/exit.c \
	$(BONUS_DIR)/image_loading/player.c \
	$(BONUS_DIR)/image_loading/wall.c \
	$(BONUS_DIR)/image_loading/win_lost.c \
	$(BONUS_DIR)/init_window/init_window.c \
	$(BONUS_DIR)/main/main.c \
	$(BONUS_DIR)/map_parsing/check_path.c \
	$(BONUS_DIR)/map_parsing/check_path_utils.c

# =======================
# === OBJ COMPILED ======
# =======================

OBJ        = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS  = $(SRC_BONUS:%.c=$(OBJ_DIR)/%.o)

# =======================
# === LIBRARIES==========
# =======================

LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a
MLX_LIBS    = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# =======================
# === COLOURS OUTPUT ====
# =======================

GREEN       = \033[0;32m
CYAN        = \033[0;36m
YELLOW      = \033[1;33m
RESET       = \033[0m

# =======================
# === MAIN RULE  ========
# =======================

all: $(NAME)
	@echo "$(GREEN)🎮 so_long is ready to play!$(RESET)"

# =======================
# === LINKING MANDATORY =
# =======================

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@echo "$(YELLOW)🔧 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_LIBS) -o $(NAME)

# =======================
# === LINKING BONUS =====
# =======================

bonus: $(LIBFT) $(MLX) $(OBJ_BONUS)
	@echo "$(YELLOW)🔧 Linking $(NAME) with bonus...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) $(MLX_LIBS) -o $(NAME)

# =======================
# === COMPILING    ======
# =======================

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(CYAN)🛠️  Compiling: %-45s$(RESET)\n" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@	

# =======================
# === BUILD LIBFT + MLX =
# =======================

$(LIBFT):
	@echo "$(CYAN)📦 Building libft...$(RESET)"
	@make -sC $(LIBFT_DIR)

$(MLX):
	@echo "$(CYAN)🧱 Building MiniLibX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1 || true

# =======================
# === CLEANING ==========
# =======================

clean:
	@echo "$(YELLOW)🪹 Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -sC $(LIBFT_DIR) clean

fclean: clean
	@echo "$(YELLOW)💫 Removing executable...$(RESET)"
	@rm -f $(NAME)
	@echo "$(YELLOW)🧹 Cleaning Valgrind logs...$(RESET)"

re: fclean all

# =======================
# === TARGET FINTI ======
# =======================

.PHONY: all clean fclean re bonus valgrind
