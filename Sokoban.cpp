#include <iostream>

const char stageData[] = 
"\
########\n\
# .. p #\n\
# oo   #\n\
#      #\n\
########";

const int stageWidth{ 8 };
const int stageHeight{ 5 };

int main()
{
    while (true)
    {
        그리기();
        if (게임종료())
            break;

        입력처리;
        업데이트();
    }
}

초기화()
{
    while (배열전체)
    {

    }
}

그리기()
{

}

게임종료()
{

}

업데이트()
{

}