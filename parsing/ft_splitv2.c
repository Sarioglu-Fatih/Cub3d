/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitv2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:47:06 by fsariogl          #+#    #+#             */
/*   Updated: 2023/04/18 18:47:07 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	**ft_split_next(char **tab, const char *str, char c)
{
	int	i;
	int	l;
	int	co;

	i = 0;
	l = 1;
	co = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			tab[l][co] = str[i];
			co++;
		}
		else if (str[i] == c)
		{
			l++;
			co = 0;
		}
		i++;
	}
	return (tab);
}

static char	**space_in_tab(char **tab, const char *str, char c, int max_cl[2])
{
	int	l;
	int	co;

	l = 0;
	while (l < max_cl[1])
	{
		co = 0;
		tab[l] = malloc(sizeof(char) * max_cl[0] + 1);
		if (!tab[l])
			return (NULL);
		while (co < max_cl[0])
		{
			tab[l][co] = ' ';
			co++;
		}
		tab[l][co] = '\0';
		l++;
	}
	tab[l] = NULL;
	return (ft_split_next(tab, str, c));
}

static void	ft_splitv2_init(int *i, int *l, int *co, int *max_cl)
{
	(*i) = 0;
	(*l) = 0;
	(*co) = 0;
	(*max_cl) = 0;
}

void	co_and_l(int *co, int *l)
{
	(*co) = 0;
	(*l) = (*l) + 1;
}

char	**ft_splitv2(const char *str, char c)
{
	int		i;
	int		l;
	int		co;
	int		max_cl[2];
	char	**tab;

	ft_splitv2_init(&i, &l, &co, &max_cl[0]);
	while (str[i])
	{
		if (str[i] == c)
			co_and_l(&co, &l);
		co++;
		if (co > max_cl[0])
			max_cl[0] = co + 3;
		i++;
	}
	tab = malloc(sizeof(char *) * (l + 3 + 1));
	if (!tab)
		return (NULL);
	max_cl[1] = l + 3;
	return (space_in_tab(tab, str, c, max_cl));
}
