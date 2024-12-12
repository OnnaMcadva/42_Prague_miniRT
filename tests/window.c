#include "../minilibx-linux/mlx.h"
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>        // Для использования функции rand()
#include <X11/Xlib.h>    // Заголовок для работы с X11
#include <X11/keysym.h>  // Для определения кодов клавиш

// Определение размеров окон
#define WIN_WIDTH1 1024
#define WIN_HEIGHT1 1024
#define WIN_WIDTH2 800
#define WIN_HEIGHT2 600
#define ESC_KEY XK_Escape  // Код клавиши Escape для X11
#define NUM_POINTS 1000    // Количество белых точек

typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *img;         // Поле для изображения
    char    *img_data;    // Указатель на данные изображения
    int     bpp;          // Биты на пиксель
    int     size_line;    // Размер строки
    int     endian;       // Порядок байтов
    int     is_geom_displayed; // Флаг для отслеживания отображения лошади
} t_data;

// Функция для обработки закрытия окна по крестику
int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    exit(0);  // Корректное завершение программы
    return (0);
}

// Функция для обработки нажатий клавиш (переключение на окно 800x600)
int handle_keypress(int keycode, t_data *data)
{
    if (keycode == ESC_KEY)  // Если нажата клавиша ESC
    {
        mlx_destroy_window(data->mlx, data->win);
        exit(0);  // Корректное завершение программы
    }

    // Если нажата любая другая клавиша и geom еще не была показана
    if (!data->is_geom_displayed)
    {
        data->is_geom_displayed = 1; // Устанавливаем флаг
        return (0); // Не переключаемся на новое окно
    }

    // Если лошадь уже показана, открываем новое окно 800x600
    mlx_destroy_window(data->mlx, data->win);

    // Создаем новое окно 800x600
    data->win = mlx_new_window(data->mlx, WIN_WIDTH2, WIN_HEIGHT2, "Random Points");

    // Создаем изображение размером 800x600
    data->img = mlx_new_image(data->mlx, WIN_WIDTH2, WIN_HEIGHT2);
    data->img_data = mlx_get_data_addr(data->img, &data->bpp, &data->size_line, &data->endian);

    // Генерируем и отображаем белые точки на черном фоне
    srand(time(NULL));
    for (int i = 0; i < NUM_POINTS; i++)
    {
        int x = rand() % WIN_WIDTH2;
        int y = rand() % WIN_HEIGHT2;

        int pixel = (y * data->size_line) + (x * (data->bpp / 8));
        data->img_data[pixel] = 255;      // Blue
        data->img_data[pixel + 1] = 255;  // Green
        data->img_data[pixel + 2] = 255;  // Red
    }

    // Выводим изображение в новое окно
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

    // Добавляем обработку клавиш для нового окна
    mlx_key_hook(data->win, handle_keypress, data);
    mlx_hook(data->win, 33, 0, close_window, data);  // Обработка крестика

    return (0);
}

int main()
{
    t_data  data;
    Display *display;
    Window window;
    Atom    wm_delete;
    int     img_width = WIN_WIDTH1;   // Переменные для ширины и высоты изображения
    int     img_height = WIN_HEIGHT1;

    // Инициализация MinilibX
    data.mlx = windows_init();
    if (data.mlx == NULL)
    {
        printf("Ошибка: не удалось инициализировать MinilibX.\n");
        return (1);
    }

    // Создание первого окна 1024x1024
    data.win = mlx_new_window(data.mlx, WIN_WIDTH1, WIN_HEIGHT1, "Geom Image");
    if (data.win == NULL)
    {
        printf("Ошибка: не удалось создать окно.\n");
        return (1);
    }

    // Получение дисплея и окна через X11
    display = XOpenDisplay(NULL);
    window = *((Window *)(data.win));  // Преобразование указателя в X11 окно

    // Получаем Atom для обработки события закрытия окна (ClientMessage)
    wm_delete = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wm_delete, 1);



    // Загрузка изображения geom.xpm и вывод его в окно
    data.img = mlx_xpm_file_to_image(data.mlx, "geom.xpm", &img_width, &img_height);
    if (data.img == NULL)
    {
        printf("Ошибка: не удалось загрузить изображение geom.xpm.\n");
        return (1);
    }
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

    data.is_geom_displayed = 0; // Инициализация флага отображения лошади

    // Обработка нажатия клавиш (переключение на новое окно при любой клавише)
    mlx_key_hook(data.win, handle_keypress, &data);

    // Обработка крестика
    mlx_hook(data.win, 33, 0, close_window, &data);

    // Основной цикл обработки событий
    mlx_loop(data.mlx);

    return (0);
}


// cc window.c -I../minilibx-linux -L../minilibx-linux -lmlx -lX11 -lXext -lm
