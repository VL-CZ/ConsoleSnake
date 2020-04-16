#include "Game.h"
using namespace std;

Game::Game()
{
}

void Game::play()
{
	initialize();
	while (true)
	{
		update();
	}
}

void Game::update()
{
	system("cls");

	int rn = rand() % 3;
	if (rn == 0)
	{
		map->tryGenerateRandomValueCell();
	}

	map->print();
}

void Game::initialize()
{
	int boardHeight;
	int boardWidth;
	int AI_snakesCount;

	cout << "Zadejte vysku hraci plochy" << endl;
	cin >> boardHeight;

	cout << "Zadejte sirku hraci plochy" << endl;
	cin >> boardWidth;

	cout << "Zadejte pocet hadu ovladanych pocitacem" << endl;
	cin >> AI_snakesCount;

	shared_ptr<BaseSnake> userSnake = make_shared<UserSnake>("User");

	vector<shared_ptr<BaseSnake>> snakes;
	snakes.push_back(userSnake);

	map = make_shared<Map>(boardHeight, boardWidth, snakes);
}