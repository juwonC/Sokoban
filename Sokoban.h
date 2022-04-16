#pragma once

class Sokoban
{
public:
    const int stageWidth{ 8 };
    const int stageHeight{ 5 };

public:
    enum Object {
        OBJ_SPACE,
        OBJ_WALL,
        OBJ_GOAL,
        OBJ_BOX,
        OBJ_BOX_ON_GOAL,
        OBJ_MAN,
        OBJ_MAN_ON_GOAL,

        OBJ_UNKNOWN
    };

public:
    void Initialize(Object* state, int width, int height, const char* stageData);
    void Draw(const Object* state, int width, int height);
    void Update(Object* state, char input, int width, int height);
    bool CheckClear(const Object* state, int width, int height);
};

