/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:27:55 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/01 03:33:33 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double		clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

double		double_max(double a, double b)
{
	if (a > b)
		return a;
	return b;
}

double		double_min(double a, double b)
{
	if (a > b)
		return b;
	return a;
}

