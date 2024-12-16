/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primit_intersec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:22:40 by annavm            #+#    #+#             */
/*   Updated: 2024/12/16 23:50:55 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_bool	sphere_inter(t_ray *ray, t_sphere *sp, t_hit *hit)
{
	t_vect	l;
	float	tca;
	float	d2;
	float	thc;
	float	t2;

	l = vec_difference(ray->or, sp->coords);
	tca = scal_product(l, ray->dir);
	if (tca < 0)
		return (FALSE);
	d2 = scal_product(l, l) - tca * tca;
	if (d2 > sp->r2)
		return (FALSE);
	thc = sqrt(sp->r2 - d2);
	hit->t = tca - thc;
	t2 = tca + thc;
	if (hit->t < EPSILON && t2 < EPSILON)
		return (FALSE);
	if (hit->t < EPSILON || t2 < hit->t)
		hit->t = t2;
	calc_ray_point(&hit->phit, ray, hit->t);
	hit->nhit = vec_difference(sp->coords, hit->phit);
	normalize(&hit->nhit);
	return (TRUE);
}

t_bool	plane_inter(t_ray *r, t_plane *pl, t_hit *hit)
{
	float	denom;
	t_vect	tmp;

	denom = scal_product(pl->orient, r->dir);
	if (denom == 0)
		return (FALSE);
	tmp = vec_difference(r->or, pl->coords);
	hit->t = scal_product(tmp, pl->orient) / denom;
	if (hit->t < EPSILON)
		return (FALSE);
	calc_ray_point(&hit->phit, r, hit->t);
	hit->nhit = pl->orient;
	if (scal_product(hit->nhit, r->dir) > 0)
		hit->nhit = vec_oppos(hit->nhit);
	return (TRUE);
}

t_bool	triangle_inter(t_ray *r, t_triangle *t, t_hit *hit)
{
	float	dot_prod_ndir;
	float	d;
	t_vect	m;
	int		i;

	dot_prod_ndir = scal_product(t->n, r->dir);
	if (fabs(dot_prod_ndir) < EPSILON)
		return (FALSE);
	d = -scal_product(t->n, t->c[0]);
	hit->t = -(scal_product(r->or, t->n) + d) / dot_prod_ndir;
	if (hit->t < EPSILON)
		return (FALSE);
	calc_ray_point(&hit->phit, r, hit->t);
	i = -1;
	while (++i < 3)
	{
		m = vec_product(t->edge[i], vec_difference(t->c[i], hit->phit));
		if (scal_product(t->n, m) < 0)
			return (FALSE);
	}
	hit->nhit = t->n;
	if (scal_product(hit->nhit, r->dir) > 0)
		hit->nhit = vec_oppos(hit->nhit);
	return (TRUE);
}

t_bool	infinite_cyl_inter(t_ray *r, t_cylinder *cy, t_hit *hit)
{
	t_quadratic	q;
	t_vect		u;
	t_vect		v;

	u = vec_product(r->dir, cy->orient);
	v = vec_difference(cy->coords, r->or);
	v = vec_product(v, cy->orient);
	q.a = scal_product(u, u);
	q.b = 2 * scal_product(u, v);
	q.c = scal_product(v, v) - cy->r2;
	if (!find_quadr_roots(&q) || (q.t2 <= EPSILON && q.t1 <= EPSILON))
		return (FALSE);
	if (q.t1 <= EPSILON || (q.t2 > EPSILON && (q.t2 < q.t1)))
		q.t1 = q.t2;
	hit->t = q.t1;
	calc_ray_point(&hit->phit, r, q.t1);
	v = vec_difference(cy->coords, hit->phit);
	hit->nhit = vec_product(v, cy->orient);
	hit->nhit = vec_product(hit->nhit, cy->orient);
	normalize(&hit->nhit);
	if (scal_product(hit->nhit, r->dir))
		hit->nhit = vec_oppos(hit->nhit);
	return (TRUE);
}

t_bool	cylinder_inter(t_ray *r, t_cylinder *cy, t_hit *hit)
{
	t_plane	pl;
	t_hit	tmp_hit;

	hit->t = INFINITY;
	pl.coords = cy->p1;
	pl.orient = cy->orient;
	if (plane_inter(r, &pl, &tmp_hit)
		&& distance(tmp_hit.phit, cy->p1)
		<= cy->diameter * 0.5 && hit->t > tmp_hit.t)
		*hit = tmp_hit;
	pl.coords = cy->p2;
	if (plane_inter(r, &pl, &tmp_hit)
		&& distance(tmp_hit.phit, cy->p2) <= cy->diameter * 0.5
		&& hit->t > tmp_hit.t)
		*hit = tmp_hit;
	if (infinite_cyl_inter(r, cy, &tmp_hit)
		&& pow(distance(cy->coords, tmp_hit.phit), 2)
		<= pow(cy->height * 0.5, 2) + cy->r2
		&& hit->t > tmp_hit.t)
		*hit = tmp_hit;
	return (hit->t < INFINITY && hit->t > EPSILON);
}
