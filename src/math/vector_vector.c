/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:21:46 by annavm            #+#    #+#             */
/*   Updated: 2024/12/13 16:28:47 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

float	scal_product(t_vect v1, t_vect v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vect	vec_product(t_vect u, t_vect v)
{
	t_vect	dst;

	dst.x = u.y * v.z - u.z * v.y;
	dst.y = u.z * v.x - u.x * v.z;
	dst.z = u.x * v.y - u.y * v.x;
	return (dst);
}

float	distance(t_vect a, t_vect b)
{
	float	x;
	float	y;
	float	z;

	x = a.x - b.x;
	y = a.y - b.y;
	z = a.z - b.z;
	x = pow(x, 2);
	y = pow(y, 2);
	z = pow(z, 2);
	return (sqrt(x + y + z));
}

t_vect	vec_oppos(t_vect v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return (v);
}

t_vect	*normalize(t_vect *v)
{
	float	norm;

	norm = 1 / vec_len(*v);
	v->x *= norm;
	v->y *= norm;
	v->z *= norm;
	return (v);
}
