/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csummers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 20:10:54 by csummers          #+#    #+#             */
/*   Updated: 2016/11/23 20:10:56 by csummers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** sets up global variables then starts the read
**
** throws error if malloc or start_read throw an error
*/

int		read_in(int fd)
{
	g_id = 'A';
	g_block_count = 0;
	if (!(g_head = (t_block*)malloc(sizeof(t_block))))
		return (0);
	g_head->next = g_head;
	g_head->last = g_head;
	return (start_read(fd));
}

/*
** reads from the file that fd points to and fills g_head's associated list
** with the different blocks
**
** throws error if char_check or block_controller throw an error or if read
** throws an error or if the file is empty or any other sort of improper
** file as described by the spec
*/

int		start_read(int fd)
{
	int			i[2];
	int			pd_count;
	char		buff[4][4];
	int			coord[4][2];

	i[0] = 0;
	pd_count = 0;
	while (read(fd, buff[i[0]], 4) > 0)
	{
		i[1] = 0;
		while (i[1] < 4)
			if (!char_check(buff[i[0]], coord, &pd_count, i))
				return (0);
		if (++(i[0]) == 4)
		{
			if (!block_controller(coord, &pd_count, i, fd))
				return (0);
		}
		else
		{
			if (read(fd, buff[0], 1) == -1 || **buff != '\n')
				return (0);
		}
	}
	return (i[0] != 4 ? 0 : 1);
}

/*
** if '#', add location to coordinate list
** iterate i[1] to loop through current buff
**
** throws error if character isn't '.' or '#' or if there are too many '#'s
*/

int		char_check(char buff[4], int coord[4][2], int *pd_count, int i[2])
{
	if (buff[i[1]] != '.' && buff[i[1]] != '#')
		return (0);
	if (buff[i[1]] == '#')
	{
		if (*pd_count == 5)
			return (0);
		coord[*pd_count][0] = i[1];
		coord[*pd_count][1] = i[0];
		(*pd_count)++;
	}
	i[1]++;
	return (1);
}

/*
** calls convert_to_block
** resets i[0] when necessary and pd_count always
**
** throws error if pd_count is not 4 or if convert_to_block throws an error
** or if read throws an error or if the new line isn't properly there
*/

int		block_controller(int coord[4][2], int *pd_count, int i[2], int fd)
{
	char	buff[2];
	int		res;

	if (*pd_count != 4 || !convert_to_block(coord))
		return (0);
	if ((res = read(fd, buff, 2)) == -1 || *buff != '\n')
		return (0);
	if (buff[1] != '\n' && res != 1)
		return (0);
	if (res != 1)
		i[0] = 0;
	*pd_count = 0;
	return (1);
}
