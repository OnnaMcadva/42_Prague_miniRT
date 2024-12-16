#include "../minilibx-linux/mlx.h"
int main(int argc, char **argv) {
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "Test");
    mlx_destroy_window(mlx, win);
    mlx_destroy_display(mlx);
    free(mlx); // Если библиотека требует ручного освобождения
    return 0;
}
