/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:39:17 by nchonka           #+#    #+#             */
/*   Updated: 2024/12/10 14:45:21 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

int	parse_extra_params(t_rt *rt, t_obj *obj, char **params, int i)
{
	while (params && params[++i])
	{
		rt->pnum = i;
		if (ft_strncmp(params[i], "spc", 3) == 0
			&& parse_specular(params[i] + 4, obj))
			return (print_parse_err(rt, params, INVALID_SPEC_PARAMS));
		if (ft_strncmp(params[i], "ref", 3) == 0
			&& parse_float(params[i] + 4, &obj->refract))
			return (print_parse_err(rt, params, NOT_A_FLOAT));
		if (ft_strncmp(params[i], "pat", 3) == 0
			&& parse_pattern(params[i] + 4, obj))
			return (print_parse_err(rt, params, INVALID_PATTERN_PARAMS));
		if (ft_strncmp(params[i], "txm", 3) == 0
			&& parse_texture(params[i] + 4, obj))
			return (print_parse_err(rt, params, INVALID_TEXTURE_PARAMS));
		if (ft_strncmp(params[i], "alp", 3) == 0 && parse_float(params[i] + 4, &obj->alpha))
			return (print_parse_err(rt, params, NOT_A_FLOAT));
	}
	return (0);
}


