#include "SN.h"
#include <iostream>

#define N Define::N
#define B Define::B
#define flag Define::PRNG

using namespace std;
using namespace SC;

// プロトタイプ宣言
vector<int> lfsr(int seed);
vector<int> nonlinear_lfsr(int seed);
vector<int> get_seq_linear();
vector<int> get_seq_nonlinear();

/// @brief コンストラクタ，数値xを初期値seedのLFSRまたは，nonliner LFSRベースのSNGでSNに変換し、値などを変数に登録
/// @param x 定数
/// @param seed 乱数生成器のseed
SN::SN(int x, int seed)
{
    _sn = SNG(x, seed).get_sn();
    _ans = (double)x  / (double)N;
    _val = (double)_sn.count() / (double)N;
}

/// @brief コンストラクタ，数値xを初期値seedのLFSRでSNに変換し，値などを変数に登録，複数のSNGでLFSRを共有する時のビットシフトに対応
/// @param x 定数
/// @param seed 乱数生成器のseed
/// @param shift ビットシフトするビット長
SN::SN(int x, int seed, int shift)
{
    _sn = SNG(x, seed, shift).get_sn();
    _ans = (double)x  / (double)N;
    _val = (double)_sn.count() / (double)N;
}

/// @brief コンストラクタ，指定したビット列のSNを生成．
/// @param ans 本来の値
/// @param val SNの値
/// @param sn SNのビット列
SN::SN(double ans, double val, std::bitset<N> sn) : _ans(ans), _val(val), _sn(sn)
{
}

// 保持しているSNとその値を表示 
void SN::print_bs() const
{
    cout << _sn << " = " << _sn.count() << "/" << N << " = " << _val << endl;
}

/// @brief 定数xを初期値seedのLFSR，nonliner LFSRでSNに変換
/// @param x 定数
/// @param seed 乱数生成器のseed
SN SC::SNG(int x, int seed)
{
    bitset<N> sn;

    // LFSRまたは，nonliner LFSRより準乱数列を生成
    vector<int> lds = flag? nonlinear_lfsr(seed) : lfsr(seed);

    // Comparator
    for (int i = 0; i < N; i++) {
        // lfsrは1～N-1の範囲の値を出力するため，>=で比較
        if (!flag && x >= lds[i]) sn.set(i);
        // nonlinear lfsrは0～N-1の範囲の値を出力するため，>で比較
        else if(flag && x > lds[i]) sn.set(i);
    }

    return SN((double)x / (double) N, (double)sn.count()/(double)N, sn);
}

/// @brief 定数xを初期値seedのLFSR，nonliner LFSRでSNに変換
/// @param x 定数
/// @param seed 乱数生成器のseed
/// @param shift ビットシフトするビット長
SN SC::SNG(int x, int seed, int shift)
{
    bitset<N> sn;

    // ビットシフト用の値の設定
    int mask = (1 << B) - 1;
    int shift1 = (1 << shift) - 1;    int shift2 = mask - shift1;
    int shift3 = shift1 << (B - shift);  int shift4 = mask - shift3;
    
    // LFSRまたは，nonliner LFSRより準乱数列を生成
    vector<int> lds = flag? nonlinear_lfsr(seed) : lfsr(seed);

    // Comparator
    for (int i = 0; i < N; i++) {
        // ビットシフト後の値
        int shift_lfsr;

        // LFSRから出力された準乱数をビットシフトする
        int lfsr1, lfsr2;
        lds[i] = lds[i] & mask;

        if (shift == 0) {
            shift_lfsr = lds[i];
        }
        else {
            lfsr1 = lds[i] & shift1;       lfsr2 = lds[i] & shift2;
            lfsr1 = lfsr1 << (B - shift);  lfsr2 = lfsr2 >> shift;
            lfsr1 = lfsr1 & shift3;        lfsr2 = lfsr2 & shift4;
            shift_lfsr = lfsr1 | lfsr2;
        }

        // lfsrは1～N-1の範囲の値を出力するため，>=で比較
        if (!flag && x >= shift_lfsr) sn.set(i);
        // nonlinear lfsrは0～N-1の範囲の値を出力するため，>で比較
        else if(flag && x > shift_lfsr) sn.set(i);
    }

    return SN((double)x / (double) N, (double)sn.count()/(double)N, sn);
}

// 2つのSNの相関の強さを取得
double SC::SCC(const SN& lhs, const SN& rhs)
{
    bitset<N> sn1 = lhs.get_sn();
    bitset<N> sn2 = rhs.get_sn();
    bitset<N> sn3 = sn1 & sn2;

    double p12 = (double)sn3.count() / (double)N;
    double p1 = (double)sn1.count() / (double)N;
    double p2 = (double)sn2.count() / (double)N;

    double omega = p12 - (p1 * p2);
    double scc;

    double a = p1 + p2 - 1;
    double b = 0;

    if (omega > 0) {
        scc = omega / (min(p1, p2) - (p1 * p2));
    }
    else {
        scc = omega / ((p1 * p2) - max(a, b));
    }

    if (isnan(scc)) {
        return 0;
    }

    return scc;
}

/// @brief Fibonacci LFSR（線形帰還シフトレジスタ）
/// @param x 目的の定数
/// @param seed 乱数生成器のseed
/// @return 準乱数列
vector<int> lfsr(int seed)
{
    // bit mask
    int mask = (1 << B) - 1;

    // shift register
    int sr = seed;

    // XORの位置情報について取得
    vector<int> list = get_seq_linear();

    // return
    vector<int> res;

    for(int i = 0; i < N; i++) {
        res.push_back(sr);

        // 最上位ビットを抽出
        bool msb = (sr & (1 << (B - 1))) == (1 << (B - 1));

        // 配置したxorについて演算する（次の最下位ビットの決定）
        for (auto l : list) msb ^= (sr & (1 << l)) == (1 << l);

        // 1ビット左シフト
        sr <<= 1;

        // 最下位ビットにxorの演算結果を挿入
        sr |= msb;

        // bit masking
        sr &= mask;
    }

    return res;
}

/// @brief nonliner LFSR（非線形帰還シフトレジスタ）
/// @param x 目的の定数
/// @param seed 乱数生成器のseed
/// @return 準乱数列
vector<int> nonlinear_lfsr(int seed)
{
    // shift register
    int sr = seed;

    // XORの位置情報について取得
    vector<int> list = get_seq_nonlinear();

    // return
    vector<int> res;

    for(int i = 0; i < N; i++) {
        res.push_back(sr);

        // 最下位ビット以外がゼロかどうかの判定
        int nor = sr == 0 || sr == 1;

        // フェードバック関数の結果を格納する変数
        int b = nor;

        // 配置したxorについて演算する
        for(auto l : list) b ^= (sr >> l) & 1;

        // 1ビット右シフト
        sr >>= 1;
        
        // 上位にビットにフィードバック関数の結果を挿入
        sr |= b << (B-1);
    }

    return res;
}

/// @brief 最長Fibonacci LFSRの構成において、XORの入力へ繋がるビットの設定
/// @return XORの配置位置を示す配列
vector<int> get_seq_linear()
{
    if (B == 3)
        return { 1 };
    if (B == 4)
        return { 2 };
    if (B == 5)
        return { 2 };
    if (B == 6)
        return { 4 };
    if (B == 7)
        return { 5 };
    if (B == 8)
        return { 5, 4, 3 };
    if (B == 9)
        return { 4 };
    if (B == 10)
        return { 6 };
    if (B == 11)
        return { 8 };
    if (B == 12)
        return { 10, 9, 3 };

    return {};
}

/// @brief 最長Nonliner LFSRの構成において、XORの入力へ繋がるビットの設定
/// @return XORの配置位置を示す配列
vector<int> get_seq_nonlinear()
{
    if (B == 3)
        return { 2, 0 };
    if (B == 4)
        return { 3, 0 };
    if (B == 5)
        return { 3, 0 };
    if (B == 6)
        return { 5, 0 };
    if (B == 7)
        return { 6, 0 };
    if (B == 8)
        return { 6, 5, 4, 0 };
    if (B == 9)
        return { 5, 0 };
    if (B == 10)
        return { 7, 0 };
    if (B == 11)
        return { 9, 0 };
    if (B == 12)
        return { 11, 10, 4, 0 };

    return {};
}