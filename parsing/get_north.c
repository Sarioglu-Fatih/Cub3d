/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_north.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:47:35 by fsariogl          #+#    #+#             */
/*   Updated: 2023/04/18 18:47:37 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	get_north_next(t_vars *vars, int *i, int *j)
{
	vars->north[(*j)] = vars->gnl_ret[(*i)];
	(*i) = (*i) + 1;
	(*j) = (*j) + 1;
}

void	get_north(t_vars *vars, int i)
{
	int	j;

	j = 0;
	i++;
	if (vars->gnl_ret[i] == 'O')
		i++;
	else
		fail("Error\nBad format for north\n", vars);
	i++;
	while (vars->gnl_ret[i] == ' ')
		i++;
	if (vars->gnl_ret[i] == '\0')
		fail("Error\nMissing path for north\n", vars);
	vars->north = malloc(sizeof(char) * (strlen_itoc(vars->gnl_ret, i, '\0')
				+ 1));
	if (!vars->north)
		fail("Malloc error", vars);
	while (vars->gnl_ret[i] && vars->gnl_ret[i] != '\n')
		get_north_next(vars, &i, &j);
	vars->north[j] = '\0';
	j = open(vars->north, O_RDONLY);
	if (j == -1)
		fail("Error\nBad path for north\n", vars);
	close(j);
}
