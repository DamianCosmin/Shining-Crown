#include <graphics.h>
#include <winbgim.h>

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <time.h>

#define TOTAL_SLOTS 11
using namespace std;

const int WIDTH = 850;
const int HEIGHT = 850;
const char IMAGES_PATH[20][100] = {
    "Images\\orange.jpg",
    "Images\\plum.jpg",
    "Images\\lemon.jpg",
    "Images\\cherry.jpg",
    "Images\\bell.jpg",
    "Images\\watermelon.jpg",
    "Images\\grapes.jpg",
    "Images\\lucky-seven.jpg",
    "Images\\dollar-scatter.jpg",
    "Images\\star-scatter.jpg",
    "Images\\crown.jpg"
};
int VALUES_MATRIX[3][5];

int generateRandomNumber(){
    return (rand() % TOTAL_SLOTS);
}

void generateVisuals(){
    // Generate Title
    setcolor(YELLOW);
    settextstyle(BOLD_FONT, 0, 6);
    outtextxy(225,15,"SHINING CROWN");

    // Generate Border
    setcolor(RED);
    for(int i = 0; i <= 10; i++){
        rectangle(30+i,80+i,820-i,570-i);
    }

    // Generate Money Info
    setcolor(LIGHTGREEN);
    for(int i = 0; i <= 10; i++){
        rectangle(250+i,600+i,600-i,750-i);
    }

    settextstyle(COMPLEX_FONT, 0, 2);
    outtextxy(275,625,"Current Money: ");
    outtextxy(450,625,"1000$");

    outtextxy(275,665,"Current bet: ");
    outtextxy(450,665,"100$");

    outtextxy(275,705,"Last Win: ");
    outtextxy(450,705,"200$");

    // Generate Roll Button - not finished
    readimagefile("roll.jpg", 650, 600, 500, 750);
}

int main()
{
    initwindow(WIDTH, HEIGHT, "Shining Crown");
    srand(time(NULL));

    generateVisuals();

    // First line
    readimagefile(IMAGES_PATH[generateRandomNumber()], 50, 100, 200, 250);
    readimagefile(IMAGES_PATH[generateRandomNumber()], 200, 100, 350, 250);
    readimagefile(IMAGES_PATH[generateRandomNumber()], 350, 100, 500, 250);
    readimagefile(IMAGES_PATH[generateRandomNumber()], 500, 100, 650, 250);
    readimagefile(IMAGES_PATH[generateRandomNumber()], 650, 100, 800, 250);

    // Second line
    readimagefile(IMAGES_PATH[generateRandomNumber()], 50, 250, 200, 400);
    readimagefile(IMAGES_PATH[generateRandomNumber()], 200, 250, 350, 400);
    readimagefile(IMAGES_PATH[generateRandomNumber()], 350, 250, 500, 400);
    readimagefile(IMAGES_PATH[generateRandomNumber()], 500, 250, 650, 400);
    readimagefile(IMAGES_PATH[generateRandomNumber()], 650, 250, 800, 400);

    // Third line
    readimagefile(IMAGES_PATH[generateRandomNumber()], 50, 400, 200, 550);
    readimagefile(IMAGES_PATH[generateRandomNumber()], 200, 400, 350, 550);
    readimagefile(IMAGES_PATH[generateRandomNumber()], 350, 400, 500, 550);
    readimagefile(IMAGES_PATH[generateRandomNumber()], 500, 400, 650, 550);
    readimagefile(IMAGES_PATH[generateRandomNumber()], 650, 400, 800, 550);

    getch();
    return 0;
}
