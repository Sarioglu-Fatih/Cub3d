/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_west.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:47:44 by fsariogl          #+#    #+#             */
/*   Updated: 2023/04/18 18:47:46 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	get_west_next(t_vars *vars, int *i, int *j)
{
	vars->west[(*j)] = vars->gnl_ret[(*i)];
	(*i) = (*i) + 1;
	(*j) = (*j) + 1;
}

void	get_west(t_vars *vars, int i)
{
	int	j;

	j = 0;
	i++;
	if (vars->gnl_ret[i] == 'E')
		i++;
	else
		fail("Error\nBad format for west\n", vars);
	i++;
	while (vars->gnl_ret[i] == ' ')
		i++;
	if (vars->gnl_ret[i] == '\0')
		fail("Error\nMissing path for west\n", vars);
	vars->west = malloc(sizeof(char) * (strlen_itoc(vars->gnl_ret, i, '\0')
				+ 1));
	if (!vars->west)
		fail("Malloc error !", vars);
	while (vars->gnl_ret[i] && vars->gnl_ret[i] != '\n')
		get_west_next(vars, &i, &j);
	vars->west[j] = '\0';
	j = open(vars->west, O_RDONLY);
	if (j == -1)
		fail("Error\nBad path for west\n", vars);
	close(j);
}
