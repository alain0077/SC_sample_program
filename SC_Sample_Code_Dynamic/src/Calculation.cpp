#include "Calculation.h"
#include "Define.h"
#include "Random.h"

#define N Define::N

using namespace SC;
using namespace std;

/*
 * Addition
*/
SN SC::MUX(const SN& augend, const SN& addend)
{
    auto n = std::min(augend.size(), addend.size());
    
    // 1/2
    SN half = SN(n/2.0, Random(n)(), n);

    // Calculation
    vector<bool> res(n);

    for(size_t i = 0; i < n; i++)
    {
        auto and1 = augend.get_sn()[i] & (~half.get_sn()[i]);
        auto and2 = augend.get_sn()[i] & half.get_sn()[i];
        res[i] = and1 | and2;
    }

    double ans = augend.get_ans() + addend.get_ans(); ans /= 2.0;

    return SN(ans, res);
}

SN SC::MUX(const SN& augend, const SN& addend, const SN& half)
{
    auto n = std::min(augend.size(), addend.size());
    n = std::min(n, half.size());

    // Calculation
    vector<bool> res(n);

    for(size_t i = 0; i < n; i++)
    {
        auto and1 = augend.get_sn()[i] & (~half.get_sn()[i]);
        auto and2 = augend.get_sn()[i] & half.get_sn()[i];
        res[i] = and1 | and2;
    }

    double ans = augend.get_ans() + addend.get_ans(); ans /= 2.0;

    return SN(ans, res);
}

SN SC::OR(const SN& augend, const SN& addend)
{
    auto n = std::min(augend.size(), addend.size());

    // Calculation
    vector<bool> res(n);
    for(size_t i = 0; i < n; i++)
    {
        res[i] = augend.get_sn()[i] | addend.get_sn()[i]; 
    }

    double ans = augend.get_ans() + addend.get_ans();

    ans = std::min(ans, 1.0);

    return SN(ans, res);
}

SN SC::NSAdd(const SN& augend, const SN& addend)
{
    auto n = std::min(augend.size(), addend.size());

    // Calculation
    // NS Addの出力
    vector<bool> nsadd(n);
    
    // Accumlaterの初期化
    int sum1 = 0, sum2 = 0;
    
    for (size_t i = 0; i < n; i++) {
        sum1 += augend.get_sn()[i] + addend.get_sn()[i];

        if (sum1 > sum2) {
            nsadd[i] = 1;
            sum2++;
        }
        else nsadd[i] = 0;
    }

    double ans = augend.get_ans() + addend.get_ans();

    ans = std::min(ans, 1.0);

    return SN(ans, nsadd);
}

/*
 * Multiplication
*/
SN SC::AND(const SN& multiplier, const SN& multiplicand)
{
    auto n = std::min(multiplier.size(), multiplicand.size());

    // Calculation
    vector<bool> res(n);

    for(size_t i = 0; i < n; i++){
        res[i] = multiplicand.get_sn()[i] & multiplier.get_sn()[i];
    }

    double ans = multiplicand.get_ans() * multiplier.get_ans();

    return SN(ans, res);
}

/*
 * Division
*/
SN SC::CORDIV(const SN& divisor, const SN& dividend)
{
    auto n = std::min(divisor.size(), dividend.size());

    //MUX
    vector<bool> mux(n);

    //D-FF
    bool d = false;

    for (size_t i = 0; i < n; i++) {
        
        mux[i] = divisor.get_sn()[i]? dividend.get_sn()[i] : d;

        d = mux[i];
    }

    // 本来の値を計算
    double ans = dividend.get_ans() / divisor.get_ans();

    return SN(ans, mux);
}

/*
 * Maximize
*/
SN Max::OR(const SN& left, const SN& right)
{
    auto n = std::min(left.size(), right.size());

    vector<bool> res(n);

    for(size_t i = 0; i < n; i++)
    {
        res[i] = left.get_sn()[i] | right.get_sn()[i];
    }

    double ans = std::max(left.get_ans(), right.get_ans());

    return SN(ans, res);
}

/*
 * Minimize
*/
SN Min::AND(const SN& left, const SN& right)
{
    auto n = std::min(left.size(), right.size());

    vector<bool> res(n);

    for(size_t i = 0; i < n; i++)
    {
        res[i] = left.get_sn()[i] & right.get_sn()[i];
    }

    double ans = std::min(left.get_ans(), right.get_ans());

    return SN(ans, res);
}