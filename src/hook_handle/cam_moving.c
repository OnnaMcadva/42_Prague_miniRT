/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_moving.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:04:58 by annavm            #+#    #+#             */
/*   Updated: 2024/12/14 23:13:32 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

void	move_camera_forw_back(t_rt *rt,  enum moving dir)
{
	if (dir == forward)
	{
    	rt->camera.coords.x += rt->camera.orient.x * MOVE_SPEED;
    	rt->camera.coords.y += rt->camera.orient.y * MOVE_SPEED;
    	rt->camera.coords.z += rt->camera.orient.z * MOVE_SPEED;
	}
	else if (dir == backward)
	{
	    rt->camera.coords.x -= rt->camera.orient.x * MOVE_SPEED;
    	rt->camera.coords.y -= rt->camera.orient.y * MOVE_SPEED;
    	rt->camera.coords.z -= rt->camera.orient.z * MOVE_SPEED;	
	}
    render(rt);
}

void	move_camera(t_rt *rt, enum moving dir)
{
	t_vect right_vect = {
		.x = rt->camera.orient.z,
		.y = 0,
		.z = -rt->camera.orient.x
	};

	if (dir == left)
	{
    	rt->camera.coords.x += right_vect.x * MOVE_SPEED;
    	rt->camera.coords.z += right_vect.z * MOVE_SPEED;
	}
	else if (dir == right)
	{
    	rt->camera.coords.x -= right_vect.x * MOVE_SPEED;
    	rt->camera.coords.z -= right_vect.z * MOVE_SPEED;
	}
	else if (dir == up)
    	rt->camera.coords.y += MOVE_SPEED;
	else if (dir == down)
    	rt->camera.coords.y -= MOVE_SPEED;
	render(rt);
}

void rotate_camera(t_rt *rt, enum moving dir)
{
	if (dir == left)
	{
    	float angle = ROTATE_SPEED;
    	float x_new = rt->camera.orient.x * cos(angle) - rt->camera.orient.z * sin(angle);
    	float z_new = rt->camera.orient.x * sin(angle) + rt->camera.orient.z * cos(angle);
    	rt->camera.orient.x = x_new;
    	rt->camera.orient.z = z_new;
	}
	else if (dir == right)
	{
	    float angle = -ROTATE_SPEED;
    	float x_new = rt->camera.orient.x * cos(angle) - rt->camera.orient.z * sin(angle);
    	float z_new = rt->camera.orient.x * sin(angle) + rt->camera.orient.z * cos(angle);
	    rt->camera.orient.x = x_new;
 		rt->camera.orient.z = z_new;	
	}
    render(rt);
}