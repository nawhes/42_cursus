/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   degrees_to_radians.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 18:48:10 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/17 18:49:09 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

double			degrees_to_radians(double degrees)
{
	return (degrees * PI / 180.0);
}
