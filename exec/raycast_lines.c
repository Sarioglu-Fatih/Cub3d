/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:08:17 by rgarcia           #+#    #+#             */
/*   Updated: 2023/06/03 15:51:05 by rgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	get_sinangle(t_params *p, int i)
{
	float	sinangle;

	p->info.map_x = (int)p->info.start_x;
	p->info.map_y = (int)p->info.start_y;
	p->cam.angle = ((double)(p->vmlx.size_winx - i) \
		/ (double)p->vmlx.size_winx * p->cam.fov) + p->cam.camera_x;
	if (p->cam.angle > 2 * M_PI)
		p->cam.angle -= 2 * M_PI;
	else if (p->cam.angle < 0)
		p->cam.angle += 2 * M_PI;
	sinangle = p->cam.angle - (p->cam.fov / 2);
	if (sinangle > 2 * M_PI)
		sinangle -= 2 * M_PI;
	else if (sinangle < 0)
		sinangle += 2 * M_PI;
	p->cam.sinangle = sinangle;
	p->cam.cosa = cos(sinangle);
	p->cam.sina = sin(sinangle);
	if (p->cam.cosa == 1 || p->cam.cosa == -1)
		p->cam.sina = 0;
	if (p->cam.sina == 1 || p->cam.sina == -1)
		p->cam.cosa = 0;
}

static void	first_prog(t_params *p)
{
	p->cam.first_x = 1;
	p->cam.first_y = 1;
	if (p->cam.cosa > 0)
		p->cam.first_x = 1 - (p->info.start_x - (int)p->info.start_x);
	else if (p->cam.cosa < 0)
		p->cam.first_x = (p->info.start_x - (int)p->info.start_x);
	if (p->cam.sina > 0)
		p->cam.first_y = (p->info.start_y - (int)p->info.start_y);
	else if (p->cam.sina < 0)
		p->cam.first_y = 1 - (p->info.start_y - (int)p->info.start_y);
	p->cam.prog_x = p->cam.delta_x * p->cam.first_x;
	if (p->cam.prog_x < 0)
		p->cam.prog_x = p->cam.prog_x * -1;
	p->cam.prog_y = p->cam.delta_y * p->cam.first_y;
	if (p->cam.prog_y < 0)
		p->cam.prog_y = p->cam.prog_y * -1;
	p->cam.curr_x = p->cam.cosa * p->cam.prog_y;
	p->cam.curr_y = p->cam.sina * p->cam.prog_x;
}

static void	get_delta(t_params *p)
{
	p->cam.delta_x = 0.0;
	p->cam.delta_y = 0.0;
	if (p->cam.cosa == 0)
		p->cam.delta_x = 10000;
	else
		p->cam.delta_x = 1 / p->cam.cosa;
	if (p->cam.sina == 0)
		p->cam.delta_y = 10000;
	else
		p->cam.delta_y = 1 / p->cam.sina;
	if (p->cam.delta_x < 0)
		p->cam.delta_x = p->cam.delta_x * -1;
	if (p->cam.delta_y < 0)
		p->cam.delta_y = p->cam.delta_y * -1;
}

void	raycast_lines(t_params *p)
{
	int	i;

	i = 0;
	while (i < p->vmlx.size_winx)
	{
		get_sinangle(p, i);
		get_delta(p);
		first_prog(p);
		p->cam.hit = 0;
		while (p->cam.hit == 0)
			get_rayprog(p);
		get_linedraw(p);
		p->tex[p->cam.side].tex_x = \
			get_tex_x(p->cam, p->info, p->tex[p->cam.side]);
		draw_line(*p, i, p->vmlx.size_winy);
		i++;
	}
}
