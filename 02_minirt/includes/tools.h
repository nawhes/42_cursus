/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 05:54:44 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/30 06:28:59 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "struct.h"

double			clamp(double x, double min, double max);
double			random_double(void);
double			random_double_range(double min, double max);
double			degrees_to_radians(double degrees);
void			error_handle(int handler, t_minirt *rt);

#endif
