/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ceiling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:47:10 by fsariogl          #+#    #+#             */
/*   Updated: 2023/04/18 18:47:11 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_ceiling_char(t_vars *vars, int *i, int *nb, int *nb_of_nb)
{
	(*nb) = 0;
	while (vars->gnl_ret[(*i)] >= '0' && vars->gnl_ret[(*i)] <= '9')
	{
		(*i) = (*i) + 1;
		(*nb) = (*nb) + 1;
	}
	if ((*nb) > 3 || (*nb) == 0 || (vars->gnl_ret[(*i)] != ','
			&& vars->gnl_ret[(*i)] != '\0' && vars->gnl_ret[(*i)] != '\n'))
		fail("Error\nBad format of ceiling\n", vars);
	if (vars->gnl_ret[(*i)])
		(*i) = (*i) + 1;
	(*nb_of_nb) = (*nb_of_nb) + 1;
}

void	get_ceiling_next(t_vars *vars, int *i, int *temp)
{
	vars->ceiling[(*temp)] = vars->gnl_ret[(*i)];
	(*i) = (*i) + 1;
	(*temp) = (*temp) + 1;
}

void	get_ceiling(t_vars *vars, int i)
{
	int	temp[3];

	i++;
	while (vars->gnl_ret[i] == ' ')
		i++;
	temp[1] = 0;
	temp[2] = i;
	if (vars->gnl_ret[i] == '\0' || vars->gnl_ret[i] == '\n')
		fail("Error\nColors missing on ceiling\n", vars);
	while (vars->gnl_ret[i])
		check_ceiling_char(vars, &i, &temp[0], &temp[1]);
	if (temp[1] != 3)
		fail("Error\nBad format of ceiling\n", vars);
	i = temp[2];
	vars->ceiling = malloc(sizeof(char) * (strlen_itoc(vars->gnl_ret, i, 0)
				+ 1));
	if (!vars->ceiling)
		fail("Malloc error\n", vars);
	temp[0] = 0;
	while (vars->gnl_ret[i] && vars->gnl_ret[i] != '\n')
		get_ceiling_next(vars, &i, &temp[0]);
	vars->ceiling[temp[0]] = '\0';
	check_all_color(vars, temp[2]);
}
