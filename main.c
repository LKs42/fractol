/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:24:42 by lugibone          #+#    #+#             */
/*   Updated: 2019/11/27 16:07:04 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

#define ITERATION_MAX 50
#define x1 -2.1
#define x2 0.6
#define y1 -1.2
#define y2 1.2
#define zoomx (2000/ (x2 - x1))
#define zoomy (2000 / (y2 - y1))

void	md_set(int *str)
{
	t_complex c;
	t_complex z;
	float	tmp;
	int i;

	for(int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			i = 0;
			c.r = x / zoomx + x1;
			c.i = y / zoomy + y1;
			z.r = 0;
			z.i = 0;

			do
			{
				tmp = z.r;
				z.r = z.r * z.r - z.i * z.i + c.r;
				z.i = 2 * z.i * tmp + c.i;
				i++;
			} while ((z.r * z.r) + (z.i * z.i) < 4 && i < ITERATION_MAX);
			if (i == ITERATION_MAX)
				fill_pixel(str, x, y, 0x000000);
			else
				fill_pixel(str, x, y, i * 255 /ITERATION_MAX);
		}
	}

}

int	main()
{
	t_scene *scene;
	scene = NULL;
	scene = init_scene(WIDTH, HEIGHT, "hell world");
	fill_img(scene, scene->bg_color);
	md_set(scene->str);
	mlx_put_image_to_window(scene->mlx_ptr,
scene->win_ptr, scene->img_ptr, 0, 0);
	mlx_key_hook(scene->win_ptr, deal_key, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
