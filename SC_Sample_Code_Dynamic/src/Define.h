#pragma once

class Define final
{
public:
    // 乱数生成器の最小値と最大値
    const static int MIN;
    const static int MAX;

    // SNGの擬似乱数生成器のフラグ
    // 0：LFSR，1：nonliner-LFSR
    const static bool PRNG;
};
