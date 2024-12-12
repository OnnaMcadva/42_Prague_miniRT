/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_effects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:22:47 by annavm            #+#    #+#             */
/*   Updated: 2024/12/11 23:12:47 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

float	clamp(float value, float min, float max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}

t_color	add_light(t_color color, t_color light, float p2)
{
	t_color c;

	p2 = clamp(p2, 0, 1);
	c.r = clamp(color.r * light.r * p2, 0, 1);
	c.g = clamp(color.g * light.g * p2, 0, 1);
	c.b = clamp(color.b * light.b * p2, 0, 1);

	return c;
}

t_color	blend_colors(t_color c1, float p1, t_color c2, float p2)
{
	t_color dst;

	float total = p1 + p2;
	if (total > 1.0)
	{
		p1 /= total;
		p2 /= total;
	}

	dst.r = clamp(c1.r * p1 + c2.r * p2, 0, 1);
	dst.g = clamp(c1.g * p1 + c2.g * p2, 0, 1);
	dst.b = clamp(c1.b * p1 + c2.b * p2, 0, 1);

	return dst;
}

int	average_colors(t_color c[9])
{
	t_color r = newcolor(0, 0, 0);
	int i;

	for (i = 0; i < 9; i++)
	{
		r.r += c[i].r;
		r.g += c[i].g;
		r.b += c[i].b;
	}

	r.r = clamp(r.r / 9, 0, 1);
	r.g = clamp(r.g / 9, 0, 1);
	r.b = clamp(r.b / 9, 0, 1);

	return color_to_rgb(r);
}

t_color	color_obj(t_obj *obj, t_hit *hit)
{
	float	uv[2];

	if (obj->id == id_sphere && obj->has_texture)
	{
		uv_sphere_map(obj, hit->phit, uv);
		return get_pixelcolor(&obj->texture, uv[0], uv[1]);
	}

	if (obj->pattern_num > 0)
		return pattern_color(obj, hit->phit);

	return obj->color;
}
