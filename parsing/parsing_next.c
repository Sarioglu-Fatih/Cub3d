/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:47:48 by fsariogl          #+#    #+#             */
/*   Updated: 2023/04/18 18:47:50 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_vars(t_vars *vars)
{
	if (!vars->north)
		fail("Error\nNorth path missing\n", vars);
	else if (!vars->south)
		fail("Error\nSouth path missing\n", vars);
	else if (!vars->east)
		fail("Error\nEast path missing\n", vars);
	else if (!vars->west)
		fail("Error\nWest path missing\n", vars);
	else if (!vars->floor)
		fail("Error\nFloor color missing\n", vars);
	else if (!vars->ceiling)
		fail("Error\nCeiling path missing\n", vars);
	else if (!vars->map_in_str)
		fail("Error\nMap missing\n", vars);
}

int	strlen_itoc(char *str, int i, char c)
{
	int	size;

	size = 0;
	while (str[i] && str[i] != c)
	{	
		size++;
		i++;
	}
	return (size);
}

int	map_char(char c)
{
	if (c == '1' || c == '0')
		return (TRUE);
	return (FALSE);
}

int	check_path_and_colors(t_vars *vars)
{
	if (!(vars->north && vars->south && vars->east && vars->west
			&& vars->floor && vars->ceiling))
		return (FALSE);
	return (TRUE);
}
