/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_re_re.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:21:39 by annavm            #+#    #+#             */
/*   Updated: 2024/12/11 23:11:07 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

t_vect	reflect_vec(t_vect v, t_vect n)
{
	t_vect	dst;

	dst = vec_num_product(n, 2 * scal_product(v, n));
	dst = vec_difference(dst, v);
	return (dst);
}

t_vect	refract_vec(t_vect v, t_vect n, float eta)
{
	float	c1;
	float	c2;
	t_vect	dst;

	c1 = scal_product(v, n);
	c2 = sqrt(1 - eta * eta * (1 - c1 * c1));
	dst = vec_num_product(n, eta * c1 - c2);
	dst = vec_sum(dst, vec_num_product(v, eta));
	normalize(&dst);
	return (dst);
}
