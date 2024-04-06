/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_east.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:47:23 by fsariogl          #+#    #+#             */
/*   Updated: 2023/04/18 18:47:26 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_path(t_vars *vars, int *i, int *j)
{
	vars->east[(*j)] = vars->gnl_ret[(*i)];
	(*i) = (*i) + 1;
	(*j) = (*j) + 1;
}

void	get_east(t_vars *vars, int i)
{
	int	j;

	j = 0;
	i++;
	if (vars->gnl_ret[i] == 'A')
		i++;
	else
		fail("Error\nBad format for east\n", vars);
	i++;
	while (vars->gnl_ret[i] == ' ')
		i++;
	if (vars->gnl_ret[i] == '\0')
		fail("Error\nMissing path for east\n", vars);
	vars->east = malloc(sizeof(char) * (strlen_itoc(vars->gnl_ret, i, '\0')
				+ 1));
	if (!vars->east)
		fail("Malloc error !", vars);
	while (vars->gnl_ret[i] && vars->gnl_ret[i] != '\n')
		check_path(vars, &i, &j);
	vars->east[j] = '\0';
	j = open(vars->east, O_RDONLY);
	if (j == -1)
		fail("Error\nBad path for east\n", vars);
	close(j);
}
