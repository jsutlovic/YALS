#include "CLife.h"


void CLife::Initialize( int GridCols, int GridRows, int CellSize, GridStep stepping, std::string OutFile )
{
    LifeGrid = new CCellGrid( GridRows, GridCols );

    CommonInit( CellSize, stepping, OutFile );
}


void CLife::Initialize( std::string InFile, int CellSize, GridStep stepping, std::string OutFile )
{
    if ( !InFile.empty() )
    {
        this->InFile = InFile;
    }

    LifeGrid = CCellGrid::fromFile( InFile );
    if ( LifeGrid == NULL )
    {
        std::cerr << "LifeGrid not initialized." << std::endl;
        return;
    }

    CommonInit( CellSize, stepping, OutFile );
}


void CLife::CommonInit( int CellSize, GridStep stepping, std::string OutFile )
{
    GraphicGrid = new CGraphicGrid( LifeGrid, CellSize );

    //Set up colour schemes:                      dead     alive    reproduce  dying    background
    ColourSchemes.push_back( new CColourScheme( "080808", "00bb00", "ffffff", "444444", "040404" ) ); // black, green, white, mid-gray
    ColourSchemes.push_back( new CColourScheme( "000000", "04cdff", "ffffff", "3a3b3f", "080808" ) );
    ColourSchemes.push_back( new CColourScheme( "efefef", "04cdff", "b7f0ff", "aaaaaa", "dddddd" ) ); // light gray, blue, light blue, mid-gray
    ColourSchemes.push_back( new CColourScheme( "444444", "04cdff", "eeeeee", "222222" ) ); // mid gray, light blue, white, dark gray
    ColourSchemes.push_back( new CColourScheme( "444444", "ffff22", "00ee00", "aa0000" ) ); // mid gray, yellow, green, red
    ColourSchemes.push_back( new CColourScheme( "040404", "ffffff", "444444", "ee2222" ) ); // black, white, dark gray, red

    //Set to the first colour scheme
    Colours = ColourSchemes.begin();

    //Now set them to the grid
    CColourScheme::setColoursToGrid( (*Colours) );

    //If all is well, we're initialized
    if ( LifeGrid != NULL && GraphicGrid != NULL )
        Initialized = true;

    Stepping = stepping;

    Framerate = new CFPSControl( 8 );

    if ( !OutFile.empty() )
    {
        this->OutFile = OutFile;
    }
}


bool CLife::OnInit()
{
    if ( !Initialized )
    {
        return false;
    }

    if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return false;
    }

    if ( ( Surf_Display = SDL_SetVideoMode( GraphicGrid->getWidth(), GraphicGrid->getHeight(), 32, SDL_HWSURFACE ) ) == NULL )
    {
        return false;
    }

    Running = true;
    Paused = true;

    return true;
}


