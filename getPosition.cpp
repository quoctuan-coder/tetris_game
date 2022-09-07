#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
  RenderWindow window(VideoMode(320,480)," GetPosition");
  Texture t1;
  t1.loadFromFile("images/background.png");
  
  Sprite bg(t1);

  while (window.isOpen())
  {
	Event e;
	while (window.pollEvent(e))
	{
	  if (e.type == Event::MouseButtonPressed)
	  {
	 	if (e.mouseButton.button == Mouse::Left)
		{
			int x = Mouse::getPosition(window).x;
			int y = Mouse::getPosition(window).y;
			cout << "x: " << x << " - y:" << y << endl; 	
		}
	  }
	
	  if (e.key.code == Keyboard::Escape) window.close();
	}
	window.draw(bg);
	window.display();
  }
  
   
  return 0;
}
