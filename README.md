In this repository, I will use a graphics lib in SFML to try develop a mini game. 

### How to code **tetris** game on Ubuntu usinge SFML/Graphics

Version Ubuntu: 16.04

You can download source code, images and install lib on Ubuntu to run tetris game. It wil help you improve your programming skill in C++ language. Very interesting.  

### Background and tiles

<img src="/images/background.png"  width= "150" height = "225">
<img src ="/images/tiles.png">

### Result

<img src ="/images/Infor.png"  width =50% height =50% >

Need to install  SFML/Graphics library.

#### How to install SFML
```
sudo apt-get install libsfml-dev
```

Location store library


*/usr/include/SFML/*


#### How to compile
```
g++ -c tetris.cpp
g++ tetris.o -o tetris -lsfml-graphics -lsfml-window -lsfml-system
```

#### How to run
```
./tetris
```

