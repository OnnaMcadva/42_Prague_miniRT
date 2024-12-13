/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:23:56 by nchonka           #+#    #+#             */
/*   Updated: 2024/12/13 17:06:24 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
// # include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <time.h>
# include <stdint.h>
# include <stddef.h>

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "define.h"
# include "figure.h"

enum moving {
	forward,
	backward,
	left,
	right,
	up,
	down	
};

typedef struct s_event
{
	int		x;
	int		y;
	int		lastx;
	int		lasty;
	int		key[MAX_KEY];
	int		mouse;
	t_obj	*selection;
	t_bool	torender;
}	t_event;

typedef struct s_rt
{
	char			*path;
	float			width;
	float			height;
	float			aspectratio;
	float			cam_matrix[4][4];
	void			*mlx;
	void			*main_win;
	t_img			img;
	t_camera		camera;
	t_ambient		ambient;
	t_light			*light;
	t_obj			*objs;
	size_t			num_objs;
	t_event			event;
	t_color			bg_color;
	int				lnum;
	int				pnum;
	int				process;
	pthread_mutex_t	process_lock;
	char			*process_text;
	t_bool			is_processing;
}	t_rt;

typedef struct s_line_trd
{
	int			i;
	t_rt		*rt;
	pthread_t	trd;
}	t_line_trd;

/* exit_error.c */
void	goodbye(char *s);
int	print_err(char *msg);
int	print_parse_err(t_rt *rt, char **arr, char *msg);
int	exit_win(t_rt *rt);

/* free_func.c */
void	rt_free(t_rt *rt);
void	free_lights(t_light **lights);
void	free_objects(t_rt *rt, t_obj **objs);
void	free_array(char *arr[]);

/* lights_manag.c */
void	add_light_to_list(t_light *new_light, t_light **lights);
t_light	*create_light(t_rt *rt);
void	free_lights(t_light **lights);

/* object_manag.c */
t_vect	*get_coords(t_obj *o);
void	add_object_to_list(t_obj *obj, t_obj **objs);
t_obj	*create_object(t_rt *rt, t_obj_id id);

/* str_convert.c */
float	str_to_float(char *str);
int	str_to_int_color(char *str);

/* str_type_check.c  */
int	is_float(char *str);
int	is_ulong(char *str);

void title_window(t_rt *rt, const char *xpm_path);

/* cam_moving.c */
void	move_camera_forw_back(t_rt *rt,  enum moving dir);
void	move_camera(t_rt *rt, enum moving dir);
void    rotate_camera(t_rt *rt, enum moving dir);

/* hook_init.c */
void	cam_touch_key(int key, t_rt *rt);
void	light_touch_key(int key, t_rt *rt);
int		key_press(int key, t_rt *rt);
int		key_release(int key, t_rt *rt);

/* light_moving.c */
void	change_light_brightness(t_rt *rt, float change);
void	change_light_color(t_rt *rt, int r_change, int g_change, int b_change);
void	move_light(t_rt *rt, enum moving dir);

/* mouse_moving.c */
void	move_object(t_rt *rt, int x, int y);
int		mouse_press(int button, int x, int y, t_rt *rt);
int		mouse_release(int button, int x, int y, t_rt *rt);
int		mouse_moving(int x, int y, t_rt *rt);

/* geometry_norms.c */
void	triangle_norm(t_rt *rt, t_triangle *t);
void	cone_norm(t_cone *c);
void	cylinder_norm(t_cylinder *cy);
void	load_texture(t_rt *rt, t_obj *obj);
void	object_norm(t_rt *rt);

/* sec_order_line.c */
t_bool	find_quadr_roots(t_quadratic *q);

/* vector_arithm.c  */
t_vect	vec_coord(float x, float y, float z);
float	vec_len(t_vect v);
t_vect	vec_difference(t_vect a, t_vect b);
t_vect	vec_sum(t_vect a, t_vect b);
t_vect	vec_num_product(t_vect v, float f);

/* vector_re_re.c */
t_vect	reflect_vec(t_vect v, t_vect n);
t_vect	refract_vec(t_vect v, t_vect n, float eta);

/* vector_vector.c */
float	scal_product(t_vect v1, t_vect v2);
t_vect	vec_product(t_vect u, t_vect v);
float	distance(t_vect a, t_vect b);
t_vect	vec_oppos(t_vect v);
t_vect	*normalize(t_vect *v);

/* open_file.c */
int	is_invalid_file(t_rt *rt);
char	*sanitize_line(char *line);
int	read_file(t_rt *rt, int fd);
int	open_file(t_rt *rt, char *path);

/* pars_extra.c */
int	parse_extra_params(t_rt *rt, t_obj *obj, char **params, int i);

/* pars_general.c */
int	parse_camera(t_rt *rt, char *line, int i);
int	parse_ambient(t_rt *rt, char *line);
int	parse_light(t_rt *rt, char *line);
int	parse_resolution(t_rt *rt, char *line);

/* pars_object.c */
int	parse_plane(t_rt *rt, char **params, t_obj *obj);
int	parse_sphere(t_rt *rt, char **params, t_obj *obj);
int	parse_cylinder(t_rt *rt, char **params, t_obj *obj);
int	parse_cone(t_rt *rt, char **params, t_obj *obj);
int	parse_triangle(t_rt *rt, char **params, t_obj *obj);

/* parse_textures.c */
int	is_invalid_xpmfile(char *path);
int	parse_texture(char *param, t_obj *obj);
int	parse_specular(char *str, t_obj *obj);
int	parse_pattern(char *str, t_obj *obj);

/* parse_utils.c */
int	parse_vector(char *str, t_vect *vect);
int	parse_colors(char *str, t_color *color, t_color *color2);
int	parse_rgb(char *str, t_color *color);
int	parse_float(char *str, float *num);
int	parse_ulong(char *str, size_t *num);

/* primary_parse.c */
int	array_length(char *arr[]);
int parse_shape(t_rt *rt, char *line, t_obj_id id, int nb_params);
int parse_general_params(t_rt *rt, char *line);
int parse_object_params(t_rt *rt, char *line);
int parse_params(t_rt *rt, char *line);

/* anti_alias.c */
int	anti_aliasing(t_rt *rt, float x, float y);

/* color_effects.c */
float	clamp(float value, float min, float max);
t_color	add_light(t_color color, t_color light, float p2);
t_color	blend_colors(t_color c1, float p1, t_color c2, float p2);
int	average_colors(t_color c[9]);
t_color	color_obj(t_obj *obj, t_hit *hit);

/* color_utils.c */
t_color	newcolor(float r, float g, float b);
t_color	*apply_color_factor(t_color *c, float p);
t_color	scale_color(t_color c, float p);
t_color	rgb_to_color(int rgb);
int	color_to_rgb(t_color c);

/* complex_intersec.c */
t_bool	/*cone_hit*/cone_hit(t_ray *r, t_cone *co, t_hit *hit);
t_bool	/*cone_test*/cone_test(t_ray *r, t_cone *co, t_hit *hit);
int	intersect(t_ray *ray, t_obj *obj, t_hit *hit);

/* loading_bar.c */
void	draw_bar(t_rt *rt, int x, int y);
char	*format_progress(float percent);
void	update_text(t_rt *rt, float perc);
void reset_process(t_rt *rt);
void progress_update(t_rt *rt);

/* mlxwin_init.c */
void	rt_clear(t_rt *rt);
void	win_handle(t_rt *rt, char *path);

/* primit_intersec.c */
t_bool	sphere_inter(t_ray *ray, t_sphere *sp, t_hit *hit);
t_bool	plane_inter(t_ray *r, t_plane *pl, t_hit *hit);
t_bool	triangle_inter(t_ray *r, t_triangle *t, t_hit *hit);
t_bool	infinite_cyl_inter(t_ray *r, t_cylinder *cy, t_hit *hit);
t_bool	cylinder_inter(t_ray *r, t_cylinder *cy, t_hit *hit);

/* ray_intersec.c */
t_obj	*get_closest_obj(t_ray *ray, t_obj *obj, t_hit *hit);
t_color	light_to_rgb(t_obj *o, t_colors *colors);
void	handle_lights(t_rt *rt, t_rays *r, t_colors *colors);
t_color	raytrace(t_rt *rt, t_rays *r, int max_reflect);

/* ray_casting.c */
void	build_ray(t_ray *ray, t_vect *or, t_vect *dir);
void	cam_view_matrix(t_rt *rt);
t_vect	cam_to_world(float m[4][4], t_vect *v);
void	create_camera_ray(t_rt *rt, t_ray *ray, float x, float y);
t_vect	*calc_ray_point(t_vect *dst, t_ray *r, float t);

/* refle_refra.c */
t_color	specular_light(t_rays *r, t_light *light);
t_color	diffuse_light(t_rays *r, t_light *light);
t_bool	shadow_ray(t_rt *rt, t_rays *r, t_light *light);
t_color	refraction_ray(t_rt *rt, t_rays *r, int max_reflect);
t_color	reflection_ray(t_rt *rt, t_rays *r, int max_reflect);

/* render.c */
t_color	get_pixelcolor(t_img *img, float xf, float yf);
void	*render_line_chunk(void *line_trd);
void	render_parallel(t_rt *rt);
int	smart_rt(t_rt *rt, float x, float y);
void render(t_rt *rt);

/* textures.c */
void	set_patternref(t_rt *rt, t_obj *obj);
void	uv_sphere_map(t_obj *obj, t_vect p, float *uv);
void	uv_plane_map(t_obj *obj, t_vect p, float *uv);
void	uv_cylco_map(t_obj *obj, t_vect p, float *uv);
t_color	pattern_color(t_obj *obj, t_vect phit);

/* transition_matrix.c */
void cam_view_matrix(t_rt *rt);
void create_camera_axes(t_rt *rt, t_vect *forward, t_vect *right, t_vect *up);

/* minirt.c */
void	hook_init(t_rt *rt);
int		scene_name(const char *s);
int		main(int argc, char **argv);

# endif