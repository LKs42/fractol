/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:24:42 by lugibone          #+#    #+#             */
/*   Updated: 2019/12/03 18:20:06 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>

#define ITERATION_MAX 10/*
#define x1 -2.1
#define x2 0.6
#define y1 -1.2
#define y2 1.2
			 */
//#define zoomx (WIDTH/ (x2 - x1))
//#define zoomy (HEIGHT / (y2 - y1))

int	md_loop(t_complex *c, t_complex *z, int i)
{
	double tmp;

	tmp = z->r;
	z->r = z->r * z->r - z->i * z->i + c->r;
	z->i = 2 * z->i * tmp + c->i;
	return (++i);
}

int	md_set(t_scene *scene)
{
	t_complex c;
	t_complex z;
	int i;

	double zoomx;
	double zoomy;

	zoomx = WIDTH / (scene->plan.x2 - scene->plan.x1);
	zoomy = HEIGHT / (scene->plan.y2 - scene->plan.y1);

	for(int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			i = 0;
			z.r = 0;
			z.i = 0;
			c.r = x / zoomx + scene->plan.x1;
			c.i = y / zoomy + scene->plan.y1;
			i = md_loop(&c, &z, i);
			while ((z.r * z.r) + (z.i * z.i) < 4 && i < scene->iteration)
			i = md_loop(&c, &z, i);
			if (i == scene->iteration)
				fill_pixel(scene->str, x, y, scene->bg_color);
			else
				fill_pixel(scene->str, x, y, i * 0x010203 );/// scene->iteration);
		}
	}
	return (1);
}

double	x_real(t_scene *scene, int x)
{
	double tmp;
	double tmp2;
	
	tmp2 = (double)x/(double)WIDTH;
	tmp = scene->plan.x2 - scene->plan.x1;
	return (tmp2 * (scene->plan.x2 - scene->plan.x1) + scene->plan.x1);
}

double	y_real(t_scene *scene, int y)
{
	double tmp;
	double tmp2;		

	tmp2 = (double)y/(double)HEIGHT;
	tmp = scene->plan.y2 - scene->plan.y1;
	return (tmp2 * (scene->plan.y2 - scene->plan.y1) + scene->plan.y1);
}
void	zoom_out(t_scene *scene, int x, int y)
{
		scene->zoom *= 2;
		scene->plan.x1 = x_real(scene, x) - scene->zoom;
		scene->plan.x2 = x_real(scene, x) + scene->zoom;
		scene->plan.y1 = y_real(scene, y) - scene->zoom;
		scene->plan.y2 = y_real(scene, y) + scene->zoom;
}
void	zoom_in(t_scene *scene, int x, int y)
{
		scene->zoom /= 2;
		scene->plan.x1 = x_real(scene, x) - scene->zoom;
		scene->plan.x2 = x_real(scene, x) + scene->zoom;
		scene->plan.y1 = y_real(scene, y) - scene->zoom;
		scene->plan.y2 = y_real(scene, y) + scene->zoom;
}

int	deal_mouse(int key, int x, int y, t_scene *scene)
{
	ft_putnbr(key);
	ft_putchar('\n');
	
	if (key == 5)
		zoom_out(scene, x, y);
	if (key == 3)
	{
		set_md(scene);
		scene->zoom = 1;
	}
	if (key == 1)
		scene->iteration += 10;
	if (key == 2 && scene->iteration > 1)
		scene->iteration -= 10;
	if (key == 4 && x > 0 && y > 0)
		zoom_in(scene, x, y);
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
	scene->zoom = 1;
	fill_img(scene, scene->bg_color);
	set_md(scene);
	md_set(scene);
	mlx_put_image_to_window(scene->mlx_ptr,
			scene->win_ptr, scene->img_ptr, 0, 0);
	mlx_key_hook(scene->win_ptr, deal_key, scene);
	mlx_mouse_hook(scene->win_ptr, deal_mouse, scene);
	mlx_loop_hook(scene->mlx_ptr, md_set, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
