/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxwin_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:10:53 by annavm            #+#    #+#             */
/*   Updated: 2024/12/12 12:25:54 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

void rt_clear(t_rt *rt)
{
    if (rt->main_win)
        mlx_destroy_window(rt->mlx, rt->main_win);
    if (rt->img.img)
        mlx_destroy_image(rt->mlx, rt->img.img);
    if (rt->mlx)
    {
        mlx_destroy_display(rt->mlx);
        free(rt->mlx);
    }
    rt_free(rt);
    exit(0);
}

void	win_handle(t_rt *rt, char *path)
{
	rt->mlx = mlx_init();
	if (!rt->mlx)
    	exit(1);
	if (!rt->width)
		rt->width = (float) WIN_WIDTH;
	if (!rt->height)
		rt->height = (float) WIN_HEIGHT;
	if (rt->height && (rt->height < rt->width))
		rt->aspectratio = rt->width / rt->height;
	else
		rt->aspectratio = rt->height / rt->width;
	rt->main_win = mlx_new_window(rt->mlx, rt->width, rt->height, "minirt");
	if (!rt->main_win)
	    rt_clear(rt);
	rt->path = path;
	rt->img.img = mlx_new_image(rt->mlx, rt->width, rt->height);
	if (!rt->img.img)
		rt_clear(rt);
	rt->img.addr = mlx_get_data_addr(rt->img.img, &rt->img.bits_per_pixel,
			&rt->img.line_length, &rt->img.endian);
	rt->img.antialiasing_on = ANTIALIAS_ON;
	rt->img.addr_incr = rt->img.bits_per_pixel / 8;
	rt->is_processing = FALSE;
}
