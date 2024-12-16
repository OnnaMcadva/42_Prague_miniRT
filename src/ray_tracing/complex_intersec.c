/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_intersec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:15:40 by annavm            #+#    #+#             */
/*   Updated: 2024/12/16 23:44:40 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_bool	cone_hit(t_ray *r, t_cone *co, t_hit *hit)
{
	t_quadratic	q;
	float		prod_dv;
	float		prod_cov;
	t_vect		v_co;
	t_vect		cp;

	v_co = vec_difference(co->coords, r->or);
	prod_dv = scal_product(r->dir, co->orient);
	prod_cov = scal_product(v_co, co->orient);
	q.a = prod_dv * prod_dv - co->cos2;
	q.b = 2 * (prod_dv * prod_cov - scal_product(r->dir, v_co) * co->cos2);
	q.c = prod_cov * prod_cov - scal_product(v_co, v_co) * co->cos2;
	if (!find_quadr_roots(&q) || (q.t2 <= EPSILON && q.t1 <= EPSILON))
		return (FALSE);
	if (q.t1 <= EPSILON || (q.t2 > EPSILON && (q.t2 < q.t1)))
		q.t1 = q.t2;
	hit->t = q.t1;
	calc_ray_point(&hit->phit, r, hit->t);
	cp = vec_difference(co->coords, hit->phit);
	if (scal_product(co->orient, cp) > co->h
		|| scal_product(co->orient, cp) < -co->h2)
		return (FALSE);
	hit->nhit = vec_product(vec_product(cp, co->orient), cp);
	normalize(&hit->nhit);
	return (TRUE);
}

t_bool	cone_test(t_ray *r, t_cone *co, t_hit *hit)
{
	t_plane	pl;
	t_hit	tmp_hit;

	hit->t = INFINITY;
	hit->nhit.x = 0;
	hit->nhit.y = 0;
	hit->nhit.z = 0;
	pl.coords = co->c1;
	pl.orient = co->orient;
	if (plane_inter(r, &pl, &tmp_hit)
		&& distance(tmp_hit.phit, co->c1) <= co->r1 && hit->t > tmp_hit.t)
		*hit = tmp_hit;
	pl.coords = co->c2;
	if (plane_inter(r, &pl, &tmp_hit)
		&& distance(tmp_hit.phit, co->c2) <= co->r2 && hit->t > tmp_hit.t)
		*hit = tmp_hit;
	if (cone_hit(r, co, &tmp_hit) && hit->t > tmp_hit.t)
		*hit = tmp_hit;
	if (scal_product(hit->nhit, r->dir) > 0)
		hit->nhit = vec_oppos(hit->nhit);
	return (hit->t < INFINITY && hit->t > EPSILON);
}

int	intersect(t_ray *ray, t_obj *obj, t_hit *hit)
{
	if (obj->id == id_sphere)
		return (sphere_inter(ray, &obj->object.sphere, hit));
	if (obj->id == id_plane)
		return (plane_inter(ray, &obj->object.plane, hit));
	if (obj->id == id_cylinder)
		return (cylinder_inter(ray, &obj->object.cylinder, hit));
	if (obj->id == id_cone)
		return (cone_test(ray, &obj->object.cone, hit));
	if (obj->id == id_triangle)
		return (triangle_inter(ray, &obj->object.triangle, hit));
	return (FALSE);
}
