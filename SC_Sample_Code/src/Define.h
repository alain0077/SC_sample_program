#pragma once

class Define final
{
public:
    // SNのビット長:N，LFSRのビット数:B
    const static int N = 1024;
    const static short B = 10;

    // SNGの擬似乱数生成器のフラグ
    // 0：LFSR，1：nonliner-LFSR
    const static bool PRNG = false;
};
