/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csummers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 20:54:10 by csummers          #+#    #+#             */
/*   Updated: 2016/11/21 20:54:13 by csummers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		main(int argc, char **argv)
{
	int		fd;

	if (argc != 2)
		return (error_msg("usage: fillit input_file"));
	if ((fd = open(argv[1], O_RDONLY)) == -1 || !read_in(fd) || close(fd) < 0)
		return (error_msg("error"));
	g_sq_edge_size = 0;
	while (g_sq_edge_size * g_sq_edge_size < g_block_count * 4)
		g_sq_edge_size++;
	while (1)
	{
		if (!set_up_g_map())
			return (error_msg("error"));
		if (solver())
			return (print_map());
		free_g_map();
		g_sq_edge_size++;
	}
}

int		error_msg(char *s)
{
	ft_putendl(s);
	return (0);
}

int		solver(void)
{
	int			i;
	int			j;
	t_block		*b;

	if (g_head->next == g_head)
		return (1);
	i = 0;
	b = g_head->next;
	while (b != g_head)
	{
		while (IN_SQ(b->y[1] + i) && IN_SQ(b->y[2] + i) && IN_SQ(b->y[3] + i))
		{
			j = 0;
			while (IN_SQ(b->x[1] + j) && IN_SQ(b->x[2] + j) &&
					IN_SQ(b->x[3] + j))
				if (can_fit(b, j++, i))
					return (1);
			i++;
		}
		b = b->next;
	}
	return (0);
}

int		can_fit(t_block *b, int x, int y)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (g_map[b->y[i] + y][b->x[i] + x] != '.')
			return (0);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		g_map[b->y[i] + y][b->x[i] + x] = b->id;
		i++;
	}
	remove_from_list(b);
	if (solver())
		return (1);
	replace_in_list(b);
	reset_g_map(b, x, y);
	return (0);
}
