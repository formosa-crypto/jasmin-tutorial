#include <stdio.h>
#include <stdint.h>

uint64_t register_pressure(uint64_t arg1, uint64_t arg2, uint64_t arg3,
                           uint64_t arg4, uint64_t arg5, uint64_t arg6) {

    uint64_t val01 = arg1 * 7;
    uint64_t val02 = arg2 * 3;
    uint64_t val03 = arg3 + 11;
    uint64_t val04 = arg4 - 2;
    uint64_t val05 = arg5 * 9;
    uint64_t val06 = arg6 + 1;

    uint64_t val07 = val01 + val02;
    uint64_t val08 = val03 - val04;
    uint64_t val09 = val05 * val06;
    uint64_t val10 = val07 * 2;
    uint64_t val11 = val08 * 3;
    uint64_t val12 = val09 - 4;

    uint64_t val13 = val10 + val11;
    uint64_t val14 = val12 - val01;
    uint64_t val15 = val02 * val13;
    uint64_t val16 = val03 * val14;
    uint64_t val17 = val04 + val15;
    uint64_t val18 = val05 - val16;

    uint64_t val19 = val17 * val18;
    uint64_t val20 = val06 + val19;
    uint64_t val21 = val07 - val20;
    uint64_t val22 = val08 * val21;
    uint64_t val23 = val09 + val22;
    uint64_t val24 = val10 * val23;

    uint64_t val25 = val11 - val24;
    uint64_t val26 = val12 + val25;
    uint64_t val27 = val13 * val26;
    uint64_t val28 = val14 * val27;
    uint64_t val29 = val15 - val28;
    uint64_t val30 = val16 + val29;

    uint64_t val31 = val17 * val30;
    uint64_t val32 = val18 * val31;
    uint64_t val33 = val19 + val32;
    uint64_t val34 = val20 - val33;
    uint64_t val35 = val21 * val34;
    uint64_t val36 = val22 + val35;

    uint64_t val37 = val23 - val36;
    uint64_t val38 = val24 * val37;
    uint64_t val39 = val25 + val38;
    uint64_t val40 = val26 * val39;
    uint64_t val41 = val27 - val40;
    uint64_t val42 = val28 + val41;

    uint64_t final_result = val01 + val02 + val03 + val04 + val05 + val06 +
                            val07 + val08 + val09 + val10 + val11 + val12 +
                            val13 + val14 + val15 + val16 + val17 + val18 +
                            val19 + val20 + val21 + val22 + val23 + val24 +
                            val25 + val26 + val27 + val28 + val29 + val30 +
                            val31 + val32 + val33 + val34 + val35 + val36 +
                            val37 + val38 + val39 + val40 + val41 + val42;

    return final_result;
}
