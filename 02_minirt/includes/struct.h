/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:28:27 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/06 05:22:04 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "libft.h"

typedef	struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_ray
{
	t_vec3			orig;
	t_vec3			dir;
}					t_ray;

typedef struct		s_onb
{
	t_vec3			u;
	t_vec3			v;
	t_vec3			w;
}					t_onb;

typedef struct		s_record
{
	double			t_min;
	double			t_max;
	double			u;
	double			v;
}					t_record;

typedef struct		s_brdf
{
	int				texture;
	double			attr;
	t_vec3			albedo;
	int				front_face;
	t_vec3			normal;
	t_vec3			wo;
	t_vec3			reflectance;
	t_vec3			point;
	t_vec3			wi;
	t_vec3			wh;
	t_vec3			attenuation;
	t_ray			ray;
}					t_brdf;

typedef struct		s_viewport
{
	t_vec3			lookfrom;
	t_vec3			lookat;
	double			vfov;
	double			aspect_ratio;
	t_vec3			origin;
	t_vec3			horizontal;
	t_vec3			vertical;
	t_vec3			lower_left_corner;
	t_ray			(*get_ray)(struct s_viewport viewport, double s, double t);
}					t_viewport;

typedef struct		s_image
{
	int				width;
	int				height;
	int				**rgb;
}					t_image;

typedef struct		s_info
{
	void			*img;
	char			*addr;
	int				bit_per_pixel;
	int				size_line;
	int				endian;
}					t_info;

typedef struct		s_output
{
	void			*mlx;
	void			*win;
	t_info			*info;
}					t_output;

/*
** Objects
*/

typedef struct		s_object
{
	void			*info;
	int				type;
	int				texture;
	double			attr;
	int				(*hit)(struct s_object ob, t_ray r, t_record *rec, 
						t_brdf *brdf);
}					t_object;

typedef struct		s_sphere
{
	t_vec3			coord;
	t_vec3			rgb;
	double			radius;
}					t_sphere;

typedef struct		s_xyrect
{
	double			x0;
	double			x1;
	double			y0;
	double			y1;
	double			k;
	t_vec3			rgb;
}					t_xyrect;

typedef struct		s_xzrect
{
	double			x0;
	double			x1;
	double			z0;
	double			z1;
	double			k;
	t_vec3			rgb;
}					t_xzrect;

typedef struct		s_yzrect
{
	double			y0;
	double			y1;
	double			z0;
	double			z1;
	double			k;
	t_vec3			rgb;
}					t_yzrect;

typedef struct		s_square
{
	t_vec3			coord;
	t_vec3			normal;
	double			side_size;
	t_vec3			rgb;
}					t_square;

typedef struct		s_rect
{
	t_vec3			coord;
	t_vec3			normal;
	double			width;
	double			height;
	t_vec3			rgb;
}					t_rect;

typedef struct		s_plane
{
	t_vec3			coord;
	t_vec3			normal;
	t_vec3			rgb;
}					t_plane;

typedef struct		s_cylinder
{
	t_vec3			coord;
	t_vec3			normal;
	double			radius;
	double			height;
	t_vec3			rgb;
}					t_cylinder;

typedef struct		s_cy
{
	t_vec3			top;
	t_vec3			bottom;
	t_vec3			o;
	t_vec3			d;
	t_vec3			normal;
	double			radius;
	t_vec3			r;
	t_vec3			p;
	double			front;
	double			back;
}					t_cy;

typedef struct		s_triangle
{
	t_vec3			point1;
	t_vec3			point2;
	t_vec3			point3;
	t_vec3			rgb;
}					t_triangle;

typedef struct		s_minirt
{
	int				r_x;
	int				r_y;
	double			ambient_ratio;
	t_vec3			ambient_rgb;
	char			*line;
	t_list			*p_viewport;
	t_list			*p_object;
	t_list			*p_light;
	t_list			*p_image;
}					t_minirt;

#endif
