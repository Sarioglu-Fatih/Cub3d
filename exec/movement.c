/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:09:08 by rgarcia           #+#    #+#             */
/*   Updated: 2023/05/31 17:40:34 by rgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	move_ratio(double axis)
{
	double	ratio;
	double	abs_cam_y;

	if (axis < 0)
		abs_cam_y = axis * -1;
	else
		abs_cam_y = axis;
	ratio = fmod(abs_cam_y, M_PI * 2);
	ratio = ratio - M_PI;
	if (ratio < 0)
		ratio = ratio * -1;
	ratio = (ratio * (100 / M_PI)) - 50;
	return (ratio);
}

void	lateral_movement(int keycode, t_params *prms)
{
	if (keycode == 100)
	{
		prms->info.start_x += move_ratio(prms->cam.camera_y) / 100;
		prms->info.start_y += move_ratio(prms->cam.camera_x) / 100;
	}
	else if (keycode == 97)
	{
		prms->info.start_x -= move_ratio(prms->cam.camera_y) / 100;
		prms->info.start_y -= move_ratio(prms->cam.camera_x) / 100;
	}
}

void	movement(int keycode, t_params *prms)
{
	if (keycode == 119)
	{
		prms->info.start_x += move_ratio(prms->cam.camera_x) / 100;
		prms->info.start_y -= move_ratio(prms->cam.camera_y) / 100;
	}
	else if (keycode == 115)
	{
		prms->info.start_x -= move_ratio(prms->cam.camera_x) / 100;
		prms->info.start_y += move_ratio(prms->cam.camera_y) / 100;
	}
	else
		lateral_movement(keycode, prms);
}
