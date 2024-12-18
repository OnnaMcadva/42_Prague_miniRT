/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxwin_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:10:53 by annavm            #+#    #+#             */
/*   Updated: 2024/12/18 23:19:27 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	clear_objects(t_rt *rt)
{
	t_obj	*current;
	t_obj	*next;

	current = rt->objs;
	while (current)
	{
		next = current->next;
		if (current->has_texture)
		{
			free(current->texture.path);
			if (current->texture.img)
				mlx_destroy_image(rt->mlx, current->texture.img);
		}
		free(current);
		current = next;
	}
	rt->objs = NULL;
}

static void	clear_mlx(t_rt *rt)
{
	if (rt->main_win)
		mlx_destroy_window(rt->mlx, rt->main_win);
	if (rt->img.img)
		mlx_destroy_image(rt->mlx, rt->img.img);
	if (rt->mlx)
	{
		mlx_destroy_display(rt->mlx);
		free(rt->mlx);
		rt->mlx = NULL;
	}
}

void	rt_clear(t_rt *rt)
{
	clear_objects(rt);
	clear_mlx(rt);
	free_lights(&rt->light);
	free(rt);
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
