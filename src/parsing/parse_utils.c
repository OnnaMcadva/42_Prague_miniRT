/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:23:55 by annavm            #+#    #+#             */
/*   Updated: 2024/12/10 23:37:20 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

int	parse_vector(char *str, t_vect *vect)
{
	int		i;
	int		ret;
	char	**nbrs;

	i = -1;
	ret = 0;
	nbrs = ft_split(str, ',');
	while (nbrs && nbrs[++i])
		if (!is_float(nbrs[i]))
			ret = 1;
	if (array_length(nbrs) != 3)
		ret = 1;
	else
	{
		vect->x = str_to_float(nbrs[0]);
		vect->y = str_to_float(nbrs[1]);
		vect->z = str_to_float(nbrs[2]);
	}
	free_array(nbrs);
	return (ret);
}

int	parse_colors(char *str, t_color *color, t_color *color2)
{
	char	**colors;
	int		ret;

	colors = ft_split(str, ';');
	if (!colors || !colors[0])
	{
		free_array(colors);
		return (1);
	}
	ret = parse_rgb(colors[0], color);
	if (ret == 0 && colors[1])
		ret = parse_rgb(colors[1], color2);
	free_array(colors);
	return (ret);
}

int	parse_rgb(char *str, t_color *color)
{
	char	**rgb;
	int		i;

	rgb = ft_split(str, ',');
	if (!rgb || array_length(rgb) != 3)
	{
		free_array(rgb);
		return (1);
	}
	i = 0;
	while (i < 3)
	{
		if (!is_ulong(rgb[i]))
		{
			free_array(rgb);
			return (1);
		}
		i++;
	}
	color->r = (float)str_to_int_color(rgb[0]) / 255.0f;
	color->g = (float)str_to_int_color(rgb[1]) / 255.0f;
	color->b = (float)str_to_int_color(rgb[2]) / 255.0f;
	free_array(rgb);
	return (0);
}

int	parse_float(char *str, float *num)
{
	if (!is_float(str))
		return (1);
	*num = str_to_float(str);
	return (0);
}

int	parse_ulong(char *str, size_t *num)
{
	char			*endptr;
	unsigned long	value;

	value = strtoul(str, &endptr, 10);
	if (*endptr != '\0' || value > SIZE_MAX)
		return (1);
	*num = (size_t)value;
	return (0);
}
