//day1//
#include <stdio.h>
#include<stdlib.h>

#define WIDTH 20
#define HEIGHT 10

#define EMPTY '.'
#define PIXEL '#'

char picture[HEIGHT][WIDTH];

void clearPicture() {
    for(int y=0; y<HEIGHT; y++) 
        for(int x =0; x<WIDTH;x++) 
            picture[y][x] = EMPTY;
        }

void displayPicture() {
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x<WIDTH; x++) 
            printf("%c", picture[y][x]);
    
        printf("\n");
    }

}

void setPixel(int x, int y) {
    if (x >= 0 && x < WIDTH &&
        y>0 && y < HEIGHT) {
            picture[y][x] = PIXEL;
        }
}
/*_______Day 2*/

void drawLine(int x1, int y1, int x2, int y2){
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while(1)
    {
        setPixel(x1, y1);

        if(x1 == x2 && y1 == y2)
        break;

        int e2 = 2*err;

        if(e2 > -dy)
        {
            err -=dy;
            x1 += sx;
        }

        if(e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void drawRectangle(int x1, int y1, int x2, int y2)
{
    drawLine(x1, y1, x2, y1);
    drawLine(x2, y1, x2, y2);
    drawLine(x2, y2, x1, y2);
    drawLine(x1, y2, x1, y1);
}

/*________________TEST ONLY_______*/

int main()
{
    clearPicture();

    drawLine(1, 1, 15, 7);
    drawRectangle(2, 2, 12, 8);

    displayPicture();
    
    return 0;
}