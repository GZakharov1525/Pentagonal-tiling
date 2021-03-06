/**
 * This structure defines one pentagon or I am simply calling it a tile.
 */
#ifndef TILE_HPP
#define TILE_HPP
#include <algorithm>
#include "Side.hpp"

struct Tile {
    Side side[5]    = {{0.0}, {0.0}, {0.0}, {0.0}, {0.0}};
    double angle[5] = {0.0};
    Tile(double sab, double sbc, double scd, double sde, double sea, double a, double b, double c,
         double d)
    {
        this->side[0].value = sab;
        this->side[1].value = sbc;
        this->side[2].value = scd;
        this->side[3].value = sde;
        this->side[4].value = sea;
        this->angle[0]      = a;
        this->angle[1]      = b;
        this->angle[2]      = c;
        this->angle[3]      = d;
        this->angle[4]      = 540.0 - (angle[0] + angle[1] + angle[2] + angle[3]);
    }
    Tile(double sab, double sbc, double scd, double sde, double sea, double a, double b, double c,
         double d, double e)
    {
        this->side[0].value = sab;
        this->side[1].value = sbc;
        this->side[2].value = scd;
        this->side[3].value = sde;
        this->side[4].value = sea;
        this->angle[0]      = a;
        this->angle[1]      = b;
        this->angle[2]      = c;
        this->angle[3]      = d;
        this->angle[4]      = e;
    }
    Tile()
    {
        this->side[0].value = 0;
        this->side[1].value = 0;
        this->side[2].value = 0;
        this->side[3].value = 0;
        this->side[4].value = 0;
        std::fill_n(this->angle, 5, 0.0);
    }
};

#endif /* TILE_HPP */
