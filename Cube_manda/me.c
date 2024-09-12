#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 100

typedef struct s_data {
    void *mlx_ptr;
    void *win_ptr;
    int button_clicked;
} t_data;

void draw_button(t_data *data, int x, int y, int width, int height) {
    int i, j;
    for (i = x; i < x + width; i++) {
        for (j = y; j < y + height; j++) {
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, j, 0x00FF00); // Green color
        }
    }

    // Draw the "Start" text in the center of the button
    int text_x = x + (width / 2) - 20; // Adjust the -20 based on text width
    int text_y = y + (height / 2) - 10; // Adjust the -10 based on text height
    mlx_string_put(data->mlx_ptr, data->win_ptr, text_x, text_y, 0xFFFFFF, "Start");
}

int mouse_click(int button, int x, int y, t_data *data) {
    int button_x = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
    int button_y = (WINDOW_HEIGHT - BUTTON_HEIGHT) / 2;

    // Check if the click is within the button's bounds
    if (button == 1 && x >= button_x && x <= button_x + BUTTON_WIDTH &&
        y >= button_y && y <= button_y + BUTTON_HEIGHT) {
        data->button_clicked = 1;
        printf("Button clicked! Variable set to %d\n", data->button_clicked);
        mlx_clear_window(data->mlx_ptr, data->win_ptr);
        mlx_destroy_image(data->mlx_ptr, data->win_ptr);
        exit(0);
        mlx_destroy_image(data->mlx_ptr, data->win_ptr);
        exit(0);
    }

    return (0);
}

int main(void) {
    t_data data;

    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (EXIT_FAILURE);
    data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Button Click Window");
    if (data.win_ptr == NULL) {
        free(data.mlx_ptr);
        return (EXIT_FAILURE);
    }

    data.button_clicked = 0; // Initialize the variable to 0

    // Draw a big button in the center of the window
    int button_x = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
    int button_y = (WINDOW_HEIGHT - BUTTON_HEIGHT) / 2;
    draw_button(&data, button_x, button_y, BUTTON_WIDTH, BUTTON_HEIGHT);

    // Hook the mouse click event
    mlx_mouse_hook(data.win_ptr, mouse_click, &data);
    mlx_loop(data.mlx_ptr);

    return (EXIT_SUCCESS);
}
