#include "./application.hpp"

Application::Application(int wid, int hei){
    Application::width = wid;
    Application::height = hei;
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Couldn't initiade SDL_VIDEO.\n";
        std::cout << "SDL Error: " << SDL_GetError() << "\n";
        return;
    }
    std::cout << "SDL Initiated successfully...\n";

    m_window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Application::width, Application::height, 0);

    if(!m_window){
        std::cout << "Couldn't initiate SDL screen.\n";
        std::cout << "SDL Error: " << SDL_GetError() << "\n";
        return;
    }

    std::cout << "Window Object was created successfully...\n";

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    // std::cout << m_renderer << "\n";
    if(!m_renderer){
        std::cout << "Couldn't initiate SDL renderer.\n";
        std::cout << "SDL Error: " << SDL_GetError() << "\n";
        return;
    }

    if(SDL_RenderSetLogicalSize(m_renderer, Application::width, Application::height)<0){
        std::cout << "Couldn't initiate SDL renderer.\n";
        std::cout << "SDL Error: " << SDL_GetError() << "\n";
        return;
    }

    std::cout << "Renderer object was created successfully...\n";

    // SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_GetDisplayMode(0, 0, &m_display);

    std::cout << "Running on display: " << m_display.w << "x" << m_display.h << ";Refresh rate: " << m_display.refresh_rate << " \n";

    delTime = 1.0 / (double) m_display.refresh_rate; 

    m_map.importMapFromTxt("./maps/map0.txt");
    std::cout << "Currently loaded map: \n";
    for(int i=0;i<m_map.width;i++){
        for(int j=0;j<m_map.height;j++){
            std::cout << m_map.mapArray[i][j] << " ";
        }
        std::cout << "\n";
    }

    floor.x = 0; floor.y = height/2 + 1;
    floor.h = height/2; floor.w = width;

    roof.x = 0; roof.y = 0;
    roof.h = height/2; roof.w = width;
}

Application::~Application(){
    std::cout<<"Exiting\n";
    // SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    // SDL_QuitSubSystem(0)
    SDL_Quit();
}

void Application::clearscr(){
    // std::cout << m_renderer << "\n";
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, RGB_GRAY.r, RGB_GRAY.g, RGB_GRAY.b, 255);
    SDL_RenderFillRect(m_renderer, &floor);
    SDL_SetRenderDrawColor(m_renderer, RGB_TEAL.r, RGB_TEAL.g, RGB_TEAL.b, 255);
    SDL_RenderFillRect(m_renderer, &roof);
}

void Application::loop(){
    bool keep_window_open = true;
    std::cout << "Starting render loop\n";
    while(keep_window_open){
        while(SDL_PollEvent(&(m_player.m_event)) > 0){
            switch (m_player.m_event.type)
            {
            case SDL_QUIT:
                keep_window_open = false;
                break;
            
            default:
                break;
            }
        }
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        // SDL_RenderClear(m_renderer);
        clearscr();
        m_player.cameraRender(m_map, m_renderer, Application::width, Application::height);
        SDL_RenderPresent(m_renderer); 
        m_player.movePlayer(delTime);
    }
    // SDL_RenderPresent(m_renderer); 
}

