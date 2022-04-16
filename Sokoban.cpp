#include <iostream>

const char stageData[]{
"########\n\
# .. p #\n\
# oo   #\n\
#      #\n\
########" };

const int stageWidth{ 8 };
const int stageHeight{ 5 };

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

void Initialize(Object* state, int width, int height, const char* stageData);
void Draw(const Object* state, int width, int height);
void Update(Object* state, char input, int width, int height);
bool CheckClear(const Object* state, int width, int height);

int main()
{
    Object* state = new Object[stageWidth * stageHeight];
    Initialize(state, stageWidth, stageHeight, stageData);

    while (true)
    {
        Draw(state, stageWidth, stageHeight);
        
        if (CheckClear(state, stageWidth, stageHeight))
        {
            break;
        }

        char input;
        std::cout << "a:left  d:right  w:up  s:down" << std::endl << "command > ";
        std::cin >> input;
        

        Update(state, input, stageWidth, stageHeight);
    }

    std::cout << "Congratulations! You Won!" << std::endl;

    delete[] state;
}

void Initialize(Object* state, int width, int height, const char* stageData)
{
    const char* data = stageData;
    int x { 0 };
    int y { 0 };

    while (*data != '\0')
    {
        Object t;

        switch (*data)
        {
            case '#':
                t = OBJ_WALL;
                break;

            case ' ':
                t = OBJ_SPACE;
                break;

            case 'o':
                t = OBJ_BOX;
                break;

            case 'O':
                t = OBJ_BOX_ON_GOAL;
                break;

            case '.':
                t = OBJ_GOAL;
                break;

            case 'p':
                t = OBJ_MAN;
                break;

            case 'P':
                t = OBJ_MAN_ON_GOAL;
                break;

            case '\n':
                x = 0;
                ++y;
                t = OBJ_UNKNOWN;
                break;

            default:
                t = OBJ_UNKNOWN;
                break;
        }
        ++data;
        if (t != OBJ_UNKNOWN)
        {
            state[y * width + x] = t;
            ++x;
        }
    }
}

void Draw(const Object* state, int width, int height)
{
    const char font[] = { ' ', '#', '.', 'o', 'O', 'p', 'P' };
    
    for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			Object o = state[y * width + x];
            std::cout << font[o];
		}
        std::cout << std::endl;
	}
}

void Update(Object* state, char input, int width, int height)
{
    int dx { 0 };
    int dy { 0 };

    switch (input)
    {
        case 'a':
            dx = -1;
            break;

        case 'd':
            dx = 1;
            break;

        case 'w':
            dy = -1;
            break;

        case 's':
            dy = 1;
            break;

        default:
            std::cout << "Incorrect Input" << std::endl;
            break;
    }

    int i{ -1 };
    for (i = 0; i < width * height; ++i)
    {
        if (state[i] == OBJ_MAN || state[i] == OBJ_MAN_ON_GOAL)
        {
            break;
        }
    }

    int x = i % width;
    int y = i / width;

    int tx = x + dx;
    int ty = y + dy;

    if (tx < 0 || ty < 0 || tx >= width || ty >= height)
    {
        return;
    }

    int p = y * width + x;
    int tp = ty * width + tx;
    if (state[tp] == OBJ_SPACE || state[tp] == OBJ_GOAL)
    {
        state[tp] = (state[tp] == OBJ_GOAL) ? OBJ_MAN_ON_GOAL : OBJ_MAN;
        state[p] = (state[p] == OBJ_MAN_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;
    }
    else if (state[tp] == OBJ_BOX || state[tp] == OBJ_BOX_ON_GOAL)
    {
        int tx2 = tx + dx;
        int ty2 = ty + dy;
        if (tx2 < 0 || ty2 < 0 || tx2 >= width || ty2 >= height)
        {
            return;
        }

        int tp2 = (ty + dy) * width + (tx + dx);
        if (state[tp2] == OBJ_SPACE || state[tp2] == OBJ_GOAL)
        {
            state[tp2] = (state[tp2] == OBJ_GOAL) ? OBJ_BOX_ON_GOAL : OBJ_BOX;
            state[tp] = (state[tp] == OBJ_BOX_ON_GOAL) ? OBJ_MAN_ON_GOAL : OBJ_MAN;
            state[p] = (state[p] == OBJ_MAN_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;
        }
    }
}

bool CheckClear(const Object* state, int width, int height)
{
    for (int i = 0; i < width * height; ++i)
    {
        if (state[i] == OBJ_BOX)
        {
            return false;
        }
    }
    return true;
}