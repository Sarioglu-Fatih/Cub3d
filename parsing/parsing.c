/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:47:56 by fsariogl          #+#    #+#             */
/*   Updated: 2023/04/18 18:47:58 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	distribution(t_vars *vars, int i)
{
	if (vars->gnl_ret[i] == 'N')
		get_north(vars, i);
	if (vars->gnl_ret[i] == 'S')
		get_south(vars, i);
	if (vars->gnl_ret[i] == 'E')
		get_east(vars, i);
	if (vars->gnl_ret[i] == 'W')
		get_west(vars, i);
	if (vars->gnl_ret[i] == 'F')
		get_floor(vars, i);
	if (vars->gnl_ret[i] == 'C')
		get_ceiling(vars, i);
}

static void	check_double(t_vars *vars, int i)
{
	char	c;

	c = vars->gnl_ret[i];
	if (c == 'N' && vars->north)
		fail("Error\nPut one texture per face\n", vars);
	else if (c == 'S' && vars->south)
		fail("Error\nPut one texture per face\n", vars);
	else if (c == 'E' && vars->east)
		fail("Error\nPut one texture per face\n", vars);
	else if (c == 'W' && vars->west)
		fail("Error\nPut one texture per face\n", vars);
	else if (c == 'F' && vars->floor)
		fail("Error\nPut three colors for the floor one time\n", vars);
	else if (c == 'C' && vars->ceiling)
		fail("Error\nPut three colors for the ceiling one time\n", vars);
	else if (c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != 'F'
		&& c != 'C' && c != '1' && c != '\n')
		fail("Error\nPut path, colors and closed map only\n", vars);
}

static int	checking(t_vars *vars, int *mapping)
{
	if (check_path_and_colors(vars) == FALSE)
		fail("Error\nPut 4 path and 2 colors before the map\n", vars);
	(*mapping) = 1;
	vars->map_in_str = ft_strdup(vars->gnl_ret);
	return (0);
}

static void	parse_line(t_vars *vars, int *mapping)
{
	int		i;
	char	*dump;

	i = 0;
	while (vars->gnl_ret[i] && vars->gnl_ret[i] == ' ')
		i++;
	check_double(vars, i);
	if (vars->gnl_ret[i] == '1' && (*mapping) == 2)
		fail("Error\nPut one map only\n", vars);
	if (map_char(vars->gnl_ret[i]) == FALSE && (*mapping == 1))
		(*mapping) = 2;
	else if (map_char(vars->gnl_ret[i]) == TRUE && (*mapping) == 0)
		checking(vars, mapping);
	else if (map_char(vars->gnl_ret[i]) == TRUE && (*mapping) == 1)
	{
		dump = vars->map_in_str;
		vars->map_in_str = ft_strjoin(vars->map_in_str, vars->gnl_ret);
		free(dump);
	}
	if (vars->gnl_ret[i] == '\n')
		return ;
	distribution(vars, i);
}

void	parse_file(t_vars *vars)
{
	int		mapping;

	mapping = 0;
	vars->gnl_ret = "a";
	while (vars->gnl_ret)
	{
		vars->gnl_ret = get_next_line(vars->fd);
		if (vars->gnl_ret != NULL)
			parse_line(vars, &mapping);
		free(vars->gnl_ret);
	}
	check_vars(vars);
	vars->map_data = ft_splitv2(vars->map_in_str, '\n');
	if (vars->map_data == NULL)
		fail("Malloc error\n", vars);
	check_map(vars);
	free(vars->map_in_str);
	get_colors(vars);
}
