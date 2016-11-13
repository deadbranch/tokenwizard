#ifndef TOKENWIZARD_INTPOW_H
#define TOKENWIZARD_INTPOW_H

inline int int_pow(int base, int exp)
{
    int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp /= 2;
        base *= base;
    }
    return result;
}

#endif //TOKENWIZARD_INTPOW_H
