/*day1*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 80
#define HEIGHT 24
#define MAX_OBJECTS 100
#define EMPTY '_'
#define PIXEL '*'

enum {LINE=1, RECTANGLE, CIRCLE, TRIANGLE};

typedef struct {
    int type;
    int filled;
    int x1,y1,x2,y2,x3,y3;
    int radius;
    int active;
} Shape;

Shape objects[MAX_OBJECTS];
Shape undoObjects[MAX_OBJECTS];
int objectCount=0, undoCount=0;
char canvas[HEIGHT][WIDTH];
/*day2*/
void saveUndo(){
    memcpy(undoObjects, objects, sizeof(objects));
    undoCount = objectCount;
}

void undoLast(){
    memcpy(objects, undoObjects, sizeof(objects));
    objectCount = undoCount;
}

int validPoint(int x,int y){
    return x>=0 && x<WIDTH && y>=0 && y<HEIGHT;
}

void clearCanvas(){
    for(int y=0;y<HEIGHT;y++)
        for(int x=0;x<WIDTH;x++)
            canvas[y][x]=EMPTY;
}

void setPixel(int x,int y){
    if(validPoint(x,y)) canvas[y][x]=PIXEL;
}
/*day3*/
void drawLine(int x1,int y1,int x2,int y2){
    int dx=abs(x2-x1), dy=abs(y2-y1);
    int sx=x1<x2?1:-1, sy=y1<y2?1:-1;
    int err=dx-dy;
    while(1){
        setPixel(x1,y1);
        if(x1==x2 && y1==y2) break;
        int e2=2*err;
        if(e2>-dy){ err-=dy; x1+=sx; }
        if(e2<dx){ err+=dx; y1+=sy; }
    }
}

void drawRectangle(int x1,int y1,int x2,int y2,int filled){
    if(filled){
        for(int y=y1;y<=y2;y++)
            for(int x=x1;x<=x2;x++)
                setPixel(x,y);
    } else {
        drawLine(x1,y1,x2,y1);
        drawLine(x2,y1,x2,y2);
        drawLine(x2,y2,x1,y2);
        drawLine(x1,y2,x1,y1);
    }
}

void drawCircle(int cx,int cy,int r,int filled){
    for(int y=cy-r;y<=cy+r;y++){
        for(int x=cx-r;x<=cx+r;x++){
            int d=(x-cx)*(x-cx)+(y-cy)*(y-cy);
            if(filled){
                if(d<=r*r) setPixel(x,y);
            } else {
                if(d>=r*r-r && d<=r*r+r) setPixel(x,y);
            }
        }
    }
}
/*day4*/
void drawTriangle(int x1,int y1,int x2,int y2,int x3,int y3){
    drawLine(x1,y1,x2,y2);
    drawLine(x2,y2,x3,y3);
    drawLine(x3,y3,x1,y1);
}

void redraw(){
    clearCanvas();
    for(int i=0;i<objectCount;i++){
        if(!objects[i].active) continue;
        Shape s=objects[i];
        switch(s.type){
            case LINE: drawLine(s.x1,s.y1,s.x2,s.y2); break;
            case RECTANGLE: drawRectangle(s.x1,s.y1,s.x2,s.y2,s.filled); break;
            case CIRCLE: drawCircle(s.x1,s.y1,s.radius,s.filled); break;
            case TRIANGLE: drawTriangle(s.x1,s.y1,s.x2,s.y2,s.x3,s.y3); break;
        }
    }
}

void display(){
    redraw();
    for(int y=0;y<HEIGHT;y++){
        for(int x=0;x<WIDTH;x++) putchar(canvas[y][x]);
        putchar('\n');
    }
}
/*day5*/
void listObjects(){
    for(int i=0;i<objectCount;i++){
        if(objects[i].active)
            printf("Index=%d Type=%d Filled=%d\n",i,objects[i].type,objects[i].filled);
    }
}

void addObject(){
    if(objectCount>=MAX_OBJECTS){ printf("Limit reached\n"); return; }
    saveUndo();
    Shape s={0}; s.active=1;
    printf("Type(1-Line 2-Rect 3-Circle 4-Triangle): ");
    scanf("%d",&s.type);

    if(s.type==LINE)
        scanf("%d%d%d%d",&s.x1,&s.y1,&s.x2,&s.y2);
    else if(s.type==RECTANGLE){
        printf("Filled(0/1): "); scanf("%d",&s.filled);
        scanf("%d%d%d%d",&s.x1,&s.y1,&s.x2,&s.y2);
    }
    else if(s.type==CIRCLE){
        printf("Filled(0/1): "); scanf("%d",&s.filled);
        scanf("%d%d%d",&s.x1,&s.y1,&s.radius);
    }
    else if(s.type==TRIANGLE)
        scanf("%d%d%d%d%d%d",&s.x1,&s.y1,&s.x2,&s.y2,&s.x3,&s.y3);

    objects[objectCount++]=s;
}

void deleteObject(){
    int i; scanf("%d",&i);
    if(i>=0 && i<objectCount){ saveUndo(); objects[i].active=0; }
}

void moveObject(){
    int i,dx,dy;
    scanf("%d%d%d",&i,&dx,&dy);
    if(i<0||i>=objectCount) return;
    saveUndo();
    objects[i].x1+=dx; objects[i].y1+=dy;
    objects[i].x2+=dx; objects[i].y2+=dy;
    objects[i].x3+=dx; objects[i].y3+=dy;
}

void modifyObject(){
    int i; scanf("%d",&i);
    if(i<0||i>=objectCount) return;
    saveUndo();
    Shape *s=&objects[i];
    if(s->type==LINE) scanf("%d%d%d%d",&s->x1,&s->y1,&s->x2,&s->y2);
    else if(s->type==RECTANGLE) scanf("%d%d%d%d",&s->x1,&s->y1,&s->x2,&s->y2);
    else if(s->type==CIRCLE) scanf("%d%d%d",&s->x1,&s->y1,&s->radius);
    else scanf("%d%d%d%d%d%d",&s->x1,&s->y1,&s->x2,&s->y2,&s->x3,&s->y3);
}

void saveFile(){
    char f[100]; scanf("%99s",f);
    FILE *fp=fopen(f,"w");
    fprintf(fp,"%d\n",objectCount);
    fwrite(objects,sizeof(Shape),objectCount,fp);
    fclose(fp);
}

void loadFile(){
    char f[100]; scanf("%99s",f);
    FILE *fp=fopen(f,"r");
    if(!fp) return;
    fscanf(fp,"%d\n",&objectCount);
    fread(objects,sizeof(Shape),objectCount,fp);
    fclose(fp);
}

int main(){
    int ch;
    while(1){
        printf("\n1.Add 2.Delete 3.Modify 4.Display 5.List 6.Move 7.Save 8.Load 9.Undo 0.Exit\n");
        scanf("%d",&ch);
        switch(ch){
            case 1:addObject();break;
            case 2:printf("Index: ");deleteObject();break;
            case 3:printf("Index + data: ");modifyObject();break;
            case 4:display();break;
            case 5:listObjects();break;
            case 6:printf("Index dx dy: ");moveObject();break;
            case 7:printf("Filename: ");saveFile();break;
            case 8:printf("Filename: ");loadFile();break;
            case 9:undoLast();break;
            case 0:return 0;
        }
    }
}
