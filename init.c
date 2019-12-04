/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:21:05 by lugibone          #+#    #+#             */
/*   Updated: 2019/12/04 17:38:47 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_scene(t_scene *scene)
{
	scene->bg_color = 0x181818;
	scene->bg_color = 0x000000;
	scene->iteration = 50;
	scene->scale = 1;
	scene->zoom = 1;
	scene->fractal_id = 0;
}

void	set_md(t_scene *scene)
{
	scene->plan.x1 = -2.1;
	scene->plan.x2 = 0.6;
	scene->plan.y1 = -1.2;
	scene->plan.y2 = 1.2;
}
void	set_julia(t_scene *scene)
{
	scene->plan.x1 = -1;
	scene->plan.x2 = 1;
	scene->plan.y1 = -1.2;
	scene->plan.y2 = 1.2;
}

void	usage(void)
{
	ft_putendl("usage: ./fractol [1-3]");
}

void	file_error(t_scene *scene, int b)
{
	mlx_destroy_image(scene->mlx_ptr, scene->img_ptr);
	mlx_destroy_window(scene->mlx_ptr, scene->win_ptr);
	if (scene)
		free(scene);
	b ? usage() : 0;
	exit(0);
}
t_scene	*init_scene(int w, int h, char *str)
{
	t_scene *scene;
	t_plan *plan;
	t_complex *z;
	t_complex *c;

	plan = malloc(sizeof(t_plan));
	c = malloc(sizeof(t_complex));
	z = malloc(sizeof(t_complex));
	scene = malloc(sizeof(t_scene));
	scene->plan = *plan;
	scene->z = *z;
	scene->c = *c;
	set_scene(scene);
	scene->win_height = h;
	scene->win_width = w;
	scene->mlx_ptr = mlx_init();
	scene->title = str;
	scene->win_ptr = mlx_new_window(scene->mlx_ptr, w, h, str);
	scene->img_ptr = mlx_new_image(scene->mlx_ptr,
scene->win_width, scene->win_height);
	scene->str = (int*)mlx_get_data_addr(scene->img_ptr,
&scene->bpp, &scene->sl, &scene->endian);
	return (scene);
}
