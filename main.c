/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:24:42 by lugibone          #+#    #+#             */
/*   Updated: 2020/01/08 20:32:56 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			display(t_scene *scene, int x, int y)
{
	if (scene->fractal_id == 1)
		md_set(scene);
	if (scene->fractal_id == 2)
		julia_set(scene, x, y);
	if (scene->fractal_id == 3)
		bs_set(scene);
}

static int		deal_mouse(int key, int x, int y, t_scene *scene)
{
	if (key == 5)
		zoom_out(scene, x, y);
	if (key == 3)
		reset(scene);
	if (key == 1)
		scene->iteration += 10;
	if (key == 2 && scene->iteration > 1)
		scene->iteration -= 10;
	if (key == 4 && x > 0 && y > 0)
		zoom_in(scene, x, y);
	display(scene, x, y);
	mlx_put_image_to_window(scene->mlx_ptr,
			scene->win_ptr, scene->img_ptr, 0, 0);
	return (1);
}

static	int		correct_value(int ac, char **av)
{
	if (ac != 2)
		return (0);
	else
	{
		if (av[1][0] == '1' && av[1][1] == '\0')
			return (1);
		else if (av[1][0] == '2' && av[1][1] == '\0')
			return (2);
		else if (av[1][0] == '3' && av[1][1] == '\0')
			return (3);
		else
			return (0);
	}
	return (0);
}

static int		argument(t_scene *scene, int argc, char **argv)
{
	if (argc != 2)
		file_error(scene, 1);
	else
	{
		if (correct_value(argc, argv) == 1)
		{
			set_md(scene);
			md_set(scene);
			scene->fractal_id = 1;
		}
		if (correct_value(argc, argv) == 2)
		{
			set_julia(scene);
			julia_set(scene, 0, 0);
			scene->fractal_id = 2;
		}
		if (correct_value(argc, argv) == 3)
		{
			set_md(scene);
			bs_set(scene);
			scene->fractal_id = 3;
		}
	}
	return (1);
}

int				main(int argc, char **argv)
{
	t_scene *scene;

	scene = NULL;
	if (correct_value(argc, argv) > 0)
	{
		scene = init_scene(WIDTH, HEIGHT, "hell world");
		scene->zoom = 1;
		fill_img(scene, scene->bg_color);
		argument(scene, argc, argv);
	}
	if (scene == NULL)
	{
		usage();
		return (0);
	}
	mlx_put_image_to_window(scene->mlx_ptr,
			scene->win_ptr, scene->img_ptr, 0, 0);
	mlx_key_hook(scene->win_ptr, deal_key, scene);
	mlx_mouse_hook(scene->win_ptr, deal_mouse, scene);
	mlx_hook(scene->win_ptr, 6, 1L << 6, julia_hook, scene);
	mlx_loop(scene->mlx_ptr);
	return (0);
}
