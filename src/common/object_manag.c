/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_manag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:06:15 by annavm            #+#    #+#             */
/*   Updated: 2024/12/11 23:09:29 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

t_vect	*get_coords(t_obj *o)
{
	if (!o)
		return (NULL);
	if (o->id == id_plane)
		return (&o->object.plane.coords);
	if (o->id == id_sphere)
		return (&o->object.sphere.coords);
	if (o->id == id_cone)
		return (&o->object.cone.coords);
	if (o->id == id_cylinder)
		return (&o->object.cylinder.coords);
	return (NULL);
}

void	add_object_to_list(t_obj *obj, t_obj **objs)
{
	t_obj	*tmp;

	if (!(*objs))
		*objs = obj;
	else
	{
		tmp = *objs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = obj;
	}
}

t_obj	*create_object(t_rt *rt, t_obj_id id)
{
	t_obj	*obj;

	obj = ft_calloc(sizeof(t_obj), 1);
	obj->id = id;
	obj->speckv = SPECULAR_KV;
	obj->specn = SPECULAR_N;
	obj->refract = REFRACT;
	obj->pattern_len = PATTERN_LEN;
	obj->pattern_num = PATTERN_NUM;
	obj->texture.img = NULL;
	obj->has_texture = FALSE;
	add_object_to_list(obj, &rt->objs);
	rt->num_objs++;
	return (obj);
}
