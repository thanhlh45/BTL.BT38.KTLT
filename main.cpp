#include <iostream>
#include "console.h"
#include "function.h"
#include "main.h"
using namespace std;
 
short trang, vitrichon, tongmuc;

int main()
{
    resizeConsole(ConsoleWidth, ConsoleHeight);//thay doi kich thuoc

    SetConsoleTitle(TEXT("MINESWEEPER"));// dat tieu de

    vetieudegame();

    Cursor(false);//an con tro.console
    vemenuchinh(0);
    trang = 1;
    xulysk();
    return 0;
}
