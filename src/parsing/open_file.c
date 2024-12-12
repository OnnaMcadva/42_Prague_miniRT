/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:40:28 by annavm            #+#    #+#             */
/*   Updated: 2024/12/10 14:44:25 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

int	is_invalid_file(t_rt *rt)
{
	if (!rt->ambient.id)
		return (print_err(MISSING_AMBIENT_PARAMS));
	if (!rt->camera.id)
		return (print_err(MISSING_CAMERA_PARAMS));
	if (!rt->light)
		return (print_err(MISSING_LIGHT_PARAMS));
	return (0);
}

char	*sanitize_line(char *line)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = line;
	while (tmp && tmp[++i])
		if (tmp[i] == '\t' || tmp[i] == '\n')
			tmp[i] = ' ';
	line = ft_strtrim(tmp, " ");
	free(tmp);
	return (line);
}

int	read_file(t_rt *rt, int fd)
{
	int		num;
	int		ret;
	char	*line;

	num = 0;
	ret = 0;
	while (ret != 1)
	{
		num++;
		line = get_next_line(fd);
		if (!line)
			break ;
		line = sanitize_line(line);
		rt->lnum = num;
		if (parse_params(rt, line))
			ret = 1;
		free(line);
	}
	if (!ret && is_invalid_file(rt))
		ret = 1;
	return (ret);
}

int	open_file(t_rt *rt, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (!print_err(ERR_FILE_NOT_FOUND));
	if (read_file(rt, fd))
	{
		close(fd); // Закриваємо файл у разі помилки читання
		return (0);
	}
	close(fd); // Успішне завершення: файл закрито
	return (1);
}

