/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:23:41 by annavm            #+#    #+#             */
/*   Updated: 2024/12/08 16:09:15 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

int	is_invalid_xpmfile(char *path)
{
	int	fd;
	int	len;

	len = ft_strlen(path) - 4;
	if (len < 5 || ft_strncmp(path + len, ".xpm", 4) != 0)
		return (1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int	parse_texture(char *param, t_obj *obj)
{
	char	**params;

	params = ft_split(param, ',');
	if (array_length(params) == 2 && parse_float(params[1], &obj->texture_f))
		return (1);
	if (is_invalid_xpmfile(params[0]))
		return (1);
	obj->texture.path = params[0];
	obj->has_texture = TRUE;
	return (0);
}

int	parse_specular(char *str, t_obj *obj)
{
	int		i;
	int		ret;
	char	**params;

	i = -1;
	ret = 0;
	params = ft_split(str, ',');
	while (params && params[++i])
		if (!is_float(params[i]))
			ret = 1;
	if (array_length(params) != 2)
		ret = 1;
	else
	{
		obj->speckv = str_to_float(params[0]);
		obj->specn = str_to_float(params[1]);
	}
	free_array(params);
	return (ret);
}

int	parse_pattern(char *str, t_obj *obj)
{
	int		ret;
	char	**params;

	ret = 0;
	params = ft_split(str, ',');
	if (array_length(params) != 2)
		ret = 1;
	if (!is_float(params[0]))
		ret = 1;
	if (!is_ulong(params[1]))
		ret = 1;
	if (!ret)
	{
		obj->pattern_len = str_to_float(params[0]);
		obj->pattern_num = ft_atoi(params[1]);
	}
	free_array(params);
	return (ret);
}
