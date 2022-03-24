#include <iostream>

const char stageData[]{
"########\n\
# .. p #\n\
# oo   #\n\
#      #\n\
########" };

const int stageWidth{ 8 };
const int stageHeight{ 5 };

int main()
{
    while (true)
    {
        //Draw();
        std::cout << stageData << std::endl;
        //if (Clear())
        //    break;

        char input;
        std::cout << "a:left  d:right  w:up  s:down" << std::endl << "command > ";
        std::cin >> input;

        // Update();
    }
}

//Initialize()
//{
//    
//}

//Draw()
//{
//
//}

//Clear()
//{
//
//}
//
//Update()
//{
//
//}

// 스테이지 구성 요소
//# - 벽
//. - 목표지점
//  - 빈칸
//o - 상자
//O - 목표지점 위 상자
//p - 플레이어
//P - 목표지점 위 플레이어

// 문자열로 스테이지 구성(1차 배열)

//게임 클리어 여부 확인
//상자가 남아 있는지 아닌지 확인
//
//사용자 입력 처리
//상하좌우 처리
//
//입력에 따라 스테이지 내용 업데이트
//- 주어진 방향으로 이동
//- 벽으로 막혀있으면 이동 불가
//- 상자라면 상자를 해당 방향으로 밀어줌