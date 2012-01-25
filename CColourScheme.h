#ifndef _CCOLOURSCHEME_H_
#define _CCOLOURSCHEME_H_

#include <iostream>

#include "CColour.h"
#include "CGraphicCell.h"
#include "CGraphicGrid.h"


class CColourScheme
{
    public:
        CColour* background;
        CColour* dead;
        CColour* alive;
        CColour* dying;
        CColour* reprod;

    private:
        CColourScheme();

    public:
        CColourScheme( std::string dead, std::string alive, std::string reprod, std::string dying, std::string background = "" )
        {
            this->dead = new CColour( dead );
            this->alive = new CColour( alive );
            this->reprod = new CColour( reprod );
            this->dying = new CColour( dying );

            this->background = ( background.empty() ) ? ( new CColour() ) : ( new CColour( background ) );
        }

        ~CColourScheme()
        {
            delete dead;
            delete alive;
            delete dying;
            delete reprod;
        }

        void setDead( std::string deadstr ) { dead->setColour( deadstr ); }

        void setAlive( std::string alivestr ) { alive->setColour( alivestr ); }

        void setDying( std::string dyingstr ) { dying->setColour( dyingstr ); }

        void setReprod( std::string reprodstr ) { reprod->setColour( reprodstr ); }


        static void setColoursToGrid( CColourScheme* cs )
        {
            SDL_FillRect( CGraphicCell::SurfDead,      NULL, cs->dead->toRGB(       CGraphicCell::SurfDead   ) );
            SDL_FillRect( CGraphicCell::SurfAlive,     NULL, cs->alive->toRGB(      CGraphicCell::SurfAlive  ) );
            SDL_FillRect( CGraphicCell::SurfReprod,    NULL, cs->reprod->toRGB(     CGraphicCell::SurfReprod ) );
            SDL_FillRect( CGraphicCell::SurfDying,     NULL, cs->dying->toRGB(      CGraphicCell::SurfDying  ) );
            SDL_FillRect( CGraphicGrid::SurfGrid,      NULL, cs->background->toRGB( CGraphicGrid::SurfGrid   ) );
        }

};

#endif // _CCOLOURSCHEME_H_
