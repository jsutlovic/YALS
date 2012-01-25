#ifndef _CFPSCONTROL_H_
#define _CFPSCONTROL_H_

#ifdef _WIN32
# include <SDL\SDL.h>
#else
# include <SDL/SDL.h>
#endif


class CFPSControl
{
    private:
        int FPS;
        Uint32 waittime;
        Uint32 framestarttime;
        Sint32 delaytime;

    private:
        CFPSControl();

    public:
        CFPSControl( int FPS ) : FPS( FPS )
        {
            setFPS( FPS );
        }

        int getFPS() { return FPS; }

        void setFPS( int FPS )
        {
            this->FPS = FPS;
            waittime = 1000.0f/FPS;
            framestarttime = 0;
        }

        void raiseFPS() { if ( FPS < 128 ) { setFPS( FPS*2 ); } }

        void lowerFPS() { if ( FPS > 1 ) { setFPS( FPS/2 ); } }

        bool OnLoop()
        {
            delaytime = waittime - ( SDL_GetTicks() - framestarttime );
            if ( delaytime > 0 )
            {
                //SDL_Delay( (Uint32)delaytime );
                return false;
            }
            else
            {
                framestarttime = SDL_GetTicks();
                return true;
            }
        }
};

#endif //_CCELLGRID_H_
