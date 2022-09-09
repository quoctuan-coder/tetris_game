In this repository, I will use a graphics lib in SFML to try develop a mini game. 

### How to code **tetris** game on Ubuntu usinge SFML/Graphics

You can download source code, images and install lib on Ubuntu to run tetris game. It wil help you improve your programming skill in C++ language. Very interesting.  

Background and tiles

![image](/images/background.png)
![image](/images/tiles.png)

### Result

![image](/images/Infor.png)

Need to install  SFML/Graphics library.

#### How to install

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

./tetris
