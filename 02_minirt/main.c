/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 03:43:25 by sehpark           #+#    #+#             */
/*   Updated: 2020/12/10 04:19:47 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int main(void)
{
  void *mlx;
 // void *window;
  
  mlx = mlx_init();
  mlx_new_window(mlx, 1000, 1000, "Title");
  
  mlx_loop(mlx);
  return (0);
}
