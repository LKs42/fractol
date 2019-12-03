/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:24:42 by lugibone          #+#    #+#             */
/*   Updated: 2019/12/03 13:22:28 by lugibone         ###   ########.fr       */
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
#define plan_x1 -2.1
#define plan_x2 0.6
#define plan_y1 -1.2
#define plan_y2 1.2
//#define zoomx (WIDTH/ (x2 - x1))
//#define zoomy (HEIGHT / (y2 - y1))

int	md_set(t_scene *scene, t_plan *plan)
{
	t_complex c;
	t_complex z;
	double	tmp;
	int i;

	double zoomx;
	double zoomy;

	double scale = scene->scale;

	zoomx = WIDTH / (plan->x2/scale - plan->x1/scale);
	zoomy = HEIGHT / (plan->y2/scale - plan->y1/scale);

	for(int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			i = 0;
			c.r = x / zoomx + plan->x1;
			c.i = y / zoomy + plan->y1;
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
				fill_pixel(scene->str, x, y, i * 0x0000FF / scene->iteration);
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
	double tmp;
	double tmp2;
	double xtmp;
	double ytmp;
	(void) ytmp;
	(void) xtmp;
	(void) tmp;
	(void) tmp2;
	float ok;
	
	ok = 0.01;
	if (key == 5)
		scene->scale = 1;
	if (key == 3)
	{
		scene->plan.x1 = plan_x1;
		scene->plan.x2 = plan_x2;
		scene->plan.y1 = plan_y1;
		scene->plan.y2 = plan_y2;
	}
	if (key == 4)
		scene->iteration += 10;
	if (key == 2 && scene->iteration > 1)
		scene->iteration -= 10;
	if (key == 1 && x > 0 && y > 0)
	{
	/*
		tmp2 = (double)x/(double)WIDTH;
		tmp = scene->plan.x2 - scene->plan.x1;
		scene->plan.x1 = tmp2 * (scene->plan.x2 - scene->plan.x1) + scene->plan.x1 - tmp/2;
		scene->plan.x2 = scene->plan.x1 + tmp;
		tmp2 = (double)y/(double)HEIGHT;
		tmp = scene->plan.y2 - scene->plan.y1;
		scene->plan.y1 = tmp2 * (scene->plan.y2 - scene->plan.y1) + scene->plan.y1 - tmp/2;
		scene->plan.y2 = scene->plan.y1 + tmp;
		scene->scale *= 1.2;
	*/		
		tmp2 = (double)x/(double)WIDTH;
		tmp = scene->plan.x2 - scene->plan.x1;
		xtmp = tmp2 * (scene->plan.x2 - scene->plan.x1) + scene->plan.x1;
		tmp2 = (double)y/(double)HEIGHT;
		tmp = scene->plan.y2 - scene->plan.y1;
		ytmp = tmp2 * (scene->plan.y2 - scene->plan.y1) + scene->plan.y1;
	
		scene->plan.x1 = xtmp - ok;
		scene->plan.x2 = xtmp + ok;
		scene->plan.y1 = ytmp - ok;
		scene->plan.y2 = ytmp + ok;
		
		printf("x:%f y:%f\n", xtmp, ytmp);
	}
	md_set(scene, &scene->plan);
	mlx_put_image_to_window(scene->mlx_ptr,
			scene->win_ptr, scene->img_ptr, 0, 0);

	return (1);
}

int	main()
{
	t_plan *plan;
	plan = malloc(sizeof(t_plan));
	plan->x1 = plan_x1;
	plan->x2 = plan_x2;
	plan->y1 = plan_y1;
	plan->y2 = plan_y2;
	t_scene *scene;
	scene = NULL;
	scene = init_scene(WIDTH, HEIGHT, "hell world");
	scene->plan = *plan;
	fill_img(scene, scene->bg_color);
	md_set(scene, plan);
	mlx_put_image_to_window(scene->mlx_ptr,
			scene->win_ptr, scene->img_ptr, 0, 0);
	mlx_key_hook(scene->win_ptr, deal_key, scene);
	mlx_mouse_hook(scene->win_ptr, deal_mouse, scene);
	mlx_loop_hook(scene->mlx_ptr, md_set, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
