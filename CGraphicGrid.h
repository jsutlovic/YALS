#ifndef _CGRAPHICGRID_H_
#define _CGRAPHICGRID_H_

#include <vector>

#include "CGraphicCell.h"
#include "CCell.h"
#include "CCellGrid.h"


class CGraphicGrid : public CDrawable
{
    public:
        static SDL_Surface* SurfGrid;

    private:
        uint16_t gridRows;
        uint16_t gridCols;

        int pixW;
        int pixH;

        int spacing;

        std::vector< std::vector< CGraphicCell* > > GCellGrid;

    private:
        CGraphicGrid();

    public:
        CGraphicGrid( CCellGrid* CGrid, int gCellSize = 4 );
        ~CGraphicGrid();

        int getWidth() { return pixW; }
        int getHeight() { return pixH; }

        int getSpacing() { return spacing; }

        uint16_t getGridRows() { return gridRows; }
        uint16_t getGridCols() { return gridCols; }

        CGraphicCell* getCellAt( int row, int col );

        void setAt( int row, int col, CGraphicCell::GCellState state );

        void OnDraw( SDL_Surface* Dest, SDL_Rect* DestRect = NULL );

};

#endif // _CGRAPHICGRID_H_
