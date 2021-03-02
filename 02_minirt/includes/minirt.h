/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 04:17:50 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 09:25:45 by sehpark          ###   ########.fr       */
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

# define	PI				3.1415926535897932385
# define	SAMPLE_PER_PIXEL	20
# define	MAX_DEPTH			5

t_vec3				reflect(t_vec3 v, t_vec3 n);
t_vec3				refract(t_vec3 uv, t_vec3 n, double etai_over_etat);
t_vec3		sphere_random(t_sphere *sp, t_vec3 o);
double		light_pdf(t_object *p_ob, t_ray r);
void		microfacet(t_brdf *brdf);
t_vec3		lambert_eval(t_brdf brdf, t_vec3 wi);
t_vec3		microfacet_eval(t_brdf brdf, t_vec3 wi);

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

t_xyrect	*xyrect(t_xyrect this);
t_xzrect	*xzrect(t_xzrect this);
t_yzrect	*yzrect(t_yzrect this);
int			xyrect_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf);
int			xzrect_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf);
int			yzrect_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf);


/*
** texture
*/


void		set_brdf(t_brdf *brdf, t_object ob, t_ray r, t_vec3 normal);
void		set_brdf2(t_brdf *brdf, t_vec3 point);
t_vec3		random_cosine_direction();
void		lambertian(t_brdf *brdf);
void		mirror(t_brdf *brdf);
void		transparent(t_brdf *brdf);
void		check_box(t_brdf *brdf);

/*
** onb
*/

t_onb		onb_build_from_w(t_vec3 n);
t_onb		onb_build_from_v(t_vec3 n);
t_vec3		onb_local(t_onb uvw, t_vec3 a);
double		onb_value(t_onb uvw, t_vec3 dir);

/*
** viewport
*/

t_viewport		*viewport(t_viewport this);

t_record	record();

t_ray			ray(t_vec3 orig, t_vec3 dir);
t_vec3			ray_at(t_ray a, double t);
t_vec3			trace(t_ray r, t_minirt *rt, int depth);

/*
** image
*/

t_image			*image(int width, int height);
void			image_render(t_minirt *rt);

/*
** tools
*/

double			double_max(double a, double b);
double			double_min(double a, double b);
double			clamp(double x, double min, double max);
double			clamp0_1(double x);
double			random_double(void);
double			random_double_range(double min, double max);
int				random_int_range(int min, int max);
double			degrees_to_radians(double degrees);
void			error_handle(int handler, t_minirt *rt);




#endif
