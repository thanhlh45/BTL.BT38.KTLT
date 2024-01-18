#include "main.h"
#include "function.h"
#include "console.h"
#include <iostream>
#include <ctime>
using namespace std;
cautrucbang CTBang;
cautrucO** CTO;
//vitri con tro hien tai
COORD Cvitricontro;
//su dung phim
bool Bsudungphim = false;

//toa do ve bang
short toadobangx;
short toadobangy;
//cap nhat trang thai choi game
bool trangthaichoigame = false;



void taomang2chieu()
{
	CTO = new cautrucO * [CTBang.Sdong];
	for (int i = 0; i < CTBang.Sdong; ++i)
	{
		CTO[i] = new cautrucO[CTBang.Scot];
	}
}
void xoamang2chieu()
{
	for (int i = 0; i < CTBang.Sdong; ++i)
	{
		delete[] CTO[i];
	}
	delete[] CTO;
}
void toadobang()
{
	toadobangx = ((ConsoleWidth / 2) - (CTBang.Sdong));
	toadobangy = (((ConsoleHeight - 6) - CTBang.Scot) / 2) + 3;
}
void khoitao(short Sdong, short Scot, short Sbom)
{
	CTBang.Sdong = Sdong;
	CTBang.Scot = Scot;
	CTBang.Sbom = Sbom;
	CTBang.SsoOdamo = 0;
	CTBang.Ssoco = 0;

	taomang2chieu();
	rdbom();
	toadobang();
	Cvitricontro = { 0,0 };
	trangthaichoigame = true;
	Vebang();
	vetrangthaichoigame(1, 0, 0);
	//xuatbom();
}
short toadoX(short Sx)//toa do x ve bang
{
	return((Sx * 2) + toadobangx);
}

short toadoY(short Sy)//toa do y ve bang
{
	return(Sy + toadobangy);
}
void VeO(short Sx, short Sy, short Skieu)
{
	switch (Skieu)
	{
	case 0://rong xanh la
		setColorBGTextXY(toadoX(Sx), toadoY(Sy), 0, 10, "  ");
		break;
	case 1://mau xanh duong
		setColorBGTextXY(toadoX(Sx), toadoY(Sy), 9, 15, "1 ");
		break;
	case 2:
		setColorBGTextXY(toadoX(Sx), toadoY(Sy), 2, 15, "2 ");
		break;
	case 3:
		setColorBGTextXY(toadoX(Sx), toadoY(Sy), 12, 15, "3 ");
		break;
	case 4:
		setColorBGTextXY(toadoX(Sx), toadoY(Sy), 1, 15, "4 ");
		break;
	case 5:
		setColorBGTextXY(toadoX(Sx), toadoY(Sy), 4, 15, "5 ");
		break;
	case 6:
		setColorBGTextXY(toadoX(Sx), toadoY(Sy), 2, 15, "6 ");
		break;
	case 7:
		setColorBGTextXY(toadoX(Sx), toadoY(Sy), 0, 15, "7 ");
		break;
	case 8:
		setColorBGTextXY(toadoX(Sx), toadoY(Sy), 13, 15, "8 ");
		break;
	case 9://bom
		setColorBGTextXY(toadoX(Sx), toadoY(Sy), 0, 12, "B ");
		break;
	case 10:// o chan
		setColorBGTextXY(toadoX(Sx), toadoY(Sy), 0, 8, "  ");
		break;
	case 11:// o le
		setColorBGTextXY(toadoX(Sx), toadoY(Sy), 0, 7, "  ");
		break;
	case 12:
		setColorBGTextXY(toadoX(Sx) + 1, toadoY(Sy), 0, 13, " ");
		break;
	case 13://cam co
		setColorBGTextXY(toadoX(Sx), toadoY(Sy), 12, 14, "P ");
		break;
	case 14://cam co sai
		setColorBGTextXY(toadoX(Sx), toadoY(Sy), 15, 6, "Px");
		break;
	case 15://cam co dung
		setColorBGTextXY(toadoX(Sx), toadoY(Sy), 12, 14, "B ");
		break;

	}
}
void Vebang()
{
	for (int i = 0; i < CTBang.Sdong; ++i)
	{
		for (int j = 0; j < CTBang.Scot; ++j)
		{

			if (CTO[i][j].Bcamco)
				VeO(j, i, 13);
			else if (CTO[i][j].Scobom)
				VeO(j, i, CTO[i][j].Scobom);
			else if (CTO[i][j].Bdamo)//o rong
				VeO(j, i, 0);
			else if ((i + j) % 2)
				VeO(j, i, 11);
			else
				VeO(j, i, 10);
			if (Bsudungphim)
				VeO(Cvitricontro.X, Cvitricontro.Y, 12);
		}
	}
}
void rdbom()
{
	short Sbom = CTBang.Sbom;
	short Si, Sj;//si la vi tri dong, sj la vi tri cot random bom
	srand(time(NULL));// reset time
	while (Sbom)
	{
		//ct random trong khoang x,y thi rand()&(y-x+1)+x
		Si = rand() % CTBang.Sdong;
		Sj = rand() % CTBang.Scot;
		if (CTO[Si][Sj].Bcobom)
			continue;
		CTO[Si][Sj].Bcobom = true;
		--Sbom;//cap nhat lai so luong bom
	}
}
void clickphai(short SX, short SY)//cam co
{
	if (!CTO[SX][SY].Bdamo)
	{
		if (CTO[SX][SY].Bcamco)
		{
			CTO[SX][SY].Bcamco = false;
			CTBang.Ssoco--;
		}
		else
		{
			CTO[SX][SY].Bcamco = true;
			CTBang.Ssoco++;
		}
	}
	Vebang();
}
short demblancan(short SX, short SY)
{
	short Sdem = 0;
	for (int i = SX - 1; i <= SX + 1; ++i)
	{
		for (int j = SY - 1; j <= SY + 1; ++j)
		{
			//xet cac vi tri khong hop le
			if (i < 0 || i >= CTBang.Sdong || j < 0 || j >= CTBang.Scot || (i == SX && j == SY))
				continue;
			//xet xem o co bom hay khong.co tang len 1
			if (CTO[i][j].Bcobom)
				++Sdem;
		}
	}
	return Sdem;
}
void moO(short SX, short SY)
{
	if (!CTO[SX][SY].Bdamo && !CTO[SX][SY].Bcamco)
	{
		CTO[SX][SY].Bdamo = true;
		if (CTO[SX][SY].Bcobom)//o co bom
			thua();//=>thua
		else
		{
			CTBang.SsoOdamo++;
			short Ssobomlancan = demblancan(SX, SY);
			if (Ssobomlancan)// co bom lan can
				CTO[SX][SY].Scobom = Ssobomlancan;
			else// o rong
			{
				//duyet cac o lan can va goi de quy
				for (int i = SX - 1; i <= SX + 1; ++i)
				{
					for (int j = SY - 1; j <= SY + 1; ++j)
					{
						//xet cac vi tri khong hop le
						if (i < 0 || i >= CTBang.Sdong || j < 0 || j >= CTBang.Scot || (i == SX && j == SY))
							continue;
						//goi de quy
						moO(i, j);
					}
				}
			}
		}
	}
}
bool thongke()
{
	if ((CTBang.SsoOdamo + CTBang.Sbom) == (CTBang.Sdong * CTBang.Scot))
		return true;
	return false;
}
void clicktrai(short SX, short SY)
{
	if (!CTO[SX][SY].Bdamo && !CTO[SX][SY].Bcamco)
	{
		moO(SX, SY);
		if (trangthaichoigame)
		{
			Vebang();
			if (thongke())
				thang();
		}
	}
}
void thang()
{
	trangthaichoigame = false;
	xoamang2chieu();//giai phong con tro
	trang = 5;
	deleteRow(4, 1);
	vetrangthaichoigame(2, 2, 0);//cap nhat trang thai la thang
}
void thua()
{
	//hien bom an va kiem tra co dung hay sai
	for (int i = 0; i < CTBang.Sdong; ++i)
	{
		for (int j = 0; j < CTBang.Scot; ++j)
		{
			if (CTO[i][j].Bcamco)//co cam co
			{
				if (CTO[i][j].Bcobom)
					VeO(j, i, 15);//cam co dung.
				else
					VeO(j, i, 14);//cam co sai.
			}
			else//khong co cam co
			{
				if (CTO[i][j].Bcobom)//co bom thi hien bom
					VeO(j, i, 9);//hien bom an

			}
		}
	}
	trangthaichoigame = false;
	xoamang2chieu();//giai phong con tro
	trang = 4;
	deleteRow(4, 1);
	vetrangthaichoigame(3, 3, 0);//cap nhattrang thai thua
}
//y tuong xu ly menu
/*1. menu chinh
* 2.menu cap do
* 3.trang choi game
* 4 trang thua
* 5. trang thang
* 6 trang luu game
*/
void xulyphim(KEY_EVENT_RECORD key)
{
	if (key.bKeyDown)// co nhan phim
	{
		switch (key.wVirtualKeyCode)
		{
		case VK_UP://mui ten len
			switch (trang)
			{
			case 1://menu chinh
				if (tongmuc == 4)
				{
					if (vitrichon == 0)
						vitrichon = tongmuc - 1;
					else
						vitrichon -= 1;
					vemenuchinh(vitrichon);
				}
				break;
			case 2://menu lv
				if (tongmuc == 4)
				{
					if (vitrichon == 0)
						vitrichon = tongmuc - 1;
					else
						vitrichon -= 1;
					vemenulv(vitrichon);
				}
				break;
			case 3://trang choi game
				if (trangthaichoigame = true)
				{
					Bsudungphim = true;
					Cvitricontro.Y = ((Cvitricontro.Y == 0) ? CTBang.Sdong - 1 : Cvitricontro.Y - 1);
					Vebang();
				}
				break;
			case 4://trang thua
				vetrangthaichoigame(3, 3, (vitrichon == 0) ? 1 : 0);
				break;
			case 5://trang thang
				vetrangthaichoigame(2, 2, (vitrichon == 0) ? 1 : 0);
				break;
			}
			break;
		case VK_DOWN://mui ten xuong
			switch (trang)
			{
			case 1://menu chinh
				if (tongmuc == 4)
				{
					if (vitrichon == tongmuc - 1)
						vitrichon = 0;
					else
						vitrichon += 1;
					vemenuchinh(vitrichon);
				}
				break;
			case 2://menu lv
				if (tongmuc == 4)
				{
					if (vitrichon == tongmuc - 1)
						vitrichon = 0;
					else
						vitrichon += 1;
					vemenulv(vitrichon);
				}
				break;
			case 3://trang choi game
				if (trangthaichoigame = true)
				{
					Bsudungphim = true;
					Cvitricontro.Y = ((Cvitricontro.Y == CTBang.Sdong - 1) ? 0 : Cvitricontro.Y + 1);
					Vebang();
				}
				break;
			case 4://trang thua
				vetrangthaichoigame(3, 3, (vitrichon == 0) ? 1 : 0);
				break;
			case 5://trang thang
				vetrangthaichoigame(2, 2, (vitrichon == 0) ? 1 : 0);
				break;
			}
			break;
			break;
		case VK_LEFT://mui ten trai
			if (trangthaichoigame = true)
			{
				Bsudungphim = true;
				Cvitricontro.X = ((Cvitricontro.X == 0) ? CTBang.Scot - 1 : Cvitricontro.X - 1);
				Vebang();
			}
			break;
		case VK_RIGHT://mui ten phai
			if (trangthaichoigame = true)
			{
				Bsudungphim = true;
				Cvitricontro.X = ((Cvitricontro.X == CTBang.Scot - 1) ? 0 : Cvitricontro.X + 1);
				Vebang();
			}
			break;
		case VK_RETURN://phim enter
			switch (trang)
			{
			case 1://menu chinh
				if (vitrichon == 0)
				{
					trang = 2;
					deleteRow(3, 26);
					vemenulv(0);
				}
				else if (vitrichon == 1)//trang bang diem
				{

				}
				else if (vitrichon == 2)//trang thong tin
				{

				}
				else
				{
					exit(0);
				}
				break;
			case 2://menu lv
				if (vitrichon == 0)//de
				{
					trang = 3;//cap nhat lai trang dang choi game
					deleteRow(3, 26);
					khoitao(9, 9, 10);
				}
				else if (vitrichon == 1)//trung binh
				{
					trang = 3;//cap nhat lai trang dang choi game
					deleteRow(3, 26);
					khoitao(16, 16, 40);
				}
				else if (vitrichon == 2)//kho
				{
					trang = 3;//cap nhat lai trang dang choi game
					deleteRow(3, 26);
					khoitao(24, 24, 99);
				}
				else
				{
					trang = 1;//cap nhat lai la menuchinh
					deleteRow(3, 26);
					vemenuchinh(0);
				}
				break;
			case 4://trang thua
				if (vitrichon)
				{
					trang = 1;
					deleteRow(3, 26);
					vemenuchinh(0);
				}
				else
				{
					trang = 3;//trang choi game
					deleteRow(3, 26);
					khoitao(CTBang.Sdong, CTBang.Scot, CTBang.Sbom);
				}
				break;
			case 5://trang thang
				break;
			case 6://trang luu game
				if (vitrichon)
				{
					trang = 1;//tro ve menu chinh
					deleteRow(3, 26);
					vemenuchinh(0);
				}
				else
				{
					//luu game

				}
				break;
			}
			break;
		case VK_ESCAPE://phim esc
			switch (trang)
			{
			case 1://menu chinh
				exit(0);
				break;
			case 2://menu lv
				trang = 1;//cap nhat lai menu chinh
				deleteRow(4, 10);
				vemenuchinh(0);
				break;
			case 3:
				trang = 6;
				vetrangthaichoigame(1, 1, 0);
				break;
			case 4://trang thua
				break;
			case 5://trang thang
				trang = 2;
				deleteRow(3, 26);
				vemenulv(0);
				break;
			}
			break;
		case ClickTrai://phim z mo o
			//cout << "z" << endl;
			clicktrai(Cvitricontro.Y, Cvitricontro.X);
			break;
		case ClickPhai://phim x cam co
			//cout << "x" << endl;
			clickphai(Cvitricontro.Y, Cvitricontro.X);
			break;
		}
	}
}
void xulysk()
{
	while (1)
	{
		DWORD DWNumberOfEvents = 0;// luuw lai sk hien tai
		DWORD DWNumberOfEventsRead = 0;//luu lai so luong sk da dc loc
		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE);//thiet bi dau vao
		GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOfEvents);//dat su kien dau vao

		if (DWNumberOfEvents)
		{
			INPUT_RECORD* IREventBuffer = new INPUT_RECORD[DWNumberOfEvents];
			ReadConsoleInput(HConsoleInput, IREventBuffer, DWNumberOfEvents, &DWNumberOfEventsRead);
			// cahy vong lap doc sk
			for (DWORD i = 0; i < DWNumberOfEvents; ++i)
			{
				if (IREventBuffer[i].EventType == KEY_EVENT)//su kien phim
				{
					xulyphim(IREventBuffer[i].Event.KeyEvent);
				}
			}
		}

	}
}
//thiet ke
void vetieudegame()
{
	short i;
	for (i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 61);
	}
	setColorBGTextXY((ConsoleWidth / 2) - 5, 1, 4, 0, "MINESWEEPER\n");
	setColorBGTextXY((ConsoleWidth / 2) - 2, 2, 5, 0, "BT38\n");
	setColor(7);
	for (i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 61);
	}
	gotoXY(1, 15);
	for (int i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 61);
	}
	gotoXY(3, 16);
	printf("CAC THANH VIEN.");
	gotoXY(3, 17);
	printf("Le Hoang Thanh");
	gotoXY(3, 18);
	printf("Nguyen Gia Han");
	gotoXY(3, 19);
	printf("Vo Nguyen Truong Giang");
	
	//in hai hang doc
	for (int i = 0; i < ConsoleHeight; ++i)
	{
		gotoXY(0, i);
		printf("%c", 124);

		gotoXY(ConsoleWidth - 1, i);
		printf("%c", 124);
	}

	//in hang ngang duoi cung
	gotoXY(0, ConsoleHeight);
	for (int i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 61);
	}

}
void vetrangthaichoigame(short trangthai, short chedo, short index)
{
	vitrichon = index;
	tongmuc = 2;
	setColorBGTextXY(2, 3, 15, 0, "Ban do: %d * %d", CTBang.Sdong, CTBang.Scot);
	setColorBGTextXY(2, 4, 15, 0, "So bom: %d", CTBang.Sbom);
	//ve menu thang thua
	LPCSTR newchedo;
	if (chedo == 1)
	{
		newchedo = " SaveGame ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(newchedo) / 2), 3, 15, ((index == 0) ? 2 : 0), newchedo);
	}
	if (chedo == 2)
	{
		newchedo = " SaveName ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(newchedo) / 2), 3, 15, ((index == 0) ? 2 : 0), newchedo);
	}
	if (chedo == 3)
	{
		newchedo = " Restart ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(newchedo) / 2) + 1, 3, 15, ((index == 0) ? 2 : 0), newchedo);
	}
	if (chedo >= 1)
	{
		newchedo = " Exit ";
		setColorBGTextXY((ConsoleWidth / 2) - (strlen(newchedo) / 2), 4, 15, ((index == 1) ? 2 : 0), newchedo);

	}
	//
	if (trangthai == 1)//dang choi game
		setColorBGTextXY(ConsoleWidth - 22, 4, 15, 0, "Trang thai: %s", "Dang choi");
	if (trangthai == 2)//thang
		setColorBGTextXY(ConsoleWidth - 22, 4, 14, 0, "Trang thai: %s", "Thang");
	if (trangthai == 3)//thua
		setColorBGTextXY(ConsoleWidth - 22, 4, 12, 0, "Trang thai: %s", "Thua");
}
void vemenuchinh(short index)
{
	//cap nhat lai vi tri dang chon va tong muc cua menu
	vitrichon = index;
	tongmuc = 4;
	//ve menu
	LPCSTR newgame = " New Game ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(newgame) / 2) + 1, 6, 15, ((index == 0) ? 2 : 0), newgame);
	newgame = "  Stats  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(newgame) / 2), 7, 15, ((index == 1) ? 2 : 0), newgame);
	newgame = "  Rules  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(newgame) / 2), 8, 15, ((index == 2) ? 2 : 0), newgame);
	newgame = "  Exit   ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(newgame) / 2), 9, 15, ((index == 3) ? 2 : 0), newgame);
}
void vemenulv(short index)
{
	vitrichon = index;
	tongmuc = 4;
	//ve menu
	LPCSTR newgame = "  Easy  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(newgame) / 2), 6, 15, ((index == 0) ? 2 : 0), newgame);
	newgame = "  Medium  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(newgame) / 2), 7, 15, ((index == 1) ? 2 : 0), newgame);
	newgame = "  Hard  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(newgame) / 2), 8, 15, ((index == 2) ? 2 : 0), newgame);
	newgame = "  Back  ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(newgame) / 2), 9, 15, ((index == 3) ? 2 : 0), newgame);
}