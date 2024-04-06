/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:08:32 by rgarcia           #+#    #+#             */
/*   Updated: 2023/06/03 15:12:57 by rgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_window(t_params *prms)
{
	if (prms->tex)
	{
		mlx_destroy_image(prms->vmlx.mlx_ptr, prms->tex[0].text);
		mlx_destroy_image(prms->vmlx.mlx_ptr, prms->tex[1].text);
		mlx_destroy_image(prms->vmlx.mlx_ptr, prms->tex[2].text);
		mlx_destroy_image(prms->vmlx.mlx_ptr, prms->tex[3].text);
	}
	mlx_destroy_window(prms->vmlx.mlx_ptr, prms->vmlx.win_ptr);
	mlx_destroy_display(prms->vmlx.mlx_ptr);
	free(prms->vmlx.mlx_ptr);
	ft_free_tab(prms->v.map_data);
	free(prms->v.north);
	free(prms->v.west);
	free(prms->v.east);
	free(prms->v.south);
	free(prms->v.floor);
	free(prms->v.ceiling);
	free(prms->map);
	free(prms->tex);
	close(prms->v.fd);
	exit(0);
}

int	key_hook(int keycode, t_params *prms)
{
	if (keycode == 65307)
		close_window(prms);
	if (keycode == 65361)
		rotation_camera(keycode, prms);
	if (keycode == 65363)
		rotation_camera2(keycode, prms);
	else if (keycode == 119 || keycode == 97
		|| keycode == 115 || keycode == 100)
		movement(keycode, prms);
	drawing_map(prms);
	return (0);
}
