/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_moving.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:49:12 by annavm            #+#    #+#             */
/*   Updated: 2024/12/10 22:46:33 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

void	change_light_brightness(t_rt *rt, float change)
{
	if (!rt->light)
		return;
	t_light *light = rt->light;

	light->brightness += change;

	if (light->brightness < 0)
		light->brightness = 0;
	if (light->brightness > 1)
		light->brightness = 1;

	render(rt);
}

void	change_light_color(t_rt *rt, int r_change, int g_change, int b_change)
{
	if (!rt->light)
		return;
	t_light *light = rt->light;

	light->color.r += r_change / 255.0f;
	light->color.g += g_change / 255.0f;
	light->color.b += b_change / 255.0f;

	if (light->color.r < 0) light->color.r = 0;
	if (light->color.g < 0) light->color.g = 0;
	if (light->color.b < 0) light->color.b = 0;

	if (light->color.r > 1) light->color.r = 1;
	if (light->color.g > 1) light->color.g = 1;
	if (light->color.b > 1) light->color.b = 1;

	render(rt);
}

void	move_light(t_rt *rt, enum moving dir)
{
	if (!rt->light)
		return;
	t_light *light = rt->light;

	if (dir == left)
		light->coords.x -= MOVE_SPEED;
	else if (dir == right)
		light->coords.x += MOVE_SPEED;
	else if (dir == up)
		light->coords.y += MOVE_SPEED;
	else if (dir == down)
		light->coords.y -= MOVE_SPEED;
	render(rt);
}
