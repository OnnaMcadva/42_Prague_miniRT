/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:11:33 by annavm            #+#    #+#             */
/*   Updated: 2024/12/11 23:12:26 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

int	anti_aliasing(t_rt *rt, float x, float y)
{
	t_color	c[9];
	int		i;
	int		j;
	t_rays	r;

	y -= 0.33;
	i = 0;
	j = 0;
	while (i < 3)
	{
		j = 0;
		x -= 0.99;
		while (j < 3)
		{
			create_camera_ray(rt, &r.prime_ray, x, y);
			c[i * 3 + j] = raytrace(rt, &r, MAX_REFLECT);
			x += 0.33;
			j++;
		}
		y += 0.33;
		i++;
	}
	return (average_colors(c));
}
