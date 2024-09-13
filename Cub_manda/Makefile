NAME = cub3D
B_NAME = cub3D_bonus
SRC = main.c ./execute/execute.c ./Parsing/parsing.c ./Get_next_line/get_next_line.c \
	./Get_next_line/get_next_line_utils.c ./parsing/first_element.c ./parsing/utils_parsing.c \
	./parsing/utils_parsing_2.c ./parsing/check_valid_elem.c ./parsing/check_map.c ./parsing/utils_parsing_3.c \
	./parsing/check_element_f_c.c ./parsing/check_closed.c ./execute/textures.c ./parsing/utils_check.c
B_SRC = main_bonus.c ../Cub_bonus/execute/execute_bonus.c ../Cub_bonus/Parsing/parsing_bonus.c ../Cub_bonus/Get_next_line/get_next_line.c \
	../Cub_bonus/Get_next_line/get_next_line_utils.c ../Cub_bonus/parsing/first_element_bonus.c ../Cub_bonus/parsing/utils_parsing_bonus.c \
	../Cub_bonus/parsing/utils_parsing_2_bonus.c ../Cub_bonus/parsing/check_valid_elem_bonus.c ../Cub_bonus/parsing/check_map_bonus.c ../Cub_bonus/parsing/utils_parsing_3_bonus.c \
	../Cub_bonus/parsing/check_element_f_c_bonus.c ../Cub_bonus/parsing/check_closed_bonus.c ../Cub_bonus/execute/textures_bonus.c ../Cub_bonus/parsing/utils_check_bonus.c
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
HEADER = cub3d.h
B_HEADER = cub3d_bonus.h
LIBFT = libft/libft.a
OBJ = $(SRC:.c=.o)
B_OBJ = $(B_SRC:.c=.o)
CC = cc
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
all: make_libft $(NAME)
bonus: make_libft $(B_NAME)

make_libft:
	@cd libft && make

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)
$(B_NAME): $(B_OBJ)
	$(CC) $(CFLAGS) $(B_OBJ) $(LIBFT) $(MLXFLAGS) -o $(B_NAME)
%.o: %.c $(HEADER) $(B_HEADER)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ) $(B_OBJ)
fclean: clean
	@cd libft && make fclean
	@cd ../Cub_bonus/libft && make fclean
	rm -f $(NAME) $(B_NAME)
re: fclean all

push:
	@read -p "Enter commit message: " commit_message; \
	git add .; \
	git commit -m "$$commit_message"; \
	git push;

pull:
	@git stash
	@git pull
	@git stash pop

.PHONY: clean make_libft