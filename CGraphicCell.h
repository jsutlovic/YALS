#ifndef _CGRAPHICCELL_H_
#define _CGRAPHICCELL_H_


#include "CDrawable.h"


class CGraphicCell : public CDrawable
{
    public:
        static SDL_Surface* SurfDead;
        static SDL_Surface* SurfAlive;
        static SDL_Surface* SurfReprod;
        static SDL_Surface* SurfDying;

        static int CellSize;

        enum GCellState {
            GCELL_TYPE_DEAD = 0,
            GCELL_TYPE_ALIVE,
            GCELL_TYPE_REPROD,
            GCELL_TYPE_DYING
        };


    private:
        GCellState state;


    public:
        CGraphicCell( int x, int y );

        CGraphicCell( int x, int y, GCellState newState );

        GCellState getState();
        void setState( GCellState newState );
        void setSurfState( GCellState newState );
};


#endif // _CGRAPHICCELL_H_
