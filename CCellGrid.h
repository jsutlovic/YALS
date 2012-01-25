#ifndef _CCELLGRID_H_
#define _CCELLGRID_H_

#include "includer.h"
#include "CCell.h"


class CCellGrid
{
    public:
        enum GridState {
            GRID_CALC = 0,
            GRID_INTERMED
        };

    private:
        CCellGrid();

        uint16_t rows;
        uint16_t cols;

        uint32_t generation;

        bool calculating;

        GridState state;

        std::vector< std::vector< CCell* > > Grid;
        std::map< CCell*, bool > Changed;


    public:
        CCellGrid( uint16_t rows, uint16_t cols );
        ~CCellGrid();

        uint16_t getRows() { return rows; }
        uint16_t getCols() { return cols; }

        uint32_t getGeneration() { return generation; }

        bool isCalculating() { return calculating; }

        GridState getState() { return state; }
        void setState( GridState newState ) { state = newState; }

        CCell* getCellAt( uint16_t row, uint16_t col );

        CCell::CCellState getStateAt( uint16_t row, uint16_t col );

        std::map< CCell*, bool>* getChanged() { return &Changed; }

        uint8_t getSurrounding( CCell* cell );
        uint8_t getSurrounding( uint16_t row, uint16_t col );

        void setCellState( CCell* cell, bool alive );
        void setCellAt( uint16_t row, uint16_t col, bool alive );

        bool getRule( CCell* cell, uint8_t amt );

        void calcChanges();
        void setIntermediate();

        //Half-step
        void nextState();
        //Full next step
        void nextStep();

        friend std::ostream& operator<< ( std::ostream& out, CCellGrid& cg );

        bool toFile( const std::string outfile );
        static CCellGrid* fromFile( const std::string infile, CCellGrid* cg = NULL );

        void clearGrid();

        void reset();

}; //CCellGrid


#endif // _CCELLGRID_H_
