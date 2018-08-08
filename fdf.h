/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfranco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 23:38:46 by cfranco           #+#    #+#             */
/*   Updated: 2018/04/10 16:52:31 by cfranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define MAX(x, y) x > y ? x : y
# define MAX3(x, y, z) MAX(MAX(x, y),z)
# define ABS(x) (((x)<0)?-(x):(x))

# include <libft.h>

typedef struct	s_model
{
	t_list		*p_lst;
	int			width;
	int			height;
	int			max_z;
	int			color1;
	int			color2;
}				t_model;

typedef struct	s_view
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_model		model;
	float		h_width;
	int			scroll;
	int			pers;
	int			s_width;
	int			s_height;
}				t_view;

typedef struct	s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	int			c1;
	int			c2;
}				t_line;

typedef struct	s_vector4f
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vector4f;

typedef struct	s_point
{
	t_vector4f	coord;
	int			color;
}				t_point;

float			dot_p(float v1[4], t_vector4f v2);
void			mult(t_vector4f *point, float mat[4][4]);
void			init_matrix(float mat[4][4]);
int				clerp(float fraction, int color1, int color2);
int				check_bounds(t_line line, t_view *view);
void			translate(t_list *p_lst, float tx, float ty, float tz);
void			apply_rotation(t_list *p_lst, float xmat[4][4],
									float ymat[4][4], float zmat[4][4]);
void			rotate(t_list *p_lst, float rx, float ry, float rz);
void			cur_point(t_list *p_lst, t_line *line, t_view *view);
void			calculate_draw(t_view *view);
void			draw_line(int dh1, int dh2, t_line line, t_view *view);
void			make_line(t_line line, t_view *view);
void			draw_horizontal(t_list *p_lst, t_line line, t_view *view);
void			draw_vertical(t_list **p_lst, t_line line, t_view *view);
void			rotate_key(t_view *view, int key);
int				mouse_handler(int button, int x, int y, t_view *view);
void			delete_list(void *content, size_t content_size);
int				close_window(int key, void *param);
void			print_error();
void			create_point(char *input, t_model *model, int x);
void			read_line(t_model *model, char *line);
void			update_data(t_list *tmp, t_model *model);
void			read_input(char *file, t_model *model);
void			check_colors(int argc, char **argv, t_view *view);

#endif
