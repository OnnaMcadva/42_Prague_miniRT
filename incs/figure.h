/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 22:13:35 by annavm            #+#    #+#             */
/*   Updated: 2024/12/16 21:47:22 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURE_H
# define FIGURE_H

typedef enum e_bool
{
	FALSE,	
	TRUE
}	t_bool;

typedef enum e_object_id
{
	id_unset,
	id_ambient,
	id_light,
	id_camera,
	id_plane,
	id_cylinder,
	id_cone,
	id_sphere,
	id_triangle,
}	t_obj_id;

typedef struct s_vect
{
	float	x;
	float	y;
	float	z;
}	t_vect;

typedef struct s_quadratic
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	t1;
	float	t2;
}	t_quadratic;

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

typedef struct s_ray
{
	t_vect	or;
	t_vect	dir;
}	t_ray;

typedef struct s_hit
{
	t_vect	nhit;
	t_vect	phit;
	float	t;
	t_color	color;
}	t_hit;

typedef struct s_colors
{
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	t_color	reflect;
	t_color	refract;
	int		is_shadow;
}	t_colors;

typedef struct s_ambient
{
	t_obj_id	id;
	float		lighting;
	t_color		color;

}	t_ambient;

typedef struct s_light
{
	t_obj_id		id;
	t_vect			coords;
	float			brightness;
	t_color			color;
	struct s_light	*next;
}	t_light;

typedef struct s_camera
{
	t_obj_id	id;
	t_vect		coords;
	t_vect		orient;
	size_t		fov;
	float		scale;
}	t_camera;

typedef struct s_plane
{
	t_obj_id	id;
	t_vect		coords;
	t_vect		orient;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_obj_id	id;
	t_vect		coords;
	t_vect		orient;
	float		diameter;
	float		height;
	float		r2;
	t_vect		p1;
	t_vect		p2;
	t_vect		delta_p;
	t_color		color;
}	t_cylinder;

typedef struct s_sphere
{
	t_obj_id	id;
	t_vect		coords;
	float		diameter;
	float		r2;
	t_color		color;
}	t_sphere;

typedef struct s_triangle
{
	t_obj_id	id;
	t_vect		c[3];
	t_vect		edge[3];
	t_vect		n;
	t_color		color;
	float		area2;
}	t_triangle;

typedef struct s_cone
{
	t_obj_id	id;
	t_vect		coords;
	t_vect		orient;
	float		h;
	float		h2;
	float		angle;
	float		cos2;
	t_vect		c1;
	t_vect		c2;
	float		r1;
	float		r2;
	t_color		color;
}	t_cone;

typedef union u_object
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
	t_cone		cone;
	t_triangle	triangle;
}	t_obj_union;

typedef struct s_img
{
	void	*img;
	char	*addr;
	char	*path;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		addr_incr;
	int		antialiasing_on;
}	t_img;

typedef struct s_obj
{
	t_obj_id		id;
	t_obj_union		object;
	float			speckv;
	float			specn;
	float			mirror;
	float			refract;
	t_vect			ex;
	t_vect			ey;
	t_vect			ez;
	t_vect			coords;
	t_color			color;
	t_color			color2;
	float			h;
	float			pattern_len;
	int				pattern_num;
	float			alpha;
	float			texture_f;
	t_bool			has_texture;
	t_img			texture;
	struct s_obj	*next;
}	t_obj;

typedef struct s_rays
{
	t_ray		prime_ray;
	t_ray		shadowray;
	t_hit		hit;
	t_hit		shadow_hit;
	t_obj		*closest_obj;
}	t_rays;

#endif