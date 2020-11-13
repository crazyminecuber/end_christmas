#include <vector>

class Enemy
{
    public:
        Enemy();
        ~Enemy();
        static std::vector<Enemy*> enemies;
    private:
        int life;
};
