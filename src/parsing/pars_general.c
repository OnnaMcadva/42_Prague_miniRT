/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:22:12 by annavm            #+#    #+#             */
/*   Updated: 2024/12/11 23:11:36 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

int	parse_camera(t_rt *rt, char *line, int i)
{
	char		**params;
	t_camera	camera;

	params = ft_split(line, ' ');
	if (rt->camera.id)
		return (print_parse_err(rt, params, TOO_MANY_CAMERAS));
	if (array_length(params) != 4)
		return (print_parse_err(rt, params, INVALID_NB_PARAMS));
	ft_bzero(&camera, sizeof(t_camera));
	camera.id = id_camera;
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector(params[i], &camera.coords))
			return (print_parse_err(rt, params, INVALID_NB_COORDS));
		if (i == 2 && parse_vector(params[i], &camera.orient))
			return (print_parse_err(rt, params, INVALID_NB_ORIENT));
		if (i == 3 && parse_ulong(params[i], &camera.fov))
			return (print_parse_err(rt, params, NOT_A_ULONG));
	}
	normalize(&camera.orient);
	rt->camera = camera;
	free_array(params);
	return (0);
}

int	parse_ambient(t_rt *rt, char *line)
{
	int			i;
	char		**params;
	t_ambient	ambient;

	i = 0;
	params = ft_split(line, ' ');
	if (rt->ambient.id)
		return (print_parse_err(rt, params, TOO_MANY_AMBIENTS));
	if (array_length(params) != 3)
		return (print_parse_err(rt, params, INVALID_NB_PARAMS));
	ft_bzero(&ambient, sizeof(t_ambient));
	ambient.id = id_ambient;
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_float(params[i], &ambient.lighting))
			return (print_parse_err(rt, params, NOT_A_FLOAT));
		if (i == 2 && parse_rgb(params[i], &ambient.color))
			return (print_parse_err(rt, params, INVALID_NB_COLORS));
	}
	rt->ambient = ambient;
	free_array(params);
	return (0);
}

int	parse_light(t_rt *rt, char *line)
{
	int		i;
	char	**params;
	t_light	*light;

	i = 0;
	params = ft_split(line, ' ');
	if (array_length(params) != 4)
		return (print_parse_err(rt, params, INVALID_NB_PARAMS));
	light = create_light(rt);
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector(params[i], &light->coords))
			return (print_parse_err(rt, params, INVALID_NB_COORDS));
		if (i == 2 && parse_float(params[i], &light->brightness))
			return (print_parse_err(rt, params, NOT_A_FLOAT));
		if (i == 3 && parse_rgb(params[i], &light->color))
			return (print_parse_err(rt, params, INVALID_NB_COLORS));
	}
	free_array(params);
	return (0);
}

int	parse_resolution(t_rt *rt, char *line)
{
	int		i;
	char	**params;

	i = 0;
	params = ft_split(line, ' ');
	if (array_length(params) != 3)
		return (print_parse_err(rt, params, INVALID_NB_PARAMS));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_float(params[i], &rt->width))
			return (print_parse_err(rt, params, NOT_A_FLOAT));
		if (i == 2 && parse_float(params[i], &rt->height))
			return (print_parse_err(rt, params, NOT_A_FLOAT));
	}
	free_array(params);
	return (0);
}
