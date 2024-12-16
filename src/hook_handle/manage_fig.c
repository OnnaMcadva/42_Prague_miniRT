/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:57:53 by annavm            #+#    #+#             */
/*   Updated: 2024/12/16 23:16:39 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	elka(const char *arg)
{
	char	*args[3];

	args[0] = "./miniRT";
	args[1] = (char *)arg;
	args[2] = NULL;
	execv(args[0], args);
	perror("execv failed");
	exit(1);
}

void	manage_sphere(int key, t_rt *rt)
{
	t_obj	*sphere;
	float	radius;

	sphere = rt->event.selection;
	radius = sphere->object.sphere.diameter / 2;
	if (key == NP_1)
	{
		if (sphere->object.sphere.diameter < radius * 3)
		{
			sphere->object.sphere.diameter *= 1.1;
			rt->event.torender = TRUE;
		}
	}
	else if (key == NP_3)
	{
		if (sphere->object.sphere.diameter > radius / 3)
		{
			sphere->object.sphere.diameter /= 1.1;
			rt->event.torender = TRUE;
		}
	}
}

void	manage_cylinder(int key, t_rt *rt)
{
	t_obj		*obj;
	t_cylinder	*cylinder;
	float		angle_in_radians;
	t_vect		rotation_axis;

	obj = rt->event.selection;
	cylinder = &obj->object.cylinder;
	angle_in_radians = ROTATE_ANGLE * (M_PI / 180.0);
	rotation_axis.x = 1;
	rotation_axis.y = 0;
	rotation_axis.z = 0;
	if (key == NP_2)
	{
		rotate_vector(&cylinder->orient, rotation_axis, -angle_in_radians);
		rt->event.torender = TRUE;
	}
}

void	manage_fig(int key, t_rt *rt)
{
	if (!rt->event.selection)
		return ;
	if (rt->event.selection->id == id_sphere)
		manage_sphere(key, rt);
	else if (rt->event.selection->id == id_cylinder)
		manage_cylinder(key, rt);
	if (rt->event.torender)
	{
		render(rt);
		rt->event.torender = FALSE;
	}
}

void	rotate_vector(t_vect *vector, t_vect axis, float angle)
{
	float	cos_angle;
	float	sin_angle;
	float	x;
	float	y;
	float	z;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	x = vector->x * (cos_angle + (1 - cos_angle) * axis.x * axis.x)
		+ vector->y * ((1 - cos_angle) * axis.x * axis.y - axis.z * sin_angle)
		+ vector->z * ((1 - cos_angle) * axis.x * axis.z + axis.y * sin_angle);
	y = vector->x * ((1 - cos_angle) * axis.y * axis.x + axis.z * sin_angle)
		+ vector->y * (cos_angle + (1 - cos_angle) * axis.y * axis.y)
		+ vector->z * ((1 - cos_angle) * axis.y * axis.z - axis.x * sin_angle);
	z = vector->x * ((1 - cos_angle) * axis.z * axis.x - axis.y * sin_angle)
		+ vector->y * ((1 - cos_angle) * axis.z * axis.y + axis.x * sin_angle)
		+ vector->z * (cos_angle + (1 - cos_angle) * axis.z * axis.z);
	vector->x = x;
	vector->y = y;
	vector->z = z;
}
