/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:21:29 by lugibone          #+#    #+#             */
/*   Updated: 2019/12/04 17:40:46 by lugibone         ###   ########.fr       */
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
		file_error(scene, 0);
	if (key == 122)
		scene->fractal_id = 1;
	if (key == 120)
		scene->fractal_id = 2;
	if (key == 99)
		scene->fractal_id = 3;
	if (key == 99 || key == 120 || key == 122)
		reset(scene);
	display(scene, 0, 0);
	mlx_put_image_to_window(scene->mlx_ptr,
			scene->win_ptr, scene->img_ptr, 0, 0);
	return (0);
}
