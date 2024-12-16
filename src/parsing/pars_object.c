/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:39:17 by nchonka           #+#    #+#             */
/*   Updated: 2024/12/16 23:20:08 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	parse_plane(t_rt *rt, char **params, t_obj *obj)
{
	int		i;
	t_plane	plane;

	i = 0;
	ft_bzero(&plane, sizeof(t_plane));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector(params[i], &obj->coords))
			return (print_parse_err(rt, params, INVALID_NB_COORDS));
		if (i == 2 && parse_vector(params[i], &plane.orient))
			return (print_parse_err(rt, params, INVALID_NB_ORIENT));
		if (i == 3 && parse_colors(params[i], &obj->color, &obj->color2))
			return (print_parse_err(rt, params, INVALID_NB_COLORS));
	}
	normalize(&plane.orient);
	plane.coords = obj->coords;
	obj->object.plane = plane;
	return (0);
}

int	parse_sphere(t_rt *rt, char **params, t_obj *obj)
{
	int			i;
	t_sphere	sphere;

	i = 0;
	ft_bzero(&sphere, sizeof(t_sphere));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector(params[i], &obj->coords))
			return (print_parse_err(rt, params, INVALID_NB_COORDS));
		if (i == 2 && parse_float(params[i], &sphere.diameter))
			return (print_parse_err(rt, params, NOT_A_FLOAT));
		if (i == 3 && parse_colors(params[i], &obj->color, &obj->color2))
			return (print_parse_err(rt, params, INVALID_NB_COLORS));
	}
	sphere.coords = obj->coords;
	obj->object.sphere = sphere;
	return (0);
}

int	parse_cylinder(t_rt *rt, char **params, t_obj *obj)
{
	int			i;
	t_cylinder	cylinder;

	i = 0;
	ft_bzero(&cylinder, sizeof(t_cylinder));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector(params[i], &obj->coords))
			return (print_parse_err(rt, params, INVALID_NB_COORDS));
		if (i == 2 && parse_vector(params[i], &cylinder.orient))
			return (print_parse_err(rt, params, INVALID_NB_ORIENT));
		if (i == 3 && parse_float(params[i], &cylinder.diameter))
			return (print_parse_err(rt, params, NOT_A_FLOAT));
		if (i == 4 && parse_float(params[i], &cylinder.height))
			return (print_parse_err(rt, params, NOT_A_FLOAT));
		if (i == 5 && parse_colors(params[i], &obj->color, &obj->color2))
			return (print_parse_err(rt, params, INVALID_NB_COLORS));
	}
	normalize(&cylinder.orient);
	cylinder.coords = obj->coords;
	obj->object.cylinder = cylinder;
	return (0);
}

int	parse_cone(t_rt *rt, char **params, t_obj *obj)
{
	int		i;
	t_cone	cone;

	i = 0;
	ft_bzero(&cone, sizeof(t_cone));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector(params[i], &obj->coords))
			return (print_parse_err(rt, params, INVALID_NB_COORDS));
		if (i == 2 && parse_vector(params[i], &cone.orient))
			return (print_parse_err(rt, params, INVALID_NB_ORIENT));
		if (i == 3 && parse_float(params[i], &cone.h))
			return (print_parse_err(rt, params, NOT_A_FLOAT));
		if (i == 4 && parse_float(params[i], &cone.h2))
			return (print_parse_err(rt, params, NOT_A_FLOAT));
		if (i == 5 && parse_float(params[i], &cone.angle))
			return (print_parse_err(rt, params, NOT_A_FLOAT));
		if (i == 6 && parse_colors(params[i], &obj->color, &obj->color2))
			return (print_parse_err(rt, params, INVALID_NB_COLORS));
	}
	normalize(&cone.orient);
	cone.coords = obj->coords;
	obj->object.cone = cone;
	return (0);
}

int	parse_triangle(t_rt *rt, char **params, t_obj *obj)
{
	int			i;
	t_triangle	triangle;

	i = 0;
	ft_bzero(&triangle, sizeof(t_triangle));
	while (params && params[++i])
	{
		rt->pnum = i;
		if (i == 1 && parse_vector(params[i], &triangle.c[0]))
			return (print_parse_err(rt, params, INVALID_NB_COORDS));
		if (i == 2 && parse_vector(params[i], &triangle.c[1]))
			return (print_parse_err(rt, params, INVALID_NB_COORDS));
		if (i == 3 && parse_vector(params[i], &triangle.c[2]))
			return (print_parse_err(rt, params, INVALID_NB_COORDS));
		if (i == 4 && parse_colors(params[i], &obj->color, &obj->color2))
			return (print_parse_err(rt, params, INVALID_NB_COLORS));
	}
	triangle.color = obj->color;
	obj->object.triangle = triangle;
	return (0);
}
