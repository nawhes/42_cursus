/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 04:17:50 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/06 05:24:13 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "struct.h"
# include "libft.h"
# include "vector.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define	LAMBERTIAN				1
# define	MIRROR					2
# define	MICROFACET_METAL		3
# define	MICROFACET_NON_METAL	4
# define	TRANSPARENT				5
# define	CHECK_BOX				6
# define	DIFFUSE_LIGHT			9

# define	OB_SPHERE				11
# define	OB_XYRECT				12
# define	OB_YZRECT				13
# define	OB_XZRECT				14
# define	OB_PLANE				15
# define	OB_SQUARE				16
# define	OB_CYLINDER				17
# define	OB_TRIANGLE				18
# define	OB_RECT					19

# define	SAMPLE_PER_PIXEL		20
# define	MAX_DEPTH				5

/*
** ray trace
*/

t_record	record();
t_ray		ray(t_vec3 orig, t_vec3 dir);
t_vec3		ray_at(t_ray a, double t);
t_vec3		trace(t_ray r, t_minirt *rt, int depth);

/*
** io
*/

int			read_rt(const char *filename, t_minirt *rt);
t_output	*output(const char *title, t_minirt *rt);
int			output_print(t_output *out, t_minirt *rt);

/*
** rt
*/

void		rt_ambientlight(t_minirt *rt);
void		rt_camera(t_minirt *rt);
void		rt_light(t_minirt *rt);
void		rt_xyrect(t_minirt *rt);
void		rt_xzrect(t_minirt *rt);
void		rt_yzrect(t_minirt *rt);
void		rt_resolution(t_minirt *rt);
void		rt_sphere(t_minirt *rt);
void		rt_plane(t_minirt *rt);
void		rt_square(t_minirt *rt);
void		rt_cylinder(t_minirt *rt);
void		rt_triangle(t_minirt *rt);

int			atovec3(char *line, int *i, t_vec3 *target);
int			check_atof_parameter(char *param, int *i, double *target);
int			check_atoi_parameter(char *param, int *i, int *target);
int			next(char *line, int *i);

/*
** object
*/

t_object	*object(void *info, int type, int texture, double attr);

t_sphere	*sphere(t_sphere this);
int			sphere_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf);

t_plane		*plane(t_plane this);
int			plane_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf);

t_rect		*rect(t_rect this);
int			rect_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf);
t_xyrect	*xyrect(t_xyrect this);
int			xyrect_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf);
t_xzrect	*xzrect(t_xzrect this);
int			xzrect_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf);
t_yzrect	*yzrect(t_yzrect this);
int			yzrect_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf);

t_square	*square(t_square this);
int			square_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf);

t_cylinder	*cylinder(t_cylinder this);
int			cylinder_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf);

t_triangle	*triangle(t_triangle this);
int			triangle_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf);

/*
** brdf
*/

t_vec3		reflect(t_vec3 v, t_vec3 n);
t_vec3		refract(t_vec3 uv, t_vec3 n, double etai_over_etat);
t_vec3		random_cosine_direction();
void		set_brdf(t_brdf *brdf, t_object ob, t_ray r, t_vec3 normal);
void		set_brdf2(t_brdf *brdf, t_vec3 point);

void		lambertian(t_brdf *brdf);
t_vec3		lambert_eval(t_brdf brdf, t_vec3 wi);
void		microfacet(t_brdf *brdf);
t_vec3		microfacet_eval(t_brdf brdf, t_vec3 wi);
void		mirror(t_brdf *brdf);
void		transparent(t_brdf *brdf);
void		check_box(t_brdf *brdf);

t_vec3		sphere_random(t_sphere *sp, t_vec3 o);
double		light_pdf(t_object *p_ob, t_ray r);
t_onb		onb_build_from_w(t_vec3 n);
t_onb		onb_build_from_u(t_vec3 n);
t_onb		onb_build_from_v(t_vec3 n);
t_vec3		onb_local(t_onb uvw, t_vec3 a);
double		onb_value(t_onb uvw, t_vec3 dir);

/*
** viewport
*/

t_viewport	*viewport(t_viewport this);

/*
** image
*/

t_image		*image(int width, int height);
void		image_render(t_minirt *rt);

/*
** tools
*/

double		clamp(double x, double min, double max);
double		clamp0_1(double x);
double		random_double(void);
double		random_double_range(double min, double max);
int			random_int_range(int min, int max);
double		degrees_to_radians(double degrees);
void		error_handle(int handler, t_minirt *rt);

#endif
