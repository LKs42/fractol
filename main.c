/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:24:42 by lugibone          #+#    #+#             */
/*   Updated: 2019/11/27 18:25:25 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

#define ITERATION_MAX 10/*
#define x1 -2.1
#define x2 0.6
#define y1 -1.2
#define y2 1.2
*/
#define x1 -2.1
#define x2 0.6
#define y1 -1.2
#define y2 1.2
//#define zoomx (WIDTH/ (x2 - x1))
//#define zoomy (HEIGHT / (y2 - y1))

int	md_set(t_scene *scene)
{
	t_complex c;
	t_complex z;
	float	tmp;
	int i;

	float zoomx;
	float zoomy;

	float scale = scene->scale;

	zoomx = WIDTH / (x2/scale - x1/scale);
	zoomy = HEIGHT / (y2/scale - y1/scale);

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
			} while ((z.r * z.r) + (z.i * z.i) < 4 && i < scene->iteration);
			if (i == scene->iteration)
				fill_pixel(scene->str, x, y, scene->bg_color);
			else
				fill_pixel(scene->str, x, y, i * 255 / scene->iteration);
		}
	}
	return (1);
}

int	deal_mouse(int key, int x, int y, t_scene *scene)
{
	(void)scene;
	(void)x;
	(void)y;
	ft_putnbr(key);
	ft_putchar('\n');

	if (key == 3)
	scene->scale = 1;
	if (key == 4)
		scene->iteration++;
	if (key == 5 && scene->iteration > 1)
		scene->iteration--;
	md_set(scene);
	mlx_put_image_to_window(scene->mlx_ptr,
			scene->win_ptr, scene->img_ptr, 0, 0);

	return (1);
}

int	main()
{
	t_scene *scene;
	scene = NULL;
	scene = init_scene(WIDTH, HEIGHT, "hell world");
	fill_img(scene, scene->bg_color);
	md_set(scene);
	mlx_put_image_to_window(scene->mlx_ptr,
scene->win_ptr, scene->img_ptr, 0, 0);
	mlx_key_hook(scene->win_ptr, deal_key, scene);
	mlx_mouse_hook(scene->win_ptr, deal_mouse, scene);
	mlx_loop_hook(scene->mlx_ptr, md_set, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
