#include <zeno/Game/Core/Game.hpp>

#include <iostream>

int main(int _argc, char **_argv)
{
    zeno::Game game = zeno::Game("Game Window", 1280, 720);

    game.setResizeMethod([](unsigned int _width, unsigned int _height){
        std::cout << "New width: " << _width << ", height: " << _height << std::endl;
    });
    game.setOnCloseButtonMethod([](){
       return true;
    });


    game.setClearColour(zeno::Colour::Cyan);



    game.start();

    return EXIT_SUCCESS;
}
