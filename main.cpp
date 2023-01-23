#include <graphics.h>
#include <winbgim.h>

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <time.h>

using namespace std;

const int WIDTH = 850;
const int HEIGHT = 850;

int main()
{
    initwindow(WIDTH, HEIGHT, "Shining Crown");

    // Generate Border
    setcolor(RED);
    for(int i = 0; i <= 10; i++){
        rectangle(30+i,30+i,820-i,520-i);
    }

    // First line
    readimagefile("Images\\star-scatter.jpg", 50, 50, 200, 200);
    readimagefile("Images\\dollar-scatter.jpg", 200, 50, 350, 200);
    readimagefile("Images\\dollar-scatter.jpg", 350, 50, 500, 200);
    readimagefile("Images\\dollar-scatter.jpg", 500, 50, 650, 200);
    readimagefile("Images\\star-scatter.jpg", 650, 50, 800, 200);

    // Second line
    readimagefile("Images\\crown.jpg", 50, 200, 200, 350);
    readimagefile("Images\\watermelon.jpg", 200, 200, 350, 350);
    readimagefile("Images\\lucky-seven.jpg", 350, 200, 500, 350);
    readimagefile("Images\\bell.jpg", 500, 200, 650, 350);
    readimagefile("Images\\crown.jpg", 650, 200, 800, 350);

    // Second line
    readimagefile("Images\\orange.jpg", 50, 350, 200, 500);
    readimagefile("Images\\plum.jpg", 200, 350, 350, 500);
    readimagefile("Images\\lemon.jpg", 350, 350, 500, 500);
    readimagefile("Images\\cherry.jpg", 500, 350, 650, 500);
    readimagefile("Images\\grapes.jpg", 650, 350, 800, 500);

    getch();
    return 0;
}
