#ifndef _CCOLOUR_H_
#define _CCOLOUR_H_

#include <string>
#include <cstdlib>
#include <iostream>

#ifdef _WIN32
# include <SDL\SDL.h>
#else
# include <SDL/SDL.h>
#endif


class CColour
{
    /** 24bpp pixel colour */

    private:
        uint8_t r;
        uint8_t g;
        uint8_t b;

    public:
        CColour()
        {
            r = 0x00;
            g = 0x00;
            b = 0x00;
        }

        CColour( uint8_t r, uint8_t g, uint8_t b ) : r(r), g(g), b(b) {}

        CColour( std::string colourstring ) { setColour( colourstring ); }

        uint8_t getR() { return r; }
        uint8_t getG() { return g; }
        uint8_t getB() { return b; }

        void setColour( std::string colourstring )
        {
            uint8_t r, g, b;

            int offset = ( colourstring[0] == '#' );

            r = strtol( colourstring.substr( offset,   2 ).c_str(), NULL, 16 );
            g = strtol( colourstring.substr( offset+2, 2 ).c_str(), NULL, 16 );
            b = strtol( colourstring.substr( offset+4, 2 ).c_str(), NULL, 16 );

            setColour( r, g, b );
        }

        void setColour( uint8_t r, uint8_t g, uint8_t b )
        {
            setR( r );
            setG( g );
            setB( b );
        }

        void setR( uint8_t r ) { this->r = r; }
        void setG( uint8_t g ) { this->g = g; }
        void setB( uint8_t b ) { this->b = b; }

        Uint32 toRGB( SDL_Surface* surf )
        {
            return SDL_MapRGB( surf->format, r, g, b );
        }

        friend std::ostream& operator<< ( std::ostream& out, CColour& colour )
        {
            out << "#" << std::hex << std::setfill('0') << std::setw(2) << (int)colour.r << std::setw(2) << (int)colour.g << (int)colour.b;
            return out;
        }
};

#endif // _CCOLOUR_H_
