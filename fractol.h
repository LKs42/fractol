/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lugibone <lugibone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:39:33 by lugibone          #+#    #+#             */
/*   Updated: 2020/01/06 16:37:59 by lugibone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft.h"
# include "mlx.h"
# define WIDTH 500
# define HEIGHT 500

int		md_set(t_scene *scene);
void	init_md(t_scene *scene, int *i, int x, int y);
int		md_loop(t_scene *scene, int i);
int		bs_set(t_scene *scene);
int		bs_loop(t_scene *scene, int i);
void	zoom_in(t_scene *scene, int x, int y);
void	zoom_out(t_scene *scene, int x, int y);
double	y_real(t_scene *scene, int y);
double	x_real(t_scene *scene, int x);
int		julia_hook(int x, int y, t_scene *scene);
int		julia_set(t_scene *scene, int xx, int yy);
void	init_julia(t_scene *scene, int *i, int x, int y);
int		julia_loop(t_scene *scene, int i);
void	reset(t_scene *scene);
void	display(t_scene *scene, int x, int y);
int		md_set(t_scene *scene);
void	set_julia(t_scene *scene);
void	set_md(t_scene *scene);
t_scene	*init_scene(int w, int h, char *str);
t_point	**fileread(int fd, t_scene *scene);
t_point	*ft_rot_x(t_point *point, t_scene *scene, t_point *new_point);
t_point	*ft_rot_y(t_point *point, t_scene *scene, t_point *new_point);
t_point	*ft_rot_z(t_point *point, t_scene *scene, t_point *new_point);
t_point	*ft_rot_matrix(t_point *point, t_scene *scene, t_point *new_point);
int		rgb_r(int color);
int		rgb_g(int color);
int		rgb_b(int color);
int		deal_key(int key, t_scene *scene);
int		check_extension(char *str, char *extension);
int		check_line(char *str, t_scene *scene);
void	state_hud(t_scene *scene);
void	draw_hud(t_scene *scene);
void	draw_scene(t_scene *scene);
void	loop(char **curr_line, t_point **map, int y, t_scene *scene);
void	fill_pixel(int *my_image_string, int x, int y, int color);
void	ft_scale(t_point *point, float scale);
void	liner(int *img, t_point *a, t_point *b);
void	fill_img(t_scene *param, int color);
void	map_iter(t_scene *scene, void(*f)(t_point *, float), float a);
void	state_hud(t_scene *scene);
void	draw_hud(t_scene *scene);
void	draw_scene(t_scene *scene);
void	show_map(t_scene *scene);
void	set_scene(t_scene *scene);
void	incrementy(t_point *point, float a);
void	incrementx(t_point *point, float a);
void	incrementz(t_point *point, float a);
void	change_color(t_point *point, int color);
void	key_translate(int key, t_scene *scene);
void	key_rotate(int key, t_scene *scene);
void	key_scale(int key, t_scene *scene);
void	key_event(int key, t_scene *scene);
void	file_error(t_scene *scene, int b);
void	free2d_array(char **str);
void	usage(void);

#endif
