/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:39:05 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/08 04:51:27 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

typedef struct s_gnl
{
	char		buffer[BUFFER_SIZE];
	ssize_t		size;
	int			fd;
	char		*line;
}				t_gnl;

char	*get_next_line(int fd);
void	*ft_reallocf(void *ptr, size_t size, size_t newsize);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memncat(void *dest, size_t start, void *src, size_t nb);
char	*ft_memtostr(void *mem, size_t size);

#endif