/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 19:52:18 by cfranco           #+#    #+#             */
/*   Updated: 2018/04/10 17:05:50 by cfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fdf.h"
#include "mlx.h"
#include <libft.h>
#include <stdlib.h>
#include <math.h>

void	translate(t_list *p_lst, float tx, float ty, float tz)
{
	t_list	*tmp;
	float	tmat[4][4];

	tmp = p_lst;
	init_matrix(tmat);
	tmat[0][3] = tx;
	tmat[1][3] = ty;
	tmat[2][3] = tz;
	while (tmp)
	{
		mult((t_vector4f *)tmp->content, tmat);
		tmp = tmp->next;
	}
}

void	apply_rotation(t_list *p_lst, float xmat[4][4],
						float ymat[4][4], float zmat[4][4])
{
	while (p_lst)
	{
		mult((t_vector4f *)p_lst->content, ymat);
		mult((t_vector4f *)p_lst->content, xmat);
		mult((t_vector4f *)p_lst->content, zmat);
		p_lst = p_lst->next;
	}
}

void	rotate(t_list *p_lst, float rx, float ry, float rz)
{
	t_list	*tmp;
	float	xmat[4][4];
	float	ymat[4][4];
	float	zmat[4][4];

	tmp = p_lst;
	init_matrix(xmat);
	init_matrix(ymat);
	init_matrix(zmat);
	xmat[1][1] = cos(rx);
	xmat[1][2] = sin(rx);
	xmat[2][1] = -sin(rx);
	xmat[2][2] = cos(rx);
	ymat[0][0] = cos(ry);
	ymat[0][2] = -sin(ry);
	ymat[2][0] = sin(ry);
	ymat[2][2] = cos(ry);
	zmat[0][0] = cos(rz);
	zmat[0][1] = sin(rz);
	zmat[1][0] = -sin(rz);
	zmat[1][1] = cos(rz);
	apply_rotation(tmp, xmat, ymat, zmat);
}

void	cur_point(t_list *p_lst, t_line *line, t_view *view)
{
	float	div;
	float	scale;
	int		sum;

	sum = 500;
	div = 1;
	scale = 1;
	if (view->pers)
		scale = -10 / tan(10 * 0.5 * M_PI / 180);
	if (((t_vector4f *)p_lst->content)->z && view->pers)
		div = ((t_vector4f *)p_lst->content)->z;
	if (div != 1 && div > -0.5)
		div = -0.2;
	line->x0 = (view->h_width * scale *
		((t_vector4f *)p_lst->content)->x) / div + sum;
	line->y0 = (view->h_width * scale *
		((t_vector4f *)p_lst->content)->y) / div + sum;
	line->c1 = ((t_point *)p_lst->content)->color;
}

void	calculate_draw(t_view *view)
{
	t_list	*tmp;
	t_list	*ver;
	t_line	line;
	int		c;

	c = 0;
	tmp = view->model.p_lst;
	ver = view->model.p_lst;
	mlx_clear_window(view->mlx_ptr, view->win_ptr);
	while (tmp)
	{
		cur_point(tmp, &line, view);
		if (tmp->next && (c + 1) % view->model.width != 0)
			draw_horizontal(tmp->next, line, view);
		if (c >= view->model.width)
			draw_vertical(&ver, line, view);
		tmp = tmp->next;
		c++;
	}
	tmp = NULL;
	ver = NULL;
}
