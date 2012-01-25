#include "CGraphicGrid.h"

SDL_Surface* CGraphicGrid::SurfGrid = NULL;

CGraphicGrid::CGraphicGrid( CCellGrid* CGrid, int gCellSize )
    : CDrawable( NULL, NULL )
{
    if ( CGrid->getState() != CCellGrid::GRID_CALC )
    {
        //Can't use a grid if it's not in the resting state
        return;
    }

    spacing = 1;
    CGraphicCell::CellSize = gCellSize;

    gridRows = CGrid->getRows();
    gridCols = CGrid->getCols();

    pixW = ( CGraphicCell::CellSize*gridCols ) + ( spacing*(gridCols+1) );
    pixH = ( CGraphicCell::CellSize*gridRows ) + ( spacing*(gridRows+1) );


    setRect( 0, 0, pixW, pixH );
    SurfGrid = SDL_CreateRGBSurface( SDL_HWSURFACE, pixW, pixH, 32, 0xff0000, 0x00ff00, 0x0000ff, 0x00 );
    setSurface( SurfGrid );

    SDL_FillRect( getSurface(), NULL, SDL_MapRGB( getSurface()->format, 0x00, 0x00, 0x00 ) );

    //Set up cell surfs here
    CGraphicCell::SurfDead         = SDL_CreateRGBSurface( SDL_HWSURFACE, CGraphicCell::CellSize, CGraphicCell::CellSize, 32, 0xff0000, 0x00ff00, 0x0000ff, 0x00 );
    CGraphicCell::SurfAlive        = SDL_CreateRGBSurface( SDL_HWSURFACE, CGraphicCell::CellSize, CGraphicCell::CellSize, 32, 0xff0000, 0x00ff00, 0x0000ff, 0x00 );
    CGraphicCell::SurfReprod       = SDL_CreateRGBSurface( SDL_HWSURFACE, CGraphicCell::CellSize, CGraphicCell::CellSize, 32, 0xff0000, 0x00ff00, 0x0000ff, 0x00 );
    CGraphicCell::SurfDying        = SDL_CreateRGBSurface( SDL_HWSURFACE, CGraphicCell::CellSize, CGraphicCell::CellSize, 32, 0xff0000, 0x00ff00, 0x0000ff, 0x00 );


    //Set up cells:
    GCellGrid.resize( gridRows, std::vector < CGraphicCell* > ( gridCols ) );

    for ( int i = 0; i < gridRows; i++ )
    {
        for ( int j = 0; j < gridCols; j++ )
        {
            int cellw = ( 2 * spacing ) + ( CGraphicCell::CellSize*j ) + ( spacing * ( j-1 ) );
            int cellh = ( 2 * spacing ) + ( CGraphicCell::CellSize*i ) + ( spacing * ( i-1 ) );

            CGraphicCell::GCellState state;

            switch ( CGrid->getStateAt( i, j ) )
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

            GCellGrid[i][j] = new CGraphicCell( cellw, cellh, state );
        }
    }
}


CGraphicGrid::~CGraphicGrid()
{
    for ( int i = 0; i < gridRows; i++ )
    {
        for ( int j = 0; j < gridCols; j++ )
        {
            delete GCellGrid[i][j];
        }
    }
}


CGraphicCell* CGraphicGrid::getCellAt( int row, int col )
{
    return GCellGrid[row][col];
}


void CGraphicGrid::setAt( int row, int col, CGraphicCell::GCellState state )
{
    /** Used for setting from the CellGrid */

    CGraphicCell* c = getCellAt( row, col );

    if ( c != NULL )
        c->setState( state );
}


void CGraphicGrid::OnDraw( SDL_Surface* Dest, SDL_Rect* DestRect )
{
    for ( int i = 0; i < getGridRows(); i++ )
    {
        for ( int j = 0; j < getGridCols(); j++ )
        {
            GCellGrid[i][j]->OnDraw( getSurface() );
        }
    }
    CDrawable::OnDraw( Dest, DestRect );
}

