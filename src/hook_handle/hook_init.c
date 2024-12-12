/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:58:22 by annavm            #+#    #+#             */
/*   Updated: 2024/12/12 21:19:45 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

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
	if (key == Q_KEY)
		rotate_camera(rt, left);
	if (key == E_KEY)
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
	if (key == NP_7) // Увеличить красный компонент
		change_light_color(rt, 10, 0, 0);
	if (key == NP_8) // Увеличить зеленый компонент
		change_light_color(rt, 0, 10, 0);
	if (key == NP_9) // Увеличить синий компонент
		change_light_color(rt, 0, 0, 10);
	if (key == NP_4) // Уменьшить красный компонент
		change_light_color(rt, -10, 0, 0);
	if (key == NP_5) // Уменьшить зеленый компонент
		change_light_color(rt, 0, -10, 0);
	if (key == NP_6) // Уменьшить синий компонент
		change_light_color(rt, 0, 0, -10);
	if (key == PLUS_KEY) // Увеличить яркость
		change_light_brightness(rt, 0.1);
	if (key == MINUS_KEY) // Уменьшить яркость
		change_light_brightness(rt, -0.1);
}

void restart_program(const char *arg) 
{ 
    char *args[] = {"./minirt", (char *)arg, NULL}; 
	execv(args[0], args); 
    perror("execv failed"); 
    exit(1); 
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
	if (key == C_KEY)
		printf ("%s", MERRY);
	cam_touch_key(key, rt);
	light_touch_key(key, rt);
	if (key == X_KEY)
		restart_program("scenes/elka.rt");
	return (0);
}

int	key_release(int key, t_rt *rt)
{
	rt->event.key[key] = 0;
	return (0);
}
