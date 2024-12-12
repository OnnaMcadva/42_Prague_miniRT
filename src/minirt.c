/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:08:13 by annavm            #+#    #+#             */
/*   Updated: 2024/12/11 23:08:12 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

static int	handle_no_event(t_rt *rt)
{
	(void) rt;
	return (0);
}

void	hook_init(t_rt *rt)
{
	ft_memset(rt->event.key, 0, MAX_KEY);
	rt->event.mouse = 0;
	mlx_loop_hook(rt->mlx, handle_no_event, rt);
	mlx_hook(rt->main_win, KeyPress, KeyPressMask, key_press, rt);
	mlx_hook(rt->main_win, KeyRelease, KeyReleaseMask, key_release, rt);
	mlx_hook(rt->main_win, DestroyNotify, NoEventMask, exit_win, rt);
	mlx_hook(rt->main_win, ButtonPress, ButtonPressMask, mouse_press, rt);
	mlx_hook(rt->main_win, ButtonRelease, ButtonReleaseMask, mouse_release, rt);
	mlx_hook(rt->main_win, MotionNotify, PointerMotionMask, mouse_moving, rt);
}

int	scene_name(const char *s)
{
	const char	*prefix;
	const char	*suffix;
	size_t		s_len;
	size_t		prefix_len;
	size_t		suffix_len;

	prefix = "scenes/";
	suffix = ".rt";
	if (!s)
		return (0);
	s_len = ft_strlen(s);
	prefix_len = ft_strlen(prefix);
	suffix_len = ft_strlen(suffix);
	if (s_len < prefix_len + suffix_len)
		return (0);
	if (ft_strncmp(s, prefix, prefix_len) != 0)
		return (0);
	if (ft_strcmp(s + s_len - suffix_len, suffix) != 0)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
    t_rt *rt;

	if (argc != 2 || !scene_name(argv[1]))
		goodbye(IS_NAME);
	rt = ft_calloc(sizeof(t_rt), 1);
	if (!rt)
		goodbye(ERR_MEM_ALLOC);

	if (open_file(rt, argv[1]))
	{
		win_handle(rt, argv[1]);
		hook_init(rt);
		render(rt);
		mlx_loop(rt->mlx);
		mlx_do_key_autorepeaton(rt->mlx);
	}
	rt_free(rt);
	return (0);
}
