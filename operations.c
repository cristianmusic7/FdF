/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 19:52:18 by cfranco           #+#    #+#             */
/*   Updated: 2018/04/11 03:33:58 by cfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fdf.h"
#include "mlx.h"
#include <libft.h>
#include <stdlib.h>
#include <math.h>

float	dot_p(float v1[4], t_vector4f v2)
{
	return (v1[0] * v2.x + v1[1] * v2.y + v1[2] * v2.z + v1[3] * v2.w);
}

void	mult(t_vector4f *point, float mat[4][4])
{
	t_vector4f tmp;

	tmp = *point;
	point->x = dot_p(mat[0], tmp);
	point->y = dot_p(mat[1], tmp);
	point->z = dot_p(mat[2], tmp);
	point->w = dot_p(mat[3], tmp);
}

void	init_matrix(float mat[4][4])
{
	int		x;
	int		y;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (x == y)
				mat[x][y] = 1;
			else
				mat[x][y] = 0;
			x++;
		}
		y++;
	}
}

int		clerp(float fraction, int color1, int color2)
{
	int		red;
	int		green;
	int		blue;

	red = ((color2 >> 16) - (color1 >> 16)) * fraction + (color1 >> 16);
	green = (((color2 & 0x00FF00) >> 8) - ((color1 & 0x00FF00) >> 8))
		* fraction + ((color1 & 0x00FF00) >> 8);
	blue = (((color2 & 0x0000FF)) - ((color1 & 0x0000FF)))
		* fraction + ((color1 & 0x0000FF));
	return (red << 16 | green << 8 | blue);
}

int		check_bounds(t_line line, t_view *view)
{
	int slope;

	slope = 0;
	if ((line.x0 < 0 && line.x1 < 0) || (line.y0 < 0 && line.y1 < 0) ||
		(line.x0 > view->s_width && line.x1 > view->s_width) ||
			(line.y0 > view->s_width && line.y1 > view->s_width))
		return (0);
	return (1);
}
