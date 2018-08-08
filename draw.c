/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 19:52:18 by cfranco           #+#    #+#             */
/*   Updated: 2018/04/10 17:17:20 by cfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fdf.h"
#include "mlx.h"
#include <libft.h>
#include <stdlib.h>
#include <math.h>

void	draw_line(int dy, int dx, t_line line, t_view *view)
{
	int		d;
	int		x;
	int		y;
	int		i;
	int		h;

	if ((h = dy > dx))
		ft_swap(&dy, &dx);
	i = 1;
	d = (dy << 1) - dx;
	x = line.x0 + (line.x1 >= line.x0 ? 1 : -1);
	y = line.y0;
	while (i++ <= dx)
	{
		if (d > 0)
		{
			d += (dy - dx) << 1;
			y += line.y1 >= line.y0 ? 1 : -1;
		}
		else
			d += dy << 1;
		mlx_pixel_put(view->mlx_ptr, view->win_ptr, h ? y : x, h ? x : y, clerp(
			(float)(x - line.x0) / (line.x1 - line.x0), line.c1, line.c2));
		x += line.x1 >= line.x0 ? 1 : -1;
	}
}

void	make_line(t_line line, t_view *view)
{
	int		dx;
	int		dy;
	t_line	tmp;

	if (!check_bounds(line, view))
		return ;
	dx = ABS(line.x1 - line.x0);
	dy = ABS(line.y1 - line.y0);
	mlx_pixel_put(view->mlx_ptr, view->win_ptr, line.x0, line.y0, line.c1);
	if (dy <= dx)
		draw_line(dy, dx, line, view);
	else
	{
		tmp.x0 = line.y0;
		tmp.y0 = line.x0;
		tmp.x1 = line.y1;
		tmp.y1 = line.x1;
		tmp.c1 = line.c1;
		tmp.c2 = line.c2;
		draw_line(dy, dx, tmp, view);
	}
}

void	draw_horizontal(t_list *p_lst, t_line line, t_view *view)
{
	float div;
	float scale;

	div = 1;
	scale = 1;
	if (view->pers)
		scale = -10 / tan(10 * 0.5 * M_PI / 180);
	if (!((t_vector4f *)p_lst->content)->z || !view->pers)
		div = 1;
	else
		div = ((t_vector4f *)p_lst->content)->z;
	if (div != 1 && div > -0.5)
		div = -0.2;
	line.x1 = (view->h_width * scale *
		((t_vector4f *)p_lst->content)->x) / div + 500;
	line.y1 = (view->h_width * scale *
		((t_vector4f *)p_lst->content)->y) / div + 500;
	line.c2 = ((t_point *)p_lst->content)->color;
	make_line(line, view);
}

void	draw_vertical(t_list **p_lst, t_line line, t_view *view)
{
	float div;
	float scale;

	div = 1;
	scale = 1;
	if (view->pers)
		scale = -10 / tan(10 * 0.5 * M_PI / 180);
	if (!((t_vector4f *)(*p_lst)->content)->z || !view->pers)
		div = 1;
	else
		div = ((t_vector4f *)(*p_lst)->content)->z;
	if (div != 1 && div > -0.5)
		div = -0.2;
	line.x1 = (view->h_width * scale *
		((t_vector4f *)(*p_lst)->content)->x) / div + 500;
	line.y1 = (view->h_width * scale *
		((t_vector4f *)(*p_lst)->content)->y) / div + 500;
	line.c2 = ((t_point *)(*p_lst)->content)->color;
	make_line(line, view);
	*p_lst = (*p_lst)->next;
}

void	check_colors(int argc, char **argv, t_view *view)
{
	view->model.color1 = 0xFFFFFF;
	view->model.color2 = 0xFFFFFF;
	if (argc > 2)
		view->model.color2 = ft_atoi_base(argv[2], 16);
	if (argc > 3)
		view->model.color1 = ft_atoi_base(argv[3], 16);
	read_input(argv[1], &(view->model));
}
