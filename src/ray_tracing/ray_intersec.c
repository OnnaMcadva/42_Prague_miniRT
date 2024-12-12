/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:22:00 by annavm            #+#    #+#             */
/*   Updated: 2024/12/11 23:36:36 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

t_obj	*get_closest_obj(t_ray *ray, t_obj *obj, t_hit *hit)
{
	float	min_dist;
	t_obj	*closest_obj;
	t_hit	tmp_hit = {0};

	closest_obj = NULL;
	min_dist = INFINITY;
	while (obj)
	{
		if (intersect(ray, obj, &tmp_hit))
		{
			if (tmp_hit.t < min_dist)
			{
				closest_obj = obj;
				min_dist = tmp_hit.t;
				*hit = tmp_hit;
			}
		}
		obj = obj->next;
	}
	if (closest_obj)
		hit->color = color_obj(closest_obj, hit);
	return (closest_obj);
}

t_color	light_to_rgb(t_obj *o, t_colors *colors)
{
	t_color	c;

	c.r = colors->ambient.r + colors->diffuse.r + colors->specular.r;
	c.g = colors->ambient.g + colors->diffuse.g + colors->specular.g;
	c.b = colors->ambient.b + colors->diffuse.b + colors->specular.b;
	if (o && o->refract > 0)
		c = blend_colors(colors->refract, 0.7, c, 0.3);
	if (c.r > 1)
		c.r = 1;
	if (c.g > 1)
		c.g = 1;
	if (c.b > 1)
		c.b = 1;
	return (c);
}

void	handle_lights(t_rt *rt, t_rays *r, t_colors *colors)
{
	t_light	*l;

	colors->ambient = r->hit.color;
	colors->ambient = add_light(colors->ambient, rt->ambient.color,
			rt->ambient.lighting);
	l = rt->light;
	while (l)
	{
		colors->is_shadow = shadow_ray(rt, r, l);
		if (!colors->is_shadow)
			colors->diffuse = blend_colors(colors->diffuse, 1,
					diffuse_light(r, l), 1);
		if (!colors->is_shadow)
			colors->specular = blend_colors(colors->specular, 1,
					specular_light(r, l), 1);
		l = l->next;
	}
}

t_color	raytrace(t_rt *rt, t_rays *r, int max_reflect)
{
	t_colors	colors;
	t_obj		*o;

	ft_memset(&colors, 0, sizeof(colors));
	r->closest_obj = get_closest_obj(&r->prime_ray, rt->objs, &r->hit);
	o = r->closest_obj;
	if (!r->closest_obj)
		return (newcolor(0, 0, 0));
	handle_lights(rt, r, &colors);
	--max_reflect;
	if (r->closest_obj->refract > 0 && max_reflect)
		colors.refract = refraction_ray(rt, r, max_reflect);
	if (max_reflect < 0)
		o = NULL;
	return (light_to_rgb(o, &colors));
}
