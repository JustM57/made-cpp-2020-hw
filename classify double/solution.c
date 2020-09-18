#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>



/**
 * Library-level functions.
 * You should use them in the main sections.
 */

uint64_t convertToUint64 (double number) {
    return *((uint64_t *)(&number));
}

bool getBit (const uint64_t number, const uint8_t index) {
    uint32_t mask = 1 << index;
    uint32_t temp = mask & number;
    temp >>= index;
    return temp;
}

uint8_t countNBits (const uint64_t number, const uint8_t start_index,
                    const uint8_t end_index) {
    uint8_t counter = 0;
    for (uint8_t bit = start_index; bit <= end_index; ++bit) {
        if getBit(number, bit) ++counter;
    }
    return counter;
}
/**
 * Checkers here:
 */

bool checkForPlusZero (uint64_t number) {
    return number == 0x0000000000000000;
}

bool checkForMinusZero (uint64_t number) {
    return number == 0x8000000000000000;
}

bool checkForPlusInf (uint64_t number) {
    return number == 0x7FF0000000000000;
}

bool checkForMinusInf (uint64_t number) {
    return number == 0xFFF0000000000000;
}

bool checkForNormal (uint64_t number) {
    //count exponent bits
    uint8_t counter = countNBits(number, 1, 11);
    return ((counter > 0) && (counter < 11))
}

bool checkForPlusNormal (uint64_t number) {
    return (!getBit(number, 0) && checkForNormal(number))
}

bool checkForMinusNormal (uint64_t number) {
    return (getBit(number, 0) && checkForNormal(number))
}

bool checkForDenormal (uint64_t number) {
    uint8_t exp_bit = countNBits(number, 1, 11);
    uint8_t frac_bit = countNBits(number, 12, 63);
    return ((exp_bit == 0) && (frac_bit > 1));
}

bool checkForPlusDenormal (uint64_t number) {
    return (!getBit(number, 0) &&checkForDenormal(number));
}

bool checkForMinusDenormal (uint64_t number) {
    return (getBit(number, 0) &&checkForDenormal(number));
}

bool checkForSignalingNan (uint64_t number) {
    uint8_t exp_bit = countNBits(number, 0, 11);
    uint8_t fbit = getBit(number, 12);
    return ((exp_sum == 12) && !fbit);
}

bool checkForQuietNan (uint64_t number) {
    uint8_t bits_sum = countNBits(number, 0, 12);
    return (bits_sum == 13);
}


void classify (double number) {
    if (checkForPlusZero(convertToUint64(number))) {
        printf("Plus zero\n");
    }

    else if (checkForMinusZero(convertToUint64(number))) {
        printf("Minus zero\n");
    }

    else if (checkForPlusInf(convertToUint64(number))) {
        printf("Plus inf\n");
    }

    else if (checkForMinusInf(convertToUint64(number))) {
        printf("Minus inf\n");
    }

    else if (checkForPlusNormal(convertToUint64(number))) {
        printf("Plus normal\n");
    }

    else if (checkForMinusNormal(convertToUint64(number))) {
        printf("Minus normal\n");
    }

    else if (checkForPlusDenormal(convertToUint64(number))) {
        printf("Plus Denormal\n");
    }

    else if (checkForMinusDenormal(convertToUint64(number))) {
        printf("Minus Denormal\n");
    }

    else if (checkForSignalingNan(convertToUint64(number))) {
        printf("Signailing NaN\n");
    }

    else if (checkForQuietNan(convertToUint64(number))) {
        printf("Quiet NaN\n");
    }

    else {
        printf("Error.\n");
    }
}
