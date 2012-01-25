#include "CDrawable.h"

CDrawable::CDrawable( SDL_Surface* Surf, SDL_Rect* rect )
    : mRect( rect ), mSurf( Surf )
{
}

CDrawable::CDrawable( SDL_Surface* Surf, int x, int y, int w, int h )
    : mSurf( Surf )
{
    mRect = NULL;
    setRect( x, y, w, h );
}

CDrawable::~CDrawable()
{
    delete mRect;
}


void CDrawable::setRect( int x, int y, int w, int h )
{
    if ( mRect != NULL )
    {
        delete mRect;
    }

    SDL_Rect* newRect = new SDL_Rect;

    newRect->x = x;
    newRect->y = y;
    newRect->w = w;
    newRect->h = h;

    mRect = newRect;
}

void CDrawable::setSurface( SDL_Surface* newSurf )
{
    if ( newSurf != NULL )
        mSurf = newSurf;
}

void CDrawable::OnDraw( SDL_Surface* Dest, SDL_Rect* DestRect )
{
    if ( mRect != NULL || DestRect != NULL )
    {
        if ( DestRect != NULL )
        {
            SDL_BlitSurface( mSurf, NULL, Dest, DestRect );
        }
        else
        {
            SDL_BlitSurface( mSurf, NULL, Dest, mRect );
        }
    }
}


