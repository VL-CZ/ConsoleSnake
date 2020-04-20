#include "Game.h"
using namespace std;

Game::Game() : running(true)
{
}

void Game::play()
{
	initialize();
	while (running)
	{
		update();
	}
}

void Game::update()
{
	system("cls");

	int rn = rand() % 5;
	if (rn == 0)
	{
		map->tryGenerateRandomValueCell();
	}

	for (auto x : snakes)
	{
		x->move();
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

	map = make_shared<Map>(boardHeight, boardWidth);
}

void Game::printSummary()
{
	cout << "\n\n\n";

	for (auto snake : snakes)
	{
		cout << snake->getName() << " : " << snake->getPoints() << endl;
	}
}