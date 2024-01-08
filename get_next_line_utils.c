/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:41:46 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/08 05:04:44 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_reallocf(void *ptr, size_t size, size_t newsize)
{
	unsigned char	*old_alloc;
	unsigned char	*new_alloc;
	size_t			i;

	i = 0;
	if (ptr == 0)
		return (malloc(newsize));
	old_alloc = (unsigned char *)ptr;
	new_alloc = (unsigned char *)malloc(newsize);
	if (new_alloc == 0)
	{
		free(ptr);
		return (0);
	}
	while (i < size && i < newsize)
	{
		new_alloc[i] = old_alloc[i];
		i++;
	}
	free(ptr);
	return (new_alloc);
}

/*
*	ft_memmove copies n bytes from src to dest
*	It does protect the memory from overlapping
*	Returns dest
*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (0);
	i = 0;
	if (dest > src)
		while (i < n--)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	else
		while (i++ < n)
			((unsigned char *)dest)[i - 1] = ((unsigned char *)src)[i - 1];
	return (dest);
}

/*
 *	Search for specific byte inside *s memory pointer
 *	Return a pointer to the first occurence
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (0);
}

/*
 *	Concatenate src mem to dest mem
 *	Dest needs to have enough space
 *	Returns null if dest pointer is null
 */
void	*ft_memncat(void *dest, size_t start, void *src, size_t nb)
{
	int	i;

	if (!dest)
		return (0);
	i = 0;
	while ((unsigned int)i < nb)
	{
		((unsigned char *)dest)[start + i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

/*
 *	Extend mem allocation to add the \0 char at the end
 */
char	*ft_memtostr(void *mem, size_t size)
{
	char	eos;

	eos = '\0';
	mem = ft_reallocf(mem, size, size + 1);
	if (!mem)
		return (0);
	((unsigned char *)mem)[size] = eos;
	return ((char *)mem);
}
