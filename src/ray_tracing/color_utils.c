/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:22:54 by annavm            #+#    #+#             */
/*   Updated: 2024/12/11 23:12:59 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

t_color	newcolor(float r, float g, float b)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color	*apply_color_factor(t_color *c, float p)
{
	c->r *= c->r * p;
	c->g *= c->g * p;
	c->b *= c->b * p;
	return (c);
}

t_color	scale_color(t_color c, float p)
{
	c.r *= c.r * p;
	c.g *= c.g * p;
	c.b *= c.b * p;
	return (c);
}

t_color	rgb_to_color(int rgb)
{
	t_color	c;

	c.r = (float)((rgb >> 16) & 0xff) / 255;
	c.g = (float)((rgb >> 8) & 0xff) / 255;
	c.b = (float)(rgb & 0xff) / 255;
	return (c);
}

int	color_to_rgb(t_color c)
{
	return ((int)(c.r * 255) << 16) | ((int)(c.g * 255) << 8) | (int)(c.b * 255);
}
