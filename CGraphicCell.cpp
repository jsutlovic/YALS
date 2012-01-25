#include "CGraphicCell.h"

/*
int CGraphicCell::CellW = 0;
int CGraphicCell::CellH = 0;
*/

int CGraphicCell::CellSize = 0;


SDL_Surface* CGraphicCell::SurfDead        = NULL;
SDL_Surface* CGraphicCell::SurfAlive       = NULL;
SDL_Surface* CGraphicCell::SurfReprod      = NULL;
SDL_Surface* CGraphicCell::SurfDying       = NULL;


CGraphicCell::CGraphicCell( int x, int y )
    : CDrawable( CGraphicCell::SurfDead, x, y, CellSize, CellSize )
{
    setState( CGraphicCell::GCELL_TYPE_DEAD );
}

CGraphicCell::CGraphicCell( int x, int y, GCellState newState )
    : CDrawable( CGraphicCell::SurfDead, x, y, CellSize, CellSize )
{
    setState( newState );
}


CGraphicCell::GCellState CGraphicCell::getState()
{
    return state;
}


void CGraphicCell::setState( GCellState newState )
{
    state = newState;
    setSurfState( newState );
}

void CGraphicCell::setSurfState( GCellState newState )
{
    switch ( newState )
    {
        case GCELL_TYPE_DEAD:
        {
            setSurface( CGraphicCell::SurfDead );
            break;
        }
        case GCELL_TYPE_ALIVE:
        {
            setSurface( CGraphicCell::SurfAlive );
            break;
        }
        case GCELL_TYPE_REPROD:
        {
            setSurface( CGraphicCell::SurfReprod );
            break;
        }
        case GCELL_TYPE_DYING:
        {
            setSurface( CGraphicCell::SurfDying );
            break;
        }
    }
}


