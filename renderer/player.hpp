#include "graph.hpp"
#include "raycast.hpp"

class Player
{
    public:
        // Player(int x, int y);
        Player();
        ~Player() = default;

        SDL_Event m_event;

        void movePlayer(double delTime);
        void cameraRender(Map map, SDL_Renderer* renderer, int width, int height);

    private:
        Coords playerPos;
        Coords playerDirection;
        Coords cameraPlane;
        
        double moveSpeed;
        double rotateSpeed;
};