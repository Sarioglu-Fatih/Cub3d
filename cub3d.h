/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:49:19 by fsariogl          #+#    #+#             */
/*   Updated: 2023/06/03 16:33:35 by rgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include "mlx_linux/mlx.h"
# include "libft/libft.h"
# include "libft/get_next_line.h"

# define FLOOR = 0
# define WALL = 1
# define TRUE 2
# define FALSE 3

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_varmlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*title;
	int		size_winx;
	int		size_winy;
}	t_varmlx;

typedef struct s_vars
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*floor;
	char	*ceiling;
	char	*gnl_ret;
	char	**map_data;
	char	*map_in_str;
	int		color_floor;
	int		color_ceiling;
	int		fd;
}	t_vars;

typedef struct s_mapinfo
{
	int		points;
	int		size_x;
	int		size_y;
	double	start_x;
	double	start_y;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
}	t_mapinfo;

typedef struct s_cam
{
	float	camera_x;
	double	camera_y;
	float	first_x;
	float	first_y;
	double	prog_x;
	double	prog_y;
	double	curr_x;
	double	curr_y;
	double	delta_x;
	double	delta_y;
	double	correct_dist;
	int		hit;
	int		side;
	int		line_height;
	int		step_x;
	int		step_y;
	int		draw_start;
	int		draw_end;
	float	angle;
	float	sinangle;
	float	cosa;
	float	sina;
	float	fov;
}	t_cam;

typedef struct s_tex
{
	void	*text;
	char	*text_adr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width_img;
	int		height_img;
	int		tex_x;
	int		tex_y;
}	t_tex;

typedef struct s_map
{
	int		x;
	int		y;
	char	type;
}	t_map;

typedef struct s_params
{
	t_map		*map;
	t_cam		cam;
	t_mapinfo	info;
	t_vars		v;
	t_varmlx	vmlx;
	t_data		img;
	t_tex		*tex;
}	t_params;

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		parse_file(t_vars *vars);
void		ft_free_tab(char **tab);
void		init_vars(t_varmlx *varmlx, t_vars *vars, char *file);
int			init_all(t_params *p);
void		init_dir(char cardinal, t_cam *cam);
t_map		*init_map(char **parsed_data, t_mapinfo info);
int			init_playerpos(t_map *cmap, t_mapinfo *info, t_cam *cam);
t_mapinfo	count_points_in_tab(char **tab);
void		movement(int keycode, t_params *prms);
void		rotation_camera(int keycode, t_params *p);
void		rotation_camera2(int keycode, t_params *p);
void		floor_cast(t_params	*p);
void		raycast_lines(t_params *p);
void		get_rayprog(t_params *p);
int			iscubfile(char *file);
void		drawing_map(t_params *p);
void		draw_line(t_params p, int x, int s_wy);
void		get_linedraw(t_params *p);
int			key_hook(int keycode, t_params *prms);
int			close_window(t_params *prms);
int			get_tex_x(t_cam cam, t_mapinfo info, t_tex tex);
int			get_text_pixel(t_tex tex);
int			current_pixel(t_params p, int x, int y);
int			load_textures(t_params *p, char *texture_path, int i);
t_tex		*load_all_textures(t_varmlx vmlx, t_vars v);

//parsing
void		check_map(t_vars *vars);
void		parse_file(t_vars *vars);
void		get_colors(t_vars *vars);
void		check_vars(t_vars *vars);
void		fail(char *str, t_vars *vars);
void		get_east(t_vars *vars, int i);
void		get_west(t_vars *vars, int i);
void		get_floor(t_vars *vars, int i);
void		get_south(t_vars *vars, int i);
void		get_north(t_vars *vars, int i);
void		get_ceiling(t_vars *vars, int i);
void		check_all_color(t_vars *vars, int i);
char		**ft_splitv2(const char *str, char c);
int			map_char(char c);
int			check_path_and_colors(t_vars *vars);
int			strlen_itoc(char *str, int i, char c);
int			strlen_itoc(char *str, int i, char c);

#endif
