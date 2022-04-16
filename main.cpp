#include <iostream>
#include "Sokoban.h"

const char stageData[]{
"########\n\
# .. p #\n\
# oo   #\n\
#      #\n\
########" };

int main()
{
    Sokoban s;

    Sokoban::Object* state = new Sokoban::Object[s.stageWidth * s.stageHeight];
    s.Initialize(state, s.stageWidth, s.stageHeight, stageData);

    while (true)
    {
        s.Draw(state, s.stageWidth, s.stageHeight);

        if (s.CheckClear(state, s.stageWidth, s.stageHeight))
        {
            break;
        }

        char input;
        std::cout << "a:left  d:right  w:up  s:down" << std::endl << "command > ";
        std::cin >> input;


        s.Update(state, input, s.stageWidth, s.stageHeight);
    }

    std::cout << "Congratulations! You Won!" << std::endl;

    delete[] state;
}