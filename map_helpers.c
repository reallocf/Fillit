/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csummers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 13:16:52 by csummers          #+#    #+#             */
/*   Updated: 2016/11/25 13:16:52 by csummers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		set_up_g_map(void)
{
	int		i;
	int		j;

	if (!(g_map = ft_strarrnew(g_sq_edge_size)))
		return (0);
	i = 0;
	while (i < g_sq_edge_size)
	{
		if (!(g_map[i] = ft_strnew(g_sq_edge_size)))
			return (0);
		j = 0;
		while (j < g_sq_edge_size)
			g_map[i][j++] = '.';
		i++;
	}
	return (1);
}

void	reset_g_map(t_block *b, int x, int y)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		g_map[b->y[i] + y][b->x[i] + x] = '.';
		i++;
	}
}

void	free_g_map(void)
{
	int		i;

	i = 0;
	while (i < g_sq_edge_size)
		ft_strdel(&g_map[i++]);
	ft_strarrdel(&g_map);
}

int		print_map(void)
{
	int		i;

	i = 0;
	while (i < g_sq_edge_size)
		ft_putendl(g_map[i++]);
	free_g_map();
	return (0);
}
