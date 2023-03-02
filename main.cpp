#include <graphics.h>
#include <winbgim.h>

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include <charconv>

#define SLOT_ROWS 3
#define SLOT_COLUMNS 5
#define SLOT_PIXELSIZE 150
#define CHIP_PIXELSIZE 50
#define MAX_DIGITS_MONEY 12
#define MAX_DIGITS_BET 5
#define MAX_DIGITS_LASTWIN 12
#define MAX_DIGITS_SPINS 1
#define MAX_GAMBLE_HISTORY 5
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

const char GAMBLE_IMAGES_PATH[5][100] = {
    "Images\\black-ace.jpg",
    "Images\\red-ace.jpg"
};

const char GAMBLE_CHIPS_PATH[5][100] = {
    "Images\\black-chip.jpg",
    "Images\\red-chip.jpg"
};

const int MULTIPLICATORS[20][5] = {
    // Stage 1
    0,0,1,3,15,
    0,0,1,3,15,
    0,0,1,3,15,
    0,0,1,3,15,
    0,0,2,4,20,
    //Stage 2
    0,0,4,12,70,
    0,0,4,12,70,
    0,1,5,25,500,
    //Stage 3
    0,0,5,20,100,
    0,0,200,0,0,
    0,0,0,0,0
};
int VALUES_MATRIX[3][5];
int MONEY = 5000;
int BET = 100;
int WIN = 0;
int LASTWIN = 0;
int GAMBLE_HISTORY[5];
int GAMBLE_SPINS = 5;
int STARS = 0;

char MONEY_CHAR[MAX_DIGITS_MONEY];
char BET_CHAR[MAX_DIGITS_BET];
char LASTWIN_CHAR[MAX_DIGITS_LASTWIN];
char SPINS_CHAR[MAX_DIGITS_SPINS];

bool canSpin = true;
bool isGambling = false;
bool generatedStar = false;

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

void deleteList(node *&p){
    node *q;
    while(p != NULL){
        q = p;
        p = p -> next;
        delete q;
    }
    p = NULL;
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

    /// Every return is the ID of the photo
}


void convertMoneyToString(int money){
    // Converts money amount(Int) to Char Array
    char money_aux[MAX_DIGITS_MONEY] = "";
    to_chars(money_aux, money_aux + MAX_DIGITS_MONEY, money);
    strcpy(MONEY_CHAR, money_aux);
    strcat(MONEY_CHAR, "$");
}

void convertBetToString(int bet){
    // Converts bet amount(Int) to Char Array
    char bet_aux[MAX_DIGITS_BET] = "";
    to_chars(bet_aux, bet_aux + MAX_DIGITS_BET, bet);
    strcpy(BET_CHAR, bet_aux);
    strcat(BET_CHAR, "$");
}

void convertLastwinToString(int lastwin){
    // Converts last win amount(Int) to Char Array
    char lastwin_aux[MAX_DIGITS_LASTWIN] = "";
    to_chars(lastwin_aux, lastwin_aux + MAX_DIGITS_LASTWIN, lastwin);
    strcpy(LASTWIN_CHAR, lastwin_aux);
    strcat(LASTWIN_CHAR, "$");
}

void convertGambleSpinsToString(int spinsLeft){
    // Converts gamble spins(Int) to Char Array
    char spins_aux[MAX_DIGITS_SPINS] = "";
    to_chars(spins_aux, spins_aux + MAX_DIGITS_SPINS, spinsLeft);
    strcpy(SPINS_CHAR, spins_aux);
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

    convertMoneyToString(MONEY);
    convertBetToString(BET);
    convertLastwinToString(LASTWIN);

    settextstyle(COMPLEX_FONT, 0, 2);

    outtextxy(275,625,"Current Money: ");
    outtextxy(450,625,MONEY_CHAR);

    outtextxy(275,665,"Current bet: ");
    outtextxy(450,665,BET_CHAR);

    outtextxy(275,705,"Last Win: ");
    outtextxy(450,705,LASTWIN_CHAR);

    // Generate Buttons
    readimagefile("Images\\spin-button.jpg", 650, 600, 800, 750);
    readimagefile("Images\\gamble-button.jpg", 50, 600, 200, 750);

    // Generate Bets
    readimagefile("Images\\bet-10.jpg",250,775,300,825);
    readimagefile("Images\\bet-20.jpg",310,775,360,825);
    readimagefile("Images\\bet-50.jpg",370,775,420,825);
    readimagefile("Images\\bet-100.jpg",430,775,480,825);
    readimagefile("Images\\bet-250.jpg",490,775,540,825);
    readimagefile("Images\\bet-500.jpg",550,775,600,825);
}

// Updates the values of money, bet and last win
void updateMoney(){
    MONEY_CHAR[0] = NULL;
    convertMoneyToString(MONEY);
    readimagefile("Images\\black-bar.jpg",450,625,580,645);
    outtextxy(450,625,MONEY_CHAR);
}

void updateBet(){
    BET_CHAR[0] = NULL;
    convertBetToString(BET);
    readimagefile("Images\\black-bar.jpg",450,665,580,685);
    outtextxy(450,665,BET_CHAR);
}

void updateLastwin(){
    LASTWIN_CHAR[0] = NULL;
    convertLastwinToString(LASTWIN);
    readimagefile("Images\\black-bar.jpg",450,705,580,725);
    outtextxy(450,705,LASTWIN_CHAR);
}

void updateGambleMoney(){
    LASTWIN_CHAR[0] = NULL;
    convertLastwinToString(LASTWIN);
    readimagefile("Images\\black-bar.jpg",100,135,250,200);
    outtextxy(100,135,"Gamble Money");
    outtextxy(100,160,LASTWIN_CHAR);
}

void updateGambleWin(){
    LASTWIN_CHAR[0] = NULL;
    convertLastwinToString(LASTWIN * 2);
    readimagefile("Images\\black-bar.jpg",615,135,765,200);
    outtextxy(615,135,"Gamble Win");
    outtextxy(615,160,LASTWIN_CHAR);
}

void updateGambleHistory(){
    cout << "History: ";
    for(int i = 0; i < MAX_GAMBLE_HISTORY; i++){
        readimagefile(GAMBLE_CHIPS_PATH[GAMBLE_HISTORY[i]], 300+i*CHIP_PIXELSIZE, 150, 350+i*CHIP_PIXELSIZE, 200);
        cout << GAMBLE_HISTORY[i] << " ";
    }
    cout << '\n';
}

void updateGambleSpins(){
    outtextxy(300,530,"Gamble Spins Left : ");
    convertGambleSpinsToString(GAMBLE_SPINS);
    outtextxy(540,530,SPINS_CHAR);
}

void winningsCalculator(int ID, int number){
    WIN += (BET * MULTIPLICATORS[ID][number-1]);
}

void checkLine1(){
    int temp_line[5] = {0}, temp_ID, cnt = 0, i = 0;

    temp_line[0] = VALUES_MATRIX[0][0];
    temp_line[1] = VALUES_MATRIX[0][1];
    temp_line[2] = VALUES_MATRIX[0][2];
    temp_line[3] = VALUES_MATRIX[0][3];
    temp_line[4] = VALUES_MATRIX[0][4];

    temp_ID = temp_line[0];
    while(i < SLOT_COLUMNS && temp_line[i] == temp_ID){
        if(temp_line[i] == temp_ID){
            cnt++;
        }
        i++;
    }

    winningsCalculator(temp_ID, cnt);
}

void checkLine2(){
    int temp_line[5] = {0}, temp_ID, cnt = 0, i = 0;

    temp_line[0] = VALUES_MATRIX[1][0];
    temp_line[1] = VALUES_MATRIX[1][1];
    temp_line[2] = VALUES_MATRIX[1][2];
    temp_line[3] = VALUES_MATRIX[1][3];
    temp_line[4] = VALUES_MATRIX[1][4];

    temp_ID = temp_line[0];
    while(i < SLOT_COLUMNS && temp_line[i] == temp_ID){
        if(temp_line[i] == temp_ID){
            cnt++;
        }
        i++;
    }

    winningsCalculator(temp_ID, cnt);
}

void checkLine3(){
    int temp_line[5] = {0}, temp_ID, cnt = 0, i = 0;

    temp_line[0] = VALUES_MATRIX[2][0];
    temp_line[1] = VALUES_MATRIX[2][1];
    temp_line[2] = VALUES_MATRIX[2][2];
    temp_line[3] = VALUES_MATRIX[2][3];
    temp_line[4] = VALUES_MATRIX[2][4];

    temp_ID = temp_line[0];
    while(i < SLOT_COLUMNS && temp_line[i] == temp_ID){
        if(temp_line[i] == temp_ID){
            cnt++;
        }
        i++;
    }

    winningsCalculator(temp_ID, cnt);
}

void checkLine4(){
    int temp_line[5] = {0}, temp_ID, cnt = 0, i = 0;

    temp_line[0] = VALUES_MATRIX[0][0];
    temp_line[1] = VALUES_MATRIX[1][1];
    temp_line[2] = VALUES_MATRIX[2][2];
    temp_line[3] = VALUES_MATRIX[1][3];
    temp_line[4] = VALUES_MATRIX[0][4];

    temp_ID = temp_line[0];
    while(i < SLOT_COLUMNS && temp_line[i] == temp_ID){
        if(temp_line[i] == temp_ID){
            cnt++;
        }
        i++;
    }

    winningsCalculator(temp_ID, cnt);
}

void checkLine5(){
    int temp_line[5] = {0}, temp_ID, cnt = 0, i = 0;

    temp_line[0] = VALUES_MATRIX[2][0];
    temp_line[1] = VALUES_MATRIX[1][1];
    temp_line[2] = VALUES_MATRIX[0][2];
    temp_line[3] = VALUES_MATRIX[1][3];
    temp_line[4] = VALUES_MATRIX[2][4];

    temp_ID = temp_line[0];
    while(i < SLOT_COLUMNS && temp_line[i] == temp_ID){
        if(temp_line[i] == temp_ID){
            cnt++;
        }
        i++;
    }

    winningsCalculator(temp_ID, cnt);
}

void checkLine6(){
    int temp_line[5] = {0}, temp_ID, cnt = 0, i = 0;

    temp_line[0] = VALUES_MATRIX[0][0];
    temp_line[1] = VALUES_MATRIX[0][1];
    temp_line[2] = VALUES_MATRIX[1][2];
    temp_line[3] = VALUES_MATRIX[2][3];
    temp_line[4] = VALUES_MATRIX[2][4];

    temp_ID = temp_line[0];
    while(i < SLOT_COLUMNS && temp_line[i] == temp_ID){
        if(temp_line[i] == temp_ID){
            cnt++;
        }
        i++;
    }

    winningsCalculator(temp_ID, cnt);
}

void checkLine7(){
    int temp_line[5] = {0}, temp_ID, cnt = 0, i = 0;

    temp_line[0] = VALUES_MATRIX[2][0];
    temp_line[1] = VALUES_MATRIX[2][1];
    temp_line[2] = VALUES_MATRIX[1][2];
    temp_line[3] = VALUES_MATRIX[0][3];
    temp_line[4] = VALUES_MATRIX[0][4];

    temp_ID = temp_line[0];
    while(i < SLOT_COLUMNS && temp_line[i] == temp_ID){
        if(temp_line[i] == temp_ID){
            cnt++;
        }
        i++;
    }

    winningsCalculator(temp_ID, cnt);
}

void checkLine8(){
    int temp_line[5] = {0}, temp_ID, cnt = 0, i = 0;

    temp_line[0] = VALUES_MATRIX[1][0];
    temp_line[1] = VALUES_MATRIX[2][1];
    temp_line[2] = VALUES_MATRIX[2][2];
    temp_line[3] = VALUES_MATRIX[2][3];
    temp_line[4] = VALUES_MATRIX[1][4];

    temp_ID = temp_line[0];
    while(i < SLOT_COLUMNS && temp_line[i] == temp_ID){
        if(temp_line[i] == temp_ID){
            cnt++;
        }
        i++;
    }

    winningsCalculator(temp_ID, cnt);
}

void checkLine9(){
    int temp_line[5] = {0}, temp_ID, cnt = 0, i = 0;

    temp_line[0] = VALUES_MATRIX[1][0];
    temp_line[1] = VALUES_MATRIX[0][1];
    temp_line[2] = VALUES_MATRIX[0][2];
    temp_line[3] = VALUES_MATRIX[0][3];
    temp_line[4] = VALUES_MATRIX[1][4];

    temp_ID = temp_line[0];
    while(i < SLOT_COLUMNS && temp_line[i] == temp_ID){
        if(temp_line[i] == temp_ID){
            cnt++;
        }
        i++;
    }

    winningsCalculator(temp_ID, cnt);
}

void checkLine10(){
    int temp_line[5] = {0}, temp_ID, cnt = 0, i = 0;

    temp_line[0] = VALUES_MATRIX[0][0];
    temp_line[1] = VALUES_MATRIX[1][1];
    temp_line[2] = VALUES_MATRIX[1][2];
    temp_line[3] = VALUES_MATRIX[1][3];
    temp_line[4] = VALUES_MATRIX[0][4];

    temp_ID = temp_line[0];
    while(i < SLOT_COLUMNS && temp_line[i] == temp_ID){
        if(temp_line[i] == temp_ID){
            cnt++;
        }
        i++;
    }

    winningsCalculator(temp_ID, cnt);
}

void checkAllLines(){
    checkLine1();
    checkLine2();
    checkLine3();
    checkLine4();
    checkLine5();
    checkLine6();
    checkLine7();
    checkLine8();
    checkLine9();
    checkLine10();

    if(WIN > 0){
        LASTWIN = WIN;
        updateLastwin();
    }
}


void spin(){
    if(MONEY >= BET){
        MONEY += WIN;
        WIN = 0;
        MONEY -= BET;
        updateMoney();

        readimagefile("Images\\black-background.jpg",50,100,800,550);
        delay(100);

        for(int j = 0; j < SLOT_COLUMNS; j++){
            deleteList(SLOT_LISTS[j]);
        }

        for(int j = 0; j < SLOT_COLUMNS; j++){
            for(int i = 0; i < SLOT_ROWS; i++){
                int randomID = generateRandomPhotoID();
                //checkStars(randomID);

                VALUES_MATRIX[i][j] = randomID;
                addNode(SLOT_LISTS[j], randomID);
                readimagefile(IMAGES_PATH[randomID], 50+j*SLOT_PIXELSIZE, 100+i*SLOT_PIXELSIZE, 200+j*SLOT_PIXELSIZE, 250+i*SLOT_PIXELSIZE);
            }
            delay(100);
            showList(SLOT_LISTS[j]);
        }

        checkAllLines();
    }
    else{
        cout << "Not enough money!" << '\n';
    }
}

void generateRandomGamble(int value){
    int randomGamble = rand() % 2;
    readimagefile(GAMBLE_IMAGES_PATH[randomGamble],325,225,525,525);

    for(int i = MAX_GAMBLE_HISTORY; i > 0; i--){
        GAMBLE_HISTORY[i] = GAMBLE_HISTORY[i-1];
    }
    GAMBLE_HISTORY[0] = randomGamble;
    updateGambleHistory();

    GAMBLE_SPINS--;
    updateGambleSpins();

    if(randomGamble == value){
        cout << "Doubled" << '\n';
        WIN *= 2;
        LASTWIN = WIN;
        updateGambleMoney();
        updateGambleWin();
        delay(750);
        readimagefile("Images//back-card.jpg",325,225,525,525);
    }
    else{
        cout << "Lost the money" << '\n';
        isGambling = false;
        canSpin = true;
        WIN = 0;
        LASTWIN = WIN;
        updateGambleMoney();
        updateGambleWin();
        updateLastwin();
        delay(750);

        // Load old images
        readimagefile("Images\\black-background.jpg",50,100,800,550);
        for(int i = 0; i < SLOT_ROWS; i++){
            for(int j = 0; j < SLOT_COLUMNS; j++){
                readimagefile(IMAGES_PATH[VALUES_MATRIX[i][j]], 50+j*SLOT_PIXELSIZE, 100+i*SLOT_PIXELSIZE, 200+j*SLOT_PIXELSIZE, 250+i*SLOT_PIXELSIZE);
            }
        }
    }
}

void gamble(){
    canSpin = false;
    isGambling = true;
    int mouseX = 0, mouseY = 0;
    GAMBLE_SPINS = 5;

    readimagefile("Images\\black-background.jpg",50,100,800,550);

    // Gamble Text
    settextstyle(COMPLEX_FONT, 0, 2);

    outtextxy(100,135,"Gamble Money");
    outtextxy(100,160,LASTWIN_CHAR);

    updateGambleWin();
    outtextxy(615,135,"Gamble Win");
    outtextxy(615,160,LASTWIN_CHAR);

    //outtextxy(300,530,"Gamble Spins Left : 5");
    updateGambleSpins();

    outtextxy(380,115,"History");
    updateGambleHistory();

    // Buttons
    readimagefile("Images\\back-card.jpg",325,225,525,525);
    readimagefile("Images\\black-chip.jpg",100,300,250,450);
    readimagefile("Images\\red-chip.jpg",600,300,750,450);

    while(isGambling){
        getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

        if(((GAMBLE_SPINS == 0)|| (mouseX >= 50 && mouseX <= 200 && mouseY >= 600 && mouseY <= 750) || (GetAsyncKeyState('C') & 0x8000) || (GetAsyncKeyState(' ') & 0x8000))){
            cout << "Exit Gamble Mode!" << '\n';
            isGambling = false;
            canSpin = true;
            MONEY += WIN;
            LASTWIN = WIN;
            WIN = 0;
            updateMoney();
            updateLastwin();

            // Load old images
            readimagefile("Images\\black-background.jpg",50,100,800,550);
            for(int i = 0; i < SLOT_ROWS; i++){
                for(int j = 0; j < SLOT_COLUMNS; j++){
                    readimagefile(IMAGES_PATH[VALUES_MATRIX[i][j]], 50+j*SLOT_PIXELSIZE, 100+i*SLOT_PIXELSIZE, 200+j*SLOT_PIXELSIZE, 250+i*SLOT_PIXELSIZE);
                }
            }
        }

        if((mouseX >= 100 && mouseX <= 250 && mouseY >= 300 && mouseY <= 450) || (GetAsyncKeyState(VK_LEFT) & 0x8000)){
            cout << "Black Gamble" << '\n';
            generateRandomGamble(0);
        }

        if((mouseX >= 600 && mouseX <= 750 && mouseY >= 300 && mouseY <= 450) || (GetAsyncKeyState(VK_RIGHT) & 0x8000)){
            cout << "Red Gamble" << '\n';
            generateRandomGamble(1);
        }
    }
}

bool canGamble(){
    return (WIN > 0 && WIN < 35 * BET) ? true : false;
}

void detectMouseClicks(){
    int mouseX = 0, mouseY = 0;
    getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

    // Spin
    if(canSpin == true && ((mouseX >= 650 && mouseX <= 800 && mouseY >= 600 && mouseY <= 750) || (GetAsyncKeyState(' ') & 0x8000))){
        cout << "Spin!" << '\n';
        spin();
    }

    // Gamble
    if(canGamble() && ((mouseX >= 50 && mouseX <= 200 && mouseY >= 600 && mouseY <= 750) || (GetAsyncKeyState('G') & 0x8000))){
        cout << "Gamble!" << '\n';
        gamble();
    }

    // Bets
    if(mouseX >= 250 && mouseX <= 300 && mouseY >= 775 && mouseY <= 825){
        BET = 10;
        updateBet();
        cout << "Set bet to 10$" << '\n';
    }
    if(mouseX >= 310 && mouseX <= 360 && mouseY >= 775 && mouseY <= 825){
        BET = 20;
        updateBet();
        cout << "Set bet to 20$" << '\n';
    }
    if(mouseX >= 370 && mouseX <= 420 && mouseY >= 775 && mouseY <= 825){
        BET = 50;
        updateBet();
        cout << "Set bet to 50$" << '\n';
    }
    if(mouseX >= 430 && mouseX <= 480 && mouseY >= 775 && mouseY <= 825){
        BET = 100;
        updateBet();
        cout << "Set bet to 100$" << '\n';
    }
    if(mouseX >= 490 && mouseX <= 540 && mouseY >= 775 && mouseY <= 825){
        BET = 250;
        updateBet();
        cout << "Set bet to 250$" << '\n';
    }
    if(mouseX >= 550 && mouseX <= 600 && mouseY >= 775 && mouseY <= 825){
        BET = 500;
        updateBet();
        cout << "Set bet to 500$" << '\n';
    }
}

bool gameCondition(){
    // Money must be between the minimum bet and max INT range (2 Billion)
    if(MONEY >= 10 && MONEY <= 2000000000){
        return true;
    }
    return false;
}

int main()
{
    initwindow(WIDTH, HEIGHT, "Shining Crown");
    srand(time(NULL));

    generateVisuals();

    for(int i = 0; i < MAX_GAMBLE_HISTORY; i++){
        GAMBLE_HISTORY[i] = -1;
    }

    while(gameCondition()){
        detectMouseClicks();
    }

    while(MONEY < 10)
    {
        readimagefile("Images\\lose-screen.jpg",0,0,850,850);
    }

    getch();
    return 0;
}
