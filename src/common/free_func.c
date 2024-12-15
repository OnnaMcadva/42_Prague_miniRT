/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:23:41 by annavm            #+#    #+#             */
/*   Updated: 2024/12/15 21:32:48 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

void rt_free(t_rt *rt)
{
    if (rt)
    {
        if (rt->light)
            free_lights(&rt->light);

        if (rt->objs)
        {
            t_obj *obj = rt->objs;
            while (obj)
            {
                if (obj->has_texture)
                {
                    free(obj->texture.path);
                    obj->has_texture = FALSE;
                }
                obj = obj->next;
            }
            free_objects(rt, &rt->objs);
        }
        free(rt);
    }
}

void	free_lights(t_light **lights)
{
	t_light	*tmp;
	t_light	*light;

	light = *lights;
	while (light)
	{
		tmp = light;
		light = light->next;
		free(tmp);
	}
	*lights = 0;
}

void	free_objects(t_rt *rt, t_obj **objs)
{
	t_obj	*tmp;
	t_obj	*obj;

	obj = *objs;
	(void)rt;
	while (obj)
	{
		tmp = obj;
		obj = obj->next;
		free(tmp);
	}
	*objs = 0;
}

void	free_array(char *arr[])
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}