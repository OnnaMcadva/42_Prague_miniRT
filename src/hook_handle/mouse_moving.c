/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_moving.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:06:30 by annavm            #+#    #+#             */
/*   Updated: 2024/12/12 12:35:00 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

void	move_object(t_rt *rt, int x, int y)
{
	t_vect	*obj_pos;
	t_ray	select_ray;
	float	t;

	if (!rt->event.selection || rt->event.selection->id == id_triangle)
		return;

	obj_pos = get_coords(rt->event.selection);
	if (!obj_pos)
		return;

	create_camera_ray(rt, &select_ray, x, y);
	t = (obj_pos->z - select_ray.or.z) / select_ray.dir.z;
	calc_ray_point(obj_pos, &select_ray, t);
	rt->event.torender = TRUE;
}

int	mouse_press(int button, int x, int y, t_rt *rt)
{
	if (y < 0)
		return (0);

	t_ray	mouse_ray;
	t_hit	hit;

	create_camera_ray(rt, &mouse_ray, x, y);
	rt->event.mouse |= (1 << button);
	rt->event.selection = get_closest_obj(&mouse_ray, rt->objs, &hit);

	return (0);
}

int	mouse_release(int button, int x, int y, t_rt *rt)
{
	(void)x;
	(void)y;

	if (button != LEFT_CLICK)
		return (0);

	rt->event.mouse &= ~(1 << button);
	rt->event.selection = NULL;

	if (rt->event.torender)
		render(rt);

	rt->event.torender = FALSE;
	rt->img.antialiasing_on = FALSE;

	return (0);
}

int	mouse_moving(int x, int y, t_rt *rt)
{
	if (x < 0 || y < 0)
		return (0);

	rt->event.lastx = rt->event.x;
	rt->event.lasty = rt->event.y;
	rt->event.x = x;
	rt->event.y = y;

	if (rt->event.selection)
		move_object(rt, x, y);

	return (0);
}
