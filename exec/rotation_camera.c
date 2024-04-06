/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warnora <warnora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:08:45 by rgarcia           #+#    #+#             */
/*   Updated: 2023/06/03 15:16:09 by rgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotation_camera2(int keycode, t_params *p)
{
	double	angle;

	angle = M_PI / 12;
	if (keycode == 65363)
	{
		p->cam.camera_x -= angle;
		p->cam.camera_y -= angle;
	}
}

void	rotation_camera(int keycode, t_params *p)
{
	double	angle;

	angle = M_PI / 12;
	if (keycode == 65361)
	{
		p->cam.camera_x += angle;
		p->cam.camera_y += angle;
	}
}
