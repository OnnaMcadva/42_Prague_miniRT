/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:21:53 by annavm            #+#    #+#             */
/*   Updated: 2024/12/11 23:10:58 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

t_vect	vec_coord(float x, float y, float z)
{
	t_vect	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

float	vec_len(t_vect v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vect	vec_difference(t_vect a, t_vect b)
{
	t_vect	dst;

	dst.x = b.x - a.x;
	dst.y = b.y - a.y;
	dst.z = b.z - a.z;
	return (dst);
}

t_vect	vec_sum(t_vect a, t_vect b)
{
	t_vect	dst;

	dst.x = b.x + a.x;
	dst.y = b.y + a.y;
	dst.z = b.z + a.z;
	return (dst);
}

t_vect	vec_num_product(t_vect v, float f)
{
	t_vect	dst;

	dst.x = v.x * f;
	dst.y = v.y * f;
	dst.z = v.z * f;
	return (dst);
}
