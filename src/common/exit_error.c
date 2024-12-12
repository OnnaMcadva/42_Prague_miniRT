/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:18:38 by nchonka           #+#    #+#             */
/*   Updated: 2024/12/12 19:30:29 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

void	goodbye(char *s)
{
	if (errno == 0)
		printf ("%s", s);
	else
		perror(s);
	exit(1);
}

int	print_parse_err(t_rt *rt, char **arr, char *msg)
{
	printf("Error: %s", msg);
	if (rt->lnum)
		printf(" [line: %d :param: %d]\n", rt->lnum, (rt->pnum + 1));
	else
		printf("\n");

	free_array(arr);
	return (1);
}

int	print_err(char *msg)
{
	printf ("Error: %s\n", msg);
	return (1);
}

int	exit_win(t_rt *rt)
{
	rt_clear(rt);
	exit(0);
	return (0);
}