/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 19:52:18 by cfranco           #+#    #+#             */
/*   Updated: 2018/04/11 03:49:32 by cfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fdf.h"
#include "mlx.h"
#include <libft.h>
#include <stdlib.h>
#include <math.h>

void	create_point(char *input, t_model *model, int x)
{
	t_point point;

	point.coord.x = x;
	point.coord.y = model->height;
	point.coord.z = (float)ft_atoi(input);
	point.coord.w = 1;
	ft_lstadd(&(model->p_lst), ft_lstnew(&point, sizeof(t_point)));
	model->max_z = MAX(model->max_z, (int)point.coord.z);
	free(input);
}

void	read_line(t_model *model, char *line)
{
	char	**input;
	char	**in_tmp;
	int		x;

	x = 0;
	input = ft_strsplit(line, ' ');
	in_tmp = input;
	while (input[x])
		x++;
	model->width = x;
	x = -(x / 2);
	while (*input)
	{
		create_point(*input, model, x++);
		input++;
	}
	free(*input);
	free(in_tmp);
	(model->height)++;
	free(line);
}

void	update_data(t_list *tmp, t_model *model)
{
	while (tmp)
	{
		((t_vector4f *)tmp->content)->y -= (model->height / 2);
		if (((t_vector4f *)tmp->content)->z == 0)
			((t_point *)tmp->content)->color = model->color1;
		else
			((t_point *)tmp->content)->color =
				clerp(ABS(((t_vector4f *)tmp->content)->z)
						/ model->max_z, model->color1, model->color2);
		tmp = tmp->next;
	}
}

void	read_input(char *file, t_model *model)
{
	int		fd;
	char	*line;
	int		res;
	t_list	*tmp;

	model->p_lst = NULL;
	model->height = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		print_error();
	while ((res = get_next_line(fd, &line)) && res != -1)
		read_line(model, line);
	if (res == -1)
		print_error();
	free(line);
	line = NULL;
	if (close(fd) == -1)
		print_error();
	tmp = model->p_lst;
	update_data(tmp, model);
}

int		main(int argc, char **argv)
{
	t_view view;

	view.s_width = 1000;
	view.s_height = 1000;
	if (argc == 1 || argc > 4)
		ft_putendl("usage: file_name [front color] [back color]");
	else
	{
		check_colors(argc, argv, &view);
		view.mlx_ptr = mlx_init();
		view.win_ptr = mlx_new_window(view.mlx_ptr, view.s_width,
				view.s_height, "fdf project");
		view.pers = 0;
		view.h_width = view.s_width / (MAX3(view.model.width,
					view.model.height, view.model.max_z * 2) + 10);
		view.scroll = view.s_width / view.h_width;
		rotate(view.model.p_lst, -M_PI / 20, -M_PI / 20, 0);
		translate(view.model.p_lst, 0, 0, -view.scroll);
		calculate_draw(&view);
		mlx_key_hook(view.win_ptr, close_window, &view);
		mlx_mouse_hook(view.win_ptr, mouse_handler, &view);
		mlx_loop(view.mlx_ptr);
	}
	return (0);
}
