/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 02:04:41 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/24 22:16:41 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <fcntl.h>
# include "struct.h"

int			read_rt(const char *filename, t_minirt *rt);
int			output_init
		(t_output *output, const char *title, t_image *image, int count_img);
int			output_print(t_output *output, t_info *info, t_image *image);

#endif
