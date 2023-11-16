#include "Define.h"

// 乱数生成器の最小値と最大値
const int Define::MAX = 1023;
const int Define::MIN = 1;

// SNGの擬似乱数生成器のフラグ
// 0：LFSR，1：nonliner-LFSR
const bool Define::PRNG = false;