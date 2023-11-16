#pragma once
#include "SN.h"

namespace SC
{
    /*
     * Addition
    */
    SN MUX(const SN& augend, const SN& addend);
    SN MUX(const SN& augend, const SN& addend, const SN& half);
    SN OR(const SN& augend, const SN& addend);
    SN NSAdd(const SN& augend, const SN& addend);
    
    /*
     * Multiplication
    */
    SN AND(const SN& multiplier, const SN& multiplicand);

    /*
     * Division
    */
    SN CORDIV(const SN& divisor, const SN& dividend);

    namespace Min
    {
        SN AND(const SN& left, const SN& right);
    }

    namespace Max
    {
        SN OR(const SN& left, const SN& right);
    }
}