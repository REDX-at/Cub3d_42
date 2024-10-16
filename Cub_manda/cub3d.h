/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitaouss <aitaouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:06:47 by mkibous           #+#    #+#             */
/*   Updated: 2024/10/13 21:57:40 by aitaouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE INT_MAX
# endif
# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include <stddef.h>

// --------
# define FOV 60

// define color
# define RESET    "\033[0m"
# define RESOLVE      100000
# define RED	"\033[1;31m"
# define G      "\033[1;32m"
# define Y      "\033[1;33m"
# define B      "\033[1;34m"
# define M      "\033[1;35m"
# define C      "\033[1;36m"
# define W      "\033[1;37m"

typedef struct s_alloc		t_alloc;
typedef struct s_data		t_data;
typedef struct s_textures	t_textures;

# define POV 1.0471975511965976
# define TILE 64
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define MINIMAP_WIDTH 14
//mkibous

typedef struct s_start
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		button_clicked;
}	t_start;

typedef struct s_data
{
	char		**map;
	void		*mlx;
	void		*win;
	int			height;
	int			width;
	int			med;
	double		x;
	double		y;
	double		hx;
	double		hy;
	double		vx;
	double		vy;
	int			wallx;
	int			wally;
	int			wallhit;
	int			hit_index;
	int			xs;
	int			ys;
	int			xstep;
	int			ystep;
	double		hc;
	double		vc;
	double		view;
	double		angle;
	void		*img;
	char		*addr;
	int			bpp;
	int			size_l;
	int			endian;
	double		up_down_x;
	double		up_down_y;
	double		lr_x;
	double		lr_y;
	double		view_speed;
	double		c;
	int			px_x;
	double		al;
	int			color;
	int			w;
	int			a;
	int			s;
	int			d;
	int			tex_x;
	int			tex_y;
	double		wall_height;
	char		*texture_north;
	char		*texture_south;
	char		*texture_west;
	char		*texture_east;
	t_textures	*textures_north_struct;
	t_textures	*textures_south_struct;
	t_textures	*textures_west_struct;
	t_textures	*textures_east_struct;
	t_alloc		*alloc;
}	t_data;

typedef struct s_alloc
{
	int		k;
	char	**file;
	int		end_element;
	char	**element;
	char	**map;
	char	*map_path;
	char	**split;
	char	*tmp;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	player;
	int		*rgb_c;
	int		*rgb_f;
	int		color_c;
	int		color_f;
}				t_alloc;

typedef struct s_textures
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
	int		width;
	int		height;
}	t_textures;

void		ft_execute(t_alloc *alloc);
void		ft_mlx(t_data *vars);
int			ft_player(t_data *vars);
void		ft_imgs(t_data *vars);
void		ft_color(t_data *vars);
void		ft_add(t_data *vars);
void		ft_draw_ray(t_data *vars);
void		ft_calculate(t_data *vars, t_textures **texture, int *h,
				int *wall_h);
void		ft_find_texture(t_data *vars, t_textures **texture);
void		ft_take_first_hit(t_data *vars);
void		ft_horisontale(t_data *vars);
void		ft_vertical_ray(t_data *vars);
int			ft_check_wall(t_data *vars, double x, double y);
void		get_view(t_data *vars);
void		my_pixel_put(t_data *vars, int x, int y, int color);
int			ft_rel(int key, t_data *vars);
int			ft_key(int key, t_data *vars);
void		ft_w(t_data *vars);
void		ft_a(t_data *vars);
void		ft_s(t_data *vars);
void		ft_d(t_data *vars);
int			ft_check(t_data *vars, double x, double y);
void		ft_get_sign(int *sx, int *sy, double x, double y);
int			ft_close(t_data *vars);
void		ft_get_size(t_data *vars);
void		ft_get_player(t_data *vars, int i, int j);
double		ft_get_angle(char c);
void		ft_map(t_data *vars);
void		ft_wall(t_data *vars, int x, int y, int color);
void		get_map(t_alloc *alloc);
char		*get_next_line(int fd);
char		*ft_strjoin_next(char *line, char *buff);
char		*ft_strchr_next(char *s, int c);
size_t		ft_strlngn(char *s);
char		*ft_getline(char *line);
char		*readline(int fd, char *line);
char		*ft_newline(char *line);
void		loop_check_first(t_alloc *alloc, int *i, int *check, int count);
void		check_first_elem(t_alloc *alloc);
void		check_f_c(t_alloc *alloc);
void		free_2d(char **str);
int			ft_strlen_2d(char **str);
char		*skip_space(char *str, int flag);
int			count_virgule(char *str);
int			check_digit(char **str);
void		print_err_exit(char *str, t_alloc *alloc);
void		print_2d(char **str);
int			check_space(char *str);
char		**convert_tabs_space(char **str);
void		check_space_and_open(char *str, char *element);
int			ft_strlen_2d_d(char **str);
int			is_number(char *str);
char		**ft_strdup_2d(char **str);
void		print_element_map(t_alloc *alloc);
void		check_invalid_elem(t_alloc *alloc, int i, int j);
void		check_closed(t_alloc *alloc, int flag, int i, int j);
int			ft_strlen_split(char **str);
void		check_arround(t_alloc *alloc);
t_textures	*init_textures(t_data *data);
void		load_textures(t_data *data, char *path, t_textures *textures);
void		join_double_pointer(t_alloc *alloc, char **tmp, char **tmp_2);
int			count_line(t_alloc *alloc);
void		fix_map(t_alloc *alloc);
void		condition_impostert(t_alloc *alloc, int i, int j);
// clear
void		out_clean(t_alloc *alloc);

// check elem
void		check_element_we(t_alloc *alloc, int i);
void		check_element_so(t_alloc *alloc, int i);
void		check_element_ea(t_alloc *alloc, int i);
void		check_element_no(t_alloc *alloc, int i);

// textures
void		get_texture(t_data *data);

// Map
void		check_map(t_alloc *alloc);

#endif