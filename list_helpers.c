/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csummers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 15:03:45 by csummers          #+#    #+#             */
/*   Updated: 2016/11/25 15:03:46 by csummers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	place_in_list(t_block *block)
{
	block->last = g_head->last;
	block->next = g_head;
	block->last->next = block;
	g_head->last = block;
	g_block_count++;
}

void	remove_from_list(t_block *b)
{
	b->next->last = b->last;
	b->last->next = b->next;
}

void	replace_in_list(t_block *b)
{
	b->next->last = b;
	b->last->next = b;
}
