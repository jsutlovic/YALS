#ifndef _CDRAWABLE_H_
    #define _CDRAWABLE_H_

#ifdef _WIN32
# include <SDL\SDL.h>
#else
# include <SDL/SDL.h>
#endif

//! CDrawable, the most basic drawable object
/*!
    Anything that is drawn should subclass this.
 */

class CDrawable
{
    private:
        CDrawable();

        SDL_Rect* mRect;
        SDL_Surface* mSurf;

    public:
        ~CDrawable();

        CDrawable( SDL_Surface* Surf, SDL_Rect* rect );
        CDrawable( SDL_Surface* Surf, int x, int y, int w, int h );

        SDL_Rect* getRect() { return mRect; }
        void setRect( SDL_Rect* newRect ) { mRect = newRect; }
        void setRect( int x, int y, int w, int h );

        SDL_Surface* getSurface() { return mSurf; }
        void setSurface( SDL_Surface* newSurf );

        void OnDraw( SDL_Surface* Dest, SDL_Rect* DestRect = NULL );
};

#endif // _CDRAWABLE_H_
