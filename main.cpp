#include "Graphics Libraries\graphics.h"
using namespace std;

const int WIDTH = 500;
const int HEIGHT = 500;

int main()
{
    initwindow(WIDTH, HEIGHT, "Shining Crown");
    readimagefile("Images/shining-crown.jpg", 0, 0, 500, 500);
    getch();
    return 0;
}
