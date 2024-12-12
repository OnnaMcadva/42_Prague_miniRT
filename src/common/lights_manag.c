/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_manag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:06:46 by annavm            #+#    #+#             */
/*   Updated: 2024/12/11 23:09:22 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

void	add_light_to_list(t_light *new_light, t_light **lights)
{
	t_light	*tmp;

	if (!(*lights))
		*lights = new_light;
	else
	{
		tmp = *lights;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_light;
	}
}

t_light	*create_light(t_rt *rt)
{
	t_light	*new_light;

	new_light = ft_calloc(sizeof(t_light), 1);
	if (!new_light)
		return (0);
	new_light->id = id_light;
	add_light_to_list(new_light, &rt->light);
	return (new_light);
}
