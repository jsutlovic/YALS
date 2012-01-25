#include "CLife.h"

void CLife::OnEvent( SDL_Event* Event )
{
    CEvent::OnEvent( Event );
}

void CLife::OnKeyDown( SDLKey sym, SDLMod mod, Uint16 unicode )
{
    switch ( sym )
    {
        case SDLK_ESCAPE:
        {
            OnExit();
            break;
        }

        case SDLK_RIGHT:
        {
            UnPause();
            break;
        }

        case SDLK_SPACE:
        {
            UnPause();
            StepOnce = true;
            break;
        }

        default:
        {
            break;
        }
    }
}

void CLife::OnKeyUp( SDLKey sym, SDLMod mod, Uint16 unicode )
{
    switch ( sym )
    {
        case SDLK_RIGHT:
        {
            Pause();
            break;
        }

        case SDLK_s:
        {
            Pause();
            Save();
            break;
        }

        case SDLK_RETURN:
        {
            TogglePause();
            break;
        }

        case SDLK_UP:
        case SDLK_PLUS:
        case SDLK_KP_PLUS:
        case SDLK_PERIOD:
        {
            Framerate->raiseFPS();
            break;
        }

        case SDLK_DOWN:
        case SDLK_MINUS:
        case SDLK_KP_MINUS:
        case SDLK_COMMA:
        {
            Framerate->lowerFPS();
            break;
        }

        case SDLK_e:
        {
            ToggleEditMode();
            break;
        }

        case SDLK_h:
        {
            //Pause();
            TogglePause();
            Stabilize();
            ToggleStepping();
            TogglePause();
            break;
        }

        case SDLK_c:
        {
            SwitchColours();
            break;
        }

        case SDLK_r:
        {
            Reset();
            break;
        }

        //Patterns:
        case SDLK_0:
        case SDLK_KP0:
        {
            Patternify(0);
            break;
        }

        case SDLK_1:
        case SDLK_KP1:
        {
            Patternify(1);
            break;
        }

        case SDLK_2:
        case SDLK_KP2:
        {
            Patternify(2);
            break;
        }

        case SDLK_3:
        case SDLK_KP3:
        {
            Patternify(3);
            break;
        }

        case SDLK_8:
        case SDLK_KP8:
        {
            Patternify(8);
            break;
        }

        case SDLK_9:
        case SDLK_KP9:
        {
            Patternify(9);
            break;
        }

        default:
        {
            break;
        }
    }
}


void CLife::OnMouseMove( int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle )
{
}


void CLife::OnLButtonDown( int mX, int mY )
{
    if ( EditMode )
    {
        int row = ( mY / ( CGraphicCell::CellSize + GraphicGrid->getSpacing() ) );
        int col = ( mX / ( CGraphicCell::CellSize + GraphicGrid->getSpacing() ) );

        bool cellalive = LifeGrid->getCellAt( row, col )->isAlive();

        LifeGrid->setCellAt( row, col, !cellalive );
        GraphicGrid->setAt( row, col, static_cast<CGraphicCell::GCellState>( !cellalive ) );
    }
}


void CLife::OnExit()
{
    Pause();
    Running = false;
}
