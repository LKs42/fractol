/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:24:42 by lugibone          #+#    #+#             */
/*   Updated: 2019/12/04 16:34:36 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	md_loop(t_scene *scene, int i)
{
	double tmp;

	tmp = scene->z.r;
	scene->z.r = scene->z.r *scene->z.r - scene->z.i * scene->z.i + scene->c.r;
	scene->z.i = 2 * scene->z.i * tmp + scene->c.i;
	return (++i);
}

void	init_md(t_scene *scene, int *i, int x, int y)
{
	double zoomx;
	double zoomy;

	zoomx = WIDTH / (scene->plan.x2 - scene->plan.x1);
	zoomy = HEIGHT / (scene->plan.y2 - scene->plan.y1);
	*i = 0;
	scene->z.r = 0;
	scene->z.i = 0;
	scene->c.r = x / zoomx + scene->plan.x1;
	scene->c.i = y / zoomy + scene->plan.y1;
}

int	md_set(t_scene *scene)
{
	int i;
	int x;
	int y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			init_md(scene, &i, x, y);
			i = md_loop(scene, i);
			while ((scene->z.r * scene->z.r) + (scene->z.i * scene->z.i) < 4 && i < scene->iteration)
			i = md_loop(scene, i);
			if (i == scene->iteration)
				fill_pixel(scene->str, x, y, scene->bg_color);
			else
				fill_pixel(scene->str, x, y, i * 0x010203 );/// scene->iteration);
			y++;
		}
		x++;
	}
	return (1);
}

int	bs_loop(t_scene *scene, int i)
{
	double tmp;

	tmp = fabs(scene->z.r);
	scene->z.r = fabs(scene->z.r) * fabs(scene->z.r) - fabs(scene->z.i) * fabs(scene->z.i) + scene->c.r;
	scene->z.i = 2 * fabs(scene->z.i) * tmp + scene->c.i;
	return (++i);
}

int	bs_set(t_scene *scene)
{
	int i;
	int x;
	int y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			init_md(scene, &i, x, y);
			i = bs_loop(scene, i);
			while ((scene->z.r * scene->z.r) + (scene->z.i * scene->z.i) < 4 && i < scene->iteration)
			i = bs_loop(scene, i);
			if (i == scene->iteration)
				fill_pixel(scene->str, x, y, scene->bg_color);
			else
				fill_pixel(scene->str, x, y, i * 0x010203 );/// scene->iteration);
			y++;
		}
		x++;
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

void	init_julia(t_scene *scene, int *i, int x, int y)
{

	double zoomx;
	double zoomy;
	zoomx = WIDTH / (scene->plan.x2 - scene->plan.x1);
	zoomy = HEIGHT / (scene->plan.y2 - scene->plan.y1);
	*i = 0;
	scene->z.r = x / zoomx + scene->plan.x1;
	scene->z.i = y / zoomy + scene->plan.y1;
}

int	julia_loop(t_scene *scene, int i)
{
	double tmp;
	tmp = scene->z.r;
	scene->z.r = scene->z.r * scene->z.r - scene->z.i * scene->z.i + scene->c.r;
	scene->z.i = 2 * scene->z.i * tmp + scene->c.i;
	return(++i);
}

int	julia_set(t_scene *scene, int xx, int yy)
{
	int i;
	int x;
	int y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			init_julia(scene, &i, x, y);
			scene->c.r = x_real(scene, xx);
			scene->c.i = y_real(scene, yy);
			i = julia_loop(scene, i);
			while ((scene->z.r * scene->z.r) + (scene->z.i * scene->z.i) < 4 && i < scene->iteration)
			i = julia_loop(scene, i);
			if (i == scene->iteration)
				fill_pixel(scene->str, x, y, scene->bg_color);
			else
				fill_pixel(scene->str, x, y, i * 0x010203);// / scene->iteration);
			y++;
		}
		x++;
	}
	return (1);
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
	//md_set(scene);
	julia_set(scene, x, y);
	//bs_set(scene);
	mlx_put_image_to_window(scene->mlx_ptr,
			scene->win_ptr, scene->img_ptr, 0, 0);

	return (1);
}

int	julia_hook(int x, int y, t_scene *scene)
{
	julia_set(scene, x, y);
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
	//md_set(scene);
	//bs_set(scene);
	set_julia(scene);
	julia_set(scene, 0, 0);
	mlx_put_image_to_window(scene->mlx_ptr,
			scene->win_ptr, scene->img_ptr, 0, 0);
	mlx_key_hook(scene->win_ptr, deal_key, scene);
	mlx_mouse_hook(scene->win_ptr, deal_mouse, scene);
	mlx_hook(scene->win_ptr, 6, 1L << 6, julia_hook, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
