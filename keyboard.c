/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:21:29 by lugibone          #+#    #+#             */
/*   Updated: 2019/11/21 18:59:22 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_scale(int key, t_scene *scene)
{
	if (key == 0x7E)
		scene->scale += 0.5;
	if (key == 0x7D)
		scene->scale -= 0.5;
}

int		deal_key(int key, t_scene *scene)
{
	if (key == 53)
		exit(0);
	fill_img(scene, scene->bg_color);
	mlx_put_image_to_window(scene->mlx_ptr,
			scene->win_ptr, scene->img_ptr, 0, 0);
	return (0);
}
