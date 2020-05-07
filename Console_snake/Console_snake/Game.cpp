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

	bool activeSnakes = 0;

	for (auto x : snakes)
	{
		if (x->isAlive())
		{
			activeSnakes++;
			x->move();
		}
	}

	if (activeSnakes == 0)
		running = false;

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

	for (int i = 0; i < AI_snakesCount; i++)
	{
		shared_ptr<AISnake> ai_snake = make_shared<AISnake>("Bot " + to_string(i), MapPosition(11, 10), Direction::Left, map);
		snakes.push_back(ai_snake);
	}
}

void Game::printSummary()
{
	cout << endl << endl << endl;

	for (auto snake : snakes)
	{
		cout << snake->getPoints() << " | " << snake->getName() << endl;
	}
}