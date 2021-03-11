/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 11:41:20 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/08 18:53:17 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	get_bmp_file(const char *filename)
{
	int		fd;
	char	*bmp_name;

	if (ft_strrchr(filename, '/'))
	{
		filename = ft_strrchr(filename, '/');
		filename++;
	}
	if (!(bmp_name = malloc(sizeof(char) * (ft_strlen(filename) + 
						ft_strlen(OUTPUT_DIR) + 5))))
		return (-1);
	ft_strcpy(bmp_name, OUTPUT_DIR);
	ft_strcat(bmp_name, filename);
	ft_strcat(bmp_name, ".bmp");
	if (!(fd = open(bmp_name, O_WRONLY | O_CREAT | O_TRUNC, 
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)))
		return (-1);
	free(bmp_name);
	return (fd);
}

static t_bmp	get_header(t_minirt *rt)
{
	t_bmp	header;

	header.bf_type[0] = 'B';
	header.bf_type[1] = 'M';
	header.bf_size = rt->r_x * rt->r_y * PIXEL_PER_BYTE + 54;
	header.bf_reserved = 0;
	header.bf_offbits = 54;
	header.bi_size = 40;
	header.bi_width = rt->r_x;
	header.bi_height = rt->r_y * -1;
	header.bi_planes = 1;
	header.bi_bitcount = PIXEL_PER_BIT;
	header.bi_compression = 0;
	header.bi_sizeimage = rt->r_x * rt->r_y * PIXEL_PER_BYTE;
	header.bi_xpelspermeter = 2835;
	header.bi_ypelspermeter = 2835;
	header.bi_clrused = 0;
	header.bi_clrimportant = 0;
	return (header);
}

static char		*get_body(t_image *p_image, t_minirt *rt)
{
	int				i;
	char			*body;
	union u_rgba	rgba;

	if (!(body = malloc(sizeof(char) * (rt->pixel * PIXEL_PER_BYTE))))
		return (NULL);
	i = 0;
	while (i < rt->pixel)
	{
		rgba.color = p_image->rgba[i];
		if (PIXEL_PER_BIT == 32)
			ft_memcpy(body + (i * PIXEL_PER_BYTE), rgba.rgba, PIXEL_PER_BYTE);
		if (PIXEL_PER_BIT == 24)
			ft_memcpy(body + (i * PIXEL_PER_BYTE), rgba.rgb, PIXEL_PER_BYTE);
		i++;
	}
	return (body);
}

void			export_bmp(const char *filename, t_minirt *rt)
{
	int		fd;
	t_bmp	header;
	t_image	*p_image;
	char	*body;

	if (!(fd = get_bmp_file(filename)))
		error_handle(-1, rt);
	header = get_header(rt);
	write(fd, &header, 2);
	write(fd, &header.bf_size, 52);
	p_image = rt->p_image->content;
	body = get_body(p_image, rt);
	write(fd, body, rt->pixel * PIXEL_PER_BYTE);
	free(body);
	close(fd);
	return ;
}
