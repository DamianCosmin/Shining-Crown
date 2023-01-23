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
    readimagefile("Images\\New Photos\\Star Scatter.jpg", 50, 50, 200, 200);
    readimagefile("Images\\New Photos\\Star Scatter.jpg", 200, 50, 350, 200);
    readimagefile("Images\\New Photos\\Star Scatter.jpg", 350, 50, 500, 200);
    readimagefile("Images\\New Photos\\Star Scatter.jpg", 500, 50, 650, 200);
    readimagefile("Images\\New Photos\\Star Scatter.jpg", 650, 50, 800, 200);

    // Second line
    readimagefile("Images\\New Photos\\Dollar Scatter.jpg", 50, 200, 200, 350);
    readimagefile("Images\\New Photos\\Dollar Scatter.jpg", 200, 200, 350, 350);
    readimagefile("Images\\New Photos\\Dollar Scatter.jpg", 350, 200, 500, 350);
    readimagefile("Images\\New Photos\\crown.jpg", 500, 200, 650, 350);
    readimagefile("Images\\New Photos\\watermelon.jpg", 650, 200, 800, 350);

    // Second line
    readimagefile("Images\\New Photos\\bell.jpg", 50, 350, 200, 500);
    readimagefile("Images\\New Photos\\cheries.jpg", 200, 350, 350, 500);
    readimagefile("Images\\New Photos\\grapes.jpg", 350, 350, 500, 500);
    readimagefile("Images\\New Photos\\lemon.jpg", 500, 350, 650, 500);
    readimagefile("Images\\New Photos\\plum.jpg", 650, 350, 800, 500);

    getch();
    return 0;
}
