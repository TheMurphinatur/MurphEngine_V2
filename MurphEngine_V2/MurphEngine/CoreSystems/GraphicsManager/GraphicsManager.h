#pragma once
#include "../../LoggingSystem/Logging.h"
#include "../../Middleware/SDL2/include/SDL.h"
#include "../../Middleware/SDL2/include/SDL_image.h"



class GraphicsManager
{
    int m_windowWidth = 0;
    int m_windowHeight = 0;


    SDL_Renderer* m_pRenderer = nullptr;
    SDL_Window* m_pWindow = nullptr;

    SDL_Color m_drawColor{0, 0, 0, 255};


public:
    GraphicsManager();
    ~GraphicsManager();

    void StartDrawingFrame() const;
    void PresentCurrentFrame() const;

    void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
    void SetDefaultDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void SetDrawColorToDefault() const;

    void DrawLine(int x1, int y1, int x2, int y2) const;
    void DrawRect(int x, int y, int width, int height) const;

    /**
     * \brief Get Renderer
     * \return Current SDL_Renderer*
     */
    SDL_Renderer* GetRenderer() const { return m_pRenderer; }

    /**
     * \brief Get Window   
     * \return current SDL_Window*
     */
    SDL_Window* GetWindow() const { return m_pWindow; }

    int GetWindowWidth() const { return m_windowWidth; }
    int GetWindowHeight() const { return m_windowHeight; }

    void CreateNewWindow(const char* windowName, int locationX, int locationY, int windowWidth, int windowHeight)
    {
        m_windowWidth = windowWidth;
    	m_windowHeight = windowHeight;
        m_pWindow = SDL_CreateWindow(windowName, locationX, locationY, windowWidth, windowHeight, 0);
        CreateRenderer(m_drawColor);
    }

    SDL_Texture* LoadTexture(const char* filePath) const
    {
        SDL_Surface* temp = IMG_Load(filePath);
        if (temp == nullptr)
        {
            LOG_TO_CONSOLE(kError, "failed to load image. ");
        }

        //Creating a texture from temp surface above.
        SDL_Texture* texture = SDL_CreateTextureFromSurface(m_pRenderer, temp);
        if (texture == nullptr)
        {
            LOG_TO_CONSOLE(kError, "failed to load texture. ");
        }

        //clear the surface
        SDL_FreeSurface(temp);

        return texture;
    }

    void RemoveRenderer() const
    {
        SDL_DestroyRenderer(m_pRenderer);
    }

private:

    void CreateRenderer(SDL_Color color);


};

