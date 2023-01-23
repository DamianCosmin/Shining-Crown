#include <graphics.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <time.h>

using namespace std;

const int WIDTH = 500;
const int HEIGHT = 500;
const char SLOTS_NAMES[12][20] = {"ORANGE", "PLUM", "CHERRY", "LEMON", "BELL", "WATERMELON", "GRAPES", "SEVEN", "DOLLAR SCATTER", "STAR SCATTER", "CROWN"};
const int SLOTS_NUMBER = 11;

struct Slot{
    int id;
    char name[20];
};

struct node{
    Slot slot;
    node *next;
};

void addNode(node *&p , int value){
    node *q, *add;

    add = new node;
    add -> slot.id = value;
    strcpy(add -> slot.name, SLOTS_NAMES[value]);
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
        cout << q -> slot.id << " " << q -> slot.name  << '\n';
        q = q -> next;
    }
}

int main()
{
    //initwindow(WIDTH, HEIGHT, "Shining Crown");
    //readimagefile("Images/shining-crown.jpg", 0, 0, 500, 500);
    //getch();
    node *firstNode = NULL;
    int number;

    srand(time(NULL));

    for(int i = 1; i <= SLOTS_NUMBER; i++){
        number = rand() % SLOTS_NUMBER;
        addNode(firstNode, number);
    }

    showList(firstNode);
    return 0;
}
