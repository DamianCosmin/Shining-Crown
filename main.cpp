#include <graphics.h>
#include <winbgim.h>

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <time.h>

#define SLOT_ROWS 3
#define SLOT_COLUMNS 5
#define SLOT_PIXELSIZE 150
#define CHANCES 140
using namespace std;

/// VARIABLES
const int WIDTH = 850;
const int HEIGHT = 850;
const char IMAGES_PATH[20][100] = {
    // Stage 1
    "Images\\orange.jpg",
    "Images\\plum.jpg",
    "Images\\lemon.jpg",
    "Images\\cherry.jpg",
    "Images\\bell.jpg",
    // Stage 2
    "Images\\watermelon.jpg",
    "Images\\grapes.jpg",
    "Images\\lucky-seven.jpg",
    // Stage 3 - special symbols
    "Images\\dollar-scatter.jpg",
    "Images\\star-scatter.jpg",
    "Images\\crown.jpg"
};
int VALUES_MATRIX[3][5];

struct node{
    int info;
    node *next;
};
node *SLOT_LISTS[5];

/// FUNCTIONS
void addNode(node *&p , int value){
    node *q, *add;
    add = new node;
    add -> info = value;
    add -> next = NULL;

    if(p == NULL){
        p = add;
    }
    else{
        q = p;
        while(q -> next != NULL){
            q = q -> next;
        }

        q -> next = add;
    }
}

void showList(node *p){
    node *q;
    q = p;
    while(q != NULL){
        cout << q -> info << " ";
        q = q -> next;
    }
    cout << '\n';
}

int generateRandomPhotoID(){
    int random = (rand() % CHANCES);

    // Stage 1 returns
    if(random >= 0 && random <= 19){
        return 0;
    }
    if(random >= 20 && random <= 39){
        return 1;
    }
    if(random >= 40 && random <= 59){
        return 2;
    }
    if(random >= 60 && random <= 79){
        return 3;
    }
    if(random >= 80 && random <= 99){
        return 4;
    }

    // Stage 2 returns
    if(random >= 100 && random <= 109){
        return 5;
    }
    if(random >= 110 && random <= 119){
        return 6;
    }
    if(random >= 120 && random <= 129){
        return 7;
    }

    // Stage 3 returns
    if(random >= 130 && random <= 133){
        return 8;
    }
    if(random >= 134 && random <= 137){
        return 9;
    }
    if(random >= 138 && random <= 139){
        return 10;
    }

    // Every return is the ID of the photo
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

    // Generate Buttons
    readimagefile("Images\\spin-button.jpg", 650, 600, 500, 750);
    readimagefile("Images\\gamble-button.jpg", 50, 600, 200, 750);

    // Generate Bets
    readimagefile("Images\\bet-10.jpg",250,775,300,825);
    readimagefile("Images\\bet-20.jpg",310,775,360,825);
    readimagefile("Images\\bet-50.jpg",370,775,420,825);
    readimagefile("Images\\bet-100.jpg",430,775,480,825);
    readimagefile("Images\\bet-250.jpg",490,775,540,825);
    readimagefile("Images\\bet-500.jpg",550,775,600,825);
}

int main()
{
    initwindow(WIDTH, HEIGHT, "Shining Crown");
    srand(time(NULL));

    generateVisuals();

    for(int j = 0; j < SLOT_COLUMNS; j++){
        for(int i = 0; i < SLOT_ROWS; i++){
            int randomID = generateRandomPhotoID();

            VALUES_MATRIX[i][j] = randomID;
            addNode(SLOT_LISTS[j], randomID);
            readimagefile(IMAGES_PATH[randomID], 50+j*SLOT_PIXELSIZE, 100+i*SLOT_PIXELSIZE, 200+j*SLOT_PIXELSIZE, 250+i*SLOT_PIXELSIZE);
        }
        showList(SLOT_LISTS[j]);
    }

    getch();
    return 0;
}
