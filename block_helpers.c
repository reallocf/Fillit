/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csummers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 15:03:34 by csummers          #+#    #+#             */
/*   Updated: 2016/11/25 15:03:34 by csummers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** mallocates room for new block and fills it with info from coords
** also shifts the coordinates to their top-left-most orientation
** then places the block in the list of blocks
**
** throws error if any disjointedness in the coordinates
*/

int		convert_to_block(int coord[4][2])
{
	int			i;
	t_block		*new;

	if (!(new = (t_block*)malloc(sizeof(t_block))))
		return (0);
	new->id = g_id++;
	i = 0;
	while (i < 4)
	{
		new->x[i] = coord[i][0];
		new->y[i] = coord[i][1];
		i++;
	}
	if (!check_adjacency(new))
		return (0);
	shift_to_top_left(new);
	place_in_list(new);
	return (1);
}

/*
** throws error if there are not 6 or 8 total coordinate adjacencies,
** signalling disjointed coordinates
*/

int		check_adjacency(t_block *block)
{
	int		i;
	int		adj_counter;

	i = 0;
	adj_counter = 0;
	while (i < 4)
	{
		adj_adder(block, i, &adj_counter);
		i++;
	}
	if (adj_counter != 6 && adj_counter != 8)
		return (0);
	return (1);
}

/*
** iterates adj_counter up if there is another coord in any direction
*/

void	adj_adder(t_block *block, int i, int *adj_counter)
{
	int		j;

	j = 0;
	while (j < 4)
	{
		if (block->x[i] + 1 == block->x[j] &&
			block->y[i] == block->y[j])
			(*adj_counter)++;
		if (block->x[i] == block->x[j] &&
			block->y[i] + 1 == block->y[j])
			(*adj_counter)++;
		if (block->x[i] - 1 == block->x[j] &&
			block->y[i] == block->y[j])
			(*adj_counter)++;
		if (block->x[i] == block->x[j] &&
			block->y[i] - 1 == block->y[j])
			(*adj_counter)++;
		j++;
	}
}

/*
** rearranges the block so that it points to its top-left-most
** potential spot to place
*/

void	shift_to_top_left(t_block *b)
{
	int		i;

	while (b->x[0] > 0 && b->x[1] > 0 && b->x[2] > 0 && b->x[3] > 0)
	{
		i = 0;
		while (i < 4)
			b->x[i++]--;
	}
	while (b->y[0] > 0 && b->y[1] > 0 && b->y[2] > 0 && b->y[3] > 0)
	{
		i = 0;
		while (i < 4)
			b->y[i++]--;
	}
}
