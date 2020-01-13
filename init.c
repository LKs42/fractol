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
        


void    fill_map(t_scene *scene)
{
    for(int a = 0; a < scene->win_height * scene->win_width; a++)
        scene->map[a] = 0;
    for(int i = 0; i < scene->win_height; i++)
    {
         
        for(int j = 0; j < scene->win_width; j++)
        {
            if (i == scene->win_height / 4 && j == scene->win_width / 4)
                for (int k = 0; k <= scene->win_width / 2; k++)
                    scene->map[j + scene->win_width *i + k] = 1;
        
            if (i == scene->win_height / 4 && j == scene->win_width / 4)
                for (int k = 0; k <= scene->win_width / 2; k++)
                    scene->map[j + scene->win_width *i + k * scene->win_width] = 1;
        
            if (i == scene->win_height / 4 * 3 && j == scene->win_width / 4)
                for (int k = 0; k <= scene->win_width / 2; k++)
                    scene->map[j + scene->win_width *i + k] = 1;
         
            if (i == scene->win_height / 4 && j == scene->win_width / 4 * 3)
                for (int k = 0; k <= scene->win_width / 2; k++)
                    scene->map[j + scene->win_width *i + k * scene->win_width] = 1;
        }
        /*
        for(int j = 0; j < scene->win_width; j++)
        {
            if (i == 0 && j == 0)
                for (int k = 0; k <= scene->win_width ; k++)
                    scene->map[j + scene->win_width *i + k] = 1;
        
            if (i == 0 && j == 0)
                for (int k = 0; k <= scene->win_width ; k++)
                    scene->map[j + scene->win_width *i + k * scene->win_width] = 1;
        
            if (i == scene->win_height && j == scene->win_width )
                for (int k = 0; k <= scene->win_width ; k++)
                    scene->map[j + scene->win_width *i + k] = 1;
         
            if (i == scene->win_height && j == scene->win_width )
                for (int k = 0; k <= scene->win_width ; k++)
                    scene->map[j + scene->win_width *i + k * scene->win_width] = 1;
        }*/ 
    }
}

t_scene	*init_scene(int w, int h, char *str)
{
    t_scene *scene;

    scene = malloc(sizeof(t_scene));
    scene->map = malloc(sizeof(char) * h * w );
    scene->mousex = 0;
    scene->mousey = 0;
    scene->win_height = h;
    scene->win_width = w;
    fill_map(scene);
    scene->player.x = w/2;
    scene->player.y = h/2;
    scene->player.color = 0xFFFFFF;
    scene->bg_color = 0x181818;
    scene->mlx_ptr = mlx_init();
    scene->title = str;
    scene->win_ptr = mlx_new_window(scene->mlx_ptr, w, h, str);
    scene->img_ptr = mlx_new_image(scene->mlx_ptr,
            scene->win_width, scene->win_height);
    scene->str = (int*)mlx_get_data_addr(scene->img_ptr,
            &scene->bpp, &scene->sl, &scene->endian);
    return (scene);
}
