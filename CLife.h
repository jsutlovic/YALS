#ifndef _CLIFE_H_
#define _CLIFE_H_

#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include "CEvent.h"
#include "CCell.h"
#include "CCellGrid.h"
#include "CGraphicCell.h"
#include "CGraphicGrid.h"
#include "CFPSControl.h"
#include "CColourScheme.h"


class CLife : public CEvent
{
    public:
        enum GridStep
        {
            STEP_FULL = 1,
            STEP_HALF
        };

    private:
        bool Running;
        bool Paused;
        bool StepOnce;
        bool EditMode;

        bool Initialized;
        GridStep Stepping;

        std::vector< CColourScheme* >::iterator Colours;
        std::vector< CColourScheme* > ColourSchemes;

        std::string InFile;
        std::string OutFile;

        std::string Caption;

        CCellGrid* LifeGrid;

        CGraphicGrid* GraphicGrid;

        SDL_Surface* Surf_Display;

        CFPSControl* Framerate;

    private:
        void CommonInit( int CellSize, GridStep stepping, std::string OutFile );

    public:
        CLife();

        ~CLife();

        void Initialize( int GridCols, int GridRows, int CellSize, GridStep stepping, std::string OutFile = "" );

        void Initialize( std::string InFile, int CellSize, GridStep stepping, std::string OutFile = "" );

        int OnExecute();

        bool OnInit();

        void OnEvent( SDL_Event* Event );

        void OnLoop();

        void OnRender();

        void OnExit();

        void OnKeyDown( SDLKey sym, SDLMod mod, Uint16 unicode );

        void OnKeyUp( SDLKey sym, SDLMod mod, Uint16 unicode );

        void OnMouseMove( int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle );

        void OnLButtonDown( int mX, int mY );


        void SyncGrids();

        //bool CheckStable();
        void Stabilize();

        void Pause();
        void UnPause();
        void TogglePause();

        void Flash();

        void Reset();

        void Save();

        void ToggleEditMode();

        void ToggleStepping();

        void SwitchColours();

        void Patternify( int pattern );

};

#endif // _CLIFE_H_
