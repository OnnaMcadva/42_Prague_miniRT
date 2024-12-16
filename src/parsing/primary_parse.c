/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 23:04:22 by annavm            #+#    #+#             */
/*   Updated: 2024/12/16 23:30:31 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	array_length(char *arr[])
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

int	parse_shape(t_rt *rt, char *line, t_obj_id id, int nb_params)
{
	t_obj	*obj;
	char	**params;

	params = ft_split(line, ' ');
	if (array_length(params) < nb_params)
		return (print_parse_err(rt, params, INVALID_NB_PARAMS));
	obj = create_object(rt, id);
	if ((id == id_plane && parse_plane(rt, params, obj))
		|| (id == id_sphere && parse_sphere(rt, params, obj))
		|| (id == id_cylinder && parse_cylinder(rt, params, obj))
		|| (id == id_cone && parse_cone(rt, params, obj))
		|| (id == id_triangle && parse_triangle(rt, params, obj)))
		return (1);
	if (array_length(params) > nb_params
		&& parse_extra_params(rt, obj, params, nb_params - 1))
		return (1);
	free_array(params);
	return (0);
}

int	parse_general_params(t_rt *rt, char *line)
{
	if (ft_strncmp(line, "R", 1) == 0)
		return (parse_resolution(rt, line));
	if (ft_strncmp(line, "A", 1) == 0)
		return (parse_ambient(rt, line));
	if (ft_strncmp(line, "C", 1) == 0)
		return (parse_camera(rt, line, 0));
	if (ft_strncmp(line, "L", 1) == 0)
		return (parse_light(rt, line));
	return (0);
}

int	parse_object_params(t_rt *rt, char *line)
{
	if (ft_strncmp(line, "sp", 2) == 0)
		return (parse_shape(rt, line, id_sphere, NB_PARAMS_SPHERE));
	if (ft_strncmp(line, "pl", 2) == 0)
		return (parse_shape(rt, line, id_plane, NB_PARAMS_PLANE));
	if (ft_strncmp(line, "cy", 2) == 0)
		return (parse_shape(rt, line, id_cylinder, NB_PARAMS_CYLINDER));
	if (ft_strncmp(line, "co", 2) == 0)
		return (parse_shape(rt, line, id_cone, NB_PARAMS_CONE));
	if (ft_strncmp(line, "tr", 2) == 0)
		return (parse_shape(rt, line, id_triangle, NB_PARAMS_TRIANGLE));
	return (0);
}

int	parse_params(t_rt *rt, char *line)
{
	int	result;

	result = parse_general_params(rt, line);
	if (result != 0)
		return (result);
	return (parse_object_params(rt, line));
}
