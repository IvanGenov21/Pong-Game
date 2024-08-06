#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define WIDTH 40
#define HEIGHT 20
enum Dir
{
	STOP = 0,
	LEFT = 1,
	UPLEFT = 2,
	DOWNLEFT = 3,
	RIGHT = 4,	
	UPRIGHT = 5,	
	DOWNRIGHT = 6

};
class Ball {
private:
	int x, y, originalX, originalY;
	Dir direction;
public:
	Ball(int posX, int posY) {
		originalX = posX; originalY = posY;		
		x = posX; y = posY;
		direction = STOP;
	};


	void Reset() {
		x = originalX; y = originalY;
		direction = STOP;
	}

	void ChangeDirection(Dir d) {
		direction = d;
	}

	void RandomDirection() {
		direction = (Dir)((rand() % 6) + 1);
	}
	inline int getX() { return x; }
	inline int getY() { return y; }
	inline Dir getDirection() { return direction; }

	void Move() {
		switch (direction)
		{
		case STOP:
			break;
		case LEFT:
			x--;
			break;
		case UPLEFT:
			x--;
			y--;
			break;
		case DOWNLEFT:
			x--;
			y++;
			break;
		case RIGHT:
			x++;
			break;
		case UPRIGHT:
			x++;
			y--;
			break;
		case DOWNRIGHT:
			x++;
			y++;
			break;
		default:
			break;
		}
	}

	//debug print
	friend std::ostream & operator<<(std::ostream& o, Ball c) {
		o << "Ball [" << c.x << "," << c.y << "] [" << c.direction << "]";
		return o;
	}
};

class Paddle {
private:
	int x, y, originalX, originalY;

public:
	Paddle(){
		x = y = 0;
	}

	Paddle(int posX,int posY) : Paddle(){
		originalX = posX;
		originalY = posY;
		x = posX;
		y = posY;
	}
	inline void  Reset() { x = originalX, y = originalY; }
	inline int  getX() { return x; }
	inline int getY() { return y; }
	inline void moveUp() { y--; }
	inline void moveDown() { y++; }

	//debug print
	friend std::ostream& operator<<(std::ostream& o, Paddle c) {
		o << "Paddle [" << c.x << "," << c.y << "]";
		return o;
	}

};

class GameManager{
private:
	int width, height;
	int score1, score2;
	char up1, down1, up2, down2;
	bool quit;
	Ball* ball;
	Paddle* p1;
	Paddle* p2;

public:
	GameManager(int w, int h){
		srand(time(NULL));
		quit = false;
		//Add caps lock keybinds
		up1 = 'w'; up2 = 'i';
		down1 = 's'; down2 = 'k';
		score1 = score2 = 0;
		width = w; height = h;
		ball = new Ball(w / 2, h / 2);
		p1 = new Paddle(1, h / 2 - 3);
		p2 = new Paddle(w - 2, h / 2 - 3);
	}

	~GameManager()
	{
		delete ball, p1, p2;
	}

	void ScoreUp(Paddle* player) {

		if (player != nullptr) {
			if (player == p1) 
				score1++;			
			else if (player == p2) 
				score2++;			
		}

		ball->Reset();
		p1->Reset();
		p2->Reset();
	}

	void Draw() {
		system("cls"); //linux -> clear
		for (int i = 0; i < width + 2; i++) {
			std::cout << "\xB2";
		}
		std::cout << std::endl;

		for (int i = 0; i < height; i++) {

			for (int j = 0; j < width; j++) {
				int ballx = ball->getX();
				int bally = ball->getY();
				int player1x = p1->getX();
				int player1y = p1->getY();
				int player2x = p2->getX();
				int player2y = p2->getY();

				if (j == 0)
					std::cout << "\xB2";

				if (ballx == j && bally == i)
					std::cout << "O"; //ball
				else if (player1x == j && player1y == i)
					std::cout << "\xDB"; //p1
				else if (player2x == j && player2y == i)
					std::cout << "\xDB"; //p2

				else if (player1x == j && player1y + 1 == i)
					std::cout << "\xDB"; 
				else if (player1x == j && player1y + 2 == i)
					std::cout << "\xDB"; 
				else if (player1x == j && player1y + 3 == i)
					std::cout << "\xDB"; 

				else if (player2x == j && player2y + 1 == i)
					std::cout << "\xDB"; 
				else if (player2x == j && player2y + 2 == i)
					std::cout << "\xDB"; 
				else if (player2x == j && player2y + 3 == i)
					std::cout << "\xDB"; 

				else
					std::cout << " ";


				if (j == width - 1)
					std::cout << "\xB2";

 
			  }
			std::cout << std::endl;
			}
			for (int i = 0; i < width + 2; i++) {
				std::cout << "\xB2";
			}

			std::cout << std::endl;
			std::cout << "Player 1: " << score1 << std::endl << "Player 2: " << score2 << std::endl;
	
	}

	void Input() {
		ball->Move();

		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = p1->getX();
		int player1y = p1->getY();
		int player2x = p2->getX();
		int player2y = p2->getY();

		if (_kbhit()) {
			char  current = _getch();
			if (current == up1)
				if (player1y > 0)
					p1->moveUp();
			if (current == up2)
				if (player2y > 0)
					p2->moveUp();
			if (current == down1)
				if (player1y + 4 < height)
					p1->moveDown();
			if (current == down2)
				if (player2y + 4 < height)
					p2->moveDown();
			if (ball->getDirection() == STOP)
				ball->RandomDirection();

			if (current == 'q') {
				quit = true;
			}
		}

	}

	void Logic() {
		int ballx = ball->getX();
		int bally = ball->getY();
		int player1x = p1->getX();
		int player1y = p1->getY();
		int player2x = p2->getX();
		int player2y = p2->getY();

		//left player
		for (int i = 0; i < 4; i++) {
			if (ballx == player1x + 1) {
				if (bally == player1y + i)
					ball->ChangeDirection((Dir)(rand()%3 + 4));
			}
		}
		//right player
		for (int i = 0; i < 4; i++) {
			if (ballx == player2x - 1) {
				if (bally == player2y + i)
					ball->ChangeDirection((Dir)(rand() % 3 + 1));
			}
		}
		//bottom wall
		if (bally == height - 1)
			ball->ChangeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
		//top wall
		if (bally == 0)
			ball->ChangeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
		//right wall
		if (ballx == width - 1)
			ScoreUp(p1);
		//left wall 
		if (ballx == 0)
			ScoreUp(p2);
	}

	void HideCursor() {
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cursorInfo;

		GetConsoleCursorInfo(consoleHandle, &cursorInfo);
		cursorInfo.bVisible = FALSE; 
		SetConsoleCursorInfo(consoleHandle, &cursorInfo);
	}

	void Run() {
		while (!quit) {
			HideCursor();
			Draw();
			Input();
			Logic();
			Sleep(15);
		}
	}
};


int main() {
	GameManager c(WIDTH, HEIGHT);
	c.Run();
	return 0;
}