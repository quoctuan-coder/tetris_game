#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;
using namespace sf;

const int Heigh = 20;
const int Width = 10;

int field[Heigh][Width] = {0};

struct Point
{int x,y;} cur_point[4], tmp_point[4], example_point[4],pre_point[4] ;

int dx=0, cur_color=1,color_example = 1, pre_color_example = 1;

bool check_rotate=false;

float timer=0,delay=0.3; 
int score = 0;

bool isNotEndGame =  true;
bool isInit = true;

int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

bool check()
{
	for (int i=0;i<4;i++)
		if (cur_point[i].x<0 || cur_point[i].x>=Width || cur_point[i].y>=Heigh) return 0;
		else if (field[cur_point[i].y][cur_point[i].x]) return 0;

	return 1;
};

int main()
{
	srand(time(0));     

	RenderWindow window(VideoMode(320, 480), "Tetris");

	Text text,text1;
	Font font;
	// Color color;
	if (!font.loadFromFile("fonts/OpenSans-ExtraBold.ttf"));
	{
		cout <<"Error";
	}
	text.setFont(font);
	text1.setFont(font);

	Texture t1,t2,t3;
	t1.loadFromFile("images/tiles.png");
	t2.loadFromFile("images/background.png");

	Sprite frame(t1), background(t2);

	Clock clock;

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=time;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();

			if (e.type == Event::KeyPressed)
				if (e.key.code==Keyboard::Up) check_rotate = true;
				else if (e.key.code==Keyboard::Left) dx=-1;
				else if (e.key.code==Keyboard::Right) dx=1;
				else if (e.key.code == Keyboard::Escape) window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) delay=0.05;


		///////Tick//////
		if ((timer>delay && isNotEndGame) || isInit)
		{
			for (int i=0;i<4;i++) { tmp_point[i]=cur_point[i]; cur_point[i].y+=1; }

			if (!check() || isInit)
			{
				int obj=rand()%7;

				if (!isInit)
				{
					for (int i=0;i<4;i++) field[tmp_point[i].y][tmp_point[i].x]=cur_color;
				}

				color_example=1+rand()%7;
				cur_color = pre_color_example;
				pre_color_example = color_example;

				for (int i=0;i<4;i++)
				{
					if (isInit)
					{
						cur_point[i].x = figures[obj][i] % 2 + 4;
						cur_point[i].y = figures[obj][i] / 2;
					}
					else
					{
						cur_point[i].x = pre_point[i].x + 4;
						cur_point[i].y = pre_point[i].y;
					}

					example_point[i].y = figures[obj][i] / 2;
					example_point[i].x = figures[obj][i] % 2;

					if (obj == 0)
					{
						pre_point[i].y = example_point[i].y;
					}
					else
					{
						pre_point[i].y = example_point[i].y-1;
					}
					pre_point[i].x = example_point[i].x;

				}

			}
			timer=0;
			isInit = false;
		}


		if (check_rotate)
		{
			Point p = cur_point[1]; 
			for (int i=0;i<4;i++)
			{
				int x = cur_point[i].y-p.y;
				int y = cur_point[i].x-p.x;
				cur_point[i].x = p.x - x;
				cur_point[i].y = p.y + y;
			}
			if (!check()) for (int i=0;i<4;i++) cur_point[i]=tmp_point[i];
		}

		// Move object
		for (int i=0;i<4;i++)  { tmp_point[i]=cur_point[i]; cur_point[i].x+=dx; }
		if (!check()) for (int i=0;i<4;i++) cur_point[i]=tmp_point[i];

		// Check line success
		int k=Heigh-1;

		for (int i=Heigh-1;i>0;i--)
		{
			int count=0;
			for (int j=0;j<Width;j++)
			{
				if (field[i][j]) 
				{
					count++;
				}
				field[k][j]=field[i][j];
				if (count == 10)
				{
					score +=1;
				}

			}
			if (count<Width) 
			{
				k--;
			}

		}
		// Reset variable
		dx=0; check_rotate=0; delay=0.3;

		// Setup to display
		window.clear(Color::White);    
		window.draw(background);

		// Draw score
		ostringstream out;
		out << score;

		text.setCharacterSize(10);
		text.setColor(Color::Black);
		text.setString("score " + out.str());
		text.setPosition(0,0);
		text.move(250,86);

		window.draw(text);

		// Draw example
		for (int i=0;i<4;i++)
		{
			frame.setTextureRect(IntRect(color_example*18,0,18,18));
			frame.setPosition(example_point[i].x*18,example_point[i].y*18);
			frame.move(255,120); //offset
			window.draw(frame);
		}
		// Draw field
		for (int i=0;i<Heigh;i++)
			for (int j=0;j<Width;j++)
			{
				if (field[i][j]==0) continue;

				frame.setTextureRect(IntRect(field[i][j]*18,0,18,18));
				frame.setPosition(j*18,i*18);
				frame.move(51,65); //offset
				window.draw(frame);
			}
		// Draw object when move
		for (int i=0;i<4;i++)
		{
			frame.setTextureRect(IntRect(cur_color*18,0,18,18));
			frame.setPosition(cur_point[i].x*18,(cur_point[i].y)*18);
			frame.move(51,65); //offset
			window.draw(frame);
		}

		// Draw end game
		for (int j = 0; j < Width ; j ++)
		{
			if (field[0][j] != 0)
			{
				text1.setCharacterSize(40);
				text1.setColor(Color::Red);
				text1.setString("Game over");
				text1.setPosition(0,0);
				text1.move(57,200);
				window.draw(text1);
				isNotEndGame = false;
			}
		}

		window.display();
	}

	return 0;
}
