//day 1//
#include <stdio.h>

#define WIDTH  20
#define HEIGHT 10

#define EMPTY  '.'
#define PIXEL  '#'

char picture[HEIGHT][WIDTH];

void clearPicture() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            picture[y][x] = EMPTY;
        }
    }
}

void displayPicture() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", picture[y][x]);
        }
        printf("\n");
    }
}

void setPixel(int x, int y) {
    if (x >= 0 && x < WIDTH &&
        y >= 0 && y < HEIGHT) {
        picture[y][x] = PIXEL;
    }
}

int main() {

    clearPicture();

    setPixel(10, 5);
    setPixel(11, 5);
    setPixel(12, 5);

    displayPicture();

    return 0;
}