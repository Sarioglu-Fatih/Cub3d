/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:46:56 by fsariogl          #+#    #+#             */
/*   Updated: 2023/04/18 18:46:58 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_nb_of_cardinal_points(int nb, t_vars *vars)
{
	if (nb < 1)
		fail("Error\nPut N, S, E or W for player spawn\n", vars);
	else if (nb > 1)
		fail("Error\nSeveral spawn in the map\n", vars);
}

static void	check_all_char(t_vars *vars)
{
	int		l;
	int		co;
	int		nb;
	char	c;

	l = 0;
	co = 0;
	nb = 0;
	while (vars->map_data[l])
	{
		co = 0;
		while (vars->map_data[l][co])
		{
			c = vars->map_data[l][co];
			if (c != ' ' && c != '0' && c != '1' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W')
				fail("Error\nBad character in the map\n", vars);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				nb++;
			co++;
		}
		l++;
	}
	check_nb_of_cardinal_points(nb, vars);
}

void	check_map(t_vars *vars)
{
	int		l;
	int		co;
	char	c;

	l = 1;
	check_all_char(vars);
	while (vars->map_data[l + 1])
	{
		co = 1;
		while (vars->map_data[l][co + 1] != '\0')
		{
			c = vars->map_data[l][co];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (vars->map_data[l][co + 1] == ' '
					|| vars->map_data[l][co - 1] == ' '
					|| vars->map_data[l + 1][co] == ' '
					|| vars->map_data[l - 1][co] == ' ')
					fail("Error\nThe map is open\n", vars);
			}
			co++;
		}
		l++;
	}
}
