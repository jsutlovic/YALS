#include "CLife.h"


void CLife::SyncGrids()
{
    for ( int i = 0; i < LifeGrid->getRows(); i++ )
    {
        for ( int j = 0; j < LifeGrid->getCols(); j++ )
        {
            CGraphicCell::GCellState state;

            switch ( LifeGrid->getStateAt( i, j ) )
            {
                case CCell::CCELL_TYPE_ALIVE:
                    state = CGraphicCell::GCELL_TYPE_ALIVE;
                    break;
                case CCell::CCELL_TYPE_DEAD:
                    state = CGraphicCell::GCELL_TYPE_DEAD;
                    break;
                case CCell::CCELL_TYPE_REPROD:
                    state = CGraphicCell::GCELL_TYPE_REPROD;
                    break;
                case CCell::CCELL_TYPE_DYING:
                    state = CGraphicCell::GCELL_TYPE_DYING;
                    break;
            }

            GraphicGrid->setAt( i, j, state );
        }
    }
}

void CLife::Stabilize()
{
    if ( LifeGrid->getState() != CCellGrid::GRID_CALC && !LifeGrid->isCalculating() )
    {
        LifeGrid->nextState();
    }
    else if ( LifeGrid->isCalculating() )
    {
        //This shouldn't happen...
    }
    SyncGrids();
}


void CLife::Pause()
{
    Paused = true;
}


void CLife::UnPause()
{
    if ( !EditMode )
    {
        Paused = false;
    }
    else
    {
        ToggleEditMode();
        Paused = false;
    }
}


void CLife::TogglePause()
{
    if ( EditMode )
    {
        ToggleEditMode();
    }
    Paused = !Paused;
}


void CLife::Flash()
{
    SDL_FillRect( Surf_Display, NULL, SDL_MapRGB( Surf_Display->format, 0xff, 0xff, 0xff ) );

    SDL_Flip( Surf_Display );
}

void CLife::Save()
{
    Stabilize();
    Flash();
    LifeGrid->toFile(OutFile);
}

void CLife::Reset()
{
    Pause();

    if ( InFile.empty() )
    {
        LifeGrid->reset();
    }
    else
    {
        CCellGrid::fromFile( InFile, LifeGrid );
    }

    SyncGrids();
}

void CLife::ToggleEditMode()
{
    if ( !EditMode )
    {
        Pause();
        Stabilize();
        SyncGrids();
        EditMode = true;
    }
    else
    {
        EditMode = false;
        //UnPause();
    }
}

void CLife::ToggleStepping()
{
    Stepping = ( Stepping == STEP_FULL ) ? STEP_HALF : STEP_FULL;
}

void CLife::SwitchColours()
{
    Colours++;

    if ( Colours == ColourSchemes.end() )
    {
        Colours = ColourSchemes.begin();
    }

    CColourScheme::setColoursToGrid( (*Colours) );
}


void CLife::Patternify( int pattern )
{
    Pause();

    switch ( pattern )
    {
        case 0:
        {
            //Just clear the grid
            LifeGrid->clearGrid();
            break;
        }

        case 1:
        {
            // Checkerboard
            LifeGrid->clearGrid();

            for ( int i = 0; i < LifeGrid->getRows(); i++ )
            {
                for ( int j = 0; j < LifeGrid->getCols(); j++ )
                {
                    if ( (i + j) % 2 == 0 )
                    {
                        LifeGrid->setCellAt( i, j, 1 );
                    }
                    else
                    {
                        LifeGrid->setCellAt( i, j, 0 );
                    }
                }
            }

            break;
        }

        case 2:
        {
            // Horizontal lines
            LifeGrid->clearGrid();

            for ( int i = 0; i < LifeGrid->getRows(); i++ )
            {
                for ( int j = 0; j < LifeGrid->getCols(); j++ )
                {
                    if ( i%2 == 0 )
                    {
                        LifeGrid->setCellAt( i, j, 1 );
                    }
                    else
                    {
                        LifeGrid->setCellAt( i, j, 0 );
                    }
                }
            }

            break;
        }

        case 3:
        {
            //Every 3rd cell
            LifeGrid->clearGrid();

            for ( int i = 0; i < LifeGrid->getRows(); i++ )
            {
                for ( int j = 0; j < LifeGrid->getCols(); j++ )
                {
                    if ( (i+j) % 3 == 0 )
                    {
                        LifeGrid->setCellAt( i, j, 1 );
                    }
                    else
                    {
                        LifeGrid->setCellAt( i, j, 0 );
                    }
                }
            }

            break;
        }

        case 8:
        {
            LifeGrid->clearGrid();

            for ( int i = 0; i < ( LifeGrid->getRows() * LifeGrid->getCols() ) / 2; i++ )
            {
                int m = rand() % LifeGrid->getRows();
                int n = rand() % LifeGrid->getCols();

                LifeGrid->setCellAt( m, n, 1 );
            }

            break;
        }

        case 9:
        {
            LifeGrid->clearGrid();

            for ( int i = 0; i < LifeGrid->getRows(); i++ )
            {
                for ( int j = 0; j < LifeGrid->getCols(); j++ )
                {
                    LifeGrid->setCellAt( i, j, ( rand()%3 ) > 1 );
                }
            }

            break;
        }

        default:
        {
            //Leave as-is
            break;
        }
    }

    SyncGrids();
}

