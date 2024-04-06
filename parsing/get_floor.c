/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_floor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:47:29 by fsariogl          #+#    #+#             */
/*   Updated: 2023/04/18 18:47:32 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_floor_char(t_vars *vars, int *i, int *nb, int *nb_of_nb)
{
	(*nb) = 0;
	while (vars->gnl_ret[(*i)] >= '0' && vars->gnl_ret[(*i)] <= '9')
	{
		(*i) = (*i) + 1;
		(*nb) = (*nb) + 1;
	}
	if ((*nb) > 3 || (*nb) == 0 || (vars->gnl_ret[(*i)] != ','
			&& vars->gnl_ret[(*i)] != '\0' && vars->gnl_ret[(*i)] != '\n'))
	{
		fail("Error\nBad format of floor\n", vars);
	}
	if (vars->gnl_ret[(*i)])
		(*i) = (*i) + 1;
	(*nb_of_nb) = (*nb_of_nb) + 1;
}

void	get_floor_next(t_vars *vars, int *i, int *temp)
{
	vars->floor[(*temp)] = vars->gnl_ret[(*i)];
	(*i) = (*i) + 1;
	(*temp) = (*temp) + 1;
}

void	get_floor(t_vars *vars, int i)
{
	int	temp[3];

	i++;
	while (vars->gnl_ret[i] == ' ')
		i++;
	temp[1] = 0;
	temp[2] = i;
	if (vars->gnl_ret[i] == '\0' || vars->gnl_ret[i] == '\n')
		fail("Error\nColors missing on floor\n", vars);
	while (vars->gnl_ret[i])
		check_floor_char(vars, &i, &temp[0], &temp[1]);
	if (temp[1] != 3)
		fail("Error\nBad format of floor\n", vars);
	i = temp[2];
	vars->floor = malloc(sizeof(char) * (strlen_itoc(vars->gnl_ret, i, 0) + 1));
	if (!vars->floor)
		fail("Malloc error\n", vars);
	temp[0] = 0;
	while (vars->gnl_ret[i] && vars->gnl_ret[i] != '\n')
		get_floor_next(vars, &i, &temp[0]);
	vars->floor[temp[0]] = '\0';
	check_all_color(vars, temp[2]);
}
