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

int		deal_key(int key, t_scene *scene)
{
    ft_putnbr(key);
    ft_putchar('\n');
	if (key == 53)
		file_error(scene, 0);
	if (key == 65307)
		file_error(scene, 0);
    if (key == 65361)
	    scene->player.x -= 1;
	if (key == 65363)
	    scene->player.x += 1;
	if (key == 65362)
	    scene->player.y -= 1;
	if (key == 65364)
	    scene->player.y += 1;
    draw(scene);
    return (0);
}
