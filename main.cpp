#include <iostream>
#include <string>
#include <ctime>
using namespace std;

#include <Windows.h>
#include <conio.h>

// Plansza do gry w kolko i krzyzyk
enum BoardState { Empty, Field_X, Field_O };

unsigned int tab[3][3];

// Imie gracza pierwszego
string player01 = " ";

// Imie gracza drugiego
string player02 = " ";
char playerOneSign = ' ';
char playerTwoSign = ' ';

int players;
int choose;
int tmp;

int win = 0;
int gameState = 0;
int score01 = 0; // Punkty gracza pierwszego
int score02 = 0; // Punkty gracza drugiego

/* Funkcje */
void MainMenu();
void MenuChoose(int choose);

void Start();
int WhichPlayerStart();
int StartGame();
void DrawBoard();
void PlayerInput(int players);
void Field(int x, int y);
int CheckResult();
void Result(int win);
void Loading();
void Options();
void Exits();
void Clear();

int main()
{	
	// Tytul gry
	Start();

	// Ladowanie gry
	Loading();

	// Menu glowne
	MainMenu();

	system("pause");

	return 0;
}

void Start()
{
	Clear();
	cout << "Zapraszam do gry w kolko i krzyzyk\n";
	Sleep(1000);
}

void MainMenu()
{
	Clear();
	cout << "===== Menu glowne ================================\n";
	cout << "==================================================\n";
	cout << "= 1. Nowa gra                                    =\n";
	cout << "= 2. Opcje                                       =\n";
	cout << "= 3. Wyjscie                                     =\n";
	cout << "==================================================\n";
	cin >> choose;

	MenuChoose(choose);
}

void MenuChoose(int choose)
{
	Clear();
	switch (choose)
	{
	case 1:
		win = 0;
		// Start gry
		StartGame();
		players = WhichPlayerStart();
		while (true)
		{
			// Rysowanie planszy
			DrawBoard();
			PlayerInput(players);
			win = CheckResult();
			// Sprawdzenie czy win (wygrana) wynosi 1. Jezeli tak to wyswietlamy wyniki gry w kolko i krzyzyk
			if (win != 0)
			{
				break;
			}
		}
		Result(win);
		players++;
		break;
	case 2:
		Options();
		break;
	case 3:
		Exits();
		break;
	}
}

int StartGame()
{
	cout << "Prosze podac imie gracza pierwszego: ";
	cin >> player01;
	cin.ignore();
	cout << "Prosze podac imie gracza drugiego: ";
	cin >> player02;
	cin.ignore();

	return 1;
}

int WhichPlayerStart()
{
	cout << "Ktory gracz zaczyna gre:\n";
	cout << "1. " << player01 << endl;
	cout << "2. " << player02 << endl;
	cin >> players;

	return players;
}

void DrawBoard()
{
	for (int x = 0; x < 3; x++)
	{
		cout << "\t";
		for (int y = 0; y < 3; y++)
		{
			//cout<<tab[x][y];
			Field(x, y);
			if (y < 2)cout << "|";
		}
		cout << "\n";
		if (x < 2)cout << "\t-----\n";
	}
	cout << "\n\n";
}

void PlayerInput(int players)
{
	// Blad uzytkownika przy podawaniu pol na planszy
	int errorMove = 0;
	//int boardSize;
	int playerOneChoose = 0;
	int playerTwoChoose = 0;

	int row = 3;
	int column = 3;

	while (errorMove != 1)
	{
		players = 1;
		if (players == 1)
		{
			cout << player01 << " wybierz pole:";
			cin >> playerOneChoose;
			DrawBoard();

			if (playerOneChoose < 1 || playerOneChoose > 9)
			{
				cout << "Brak podanego pola. Wybierz jeszcze raz\n";
				cin >> playerOneChoose;
				errorMove = 0;
				DrawBoard();
			}
			else
			{
				/*A*/if (playerOneChoose < 4 && playerOneChoose > 0) { column = (playerOneChoose - 1); row = 2; errorMove = 1; }
				/*B*/if (playerOneChoose < 7 && playerOneChoose > 3) { column = (playerOneChoose - 4); row = 1; errorMove = 1; }
				/*C*/if (playerOneChoose < 10 && playerOneChoose > 6) { column = (playerOneChoose - 7); row = 0; errorMove = 1; }

				if (tab[row][column] != 0)
				{
					cout << "Podane pole jest zajete\n";
					cin >> playerOneChoose;
					cout << "X";
					errorMove = 0;
					DrawBoard();
				}
			}
		}
 
		players = 2;

		if (players == 2)
		{
			cout << player02 << " wybierz pole:";
			cin >> playerTwoChoose;
			cout << "O";
			DrawBoard();

			if (playerTwoChoose < 1 || playerTwoChoose > 9)
			{
				cout << "Brak podanego pola. Wybierz jeszcze raz\n";
				cin >> playerTwoChoose;
				cout << "O";
				errorMove = 0;
				DrawBoard();
			}
			else
			{
				/*A*/if (playerTwoChoose < 4 && playerTwoChoose > 0) { column = (playerTwoChoose - 1); row = 2; errorMove = 1; }
				/*B*/if (playerTwoChoose < 7 && playerTwoChoose > 3) { column = (playerTwoChoose - 4); row = 1; errorMove = 1; }
				/*C*/if (playerTwoChoose < 10 && playerTwoChoose > 6) { column = (playerTwoChoose - 7); row = 0; errorMove = 1; }

				if (tab[row][column] != 0)
				{
					cout << "Podane pole jest zajete\n";
					cin >> playerTwoChoose;
					cout << "O";
					errorMove = 0;
					DrawBoard();
				}
			}
		}
	}
}

void Field(int x, int y)
{
	// Ustawienie potrzebnych zmiennych
	if (tab[x][y] == 0) cout << " ";
	if (tab[x][y] == 1) cout << "X";
	if (tab[x][y] == 2) cout << "O";
}

int CheckResult()
{
	for (int c = 0; c < 3; c++) 
	{
		if (((tab[c][0] == 1) && (tab[c][1] == 1) && (tab[c][2] == 1)) || ((tab[c][0] == 2) && (tab[c][1] == 2) && (tab[c][2] == 2)))
			return 1;
		if (((tab[0][c] == 1) && (tab[1][c] == 1) && (tab[2][c] == 1)) || ((tab[0][c] == 2) && (tab[1][c] == 2) && (tab[2][c] == 2)))
			return 1;
	}
	if (((tab[0][0] == 1) && (tab[1][1] == 1) && (tab[2][2] == 1)) || ((tab[0][0] == 2) && (tab[1][1] == 2) && (tab[2][2] == 2)))
		return 1;
	else 
	{
		if (((tab[0][2] == 1) && (tab[1][1] == 1) && (tab[2][0] == 1)) || ((tab[0][2] == 2) && (tab[1][1] == 2) && (tab[2][0] == 2)))
			return 1;

		tmp = 9; 

		for (int c = 0; c < 3; c++) 
		{ 
			for (int d = 0; d < 3; d++) 
			{ 
				if ((tab[c][d] == 1) || (tab[c][d] == 2))tmp--; 
			} 
		}
		if 
			(tmp == 0)return 2;
		else return 0;
	}
}

void Result(int win)
{
	if (win == 1)
	{
		if (players == 1)
		{
			cout << "Gracz pierwszy wygrywa majac: " << score01 << " punktow zdobytych";
			score01++;
		}
		else if (players == 2)
		{
			cout << "Gracz drugi wygrywa majac: " << score02 << " punktow zdobytych";
			score02++;
		}
	}
	else
	{
		cout << "Remis\n";
	}
}

void Loading()
{
	for (int i = 0; i < 4; i++)
	{
		Clear();
		cout << "Loading.";
		Sleep(100);
		Clear();
		cout << "Loading..";
		Sleep(100);
		Clear();
		cout << "Loading...";
		Sleep(100);
	}
}

/*
		 Column
	    1   2   3
      1 0 | 0 | 0
	    ---------
Row   2 0 | 0 | 0
	    ---------
      3 0 | 0 | 0
*/

void Options()
{

}

void Exits()
{
	// Wyjscie z gry
	cout << "Czy napewno chcesz wyjsc z gry?";
	char sign;
	cin >> sign;

	if (sign == 'N' || sign == 'n')
	{
		MainMenu();
	}
	else
	{
		exit(0);
	}
}

void Clear()
{
	system("cls");
}