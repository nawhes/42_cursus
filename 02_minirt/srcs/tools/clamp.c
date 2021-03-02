/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:27:55 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 09:23:08 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double		clamp0_1(double x)
{
	if (x < 0)
		return (0);
	if (x > 1)
		return (1);
	return (x);
}

double		clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}
