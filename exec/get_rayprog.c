/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rayprog.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:06:20 by rgarcia           #+#    #+#             */
/*   Updated: 2023/06/03 15:13:20 by rgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	get_mapstep(t_params *p, int *step_x, int *step_y)
{
	*step_x = 0;
	*step_y = 0;
	if (p->cam.cosa > 0)
		*step_x = 1;
	else if (p->cam.cosa < 0)
		*step_x = -1;
	if (p->cam.sina > 0)
		*step_y = -1;
	else if (p->cam.sina < 0)
		*step_y = 1;
}

static void	get_prog(t_params *p, int mode, int step_x, int step_y)
{
	if (mode == 1)
	{
		p->info.map_x += step_x;
		if (step_x == 1)
			p->cam.side = 0;
		else if (step_x == -1)
			p->cam.side = 2;
		p->cam.prog_x += p->cam.delta_x;
		p->cam.curr_y += p->cam.sina * p->cam.delta_x;
	}
	else
	{
		p->info.map_y += step_y;
		if (step_y == 1)
			p->cam.side = 1;
		else if (step_y == -1)
			p->cam.side = 3;
		p->cam.prog_y += p->cam.delta_y;
		p->cam.curr_x += p->cam.cosa * p->cam.delta_y;
	}
}

void	get_rayprog(t_params *p)
{
	int	step_x;
	int	step_y;

	get_mapstep(p, &step_x, &step_y);
	if (p->cam.prog_x <= p->cam.prog_y)
		get_prog(p, 1, step_x, step_y);
	else
		get_prog(p, 2, step_x, step_y);
	if (p->info.map_y < 0 || p->info.map_y >= p->info.size_y)
		p->cam.hit = 1;
	else if (p->info.map_x < 0 || p->info.map_x > p->info.size_x)
		p->cam.hit = 1;
	else if (p->v.map_data[p->info.map_y][p->info.map_x] == '1')
		p->cam.hit = 1;
}
