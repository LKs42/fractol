/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:21:05 by lugibone          #+#    #+#             */
/*   Updated: 2019/11/21 18:58:48 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_scene(t_scene *scene)
{
	scene->bg_color = 0x181818;
	scene->scale = 10;
}

t_scene	*init_scene(int w, int h, char *str)
{
	t_scene *scene;

	scene = malloc(sizeof(t_scene));
	scene->point_a = malloc(sizeof(t_point*));
	scene->point_b = malloc(sizeof(t_point*));
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
