<<<<<<< HEAD
#include "SDL.h"
#include <stdio.h>
#include "libft.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "bitmap/bitmap.h"
#include "error/error.h"
#define RATIO 16 / 9
#define HEIGHT 180
#define WIDTH (HEIGHT * RATIO) 
#define MAX(a,b) (a>=b?a:b)
#define MIN(a,b) (a<=b?a:b)
#define DegToRad(agdeg) (agdeg * M_PI / 180.0)

#include <inttypes.h>
#include <stdint.h>

typedef struct		s_point
{
    int			x;
    int			y;
}					t_point;

typedef struct		s_rect
{
    int			x;
    int			y;
    int			h;
    int			w;
}					t_rect;

typedef struct		s_poly
{
    int			x1;
    int			y1;
    int			x2;
    int			y2;
    int			x3;
    int			y3;
    int			x4;
    int			y4;
}					t_poly;

uint32_t	pp_get_SDLcolor(SDL_Color color)
{
    uint32_t c;
    c = 0xFFFFFFFF;
    c = c | color.a;
    c = c << 8;
    c = c | color.r;
    c = c << 8;
    c = c | color.g;
    c = c << 8;
    c = c | color.b;
    return (c);
}

int pp_putpixel(uint32_t *pixel, int x, int y, uint32_t color)
{
    pixel[y * WIDTH + x] = color; 
    return (0);
}

int pp_putpixel_SDL(uint32_t *pixel, int x, int y, SDL_Color color)
{
    uint32_t c;
    c = 0xFFFFFFFF;
    c = c | color.a;
    c = c << 8;
    c = c | color.r;
    c = c << 8;
    c = c | color.g;
    c = c << 8;
    c = c | color.b;
    pixel[y * WIDTH + x] = c; 
    return (0);
}

int pp_putpixel_renderer(SDL_Renderer *renderer, int x, int y, SDL_Color color)
{
    SDL_Color tmp;

    SDL_GetRenderDrawColor(renderer, &tmp.r, &tmp.g, &tmp.g, &tmp.a);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderer, x, y);
    SDL_SetRenderDrawColor(renderer, tmp.r, tmp.g, tmp.b, tmp.a);
    return (0);
}

void	brush_square(uint32_t *pixels, int x, int y, int size, SDL_Color color)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            pp_putpixel_SDL(pixels, x + j, y + i, color);
}

void	pp_liner(uint32_t *pixel, t_point *a, t_point *b, uint32_t color)
{
    int tab[10];

    tab[0] = a->x;
    tab[1] = b->x;
    tab[2] = a->y;
    tab[3] = b->y;
    tab[4] = abs(tab[1] - tab[0]);
    tab[5] = tab[0] < tab[1] ? 1 : -1;
    tab[6] = abs(tab[3] - tab[2]);
    tab[7] = tab[2] < tab[3] ? 1 : -1;
    tab[8] = (tab[4] > tab[6] ? tab[4] : -tab[6]) / 2;
    while (!(tab[0] == tab[1] && tab[2] == tab[3]))
    {
        pp_putpixel(pixel, tab[0], tab[2], color);
        tab[9] = tab[8];
        tab[8] -= (tab[9] > -tab[4]) ? tab[6] : 0;
        tab[0] += (tab[9] > -tab[4]) ? tab[5] : 0;
        tab[8] += (tab[9] < tab[6]) ? tab[4] : 0;
        tab[2] += (tab[9] < tab[6]) ? tab[7] : 0;
    }
}

void	pp_liner_SDL(uint32_t *pixel, t_point *a, t_point *b, SDL_Color color)
{
    int tab[10];

    tab[0] = a->x;
    tab[1] = b->x;
    tab[2] = a->y;
    tab[3] = b->y;
    tab[4] = abs(tab[1] - tab[0]);
    tab[5] = tab[0] < tab[1] ? 1 : -1;
    tab[6] = abs(tab[3] - tab[2]);
    tab[7] = tab[2] < tab[3] ? 1 : -1;
    tab[8] = (tab[4] > tab[6] ? tab[4] : -tab[6]) / 2;
    while (!(tab[0] == tab[1] && tab[2] == tab[3]))
    {
        pp_putpixel_SDL(pixel, tab[0], tab[2], color);
        tab[9] = tab[8];
        tab[8] -= (tab[9] > -tab[4]) ? tab[6] : 0;
        tab[0] += (tab[9] > -tab[4]) ? tab[5] : 0;
        tab[8] += (tab[9] < tab[6]) ? tab[4] : 0;
        tab[2] += (tab[9] < tab[6]) ? tab[7] : 0;
    }
}

void	pp_liner_renderer(SDL_Renderer *renderer, t_point *a, t_point *b, SDL_Color color)
{
    int tab[10];

    tab[0] = a->x;
    tab[1] = b->x;
    tab[2] = a->y;
    tab[3] = b->y;
    tab[4] = abs(tab[1] - tab[0]);
    tab[5] = tab[0] < tab[1] ? 1 : -1;
    tab[6] = abs(tab[3] - tab[2]);
    tab[7] = tab[2] < tab[3] ? 1 : -1;
    tab[8] = (tab[4] > tab[6] ? tab[4] : -tab[6]) / 2;
    while (!(tab[0] == tab[1] && tab[2] == tab[3]))
    {
        pp_putpixel_renderer(renderer, tab[0], tab[2], color);
        tab[9] = tab[8];
        tab[8] -= (tab[9] > -tab[4]) ? tab[6] : 0;
        tab[0] += (tab[9] > -tab[4]) ? tab[5] : 0;
        tab[8] += (tab[9] < tab[6]) ? tab[4] : 0;
        tab[2] += (tab[9] < tab[6]) ? tab[7] : 0;
    }
}

int pp_rect(SDL_Renderer *renderer, t_rect rect, SDL_Color color)
=======
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
>>>>>>> f72a84903d5213055472c4df561d038ee8a3863e
{
    int i;
    int j;

    i = 0;
    while (i < rect.h)
    {
        j = 0;
        while (j < rect.w)
        {
            pp_putpixel_renderer(renderer, rect.x + j, rect.y + i, color);
            j++;
        }
        i++;
    }
    return (0);
}

<<<<<<< HEAD
int pp_drawsquare(SDL_Renderer *renderer, int x, int y, int size, SDL_Color color)
{
    int i;
    int j;

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            pp_putpixel_renderer(renderer, x + j, y + i, color);
            j++;
        }
        i++;
    }
    return (0);
}

void	pp_bucket_tool(uint32_t *pixels, int x, int y, uint32_t color)
=======
static int		deal_mouse(int key, int x, int y, t_scene *scene)
>>>>>>> f72a84903d5213055472c4df561d038ee8a3863e
{
    pixels[y * WIDTH + x] = color;
    if (pixels[y * WIDTH + x + 1] <= WIDTH)
        if (pixels[y * WIDTH + x + 1] != color)
            pp_bucket_tool(pixels, x + 1, y, color);
    if (pixels[y * WIDTH + x - 1] >= 0)
        if (pixels[y * WIDTH + x - 1] != color)
            pp_bucket_tool(pixels, x - 1, y, color);
    if (pixels[(y + 1) * WIDTH + x] <= HEIGHT)
        if (pixels[(y + 1) * WIDTH + x] != color)
            pp_bucket_tool(pixels, x, y + 1, color);
    if (pixels[(y - 1) * WIDTH + x] >= 0)
        if (pixels[(y - 1) * WIDTH + x] != color)
            pp_bucket_tool(pixels, x, y - 1, color);
}

<<<<<<< HEAD
void    draw_column(uint32_t *pixels, int i, uint32_t height, uint32_t color)
{
    t_point a;
    t_point b;

    b.x = i;
    b.y = HEIGHT;
    a.x = i;
    a.y = b.y - height;
    pp_liner(pixels, &a, &b, color);
}

/*
 *
 * tracer un rayon a une distance d
 * et un angle phi
 *
 * point.x = cos(phi) * d
 * point.y = sin(phi) * d
 *
 * bresenham player, point
 *
 *
 */


int     display(uint32_t *pixels, uint32_t *heightmap, int renderdistance, float viewangle, t_point player)
{
    memset(pixels, 0xFF00FFFF, WIDTH * HEIGHT * sizeof(uint32_t));
    float fov;
    float dx;
    fov = 90;
    dx = fov / WIDTH * M_PI / 180;
    float tmp = dx;
    int j = 0;
    uint32_t height, tmp2, tmp3;
    height = 0;
    int rd = renderdistance;
    int k = 0;
    while (rd >= 0)
    {
        for(int i = 0; i < WIDTH; i++)
        {
        //    x = player.x;
      //      y = player.y;
    //        x += cos(viewangle)
          //  la hauteur de la column est la valeur de la heightmap au point p de distance d et d angle phi
            height = heightmap[(int)((((sin(viewangle + DegToRad(dx)) * renderdistance) + player.y) * WIDTH) + (cos(viewangle + DegToRad(dx)) * renderdistance) + player.x)];
            
            tmp3 = height;
            
            tmp2 = height << 8;
            tmp2 = tmp2 >> 24;
            draw_column(pixels, i, tmp2/5, 0xFF000000 | tmp2 << 8);
            dx += tmp;
        }
        rd--;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage: ./exec texture.png\n");
        return (0);
    }
    SDL_Event e;
    int quit = 0;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;
    SDL_Color orange = {18, 18, 18, 255};
    SDL_Color green = {0, 255, 0, 255};
    SDL_Color red = {255, 0, 0, 255};
    SDL_Texture *texture;


    if(0 != SDL_Init(SDL_INIT_VIDEO))
        goto Quit;
    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(NULL == window)
        goto Quit;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(NULL == renderer)
        goto Quit;
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);

    SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a);
    SDL_RenderClear(renderer);

    uint32_t *screen;
    uint32_t *raycast;
    uint32_t *heightmap;
    t_bitmap_texture *img;
    img = load_bmp(argv[1]);
    heightmap = img->pixels;
    screen = malloc(sizeof(uint32_t) * HEIGHT * WIDTH );
    raycast = malloc(sizeof(uint32_t) * HEIGHT * WIDTH );
    //memset(screen, 255, WIDTH * HEIGHT * (sizeof(uint32_t)));

    t_point player;
    player.x = WIDTH/2;
    player.y = HEIGHT/2;

    t_point a;
    t_point b;
    a.x = 20;
    a.y = 30;
    b.y = HEIGHT - 40;
    b.x = WIDTH - 50;

    t_rect rect;
    rect.x = 200;
    rect.y = 200;
    rect.h = 50;
    rect.w = 100;

    pp_rect(renderer, rect, green);
    pp_liner_renderer(renderer, &a, &b, green);
    pp_drawsquare(renderer, 50, 50, 75, red);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    //SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);


    memset(screen, 0x00000000, WIDTH * HEIGHT * sizeof(uint32_t));
    memset(raycast, 0x00000000, WIDTH * HEIGHT * sizeof(uint32_t));
    pp_liner_SDL(screen, &a, &b, green);
    int draw = 0;
    //texture2 = image
    //texture = ecran 
//draw(uint32_t *pixels, uint32_t *heightmap, int renderdistance, float viewangle, t_point *player)
    int ag = 45;
    while(!quit)
    {
        SDL_UpdateTexture(texture, NULL, raycast, WIDTH * sizeof(uint32_t));
      //SDL_UpdateTexture(texture, NULL, heightmap, WIDTH * sizeof(uint32_t));
      //SDL_UpdateTexture(texture, NULL, screen, WIDTH * sizeof(uint32_t));
        a.x = e.button.x;
        a.y = e.button.y;
        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) {quit = 1;}
            if (e.type == SDL_KEYDOWN){
                if (e.key.keysym.sym == SDLK_SPACE)
                    memset(raycast, 0x00000000, WIDTH * HEIGHT * sizeof(uint32_t));
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    quit = 1;
                if (e.key.keysym.sym == SDLK_UP)
                player.y--;
                if (e.key.keysym.sym == SDLK_DOWN)
                player.y++;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
                if (e.button.button == SDL_BUTTON_LEFT)
                    ag++;
                if (e.button.button == SDL_BUTTON_RIGHT)
                    ag--;
            if (e.type == SDL_MOUSEBUTTONUP)
                if (e.button.button == SDL_BUTTON_LEFT)
                    draw = 0;
            display(raycast, heightmap, 60, DegToRad(ag), player);
        }
        b.x = e.button.x;
        b.y = e.button.y;
        if (draw)
            brush_square(screen, e.button.x, e.button.y, 10, green);
        if (draw)
            pp_liner_SDL(screen, &a, &b, green);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    statut = EXIT_SUCCESS;

Quit:
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != texture)
        SDL_DestroyTexture(texture);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
=======
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
>>>>>>> f72a84903d5213055472c4df561d038ee8a3863e
}
