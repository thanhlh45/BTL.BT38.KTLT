#pragma once
#include <iostream>
#include <ctime>
using namespace std;

#define ConsoleWidth 80
#define ConsoleHeight 35

#define ClickTrai 0x5A
#define ClickPhai 0x58

struct cautrucbang
{
	short Sdong = 0;
	short Scot = 0;
	short Sbom = 0;
	short SsoOdamo = 0;
	short Ssoco = 0;
};
struct cautrucO
{
	bool Bcobom = false;
	bool Bdamo = false;
	bool Bcamco = false;
	short Scobom = 0;
};
extern short trang, vitrichon, tongmuc;