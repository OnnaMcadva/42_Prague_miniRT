/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refle_refra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:22:29 by annavm            #+#    #+#             */
/*   Updated: 2024/12/11 23:15:46 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

t_color	specular_light(t_rays *r, t_light *light)
{
	t_vect	spec;
	float	dot_p;
	t_color	color;

	dot_p = scal_product(r->shadowray.dir, r->hit.nhit);
	spec = vec_num_product(r->hit.nhit, dot_p * 2);
	spec = vec_difference(spec, r->shadowray.dir);
	dot_p = scal_product(spec, r->prime_ray.dir);
	if (dot_p > EPSILON)
		dot_p = pow(dot_p, r->closest_obj->specn) * r->closest_obj->speckv;
	color = newcolor(1, 1, 1);
	color = add_light(color, color, light->brightness * dot_p);
	return (color);
}

t_color	diffuse_light(t_rays *r, t_light *light)
{
	t_color	color;
	float	dot_p;

	color = r->hit.color;
	dot_p = scal_product(r->shadowray.dir, r->hit.nhit);
	color = add_light(color, light->color, light->brightness * dot_p);
	return (color);
}

t_bool	shadow_ray(t_rt *rt, t_rays *r, t_light *light)
{
	r->shadowray.or = r->hit.phit;
	r->shadowray.dir = vec_difference(r->hit.phit, light->coords);
	normalize(&r->shadowray.dir);
	calc_ray_point(&r->shadowray.or, &r->shadowray, 0.01);
	return (get_closest_obj(&r->shadowray, rt->objs, &r->shadow_hit)
		&& distance(r->shadowray.or, light->coords)
		> distance(r->shadow_hit.phit, r->shadowray.or));
}

t_color	refraction_ray(t_rt *rt, t_rays *r, int max_reflect)
{
	float	eta;

	eta = 1 / r->closest_obj->refract;
	r->prime_ray.or = r->hit.phit;
	r->prime_ray.dir = refract_vec(r->prime_ray.dir, r->hit.nhit, eta);
	calc_ray_point(&r->prime_ray.or, &r->prime_ray, EPSILON);
	intersect(&r->prime_ray, r->closest_obj, &r->hit);
	r->prime_ray.or = r->hit.phit;
	r->hit.nhit = vec_oppos(r->hit.nhit);
	r->prime_ray.dir = refract_vec(r->prime_ray.dir, r->hit.nhit, eta);
	return (raytrace(rt, r, max_reflect));
}

t_color	reflection_ray(t_rt *rt, t_rays *r, int max_reflect)
{
	t_rays		reflect;

	reflect.prime_ray.or = r->hit.phit;
	reflect.prime_ray.dir = reflect_vec(r->prime_ray.dir, r->hit.nhit);
	normalize(&reflect.prime_ray.dir);
	return (raytrace(rt, &reflect, max_reflect));
}
