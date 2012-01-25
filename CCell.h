#ifndef _CCELL_H_
#define _CCELL_H_

#include "includer.h"

class CCell
{
    private:
        bool alive;
        uint16_t row;
        uint16_t col;

    public:
        enum CCellState {
            CCELL_TYPE_DEAD = 0,
            CCELL_TYPE_ALIVE,
            CCELL_TYPE_REPROD,
            CCELL_TYPE_DYING
        };

    private:
        CCell();

    public:
        CCell( uint16_t row, uint16_t col, bool alive ) : alive( alive ), row( row ), col( col ) {}

        bool isAlive  ()             { return alive; }
        void setAlive ( bool alive ) { this->alive = alive; }

        uint16_t getRow () { return row; }
        uint16_t getCol () { return col; }

        friend std::ostream& operator<< ( std::ostream& out, const CCell& cell ) { return out << "[" << cell.row << "," << cell.col << "]: " << cell.alive; }

}; //CCell


#endif // _CCELL_H_
