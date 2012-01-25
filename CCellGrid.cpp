#include "CCellGrid.h"
#include "StringSep.h"

CCellGrid::CCellGrid( uint16_t rows, uint16_t cols )
    : rows( rows ), cols( cols )
{
    setState( GRID_CALC );

    Grid.resize( rows, std::vector< CCell* > ( cols ) );

    for ( int i = 0; i < rows; i++ )
    {
        for ( int j = 0; j < cols; j++ )
        {
            //Fill with dead cells
            Grid[i][j] = new CCell( i, j, false );
        }
    }

    generation = 0;
    calculating = false;
}

CCellGrid::~CCellGrid()
{
    for ( int i = 0; i < rows; i++ )
    {
        for ( int j = 0; j < cols; j++ )
        {
            //Free all cells
            delete Grid[i][j];
        }
    }
}

CCell* CCellGrid::getCellAt( uint16_t row, uint16_t col )
{
    return Grid[row][col];
}

CCell::CCellState CCellGrid::getStateAt( uint16_t row, uint16_t col )
{
    CCell* cell = getCellAt( row, col );
    std::map< CCell*, bool >::iterator it = getChanged()->find( cell );
    CCell::CCellState state;

    if ( getState() == CCellGrid::GRID_INTERMED && it != getChanged()->end() )
    {
        state = ( it->second ? CCell::CCELL_TYPE_REPROD : CCell::CCELL_TYPE_DYING );
    }
    else
    {
        state = ( cell->isAlive() ? CCell::CCELL_TYPE_ALIVE : CCell::CCELL_TYPE_DEAD );
    }

    return state;
}

uint8_t CCellGrid::getSurrounding( uint16_t row, uint16_t col )
{
    uint8_t surrounding_alive = 0;

    int k = 1, l=2;
    for ( int i = 0, j=2; i < 8; i++, j++)
    {
        int r, c;

        if ( i%4 == 0 )
        {
            r = 0;
            k++;
        }
        else
        {
            r = pow(-1, k);
        }

        if ( j%4 == 0 )
        {
            c = 0;
            l++;
        }
        else
        {
            c =  pow(-1, l);
        }
        //Translate to grid

        r += row;
        c += col;

        if (( r >= 0 && r < getRows() ) && ( c >= 0 && c < getCols() ))
        {
            //std::cout << std::setw(2) << r << std::setw(3) << c << std::endl;
            surrounding_alive += getCellAt( r, c )->isAlive() ? 1 : 0;
        }
    }

    return surrounding_alive;
}

uint8_t CCellGrid::getSurrounding( CCell* cell )
{
    return getSurrounding( cell->getRow(), cell->getCol() );
}

void CCellGrid::setCellState( CCell* cell, bool alive )
{
    cell->setAlive( alive );
}

void CCellGrid::setCellAt( uint16_t row, uint16_t col, bool alive )
{
    CCell* cell = getCellAt( row, col );
    setCellState( cell, alive );
}

bool CCellGrid::getRule( CCell* cell, uint8_t amt )
{
    bool will_live;

    /* The rules */
    switch ( amt )
    {
        case 0:
        case 1:
        {
            //die (lonely)
            will_live = false;
            break;
        }
        case 2:
        {
            //persist the current state of the cell
            will_live = cell->isAlive();
            break;
        }
        case 3:
        {
            //Reproduce or live?
            //switch boolean: ((int)b + 1) % 2
            will_live = true;
            break;
        }
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        {
            //die (overcrowding)
            will_live = false;
            break;
        }
        default:
            will_live = false;
            break;
    }

    return will_live;
}

void CCellGrid::calcChanges()
{
    //Reset all previous changes:
    Changed.clear();

    for ( int i = 0; i < rows; i++ )
    {
        for ( int j = 0; j < cols; j++ )
        {
            CCell* cell = getCellAt( i, j );

            bool changeto = getRule( cell, getSurrounding( i, j ) );

            if ( cell->isAlive() != changeto )
            {
                Changed[cell] = changeto;
            }
        }
    }
}

void CCellGrid::setIntermediate()
{
    std::map<CCell*, bool>::iterator it;

    for ( it=Changed.begin(); it != Changed.end(); it++ )
    {
        //std::cout << (*it->first) << " => " << it->second << std::endl;
        it->first->setAlive( it->second );
    }

}

void CCellGrid::nextState()
{
    switch ( state )
    {
        case GRID_CALC:
        {
            calculating = true;
            calcChanges();
            setState( GRID_INTERMED );
            calculating = false;
            break;
        }
        case GRID_INTERMED:
        {
            calculating = true;
            setIntermediate();
            setState( GRID_CALC );
            calculating = false;
            generation++;
            break;
        }
    }
}


void CCellGrid::nextStep()
{
    //Run through the first state, then the second state
    nextState();
    nextState();
}


std::ostream& operator<< ( std::ostream& out, CCellGrid& cg )
{

    for ( int i = 0; i < cg.getRows(); i++ )
    {
        if ( i == 0 )
        {
            for ( int k = 0; k < cg.getCols()+2; k++ )
            {
                out << "-";
            }
            out << std::endl;
        }

        out << "|";
        for ( int j = 0; j < cg.getCols(); j++ )
        {
            CCell::CCellState state = cg.getStateAt( i, j );

            switch ( state )
            {
                case CCell::CCELL_TYPE_DEAD:
                {
                    out << " ";
                    break;
                }
                case CCell::CCELL_TYPE_ALIVE:
                {
                    out << "O";
                    break;
                }
                case CCell::CCELL_TYPE_REPROD:
                {
                    out << "+";
                    break;
                }
                case CCell::CCELL_TYPE_DYING:
                {
                    out << "-";
                    break;
                }
            }
        }
        out << "|";

        out << std::endl;

        if ( i == cg.getRows() - 1 )
        {
            for ( int k = 0; k < cg.getCols()+2; k++ )
            {
                out << "-";
            }
            out << std::endl;
        }
    }

    return out;
}

bool CCellGrid::toFile( const std::string outfile )
{
    if ( getState() != GRID_CALC )
    {
        //We have to be in a stable state to save
        nextState();
    }

    std::ofstream celldata( outfile.c_str(), std::ios::binary );

    if ( !celldata )
    {
        std::cerr << "Could not open " << outfile << " for writing." << std::endl;
        return false;
    }

    std::stringstream fmt;
    fmt << getCols() << "," << getRows() << "," << "O" << "," << "X" << std::flush;

    //std::cout << fmt.str();

    //Make sure to only use \n for line endings
    char lend = (static_cast<char>(10));
    celldata << fmt.str() << lend;

    for ( int i = 0; i < getRows(); i++ )
    {
        for ( int j = 0; j < getCols(); j++ )
        {
            CCell* cell = getCellAt( i, j );
            celldata << ( cell->isAlive() ? "O" : "X" );
        }
        celldata << lend << std::flush;
    }

    return true;
}

CCellGrid* CCellGrid::fromFile( const std::string infile, CCellGrid* cg )
{
    std::ifstream celldata( infile.c_str(), std::ios::binary );

    if ( !celldata )
    {
        std::cerr << "Could not open " << infile << " for reading." << std::endl;
        return NULL;
    }

    std::string strdata;
    std::getline( celldata, strdata );

    std::vector<std::string> fmt;

    SplitString( strdata, ",", &fmt );

    if ( fmt.empty() == true )
    {
        std::cerr << "Format empty" << std::endl;
        return NULL;
    }

    int fw = atoi( fmt[0].c_str() ),
        fh = atoi( fmt[1].c_str() );

    int on = static_cast<int> (fmt[2][0]);
    int off = static_cast<int> (fmt[3][0]);

    int cur = celldata.tellg();

    celldata.seekg( 0, std::ios::end );
    int totcells = ( (int) celldata.tellg() ) - cur;

    celldata.seekg( -1, std::ios::end );

    totcells -= ( (fh-1) + static_cast<int> (celldata.get() == 10));

    celldata.seekg( cur, std::ios::beg );

    if ( totcells != (fw*fh) )
    {
        std::cerr << "Wrong total cells" << std::endl;
        return NULL;
    }

    CCellGrid* newgrid;

    if ( cg == NULL )
    {
        newgrid = new CCellGrid( fh, fw );
    }
    else
    {
        newgrid = cg;
        newgrid->generation = 0;
        newgrid->Changed.clear();
    }

    bool allclear = true;

    for ( int lines = 0; celldata; lines++ )
    {
        if ( (lines > fh) || !allclear )
        {
            allclear = false;
            break;
        }

        std::string line;
        std::getline( celldata, line );

        for ( std::string::iterator it = line.begin(); it != line.end(); it++ )
        {
            uint16_t col = it - line.begin();

            if ( col >= fw )
            {
                allclear = false;
                break;
            }

            if ( ( (int) *it ) == on )
            {
                newgrid->setCellAt( lines, col, true );
            }
            else if ( ( (int) *it ) == off )
            {
                newgrid->setCellAt( lines, col, false );
            }
            else
            {
                std::cerr << "e: ";
                std::cerr << (int) *it << std::endl;
            }
        }
    }

    if ( !allclear )
    {
        std::cerr << "not allclear" << std::endl;
        delete newgrid;
        return NULL;
    }

    return newgrid;
}


void CCellGrid::clearGrid()
{
    /** Clear the whole grid */

    Changed.clear();

    for ( int i = 0; i < getRows(); i++ )
    {
        for ( int j = 0; j < getCols(); j++ )
        {
            setCellAt( i, j, 0 );
        }
    }
}


void CCellGrid::reset()
{
    clearGrid();
    generation = 0;
}

