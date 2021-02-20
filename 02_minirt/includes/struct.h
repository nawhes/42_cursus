/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:28:27 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/21 00:28:12 by sehpark          ###   ########.fr       */
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

typedef struct		s_hit_record
{
	t_vec3			p;
	t_vec3			normal;
	double			t;
	double			t_min;
	double			t_max;
	double			u;
	double			v;
	int				front_face;
	void			(*set_face_normal)
		(struct s_hit_record *this, t_ray r, t_vec3 *outward_normal);
	double			attr;
	int				texture;
	t_vec3			albedo;
	t_vec3			emitted;
	t_vec3			attenuation;
	t_ray			ray;
}					t_hit_record;

/*
**
*/

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
	int				(*hit)(struct s_object ob, t_ray r, t_hit_record *rec);
}					t_object;

/*
typedef struct		s_light
{
	t_vec3			coord;
	double			ratio;
	t_vec3			rgb;
}					t_light;
*/

typedef struct		s_sphere
{
	t_vec3			coord;
	t_vec3			rgb;
	double			diameter;
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

typedef struct		s_plane
{
	t_vec3			corrd;
	t_vec3			orientation;
	t_vec3			rgb;
	double			side_size;
}					t_plane;

typedef struct		s_cylinder
{
	t_vec3			coord;
	t_vec3			orientation;
	t_vec3			rgb;
	double			diameter;
	double			height;
}					t_cylinder;

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
