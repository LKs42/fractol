/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:55:45 by lugibone          #+#    #+#             */
/*   Updated: 2020/01/08 20:41:41 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	x_real(t_scene *scene, int x)
{
	double tmp;
	double tmp2;

	tmp2 = (double)x / (double)WIDTH;
	tmp = scene->plan.x2 - scene->plan.x1;
	return (tmp2 * (scene->plan.x2 - scene->plan.x1) + scene->plan.x1);
}

double	y_real(t_scene *scene, int y)
{
	double tmp;
	double tmp2;

	tmp2 = (double)y / (double)HEIGHT;
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

void	reset(t_scene *scene)
{
	if (scene->fractal_id == 1 || scene->fractal_id == 3)
		set_md(scene);
	if (scene->fractal_id == 2)
		set_julia(scene);
	scene->zoom = 1;
}
