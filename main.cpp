#include <unistd.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include "CLife.h"


int main ( int argc, char** argv )
{
    int rows = 30;
    int cols = 60;
    int cellsize = 8;
    bool hs = false;
    char* ifile = NULL;
    char* ofile = NULL;

    int c;

    while ( ( c = getopt( argc, argv, "r:c:z:i:o:s" ) ) != -1 )
    {
        switch ( c )
        {
            case 'r':
            {
                rows = std::atoi( optarg );
                break;
            }
            case 'c':
            {
                cols = std::atoi( optarg );
                break;
            }
            case 'z':
            {
                cellsize = std::atoi( optarg );
                break;
            }
            case 'i':
            {
                ifile = optarg;
                break;
            }
            case 'o':
            {
                ofile = optarg;
                break;
            }
            case 's':
            {
                hs = true;
                break;
            }
            case '?':
            {
                std::cout << "Wrong argument: " << optopt << std::endl;
                break;
            }

            default:
                exit(1);
        }
    }

    CLife gol = CLife();

    if ( ifile != NULL )
    {
        gol.Initialize( std::string(ifile), cellsize, static_cast<CLife::GridStep>(hs+1), ( ofile == NULL ? std::string() : std::string( ofile ) ) );
    }
    else
    {
        gol.Initialize( cols, rows, cellsize, static_cast<CLife::GridStep>(hs+1), ( ofile == NULL ? std::string() : std::string( ofile ) ) );
    }

    return gol.OnExecute();
}
