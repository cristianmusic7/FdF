/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 19:52:18 by cfranco           #+#    #+#             */
/*   Updated: 2018/04/11 03:37:15 by cfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fdf.h"
#include "mlx.h"
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	rotate_key(t_view *view, int key)
{
	float	num;

	num = M_PI / 20;
	translate(view->model.p_lst, 0, 0, view->scroll);
	if (key == 125)
		rotate(view->model.p_lst, num, 0, 0);
	if (key == 126)
		rotate(view->model.p_lst, -num, 0, 0);
	if (key == 123)
		rotate(view->model.p_lst, 0, num, 0);
	if (key == 124)
		rotate(view->model.p_lst, 0, -num, 0);
	translate(view->model.p_lst, 0, 0, -view->scroll);
	calculate_draw(view);
}

int		mouse_handler(int button, int x, int y, t_view *view)
{
	if (button == 4)
		view->h_width += view->h_width / 20;
	else if (button == 5)
		view->h_width -= view->h_width / 20;
	x = 0;
	y = 0;
	calculate_draw(view);
	return (0);
}

int		close_window(int key, void *param)
{
	t_view *view;

	view = (t_view *)param;
	if (key == 53)
	{
		mlx_destroy_window(view->mlx_ptr, view->win_ptr);
		exit(0);
	}
	else if (key == 123 || key == 124 || key == 125 || key == 126)
		rotate_key(view, key);
	else if (key == 35)
	{
		view->pers = !view->pers;
		calculate_draw(view);
	}
	return (0);
}

void	print_error(void)
{
	perror("Error");
	exit(0);
}
