/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 12:56:19 by nchonka           #+#    #+#             */
/*   Updated: 2024/12/16 23:12:46 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define M_PI 3.14159265358979323846
# define MAX_KEY 65535
# define MAX_REFLECT 5
# define COLORDEF 0x81A1C1
# define BG_COLOR 0xCFCFFF
# define WHITE 0x00FFFFFF
# define BLACK 0x0000000
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

# define NB_PARAMS_PLANE 4
# define NB_PARAMS_SPHERE 4
# define NB_PARAMS_CYLINDER 6
# define NB_PARAMS_CONE 7
# define NB_PARAMS_TRIANGLE 5

# define PROGBAR_W 300
# define PROGBAR_H 3
# define MAX_THREADS 10
# define FOCAL_DIST 0.5
# define TEXTURE 1
# define EPSILON 0.0001
# define ANTIALIAS_ON FALSE
# define EPSILON 0.0001
# define SPECULAR_KV 0.5
# define SPECULAR_N 20
# define MIRROR 0.0
# define REFRACT 0.0
# define PATTERN_LEN 0.0
# define PATTERN_NUM 0

# define MOVE_SPEED 0.5f
# define ROTATE_SPEED 0.05f
# define ROTATE_ANGLE 5.0
# define LEFT_CLICK 1
# define RIGHT_CLICK 2

# define INVALID_NB_PARAMS "Invalid number of params"
# define INVALID_NB_COORDS "Invalid number of coordinates values"
# define INVALID_NB_ORIENT "Invalid number of orientation values"
# define INVALID_NB_COLORS "Invalid number of color values"

# define INVALID_SPEC_PARAMS "Invalid specular params"
# define NOT_A_FLOAT "Value is not a float"
# define INVALID_PATTERN_PARAMS "Invalid pattern params"
# define INVALID_TEXTURE_PARAMS "Invalid texture params"

# define TOO_MANY_LIGTHS "Too many light params"
# define TOO_MANY_CAMERAS "Too many camera params"
# define TOO_MANY_AMBIENTS "Too many ambient params"

# define MISSING_LIGHT_PARAMS "Missing light params"
# define MISSING_CAMERA_PARAMS "Missing camera params"
# define MISSING_AMBIENT_PARAMS "Missing ambient params"

# define NOT_A_ULONG "Value is not a unsigned long"
# define NOT_A_FLOAT "Value is not a float"

# define INVALID_FOV "\nERR_INVALID_FOV😸\n"
# define INVALID_BRIGHTNESS "\nERR_INVALID_BRIGHTNESS\n"
# define INVALID_WIDTH "\nERR_INVALID_WIDTH\n"
# define INVALID_HEIGHT "\nRR_INVALID_HEIGHT\n"
# define INVALID_LIGHTING "\nERR_INVALID_LIGHTING😸\n"

# define ERR_FILE_NOT_FOUND "file not found"
# define ERR_IS_NOT_RT_FILE "isn't a rt file"
# define ERR_FORBIDDEN_CHAR "contain forbidden character"
# define ERR_MEM_ALLOC "Memory allocation error"
# define IS_NAME "\033[0;92mPut:\n\n./minirt scenes/atom01.rt\n\n😸\n\033[0m"
# define MERRY "\033[0;92m\n\n🎄 MERRY CHRISTMAS 🎄\n\n\033[0m"

# define ESC_KEY 65307
# define L_KEY 108
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define R_KEY 114
# define F_KEY 102
# define C_KEY 99
# define Q_KEY 113
# define E_KEY 101
# define X_KEY 120

# define PLUS_KEY 65451
# define MINUS_KEY 65453

# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define UP_ARROW 65362
# define DOWN_ARROW 65364

# define NP_1       65436
# define NP_2       65433
# define NP_3       65435

# define NP_7       65429
# define NP_8       65431 
# define NP_9       65434 
# define NP_4       65430 
# define NP_5       65437 
# define NP_6       65432

#endif