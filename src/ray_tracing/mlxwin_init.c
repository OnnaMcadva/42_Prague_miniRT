/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxwin_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:10:53 by annavm            #+#    #+#             */
/*   Updated: 2024/12/16 23:48:14 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	ptr_null(void **pt)
{
	if (*pt)
		free(*pt);
	*pt = NULL;
}

void	rt_clear(t_rt *rt)
{
	if (rt->main_win)
		mlx_destroy_window(rt->mlx, rt->main_win);
	if (rt->img.img)
		mlx_destroy_image(rt->mlx, rt->img.img);
	if (rt->mlx)
	{
		mlx_destroy_display(rt->mlx);
		ptr_null(&rt->mlx);
	}
	rt_free(rt);
	exit(0);
}

static void	check_mlx_call(void *ptr, t_rt *rt)
{
	if (!ptr)
	{
		rt_clear(rt);
		exit(1);
	}
}

void	win_handle(t_rt *rt, char *path)
{
	rt->mlx = mlx_init();
	check_mlx_call(rt->mlx, rt);
	if (rt->width <= 0 || rt->height <= 0)
	{
		rt->width = (float) WIN_WIDTH;
		rt->height = (float) WIN_HEIGHT;
	}
	if (rt->height < rt->width)
		rt->aspectratio = rt->width / rt->height;
	else
		rt->aspectratio = rt->height / rt->width;
	rt->main_win = mlx_new_window(rt->mlx, rt->width, rt->height, "minirt");
	check_mlx_call(rt->main_win, rt);
	rt->path = path;
	rt->img.img = mlx_new_image(rt->mlx, rt->width, rt->height);
	check_mlx_call(rt->img.img, rt);
	rt->img.addr = mlx_get_data_addr(rt->img.img, &rt->img.bits_per_pixel,
			&rt->img.line_length, &rt->img.endian);
	rt->img.antialiasing_on = ANTIALIAS_ON;
	rt->img.addr_incr = rt->img.bits_per_pixel / 8;
	check_mlx_call(rt->img.addr, rt);
	rt->is_processing = FALSE;
}

/*
88 байт (definitely lost): Это память, которая была выделена, но утрачена, 
потому что больше нет ссылок на нее.
136 байт (indirectly lost): Это память, связанная с вышеуказанной утечкой. 
Например, указатель внутри структуры указывает на другую область памяти, и оба блока утрачены.

static void	ptr_null(void **pt)
{
	if (*pt)
		free(*pt);
	*pt = NULL;
}

void	rt_clear(t_rt *rt)
{
	// if (rt->objs->texture.img)
	// {
	// 	rt->objs->texture.img = NULL;
	// 	rt->objs->has_texture = FALSE;
	// 	free(rt->objs->texture.path);
	// }
	if (rt->main_win)
		mlx_destroy_window(rt->mlx, rt->main_win);
	if (rt->img.img)
		mlx_destroy_image(rt->mlx, rt->img.img);
	if (rt->mlx)
	{
		mlx_destroy_display(rt->mlx);
		ptr_null(&rt->mlx);
	}
	rt_free(rt);
	exit(0);
}

void	win_handle(t_rt *rt, char *path)
{
	rt->mlx = mlx_init();
	if (rt->width <= 0 || rt->height <= 0)
	{
		rt->width = (float) WIN_WIDTH;
		rt->height = (float) WIN_HEIGHT;
	}
	if (rt->height < rt->width)
		rt->aspectratio = rt->width / rt->height;
	else
		rt->aspectratio = rt->height / rt->width;
	rt->main_win = mlx_new_window(rt->mlx, rt->width, \
		rt->height, "miniRT our awesome joint project");
	rt->path = path;
	rt->img.img = mlx_new_image(rt->mlx, rt->width, rt->height);
	rt->img.addr = mlx_get_data_addr(rt->img.img, &rt->img.bits_per_pixel,
			&rt->img.line_length, &rt->img.endian);
	rt->img.antialiasing_on = ANTIALIAS_ON;
	if (!rt->img.img)
		rt_clear(rt);
	rt->img.addr_incr = rt->img.bits_per_pixel / 8;
	rt->is_processing = FALSE;
}
*/
