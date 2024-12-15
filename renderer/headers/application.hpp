#pragma once

#include "player.hpp"

class Application
{
    public:

        Application(int wid = 680, int hei = 480);
        ~Application();

        SDL_Renderer *m_renderer;
        SDL_DisplayMode m_display;
        void clearscr();
        void loop();

    private:
        SDL_Window *m_window;
        Player m_player;

        double delTime;
        int width;
        int height;
        
        Map m_map;
        SDL_Rect floor;
        SDL_Rect roof;
        // SDL_Event m_event;
        
};
