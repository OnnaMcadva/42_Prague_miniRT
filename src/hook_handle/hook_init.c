/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:58:22 by annavm            #+#    #+#             */
/*   Updated: 2024/12/16 23:16:28 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	switch_var(int *var)
{
	if (*var)
		*var = 0;
	else
		*var = 1;
}

void	cam_touch_key(int key, t_rt *rt)
{
	if (key == W_KEY)
		move_camera_forw_back(rt, forward);
	if (key == S_KEY)
		move_camera_forw_back(rt, backward);
	if (key == A_KEY)
		move_camera(rt, left);
	if (key == D_KEY)
		move_camera(rt, right);
	if (key == R_KEY)
		move_camera(rt, up);
	if (key == F_KEY)
		move_camera(rt, down);
	if (key == E_KEY)
		rotate_camera(rt, left);
	if (key == Q_KEY)
		rotate_camera(rt, right);
}

void	light_touch_key(int key, t_rt *rt)
{
	if (key == LEFT_ARROW)
		move_light(rt, left);
	if (key == RIGHT_ARROW)
		move_light(rt, right);
	if (key == UP_ARROW)
		move_light(rt, up);
	if (key == DOWN_ARROW)
		move_light(rt, down);
	if (key == NP_7)
		change_light_color(rt, 10, 0, 0);
	if (key == NP_8)
		change_light_color(rt, 0, 10, 0);
	if (key == NP_9)
		change_light_color(rt, 0, 0, 10);
	if (key == NP_4)
		change_light_color(rt, -10, 0, 0);
	if (key == NP_5)
		change_light_color(rt, 0, -10, 0);
	if (key == NP_6)
		change_light_color(rt, 0, 0, -10);
	if (key == PLUS_KEY)
		change_light_brightness(rt, 0.1);
	if (key == MINUS_KEY)
		change_light_brightness(rt, -0.1);
}

int	key_press(int key, t_rt *rt)
{
	if (key == ESC_KEY)
		exit_win(rt);
	rt->event.key[key] = 1;
	if (key == L_KEY)
	{
		switch_var(&rt->img.antialiasing_on);
		render(rt);
	}
	if (key == NP_1 || key == NP_2 || key == NP_3)
		manage_fig(key, rt);
	if (key == C_KEY)
		printf ("%s", MERRY);
	cam_touch_key(key, rt);
	light_touch_key(key, rt);
	if (key == X_KEY)
		elka("scenes/elka.rt");
	return (0);
}

int	key_release(int key, t_rt *rt)
{
	rt->event.key[key] = 0;
	return (0);
}
