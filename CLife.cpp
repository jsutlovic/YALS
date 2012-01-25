#include "CLife.h"


CLife::CLife()
{
    Surf_Display = NULL;

    LifeGrid = NULL;

    GraphicGrid = NULL;

    Framerate = NULL;

    InFile = "";
    OutFile = "out_grid.txt";

    Running = false;
    Paused = true;
    EditMode = false;
    StepOnce = false;

    Initialized = false;

    srand( time( NULL ) );
}


CLife::~CLife()
{
    SDL_FreeSurface( Surf_Display );

    delete Framerate;
    delete GraphicGrid;
    delete LifeGrid;
}


int CLife::OnExecute()
{
    if ( OnInit() == false )
    {
        return 1;
    }

    SDL_Event Event;

    while ( Running )
    {
        while ( SDL_PollEvent( &Event ) )
        {
            OnEvent ( &Event );
        }

        if ( Framerate->OnLoop() )
        {
            OnLoop();
        }

        OnRender();
    }

    return 0;
}


void CLife::OnLoop()
{
    if ( !Paused )
    {
        switch ( Stepping )
        {
            case STEP_HALF:
                LifeGrid->nextState();
                break;
            case STEP_FULL:
                LifeGrid->nextStep();
                break;
        }

        SyncGrids();

        if ( StepOnce )
        {
            StepOnce = false;
            Pause();
        }
    }

    //std::cout << "Generation: " << LifeGrid->getGeneration() << std::endl;
    std::stringstream ss;
    ss << "SDLLife: " << ( Paused ? "P" : ( ( Stepping == STEP_FULL ) ? "F" : "H" ) ) << " FPS: " << Framerate->getFPS() << " Gen: " << LifeGrid->getGeneration();
    Caption = ss.str();

    SDL_WM_SetCaption( Caption.c_str(), Caption.c_str() );
}


void CLife::OnRender()
{
    //SDL_FillRect( Surf_Display, NULL, SDL_MapRGB( Surf_Display->format, 0xff, 0x88, 0xff ) );

    GraphicGrid->OnDraw( Surf_Display );

    SDL_Flip( Surf_Display );
}

