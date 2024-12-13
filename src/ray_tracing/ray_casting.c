/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:22:07 by annavm            #+#    #+#             */
/*   Updated: 2024/12/13 23:10:18 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

void	build_ray(t_ray *ray, t_vect *or, t_vect *dir)
{
	ray->or.x = or->x;
	ray->or.y = or->y;
	ray->or.z = or->z;
	ray->dir.x = dir->x;
	ray->dir.y = dir->y;
	ray->dir.z = dir->z;
	normalize(&ray->dir);
}

t_vect cam_to_world(float matrix[4][4], t_vect *v)
{
    t_vect result;
    result.x = v->x * matrix[0][0] + v->y * matrix[1][0] + v->z * matrix[2][0] + matrix[3][0];
    result.y = v->x * matrix[0][1] + v->y * matrix[1][1] + v->z * matrix[2][1] + matrix[3][1];
    result.z = v->x * matrix[0][2] + v->y * matrix[1][2] + v->z * matrix[2][2] + matrix[3][2];
    return result;
}

void	create_camera_ray(t_rt *rt, t_ray *ray, float x, float y)
{
	t_camera	*cam;

	cam = &rt->camera;
	ray->or = vec_coord(cam->coords.x, cam->coords.y, cam->coords.z);
	ray->dir.x = (2.0 * (x + 0.5) / (float) rt->width - 1.0)
		* cam->scale * rt->aspectratio;
	ray->dir.y = (1.0 - 2.0 * (y + 0.5) / (float) rt->height) * cam->scale;
	ray->dir.z = FOCAL_DIST;
	ray->dir = cam_to_world(rt->cam_matrix, &ray->dir);
	normalize(&ray->dir);
}

t_vect	*calc_ray_point(t_vect *dst, t_ray *r, float t)
{
	dst->x = r->or.x + t * r->dir.x;
	dst->y = r->or.y + t * r->dir.y;
	dst->z = r->or.z + t * r->dir.z;
	return (dst);
}
