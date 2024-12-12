/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_bar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:11:10 by annavm            #+#    #+#             */
/*   Updated: 2024/12/12 12:37:08 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

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

char	*format_progress(float percent)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(percent * 100);
	tmp2 = ft_strjoin("Processing: ", tmp);
	free(tmp);
	tmp = ft_strjoin(tmp2, "%");
	free(tmp2);
	return (tmp);
}

void update_text(t_rt *rt, float perc)
{
    int x;
    int y;

    x = (rt->width * 0.5) - (PROGBAR_TEXT_W * 0.5);
    y = (rt->height * 0.5) + (PROGBAR_TEXT_H * 2);

    if (rt->process_text)
    {
        free(rt->process_text);
        rt->process_text = NULL;
    }
    rt->process_text = format_progress(perc);
    mlx_string_put(rt->mlx, rt->main_win, x, y, BLUE, rt->process_text);
}

void reset_process(t_rt *rt)
{
    if (rt->process_text)
    {
        free(rt->process_text);
        rt->process_text = NULL;
    }
    if (rt->process > rt->height - 1)
    {
        mlx_clear_window(rt->mlx, rt->main_win);
        rt->process = 0;
    }
}

void progress_update(t_rt *rt)
{
    float perc;
    int bar_x;
    int bar_y;

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
        update_text(rt, perc);
    }
    
    reset_process(rt);
    pthread_mutex_unlock(&rt->process_lock);
}