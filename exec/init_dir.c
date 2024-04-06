/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warnora <warnora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:08:02 by rgarcia           #+#    #+#             */
/*   Updated: 2023/06/03 15:21:28 by rgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_dir2(char cardinal, t_cam *cam)
{
	if (cardinal == 'W')
	{
		cam->camera_x = M_PI;
		cam->camera_y = M_PI / 2;
	}
	else if (cardinal == 'E')
	{
		cam->camera_x = 0;
		cam->camera_y = 3 * M_PI / 2;
	}
}

void	init_dir(char cardinal, t_cam *cam)
{
	if (cardinal == 'N')
	{
		cam->camera_x = M_PI / 2;
		cam->camera_y = 0;
	}
	else if (cardinal == 'S')
	{
		cam->camera_x = 3 * M_PI / 2;
		cam->camera_y = M_PI;
	}
	else
		init_dir2(cardinal, cam);
}
