/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:13:19 by anmakaro          #+#    #+#             */
/*   Updated: 2024/12/08 22:00:22 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_check_set(char const *s1, char c)
{
	while (*s1)
	{
		if (*s1 == c)
			return (1);
		s1++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int		i;
	unsigned int		j;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	if (*s1 == 0)
		return (ft_strdup((char *)s1));
	if (*set == 0)
		return (ft_strdup(s1));
	while (s1[i] != '\0' && ft_check_set(set, s1[i]) == 1)
		i++;
	while (ft_check_set(set, s1[j]) == 1 && j > i)
		j--;
	return (ft_substr(s1, i, j - i + 1));
}
