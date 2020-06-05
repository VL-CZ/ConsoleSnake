#include "Game.h"
#include <iomanip>
using namespace std;

Game::Game() : inProgress(true)
{
}

void Game::play()
{
	initialize();

	map->print();
	Sleep(1000);

	while (inProgress)
	{
		update();
	}
}

void Game::update()
{
	Sleep(100);
	SetConsoleCursorPosition(console, { 0,0 });

	tryToGenerateValueInMap(0.2);

	bool activeSnakes = 0;

	// move
	for (auto x : snakes)
	{
		if (x->isAlive())
		{
			activeSnakes++;
			x->move();
		}
	}

	if (activeSnakes == 0)
		inProgress = false;

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

	map = make_shared<Map>(boardHeight, boardWidth, 0.05);

	Direction d = getRandomDirection();

	shared_ptr<BaseSnake> userSnake = make_shared<UserSnake>("User", map->getValidStartPosition(d), d, map);
	snakes.push_back(userSnake);

	for (int i = 0; i < AI_snakesCount; i++)
	{
		Direction d = getRandomDirection();
		shared_ptr<AISnake> ai_snake = make_shared<AISnake>("Bot " + to_string(i), map->getValidStartPosition(d), d, map);
		snakes.push_back(ai_snake);
	}

	system("cls");
}

void Game::printSummary()
{
	cout << endl << endl << endl;

	sort(snakes.begin(), snakes.end(), SnakePointsComparer());
	for (auto snake : snakes)
	{
		string aliveString = snake->isAlive() ? "Alive" : "Dead";

		cout << setw(10) << snake->getName() << " | ";
		cout << setw(5) << snake->getPoints() << " | ";
		cout << setw(6) << aliveString << endl;
	}
}

void Game::tryToGenerateValueInMap(double probability)
{
	if (probability == 0)
		return;

	// generate random number 1-100
	int rn = rand() % 100;

	// get maximal number that indicates success
	int maxValid = probability * 100 + 1;

	if (rn <= maxValid)
	{
		map->tryGenerateRandomValueCell();
	}
}

Direction getRandomDirection()
{
	int rn = rand() % 4;
	return (Direction)rn;
}