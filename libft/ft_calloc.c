/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:10:31 by anmakaro          #+#    #+#             */
/*   Updated: 2024/12/14 21:01:53 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	ptr = calloc(count, size);
	return (ptr);
}

/*
void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	size_t	i;
	void	*ptr;

	total_size = count * size;
	if (count && total_size / count != size)
		return (NULL);
	ptr = calloc(count, total_size);
	i = 0;
	if (ptr == NULL)
		return (NULL);
	else
	{
		while (total_size-- > 0)
		{
			((char *)ptr)[i++] = 0;
		}
		return (ptr);
	}
}
*/