/* day1*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 80
#define HEIGHT 24
#define EMPTY '_'
#define PIXEL '*'

typedef enum { LINE, RECTANGLE, CIRCLE, TRIANGLE } ShapeType;

typedef struct {
    ShapeType type;
    int params[6]; // store coordinates/radius depending on shape
} Shape;

Shape objects[100]; // list of shapes
int objectCount = 0;

char picture[HEIGHT][WIDTH];
/*day2*/
// ---------------- Canvas Functions ----------------
void clearPicture() {
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            picture[y][x] = EMPTY;
}

void setPixel(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        picture[y][x] = PIXEL;
}

void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = dx + dy, e2;
    while (1) {
        setPixel(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x1 += sx; }
        if (e2 <= dx) { err += dx; y1 += sy; }
    }
}
/*day3*/
void drawRectangle(int x1, int y1, int x2, int y2) {
    for (int x = x1; x <= x2; x++) { setPixel(x, y1); setPixel(x, y2); }
    for (int y = y1; y <= y2; y++) { setPixel(x1, y); setPixel(x2, y); }
}

void drawCircle(int cx, int cy, int r) {
    int x = r, y = 0, err = 0;
    while (x >= y) {
        setPixel(cx + x, cy + y); setPixel(cx + y, cy + x);
        setPixel(cx - y, cy + x); setPixel(cx - x, cy + y);
        setPixel(cx - x, cy - y); setPixel(cx - y, cy - x);
        setPixel(cx + y, cy - x); setPixel(cx + x, cy - y);
        y++;
        if (err <= 0) err += 2*y + 1;
        else { x--; err -= 2*x + 1; }
    }
}
/*day4*/
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

void renderObjects() {
    clearPicture();
    for (int i = 0; i < objectCount; i++) {
        Shape s = objects[i];
        if (s.type == LINE) drawLine(s.params[0], s.params[1], s.params[2], s.params[3]);
        else if (s.type == RECTANGLE) drawRectangle(s.params[0], s.params[1], s.params[2], s.params[3]);
        else if (s.type == CIRCLE) drawCircle(s.params[0], s.params[1], s.params[2]);
        else if (s.type == TRIANGLE) drawTriangle(s.params[0], s.params[1], s.params[2], s.params[3], s.params[4], s.params[5]);
    }
}

void displayPicture() {
    renderObjects();
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) printf("%c", picture[y][x]);
        printf("\n");
    }
}

// ---------------- Object Management ----------------
void addObject(Shape s) {
    if (objectCount < 100) objects[objectCount++] = s;
}

void deleteObject(int index) {
    if (index >= 0 && index < objectCount) {
        for (int i = index; i < objectCount - 1; i++) objects[i] = objects[i + 1];
        objectCount--;
    }
}

void modifyObject(int index, Shape newShape) {
    if (index >= 0 && index < objectCount) objects[index] = newShape;
}
/*dat5*/
// ---------------- Main Menu ----------------
int main() {
    int choice;
    clearPicture();

    while (1) {
        printf("\nMenu\n");
        printf("1. Add Line\n");
        printf("2. Add Rectangle\n");
        printf("3. Add Circle\n");
        printf("4. Add Triangle\n");
        printf("5. Display Picture\n");
        printf("6. Delete Object\n");
        printf("7. Modify Object\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            Shape s; s.type = LINE;
            printf("Enter x1 y1 x2 y2: ");
            scanf("%d %d %d %d", &s.params[0], &s.params[1], &s.params[2], &s.params[3]);
            addObject(s);
        }
        else if (choice == 2) {
            Shape s; s.type = RECTANGLE;
            printf("Enter top-left x y and bottom-right x y: ");
            scanf("%d %d %d %d", &s.params[0], &s.params[1], &s.params[2], &s.params[3]);
            addObject(s);
        }
        else if (choice == 3) {
            Shape s; s.type = CIRCLE;
            printf("Enter center x y and radius: ");
            scanf("%d %d %d", &s.params[0], &s.params[1], &s.params[2]);
            addObject(s);
        }
        else if (choice == 4) {
            Shape s; s.type = TRIANGLE;
            printf("Enter x1 y1 x2 y2 x3 y3: ");
            scanf("%d %d %d %d %d %d", &s.params[0], &s.params[1], &s.params[2], &s.params[3], &s.params[4], &s.params[5]);
            addObject(s);
        }
        else if (choice == 5) {
            displayPicture();
        }
        else if (choice == 6) {
            int idx; printf("Enter object index (0-%d): ", objectCount - 1);
            scanf("%d", &idx);
            deleteObject(idx);
        }
        else if (choice == 7) {
            int idx; printf("Enter object index (0-%d): ", objectCount - 1);
            scanf("%d", &idx);
            if (idx >= 0 && idx < objectCount) {
                Shape s;
                printf("Enter new type (1=Line,2=Rect,3=Circle,4=Triangle): ");
                int t; scanf("%d", &t);
                s.type = (t == 1 ? LINE : t == 2 ? RECTANGLE : t == 3 ? CIRCLE : TRIANGLE);
                if (s.type == LINE) {
                    printf("Enter x1 y1 x2 y2: ");
                    scanf("%d %d %d %d", &s.params[0], &s.params[1], &s.params[2], &s.params[3]);
                } else if (s.type == RECTANGLE) {
                    printf("Enter top-left x y and bottom-right x y: ");
                    scanf("%d %d %d %d", &s.params[0], &s.params[1], &s.params[2], &s.params[3]);
                } else if (s.type == CIRCLE) {
                    printf("Enter center x y and radius: ");
                    scanf("%d %d %d", &s.params[0], &s.params[1], &s.params[2]);
                } else {
                    printf("Enter x1 y1 x2 y2 x3 y3: ");
                    scanf("%d %d %d %d %d %d", &s.params[0], &s.params[1], &s.params[2], &s.params[3], &s.params[4], &s.params[5]);
                }
                modifyObject(idx, s);
            }
        }
        else if (choice == 0) {
            printf("Exiting program.\n");
            break;
        }
        else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}
