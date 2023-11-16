#include "Calculation.h"

#include "Define.h"
#include "Random.h"

#define N Define::N

using namespace SC;

/*
 * Addition
*/
SN SC::MUX(const SN& augend, const SN& addend)
{
    // 1/2
    SN half = SN(N/2, Random()());

    // Calculation
    auto and1 = augend.get_sn() & (~half.get_sn()); 
    auto and2 = augend.get_sn() & half.get_sn();
    auto or1 = and1 | and2;

    double ans = augend.get_ans() + addend.get_ans(); ans /= 2.0;

    double val = (double)or1.count() / (double) N;

    return SN(ans, val, or1);
}

SN SC::MUX(const SN& augend, const SN& addend, const SN& half)
{
    // Calculation
    auto and1 = augend.get_sn() & (~half.get_sn()); 
    auto and2 = augend.get_sn() & half.get_sn();
    auto or1 = and1 | and2;

    double ans = augend.get_ans() + addend.get_ans(); ans /= 2.0;

    double val = (double)or1.count() / (double) N;

    return SN(ans, val, or1);
}

SN SC::OR(const SN& augend, const SN& addend)
{
    // Calculation
    auto or1 = augend.get_sn() & (~addend.get_sn()); 

    double ans = augend.get_ans() + addend.get_ans();

    ans = ans > 1.0 ? 1.0 : ans;

    double val = (double)or1.count() / (double) N;

    return SN(ans, val, or1);
}

SN SC::NSAdd(const SN& augend, const SN& addend)
{
    // Calculation
    // NS Addの出力
    std::bitset<N> nsadd;
    
    // Accumlaterの初期化
    int sum1 = 0, sum2 = 0;
    
    for (int i = 0; i < N; i++) {
        sum1 += augend.get_sn()[i] + addend.get_sn()[i];

        if (sum1 > sum2) {
            nsadd[i] = 1;
            sum2++;
        }
        else nsadd[i] = 0;
    }

    double ans = augend.get_ans() + addend.get_ans();

    ans = ans > 1.0 ? 1.0 : ans;

    double val = (double)nsadd.count() / (double) N;

    return SN(ans, val, nsadd);
}

/*
 * Multiplication
*/
SN SC::AND(const SN& multiplier, const SN& multiplicand)
{
    auto sn = multiplicand.get_sn() & multiplier.get_sn();

    double ans = multiplicand.get_ans() * multiplier.get_ans();

    double val = (double)sn.count() / (double)N;

    return SN(ans, val, sn);
}

/*
 * Division
*/
SN SC::CORDIV(const SN& divisor, const SN& dividend)
{
    //MUX
    std::bitset<N> mux;

    //D-FF
    int d = 0;

    for (int i = 0; i < N; i++) {
        
        mux[i] = divisor.get_sn()[i]? dividend.get_sn()[i] : d;

        d = mux[i];
    }

    // 本来の値を計算
    double ans = dividend.get_ans() / divisor.get_ans();

    // 出力SNの値を計算
    double val = (double)mux.count()/(double)Define::N;

    return SN(ans, val, mux);
}

/*
 * Maximize
*/
SN Max::OR(const SN& left, const SN& right)
{
    auto sn = left.get_sn() | right.get_sn();

    double ans = left.get_ans() > right.get_ans() ? left.get_ans() : right.get_ans();

    double val = (double)sn.count() / (double)N;

    return SN(ans, val, sn);
}

/*
 * Minimize
*/
SN Min::AND(const SN& left, const SN& right)
{
    auto min = left.get_sn() & right.get_sn();

    double ans = left.get_ans() < right.get_ans() ? left.get_ans() : right.get_ans();

    double val = (double)min.count() / (double)N;

    return SN(ans, val, min);
}