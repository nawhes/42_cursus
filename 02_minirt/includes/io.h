/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 02:04:41 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/31 06:09:42 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <fcntl.h>
# include "struct.h"

int			read_rt(const char *filename, t_minirt *rt);
t_output	*output(const char *title, t_minirt *rt);
int			output_print(t_output *out, t_minirt *rt);

#endif
