/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:11:01 by rgarcia           #+#    #+#             */
/*   Updated: 2023/06/03 16:45:18 by rgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	load_single_text(t_tex *tex, t_varmlx vmlx, char *texture_path)
{
	tex->text = mlx_xpm_file_to_image(vmlx.mlx_ptr, texture_path, \
		&tex->width_img, &tex->height_img);
	if (tex->text == NULL)
		return (1);
	tex->text_adr = mlx_get_data_addr(tex->text, \
		&tex->bits_per_pixel, &tex->line_length, &tex->endian);
	if (tex->text_adr == NULL)
		return (1);
	return (0);
}

t_tex	*text_error(t_tex *tex, t_varmlx vmlx, int mode)
{
	if (mode == 0)
		free(tex);
	if (mode == 1)
	{
		mlx_destroy_image(vmlx.mlx_ptr, tex[0].text);
		free(tex);
	}
	if (mode == 2)
	{
		mlx_destroy_image(vmlx.mlx_ptr, tex[0].text);
		mlx_destroy_image(vmlx.mlx_ptr, tex[1].text);
		free(tex);
	}
	if (mode == 3)
	{
		mlx_destroy_image(vmlx.mlx_ptr, tex[0].text);
		mlx_destroy_image(vmlx.mlx_ptr, tex[1].text);
		mlx_destroy_image(vmlx.mlx_ptr, tex[2].text);
		free(tex);
	}
	ft_putstr_fd("Error\nBad Texture\n", 2);
	return (NULL);
}

t_tex	*load_all_textures(t_varmlx vmlx, t_vars v)
{
	t_tex	*tex;
	int		i;

	tex = malloc(sizeof(t_tex) * 4);
	if (!tex)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		tex[i].text = NULL;
		tex[i].text_adr = NULL;
		i++;
	}
	if (load_single_text(&tex[0], vmlx, v.east) == 1)
		return (text_error(tex, vmlx, 0));
	if (load_single_text(&tex[1], vmlx, v.south) == 1)
		return (text_error(tex, vmlx, 1));
	if (load_single_text(&tex[2], vmlx, v.west) == 1)
		return (text_error(tex, vmlx, 2));
	if (load_single_text(&tex[3], vmlx, v.north) == 1)
		return (text_error(tex, vmlx, 3));
	return (tex);
}

int	get_text_pixel(t_tex tex)
{
	int	color;

	if (tex.tex_x < 0 || tex.tex_x >= tex.width_img)
		return (0);
	if (tex.tex_y < 0 || tex.tex_y >= tex.height_img)
		return (0);
	color = *(int *)(tex.text_adr + tex.tex_y * tex.line_length \
		+ tex.tex_x * tex.bits_per_pixel / 8);
	return (color);
}

int	get_tex_x(t_cam cam, t_mapinfo info, t_tex tex)
{
	double	wall_pos;
	int		tex_x;

	info.map_x = info.map_x;
	if (cam.side == 0 || cam.side == 2)
		wall_pos = info.start_y - (cam.curr_y - (cam.sina * cam.delta_x));
	else
		wall_pos = info.start_x + (cam.curr_x - (cam.cosa * cam.delta_y));
	wall_pos -= (int)(wall_pos);
	if (wall_pos < 0)
		wall_pos *= -1;
	tex_x = (int)(wall_pos * (double)tex.width_img);
	return (tex_x);
}
