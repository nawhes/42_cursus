/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 06:16:41 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/30 06:19:16 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

void		rt_ambientlight(t_minirt *rt);
void		rt_camera(t_minirt *rt);
void		rt_light(t_minirt *rt);
void		rt_rect(t_minirt *rt);
void		rt_resolution(t_minirt *rt);
void		rt_sphere(t_minirt *rt);

/*
** tools
*/

int			atovec3(char *line, int *i, t_vec3 *target);
int			check_atof_parameter(char *param, int *i, double *target);
int			check_atoi_parameter(char *param, int *i, int *target);
int			next(char *line, int *i);

#endif
