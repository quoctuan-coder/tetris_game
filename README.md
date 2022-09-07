### How to code **tetris** game on Ubuntu usinge SFML/Graphics

![image](/tetris_game/images/Infor.png)

Need to lib SFML/Graphics

**How to install**

>sudo apt-get install libsfml-dev

Location
//usr/include/SFML/

------
How to compile

g++ -c tetris.cpp
g++ tetris.o -o tetris -lsfml-graphics -lsfml-window -lsfml-system

How to run

./tetris
