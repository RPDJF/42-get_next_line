/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:38:17 by rude-jes          #+#    #+#             */
/*   Updated: 2023/10/19 18:06:07 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4
#endif

/*
*	trouver \n dans buffer
*	 si \n est prsent
*	 		aggrandir tab et concat buffer jusqu'à \n
*			décaler buffer avec memmove
*			changer valeur de bsize
*	 sinon
*			aggrandir tab et concat tout buffer
			bsize = 0
*	 Retourne la taille du nouveau tableau & met a jour la taille de bsize
*/
size_t	fill_frombuffer(void **tab, ssize_t size, char *buff, ssize_t *bsize)
{
	size_t	new_size;
	char	*p_buff_nl;

	p_buff_nl = ft_memchr(buff, '\n', *bsize);
	if (p_buff_nl)
	{
		new_size = size + p_buff_nl - buff + 1;
		*tab = ft_exallocf(*tab, size, new_size);
		if (!*tab)
			return (0);
		ft_memncat(*tab, size, buff, new_size - size);
		if (buff == p_buff_nl)
			ft_memmove(buff, p_buff_nl + 1, *bsize - 1);
		else if (p_buff_nl < buff + *bsize - 1)
			ft_memmove(buff, p_buff_nl + 1, *bsize - (p_buff_nl - buff) - 1);
		*bsize -= (p_buff_nl - buff) + 1;
		return (new_size);
	}
	new_size = size + *bsize;
	*tab = ft_exallocf(*tab, size, new_size);
	if (!*tab)
		return (0);
	ft_memncat(*tab, size, buff, new_size - size);
	*bsize = 0;
	return (new_size);
}

/*
 *	Fill tab pointer with the next line
 */
size_t	fill_tab_nextline(void **tab, ssize_t size, int *fd)
{
	static char		buffer[BUFFER_SIZE];
	static ssize_t	rbytes;

	if (read(*fd, 0, 0))
	{
		rbytes = 0;
		return (0);
	}
	if (rbytes)
		size = fill_frombuffer(tab, size, buffer, &rbytes);
	if (ft_memchr(*tab, '\n', size))
		return (size);
	rbytes = read(*fd, buffer, BUFFER_SIZE);
	if (!rbytes)
		return (size);
	else if (rbytes > 0)
		size = fill_tab_nextline(tab, size, fd);
	else
		return (0);
	return (size);
}

/*
 *	Returns the next line from a file as a string, containing \n.
 *	This functions use creates a static from fd, looping this
 *	functions sends each newline from last one, until EOF char.
 */
char	*get_next_line(int fd)
{
	char		*output;
	ssize_t		tabsize;
	static int	s_fd;

	s_fd = fd;
	output = 0;
	tabsize = 0;
	tabsize = fill_tab_nextline((void **)&output, tabsize, &s_fd);
	if (!tabsize)
	{
		s_fd = 0;
		free(output);
		return (0);
	}
	output = ft_memtostr(output, tabsize);
	if (!output)
		return (0);
	return (output);
}

/*
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	char *line;
	int fd;
	int i;

	i = -1;
	fd = open("test.txt", O_RDONLY);
	while (i++ < 18)
	{
		line = get_next_line(fd);
		printf("> %s\n", line);
		free(line);
	}
	return (0);
}
*/
