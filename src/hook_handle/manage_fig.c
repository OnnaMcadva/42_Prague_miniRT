/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annavm <annavm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:57:53 by annavm            #+#    #+#             */
/*   Updated: 2024/12/14 23:36:27 by annavm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

void elka(const char *arg) 
{ 
    char *args[] = {"./minirt", (char *)arg, NULL}; 
	execv(args[0], args); 
    perror("execv failed"); 
    exit(1); 
} 

void manage_fig(int key, t_rt *rt)
{
    // Проверка на выбранный объект
    if (!rt->event.selection)
        return;

    // Работа с выбранной сферой
    if (rt->event.selection->id == id_sphere)
    {
        t_obj *sphere = rt->event.selection;
        float radius = sphere->object.sphere.diameter / 2;

        if (key == NP_1)  // Увеличение сферы
        {
            if (sphere->object.sphere.diameter < radius * 3)
                sphere->object.sphere.diameter *= 1.1;
        }
        else if (key == NP_3)  // Уменьшение сферы
        {
            if (sphere->object.sphere.diameter > radius / 3)
                sphere->object.sphere.diameter /= 1.1;
        }
    }

    // Работа с выбранным цилиндром
    if (rt->event.selection->id == id_cylinder)
    {
        t_obj *obj = rt->event.selection;
        t_cylinder *cylinder = &obj->object.cylinder;

        float angle_in_radians = ROTATE_ANGLE * (M_PI / 180.0);
        t_vect rotation_axis = {1, 0, 0};  // Вращение по оси X (горизонтальная ось)

        if (key == NP_2)  // Вращение цилиндра
        {
            // Вращение вокруг оси X
            rotate_vector(&cylinder->orient, rotation_axis, -angle_in_radians);
            rt->event.torender = TRUE;  // Перерисовываем сцену
        }
    }

    // Отрисовка сцены после изменения
    if (rt->event.torender)
    {
        render(rt);
        rt->event.torender = FALSE;  // Останавливаем перерисовку
    }
}

// Функция для вращения вектора вокруг оси
void rotate_vector(t_vect *vector, t_vect axis, float angle)
{
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);

    // Вращение вектора вокруг оси
    float x = vector->x * (cos_angle + (1 - cos_angle) * axis.x * axis.x) +
              vector->y * ((1 - cos_angle) * axis.x * axis.y - axis.z * sin_angle) +
              vector->z * ((1 - cos_angle) * axis.x * axis.z + axis.y * sin_angle);
    float y = vector->x * ((1 - cos_angle) * axis.y * axis.x + axis.z * sin_angle) +
              vector->y * (cos_angle + (1 - cos_angle) * axis.y * axis.y) +
              vector->z * ((1 - cos_angle) * axis.y * axis.z - axis.x * sin_angle);
    float z = vector->x * ((1 - cos_angle) * axis.z * axis.x - axis.y * sin_angle) +
              vector->y * ((1 - cos_angle) * axis.z * axis.y + axis.x * sin_angle) +
              vector->z * (cos_angle + (1 - cos_angle) * axis.z * axis.z);

    vector->x = x;
    vector->y = y;
    vector->z = z;
}
