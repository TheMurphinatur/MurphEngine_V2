#include "GraphicsManager.h"
#include "../../LoggingSystem/Logging.h"

GraphicsManager::GraphicsManager() = default;

GraphicsManager::~GraphicsManager()
{
    //LOG_TO_CONSOLE(kSystem, "Destroying GraphicsManager.");
    SDL_DestroyRenderer(m_pRenderer);
}

/**
 * \brief clear renderer, and start drawing new frame
 */
void GraphicsManager::StartDrawingFrame() const
{
    SDL_RenderClear(m_pRenderer);
}

/**
 * \brief Finish drawing frame, and present it to the screen
 */
void GraphicsManager::PresentCurrentFrame() const
{
    SDL_RenderPresent(m_pRenderer);
}

/**
 * \brief Set Render Draw Color
 * \param r red
 * \param g green
 * \param b blue
 * \param a alpha
 */
void GraphicsManager::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
{
    SDL_SetRenderDrawColor(m_pRenderer, r, g,b, a);
}

/**
 * \brief set render default draw color
 * \param r red
 * \param g green
 * \param b blue
 * \param a alpha
 */
void GraphicsManager::SetDefaultDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    m_drawColor = { r, g, b, a };
}

void GraphicsManager::SetDrawColorToDefault() const
{
    SDL_SetRenderDrawColor(m_pRenderer, m_drawColor.r, m_drawColor.g, m_drawColor.b, m_drawColor.a);
}

/**
 * \brief Draw line from point1 to point2
 * \param x1 point1 X
 * \param y1 point1 Y
 * \param x2 point2 X
 * \param y2 point2 Y
 */
void GraphicsManager::DrawLine(int x1, int y1, int x2, int y2) const
{
    SDL_RenderDrawLine(m_pRenderer, x1, y1, x2, y2);
}

/**
 * \brief Draw rect at given location with given dimensions
 * \param x top left corner X
 * \param y top left corner Y
 * \param width width of rect
 * \param height height of rect
 */
void GraphicsManager::DrawRect(int x, int y, int width, int height) const
{
    const SDL_Rect rect = { x, y, width, height };
    SDL_RenderDrawRect(m_pRenderer, &rect);
}

/**
 * \brief  Create new renderer
 * \param color default draw color
 */
void GraphicsManager::CreateRenderer(SDL_Color color)
{
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!m_pRenderer)
    {
        const std::string sdlError = SDL_GetError();
        LOG_TO_CONSOLE(kError, "Renderer could not be created. Error: " + sdlError + ".\tQuitting SDL");
        SDL_Quit();
        return;
    }
    LOG_TO_CONSOLE(kSystem, "Renderer created successfully!");
    SetDefaultDrawColor(color.r, color.g, color.b, color.a);
}
