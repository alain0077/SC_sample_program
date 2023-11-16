#pragma once
#include "Define.h"
#include <vector>
#include <algorithm>
#include <cmath>

namespace SC {
  class SN
  {
  private:
    int _N;
    std::vector<bool> _sn;  // SNのビット列
    double _val;    // SNの値
    double _ans;   // 本来の分子の値

  public:
    /// @brief コンストラクタ，数値xを初期値seedのLFSRまたは，nonliner LFSRベースのSNGでSNに変換し、値などを変数に登録
    /// @param x 定数
    /// @param seed 乱数生成器のseed
    /// @param N ビット長
    SN(int x, int seed, int N);

    /// @brief コンストラクタ，数値xを初期値seedのLFSRまたは，nonliner LFSRベースのSNGでSNに変換し、値などを変数に登録
    /// @param x 定数
    /// @param seed 乱数生成器のseed
    /// @param shift ビットシフトするビット長
    /// @param N ビット長
    SN(int x, int seed, int shift, int N);

    /// @brief コンストラクタ，指定したビット列のSNを生成
    /// @param ans 本来の値
    /// @param sn SNのビット列
    SN(double ans, std::vector<bool> sn);

    // デストラクタ
    ~SN() = default;

    // 保持しているSNとその値を表示 
    void print_bs() const;

    // SNのビット長を取得
    std::size_t size() const { return _sn.size(); };

    // SNを取得
    std::vector<bool> get_sn() const { return _sn; };

    // SNの値を取得
    double get_val() const { return _val; };

    // SNの本来の分子の値を取得
    double get_ans() const { return _ans; };
  };

  /// @brief 定数xを初期値seedのLFSR，nonliner LFSRでSNに変換
  /// @param x 定数
  /// @param seed 乱数生成器のseed
  /// @param N ビット長
  SN SNG(int x, int seed, int N);

  /// @brief 定数xを初期値seedのLFSR，nonliner LFSRでSNに変換，複数のSNGでLFSRを共有する時のビットシフトに対応
  /// @param x 定数
  /// @param seed 乱数生成器のseed
  /// @param shift ビットシフトするビット長
  /// @param N ビット長
  SN SNG(int x, int seed, int shift, int N);

  /// @brief 2つのSNの相関の強さを取得
  /// @param sn 比較対象
  /// @note サイズの違うSNを与えると小さい方に合わせて処理をする．
  double SCC(const std::vector<bool>& lhs, const std::vector<bool>& rhs);

  /// @brief 2つのSNの相関の強さを取得
  /// @param sn 比較対象
  /// @note サイズの違うSNを与えると小さい方に合わせて処理をする．
  double SCC(const SN& lhs, const SN& rhs);
}