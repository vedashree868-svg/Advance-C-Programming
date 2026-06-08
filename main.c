//day1//
#include <stdio.h>
#include<stdlib.h>

#define WIDTH 80
#define HEIGHT 24
#define MAX_OBJECTS 100

#define EMPTY '.'
#define PIXEL '#'

#define LINE 1
#define RECTANGLE 2
#define CIRCLE 3
#define TRIANGLE 4

char picture[HEIGHT][WIDTH];

typedef struct
{
    int type;

    int x1, y1;
    int x2, y2;
    int x3, y3;

    int radius;
    int active;
}Shape;

Shape objects[MAX_OBJECTS];
int objectCount = 0;

/*____________________Canvas Functions_________________*/

void clearPicture() 
{
int y, x;

    for(int y=0; y<HEIGHT; y++) 
{
    for(int x =0; x<WIDTH;x++)
        { 
            
            picture[y][x] = EMPTY;
        }
    }
}

void displayPicture()
    {
int y, x;

    for(int y = 0;y<HEIGHT;y++) 
    {
        for(int x = 0; x<WIDTH; x++) 
        {
            printf("%c", picture[y][x]);
        }
        printf("\n");
    }
}

void setPixel(int x, int y)
{
    if (x >= 0 && x < WIDTH &&
        y>=0 && y < HEIGHT)
    {
            picture[y][x] = PIXEL;
        }
}
/*_______Day 2*/
/*______________________________drawing functions________*/

void drawLine(int x1, int y1, int x2, int y2)
{
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

        if(e2<dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void drawRectangle(int x1, int y1, int x2, int 
y2)
{
    drawLine(x1, y1, x2, y1);
    drawLine(x2, y1, x2, y2);
    drawLine(x2, y2, x1, y2);
    drawLine(x1, y2, x1, y1);
}

void drawCircle(int cx, int cy, int radius)
{
    int x, y;

    for(y=cy-radius; y<=cy+radius; y++)
    {
        for(x=cx-radius; x<=cx+radius; x++)
        {
            int dx = x - cx;
            int dy = y - cy;

            int d = dx*dx + dy*dy;
            int r2 = radius*radius;

            if(d >= r2 - radius && 
                d <= r2 + radius)
            {
                setPixel(x, y);
            }
        }
    }
}

void drawTriangle(int x1, int y1,
        int x2, int y2,
            int x3, int y3)
{
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}
    /*________________________object management__________________*/

    void redrawPicture()
    {
        int i;

        clearPicture();
    
    for(i=0;i<objectCount;i++)
{
    if(!objects[i].active)
    continue;

        switch(objects[i].type)
        {
            case LINE:
                drawLine(
                    objects[i].x1, 
                    objects[i].y1, 
                    objects[i].x2, 
                    objects[i].y2
                );
                break;
                
            case RECTANGLE:
                drawRectangle(
                    objects[i].x1,
                        objects[i].y1,
                        objects[i].x2,
                            objects[i].y2
                        );
                break;

            case CIRCLE:
                drawCircle(objects[i].x1,
                        objects[i].y1,
                            objects[i].radius
                        );
                break;
                
            case TRIANGLE:
                drawTriangle(objects[i].x1,
                        objects[i].y1,
                            objects[i].x2,
                                objects[i].y2,
                                    objects[i].x3,
                                        objects[i].y3
                                    );
                break;
                                }
        }
    }

    void addObjects()
    {
        Shape s;
        int type;

        printf("\nChoose shape type:\n");
        printf("1. Line\n");
        printf("2. Rectangle\n");
        printf("3. Circle\n");
        printf("4. Triangle\n");
        printf("Enter shape type: ");

        scanf("%d", &type);

        s.type = type;
        s.active = 1;

        if(type==LINE)
        {
            printf("Enter x1 y1 x2 y2: ");
            scanf("%d %d %d %d",
                    &s.x1, &s.y1,
                        &s.x2, &s.y2);
        }
        else if(type == RECTANGLE)
        {
            printf("Enter x1 y1 x2 y2: ");
            scanf("%d %d %d %d",
                    &s.x1, &s.y1,
                        &s.x2, &s.y2);
        }
        else if(type == CIRCLE)
        {
            printf("Enter cx cy radius: ");
            scanf("%d %d %d",
                    &s.x1, &s.y1,
                        &s.radius);
        }
        else if(type == TRIANGLE)
        {
            printf("Enter x1 y1 x2 y2 x3 y3: ");
            scanf("%d %d %d %d %d %d", 
                &s.x1, &s.y1,
                    &s.x2, &s.y2,
                        &s.x3, &s.y3);
        }
        else
        {
            printf("Invalid shape type.\n");
            return;
        }

        objects[objectCount] = s;

       

        
