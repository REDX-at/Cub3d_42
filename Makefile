NAME = cub3D
B_NAME = cub3D_bonus
SRC = Cub_manda/main.c Cub_manda/execute/execute.c Cub_manda/Parsing/parsing.c Cub_manda/Get_next_line/get_next_line.c \
	Cub_manda/Get_next_line/get_next_line_utils.c Cub_manda/parsing/first_element.c Cub_manda/parsing/utils_parsing.c \
	Cub_manda/parsing/utils_parsing_2.c Cub_manda/parsing/check_valid_elem.c Cub_manda/parsing/check_map.c Cub_manda/parsing/utils_parsing_3.c \
	Cub_manda/parsing/check_element_f_c.c Cub_manda/parsing/check_closed.c Cub_manda/execute/textures.c Cub_manda/parsing/utils_check.c \
	Cub_manda/execute/mouvment.c Cub_manda/execute/ray.c Cub_manda/execute/pressing_key.c Cub_manda/execute/player.c \
	Cub_manda/execute/pixels.c
B_SRC = Cub_bonus/main_bonus.c Cub_bonus/execute/execute_bonus.c Cub_bonus/Parsing/parsing_bonus.c Cub_bonus/Get_next_line/get_next_line.c \
	Cub_bonus/Get_next_line/get_next_line_utils.c Cub_bonus/parsing/first_element_bonus.c Cub_bonus/parsing/utils_parsing_bonus.c \
	Cub_bonus/parsing/utils_parsing_2_bonus.c Cub_bonus/parsing/check_valid_elem_bonus.c Cub_bonus/parsing/check_map_bonus.c Cub_bonus/parsing/utils_parsing_3_bonus.c \
	Cub_bonus/parsing/check_element_f_c_bonus.c Cub_bonus/parsing/check_closed_bonus.c Cub_bonus/execute/textures_bonus.c Cub_bonus/parsing/utils_check_bonus.c \
	Cub_bonus/execute/pressing_key_bonus.c Cub_bonus/execute/mouvment_bonus.c Cub_bonus/execute/weapon_bonus.c Cub_bonus/execute/ray_bonus.c Cub_bonus/execute/draw_bonus.c\
	Cub_bonus/execute/mouse_bonus.c Cub_bonus/execute/player_bonus.c Cub_bonus/execute/check_bonus.c Cub_bonus/execute/textures_utils_bonus.c Cub_bonus/parsing/check_map_2.c
CFLAGS = -Wall -Wextra -Werror
HEADER = Cub_manda/cub3d.h
B_HEADER = Cub_bonus/cub3d_bonus.h
L_HEADER = Cub_manda/libft/libft.h
LB_HEADER = Cub_bonus/libft/libft.h
LIBFT = Cub_manda/libft/libft.a 
OBJ = $(SRC:.c=.o)
B_OBJ = $(B_SRC:.c=.o)
CC = cc
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
all: make_libft $(NAME)
bonus: make_libft $(B_NAME)

make_libft:
	@cd Cub_manda/libft && make

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)
	@echo "libft created"
	@echo "Cub3D created"
$(B_NAME): $(B_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(B_OBJ) $(LIBFT) $(MLXFLAGS) -o $(B_NAME)
	@echo "libft created"
	@echo "Cub3D_bonus created"

Cub_manda/%.o: Cub_manda/%.c $(HEADER) $(L_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

Cub_bonus/%.o: Cub_bonus/%.c $(B_HEADER) $(LB_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(B_OBJ)
fclean: clean
	@cd Cub_manda/libft && make fclean
	@cd Cub_bonus/libft && make fclean
	rm -f $(NAME) $(B_NAME)
re: fclean all

.PHONY: clean make_libft