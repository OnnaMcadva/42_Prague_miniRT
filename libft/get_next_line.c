/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:19:37 by anmakaro          #+#    #+#             */
/*   Updated: 2024/12/11 23:54:45 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_and_append(int fd, char *saved_str)
{
	char	*temp;
	int		bytes_read;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr_v(saved_str, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		saved_str = ft_strjoin_v(saved_str, temp);
	}
	free(temp);
	return (saved_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*saved_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved_str = ft_read_and_append(fd, saved_str);
	if (!saved_str)
		return (NULL);
	line = ft_getline_fromleftstr(saved_str);
	saved_str = ft_update_leftstr(saved_str);
	return (line);
}
