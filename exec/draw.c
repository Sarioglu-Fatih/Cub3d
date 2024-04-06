/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:08:25 by rgarcia           #+#    #+#             */
/*   Updated: 2023/06/03 15:55:36 by rgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	get_drawstart(t_cam cam, int *y, int *big)
{
	if (cam.draw_start <= cam.draw_end)
	{
		*y = cam.draw_start;
		*big = cam.draw_end;
	}
	else
	{
		*y = cam.draw_end;
		*big = cam.draw_start;
	}
}

void	draw_line(t_params p, int x, int s_wy)
{
	int				y;
	int				big;
	double			step;
	double			tex_start;
	unsigned int	color;

	get_drawstart(p.cam, &y, &big);
	step = 1.0 * p.tex[p.cam.side].height_img / p.cam.line_height;
	tex_start = (y - s_wy / 2 + p.cam.line_height / 2) * step;
	while (y < big)
	{
		p.tex[p.cam.side].tex_y = \
			(int)tex_start & (p.tex[p.cam.side].height_img - 1);
		color = get_text_pixel(p.tex[p.cam.side]);
		my_mlx_pixel_put(&p.img, x, y, color);
		tex_start += step;
		y++;
	}
}

void	get_linedraw(t_params *p)
{
	float	sinangle;

	sinangle = p->cam.sinangle;
	p->cam.correct_dist = 0;
	if (p->cam.side % 2 == 0)
		p->cam.correct_dist = \
			(p->cam.prog_x - p->cam.delta_x) * cos(sinangle - p->cam.camera_x);
	else if (p->cam.side % 2 == 1)
		p->cam.correct_dist = \
			(p->cam.prog_y - p->cam.delta_y) * cos(sinangle - p->cam.camera_x);
	p->cam.line_height = (p->vmlx.size_winy / p->cam.correct_dist);
	p->cam.draw_start = (-p->cam.line_height / 2) + (p->vmlx.size_winy / 2);
	p->cam.draw_end = (p->cam.line_height / 2) + (p->vmlx.size_winy / 2);
	if (p->cam.draw_start < 0)
		p->cam.draw_start = 0;
	else if (p->cam.draw_start >= p->vmlx.size_winy)
		p->cam.draw_start = p->vmlx.size_winy - 1;
	if (p->cam.draw_end < 0)
		p->cam.draw_end = 0;
	else if (p->cam.draw_end >= p->vmlx.size_winy)
		p->cam.draw_end = p->vmlx.size_winy - 1;
}

void	drawing_map(t_params *p)
{
	p->img.img = \
		mlx_new_image(p->vmlx.mlx_ptr, p->vmlx.size_winx, p->vmlx.size_winy);
	p->img.addr = mlx_get_data_addr(p->img.img, &p->img.bits_per_pixel, \
		&p->img.line_length, &p->img.endian);
	floor_cast(p);
	raycast_lines(p);
	mlx_put_image_to_window(p->vmlx.mlx_ptr, p->vmlx.win_ptr, p->img.img, 0, 0);
	mlx_destroy_image(p->vmlx.mlx_ptr, p->img.img);
}
