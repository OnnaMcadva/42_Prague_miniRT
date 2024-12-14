/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_norms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:06:24 by annavm            #+#    #+#             */
/*   Updated: 2024/12/14 21:47:36 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

void	triangle_norm(t_rt *rt, t_triangle *t)
{
	t_vect	v;
	t_vect	tmp;

	t->edge[0] = vec_difference(t->c[0], t->c[1]);
	t->edge[1] = vec_difference(t->c[1], t->c[2]);
	t->edge[2] = vec_difference(t->c[2], t->c[0]);
	t->n = vec_product(t->edge[0], t->edge[1]);
	t->area2 = vec_len(t->n);
	normalize(&t->n);
	v = vec_difference(rt->camera.orient, t->c[0]);
	if (scal_product(v, t->n) > 0)
	{
		// Переворот нормалей
		tmp = t->c[1];
		t->c[1] = t->c[2];
		t->c[2] = tmp;
		// Повторный расчет нормали после переворота
		t->n = vec_product(t->edge[0], t->edge[1]);
		normalize(&t->n);
	}
}

void	cone_norm(t_cone *c)
{
	normalize(&c->orient);
	c->cos2 = pow(cos(c->angle), 2);
	c->c1 = vec_num_product(c->orient, c->h);
	c->c1 = vec_sum(c->c1, c->coords);
	c->c2 = vec_num_product(c->orient, -c->h2);
	c->c2 = vec_sum(c->c2, c->coords);
	c->r1 = tan(c->angle) * c->h;
	c->r2 = tan(c->angle) * c->h2;
}

void	cylinder_norm(t_cylinder *cy)
{
	normalize(&cy->orient);
	cy->r2 = cy->diameter * cy->diameter * 0.25;
	cy->delta_p = vec_num_product(cy->orient, cy->height);
	cy->p1 = vec_num_product(cy->orient, -0.5 * cy->height);
	cy->p1 = vec_sum(cy->p1, cy->coords);
	cy->p2 = vec_num_product(cy->orient, 0.5 * cy->height);
	cy->p2 = vec_sum(cy->p2, cy->coords);
}

void	load_texture(t_rt *rt, t_obj *obj)
{
	if (obj->has_texture && !obj->texture.img)
	{
		obj->texture.img = mlx_xpm_file_to_image(rt->mlx, obj->texture.path,
				&obj->texture.width, &obj->texture.height);
		if (!obj->texture.img)
			obj->has_texture = FALSE;
		else
			obj->texture.addr = mlx_get_data_addr(obj->texture.img,
					&obj->texture.bits_per_pixel, &obj->texture.line_length,
					&obj->texture.endian);
	}
}

void	object_norm(t_rt *rt)
{
	t_obj		*objs;
	t_camera	*cam;

	cam = &rt->camera;
	cam->scale = tan(cam->fov / 2 * M_PI / 180);
	rt->aspectratio = (float) rt->width / rt->height;
	rt->img.addr_incr = rt->img.bits_per_pixel / 8;
	rt->bg_color = rgb_to_color(0x424242);
	cam_view_matrix(rt);
	objs = rt->objs;
	while (objs)
	{
		load_texture(rt, objs);
		if (objs->id == id_sphere)
			objs->object.sphere.r2 = pow(objs->object.sphere.diameter / 2, 2);
		if (objs->id == id_cone)
			cone_norm(&objs->object.cone);
		if (objs->id == id_triangle)
			triangle_norm(rt, &objs->object.triangle);
		if (objs->id == id_cylinder)
			cylinder_norm(&objs->object.cylinder);
		set_patternref(rt, objs);
		objs = objs->next;
	}
}
