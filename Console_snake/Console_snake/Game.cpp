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
	printSummary();
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

	map = make_shared<Map>(boardHeight, boardWidth, 0.1);

	shared_ptr<BaseSnake> userSnake = make_shared<UserSnake>("User", MapPosition(10, 10), Direction::Left, map);
	snakes.push_back(userSnake);
}

void Game::printSummary()
{
	cout << "\n\n\n";

	for (auto snake : snakes)
	{
		cout << snake->getName() << " : " << snake->getPoints() << endl;
	}
}