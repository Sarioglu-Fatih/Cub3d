/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:47:16 by fsariogl          #+#    #+#             */
/*   Updated: 2023/04/18 18:47:19 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	atoiv2(char *str, int *i)
{
	int	nb;

	nb = 0;
	while (str[(*i)] && str[(*i)] != ',')
	{
		nb = (nb * 10) + (str[(*i)] - '0');
		(*i) = (*i) + 1;
	}
	if (str[(*i)])
		(*i) = (*i) + 1;
	return (nb);
}

void	get_colors(t_vars *vars)
{
	int	i;

	i = 0;
	vars->color_floor = 0x00 + ((atoiv2(vars->floor, &i) * 256) * 256);
	vars->color_floor = vars->color_floor + (atoiv2(vars->floor, &i) * 256);
	vars->color_floor = vars->color_floor + atoiv2(vars->floor, &i);
	i = 0;
	vars->color_ceiling = 0x00 + (((atoiv2(vars->ceiling, &i) * 256) * 256));
	vars->color_ceiling = vars->color_ceiling + (atoiv2(vars->ceiling, &i)
			* 256);
	vars->color_ceiling = vars->color_ceiling + atoiv2(vars->ceiling, &i);
}
