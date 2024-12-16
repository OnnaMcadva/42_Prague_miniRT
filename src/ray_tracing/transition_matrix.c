/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:46:46 by annavm            #+#    #+#             */
/*   Updated: 2024/12/16 23:58:55 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	create_camera_axes(t_rt *rt, t_vect *forward, t_vect *right, t_vect *up)
{
	t_vect	temp;

	temp = vec_coord(0, 1, 0);
	*forward = rt->camera.orient;
	normalize(forward);
	if (fabs(forward->x) == 0 && fabs(forward->z) == 0)
		temp = vec_coord(1, 0, 0);
	*right = vec_product(*forward, temp);
	normalize(right);
	*up = vec_product(*right, *forward);
}

void	cam_view_matrix(t_rt *rt)
{
	t_vect	forward;
	t_vect	right;
	t_vect	up;

	create_camera_axes(rt, &forward, &right, &up);
	rt->cam_matrix[0][0] = right.x;
	rt->cam_matrix[0][1] = right.y;
	rt->cam_matrix[0][2] = right.z;
	rt->cam_matrix[0][3] = -scal_product(right, rt->camera.coords);
	rt->cam_matrix[1][0] = up.x;
	rt->cam_matrix[1][1] = up.y;
	rt->cam_matrix[1][2] = up.z;
	rt->cam_matrix[1][3] = -scal_product(up, rt->camera.coords);
	rt->cam_matrix[2][0] = forward.x;
	rt->cam_matrix[2][1] = forward.y;
	rt->cam_matrix[2][2] = forward.z;
	rt->cam_matrix[2][3] = -scal_product(forward, rt->camera.coords);
	rt->cam_matrix[3][0] = 0;
	rt->cam_matrix[3][1] = 0;
	rt->cam_matrix[3][2] = 0;
	rt->cam_matrix[3][3] = 1;
}
