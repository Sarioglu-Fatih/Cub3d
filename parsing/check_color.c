/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:46:51 by fsariogl          #+#    #+#             */
/*   Updated: 2023/04/18 18:46:53 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_color_size(t_vars *vars, int i)
{
	int	nb;

	nb = vars->gnl_ret[i] - '0';
	i++;
	while (vars->gnl_ret[i] >= '0' && vars->gnl_ret[i] <= '9')
	{
		nb = nb * 10;
		nb = nb + (vars->gnl_ret[i] - '0');
		i++;
	}
	if (nb > 255)
		fail("Error\nBad color of ceiling or floor\n", vars);
}

void	check_all_color(t_vars *vars, int i)
{
	while (vars->gnl_ret[i])
	{
		check_color_size(vars, i);
		while (vars->gnl_ret[i] >= '0' && vars->gnl_ret[i] <= '9')
			i++;
		if (vars->gnl_ret[i] == ',' || vars->gnl_ret[i] == '\n')
			i++;
	}
	if (vars->gnl_ret[i] != '\0')
		fail("Error\nBad format of ceiling or floor\n", vars);
}
