/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_bar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:11:10 by annavm            #+#    #+#             */
/*   Updated: 2024/12/16 23:47:25 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	draw_bar(t_rt *rt, int x, int y)
{
	int	h;

	h = PROGBAR_H + y;
	while (y < h)
	{
		mlx_pixel_put(rt->mlx, rt->main_win, x, y, YELLOW);
		y++;
	}
}

void	progress_update(t_rt *rt)
{
	float	perc;
	int		bar_x;
	int		bar_y;

	bar_x = (rt->width * 0.5) - (PROGBAR_W / 2);
	bar_y = (rt->height * 0.5) - (PROGBAR_H / 2);
	pthread_mutex_lock(&rt->process_lock);
	rt->process += 1;
	perc = (rt->process / rt->height);
	printf("Processing : %*.2f%%\r", 6, perc * 100);
	fflush(stdout);
	if (rt->height > 100 && rt->width > PROGBAR_W)
	{
		draw_bar(rt, bar_x + ((PROGBAR_W * perc)), bar_y);
	}
	if (rt->process > rt->height - 1)
	{
		mlx_clear_window(rt->mlx, rt->main_win);
		rt->process = 0;
	}
	pthread_mutex_unlock(&rt->process_lock);
}
