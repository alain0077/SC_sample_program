# 仕様・説明 <!-- omit in toc -->
本プログラムで実装した一部のクラスや関数の使い方などについて簡単に説明．
同じディレクトリ内にあるMakefileは計算機サーバー（sota）で使えます．
SNが固定長だったのを可変長に変更しました．
`bitset<N>`を`vector<bool>`に置き換えたのでビット演算は遅いかも…？
###### ※使用例などで書いているコードはコンパイルは通らないです．

- [SC::SN](#scsn)
  - [メンバ関数](#メンバ関数)
  - [非メンバ関数](#非メンバ関数)
  - [構築・破壊](#構築破壊)
  - [表示・取得](#表示取得)
  - [生成](#生成)
  - [相関](#相関)
- [Calculation.h](#calculationh)
  - [演算](#演算)
- [AbsError](#abserror)
  - [メンバ関数](#メンバ関数-1)
  - [構築・破壊・初期化](#構築破壊初期化)
  - [更新](#更新)
  - [表示・取得](#表示取得-1)
  - [使用例](#使用例)
- [Analysis](#analysis)
  - [メンバ関数](#メンバ関数-2)
  - [構築・破壊・初期化](#構築破壊初期化-1)
  - [更新](#更新-1)
  - [表示・取得](#表示取得-2)
  - [使用例](#使用例-1)
- [Random](#random)
  - [メンバ関数](#メンバ関数-3)
  - [構築・破壊・初期化](#構築破壊初期化-2)
  - [生成](#生成-1)
  - [プロパティ](#プロパティ)
  - [使用例](#使用例-2)

# SC::SN
Stochastic Number（SN）を生成，管理するための機能をまとめた．
`namespace SC`にグルーピングされている．
SNのビット列や値を管理するクラスやSNを生成する関数，SNの相関操作を行う関数を含む．

## メンバ関数
+ [構築・破壊](#構築破壊)
  + SN(int, int, int)
  + SN(int, int, int, int)
  + SN(double, vector<bool>)
  + ~SN() = default;
+ [表示・取得](#表示取得)
  + print_bs() : void
  + get_sn() : vector<bool>
  + get_val() : double
  + get_ans() : double

## 非メンバ関数
+ [生成](#生成)
  + SNG(int, int, int) : SN
  + SNG(int, int, int, int) : SN
+ [相関](#相関)
  + SCC(vector<bool>, vector<bool>) : double
  + SCC(SN, SN) : double

## 構築・破壊
```c++
int N;      // SNのビット長
int x;      // 定数（SNに変換する値）
int seed;   // 準乱数生成器の初期値，基本的には乱数
int shift;  // シフトするビット長
double val;   // SNの値（ ビット列中の1の数 / ビット長N ）
double ans;   // SNの本来の値（演算誤差を含まない値，生成時は　x/N となる．）
vector<bool> sn; // SNのビット列．

// 与えられた引数xより，準乱数生成器（LFSR，non-LFSR）を用いてSNを生成する．
// 準乱数生成器の初期値はseedが設定される．
SN sn1 = SN(x, seed, N);

// 用いる準乱数生成器がビットシフトに対応している．
// 基本的な生成の流れは同様．第3引数にはシフトするビット長を与える．
SN sn2 = SN(x, seed, shift, N);

// 任意のSNを生成するためのコンストラクタ．
SN sn3 = SN(val, sn);
```
> Note：
> 
> コンストラクタは3つあります．それぞれ下記のように目的によって使い分けて下さい．
> LFSRなどの準乱数生成器についての仕組みは[wiki](https://ja.wikipedia.org/wiki/Linear-feedback_shift_register)などを参照して下さい．
> なお，引数なしのデフォルトコンストラクタ（```SN()```）は宣言していないため，下記のような宣言はできません．

```c++
SN sn4; // コンパイルエラー
```

## 表示・取得
|      name      | description                            |
| :------------: | :------------------------------------- |
| ```print_bs``` | ビット列とSNの値，本来の値を表示する． |
|  ```get_sn```  | ビット列を取得する．                   |
| ```get_val```  | SNの値を取得する．                     |
| ```get_ans```  | 演算誤差なしのSNの値を取得する．       |

```c++
int N;      // SNのビット長
int x, y;   // 定数（SNに変換する値）
int seed1;  // 乱数その１
int seed2;  // 乱数その２

// SNを生成
SN sn1 = SN(x, seed1, N);
SN sn2 = SN(y, seed2, N);

// 演算前のSNの状態をprint
sn1.print_bs();

// ANDで積をとる
SN sn3 = AND(sn1, sn2);

// 演算後のSNの状態をprint
sn3.print_bs();

// 演算後のSNのパラメータを取得
double val = sn3.get_val();
double ans = sn3.get_ans();

// 演算誤差を計算
double err = ans - val;
```

## 生成
|   name    | description  |
| :-------: | :----------- |
| ```SNG``` | SNを生成する |

```c++
int N;      // SNのビット長
int x;      // 定数（SNに変換する値）
int seed;   // 準乱数生成器の初期値，基本的には乱数
int shift;  // シフトするビット長

// 与えられた引数xより，準乱数生成器（LFSR，non-LFSR）を用いてSNを生成する．
// 準乱数生成器の初期値はseedが設定される
SN sn1 = SNG(x, seed, N);

// 用いる準乱数生成器がビットシフトに対応している
// 基本的な生成の流れは同様．第3引数にはシフトするビット長を与える
SN sn2 = SNG(x, seed, shift, N);
```

## 相関
|   name    | description                          |
| :-------: | :----------------------------------- |
| ```SCC``` | 引数で与えられたSNとの相関を求める． |

```c++
int N;      // SNのビット長
int x, y;   // 定数（SNに変換する値）
int seed1;  // 乱数その１
int seed2;  // 乱数その２

// SNを生成
SN sn1 = SN(x, seed1, N);
SN sn2 = SN(y, seed1, N);
SN sn3 = SN(y, seed2, N);

// 2つのSNの相関を求める
double scc1 = SCC(sn1, sn2);
double scc2 = SCC(sn1, sn3);

// andをとる
AND(sn1, sn2); // Min
AND(sn1, sn3); // 掛け算
```
> Note：
> 
> この例の```scc1```と```scc2```は違う値になります．
> 厳密には，```scc1```は1に近い値を，```scc2```は0に近い値をそれぞれとる（はず…）．
> このとき，```sn1```と```sn2```，```sn1```と```sn3```の組み合わせでANDをとると，Min関数と掛け算という結果にそれぞれなります．

# Calculation.h
SCに関する演算をまとめたヘッダ．実装した関数は，`namespace SC`にグルーピングしている．SCにおける演算をまとめている．実装した演算は，下記の表の通り．

## 演算
|      name      | description                                  |
| :------------: | :------------------------------------------- |
|   ```MUX```    | 1/2スケール加算．                            |
|    ```OR```    | 入力の負の相関が最大のときに，飽和加算．     |
|  ```NSAdd```   | 飽和加算．                                   |
|   ```AND```    | 入力に相関ないときに，乗算．                 |
|  ```CORDIV```  | 入力の正の相関が最大のときに，除算．         |
| ```Min::AND``` | 入力の正の相関が最大のときに，最小値を出力． |
| ```Max::OR```  | 入力の正の相関が最大のときに，最小値を出力． |

# AbsError
演算誤差を保持・管理するクラス．
Mean Absolute Error（MAE）やMean Absolute Percentage Error（MAPE）を計算し，それらの最大値や最小値も記録する．

## メンバ関数
+ [構築・破壊・初期化](#構築破壊初期化)
  + AbsError()
  + ~AbsError() = default;
  + reset()
+ [更新](#更新)
  + Update(const double&, const double&) : void
+ [表示・取得](#表示取得-1)
  + get_MAE() : double
  + get_MAPE() : double
  + get_MAX_AE() : double
  + get_MAX_APE() : double
  + get_MIN_AE() : double
  + get_MIN_APE() : double
  + print_Summary() : void

## 構築・破壊・初期化
|      name      | description                                   |
| :------------: | :-------------------------------------------- |
| ```AbsError``` | 生成．                                        |
|  ```reset```   | MAEやMAPEなどの演算誤差のパラメータの初期化． |

## 更新
|     name     | description                          |
| :----------: | :----------------------------------- |
| ```Update``` | 与えられた引数からパラメータを更新． |

## 表示・取得
|        name         | description                              |
| :-----------------: | :--------------------------------------- |
|    ```get_MAE```    | 絶対平均誤差を取得する．                 |
|   ```get_MAPE```    | 平均エラー率を取得する．                 |
|  ```get_MAX_AE```   | 最大の絶対誤差を取得する．               |
|  ```get_MAX_APE```  | 最大のエラー率を取得する．               |
|  ```get_MIN_AE```   | 最小の絶対誤差を取得する．               |
|  ```get_MIN_APE```  | 最小のエラー率を取得する．               |
| ```print_Summary``` | それぞれのパラメータをまとめて表示する． |

## 使用例
Stochastic Number Generator（SNG）に与えるseed値を固定したとき，Nビット長のSNの全ての組み合わせに対して，掛け算を実行しています．そして，結果を`print_Summary()`で表示すると，MAEやMAPEなどを確認することができます．

```c++
int N;      // SNのビット長
int seed1;  // 乱数その１
int seed2;  // 乱数その２

// AbsErrorクラスを生成
AbsError error;

// SNGに与えるseedを固定して
// 入力の全パターンを実行
for(int i = 1; i < N; i++) {
  for(int j = 1; j < N; j++) {
    // 入力SNを生成
    SN sn1 = SN(i, seed1, N);
    SN sn2 = SN(j, seed2, N);

    // 演算実行
    SN ans = AND(sn1, sn2);

    // 誤差の更新
    error.Update(ans.get_ans(), ans.get_val())
  }
}

// 演算誤差などの結果を表示
error.print_Summary();
```

# Analysis
[AbsError](#abserror)クラスを継承したクラス．相関による演算誤差を確かめるために，与えられた入力の組み合わせの中で，相関が1，0，-1にそれぞれ一番近いときの誤差を記録する機能を追加した．

## メンバ関数
+ [構築・破壊・初期化](#構築破壊初期化-1)
  + Analysis()
  + ~Analysis() = default;
  + reset()
+ [更新](#更新-1)
  + Update(const double&, const double&, const double&) : void
+ [表示・取得](#表示取得-2)
  + get_MAE() : double
  + get_MAPE() : double
  + get_MAX_AE() : double
  + get_MAX_APE() : double
  + get_MIN_AE() : double
  + get_MIN_APE() : double
  + get_SCC() : vector<pair<double, double>>
  + print_Summary() : void

## 構築・破壊・初期化
|      name      | description                                   |
| :------------: | :-------------------------------------------- |
| ```Analysis``` | 生成．                                        |
|  ```reset```   | MAEやMAPEなどの演算誤差のパラメータの初期化． |

## 更新
|     name     | description                          |
| :----------: | :----------------------------------- |
| ```Update``` | 与えられた引数からパラメータを更新． |

## 表示・取得
|        name         | description                                            |
| :-----------------: | :----------------------------------------------------- |
|    ```get_MAE```    | 絶対平均誤差を取得する．                               |
|   ```get_MAPE```    | 平均エラー率を取得する．                               |
|  ```get_MAX_AE```   | 最大の絶対誤差を取得する．                             |
|  ```get_MAX_APE```  | 最大のエラー率を取得する．                             |
|  ```get_MIN_AE```   | 最小の絶対誤差を取得する．                             |
|  ```get_MIN_APE```  | 最小のエラー率を取得する．                             |
|    ```get_SCC```    | 相関が1，0，-1にそれぞれ一番近いときの誤差を取得する． |
| ```print_Summary``` | それぞれのパラメータをまとめて表示する．               |

## 使用例
基本的な使い方はAbsErrorの[使用例](#使用例-2)で示されている通りですが，`Update`の引数が違う点に注意して下さい．

```c++
int N;      // SNのビット長
int seed1;  // 乱数その１
int seed2;  // 乱数その２

// AbsErrorクラスを生成
Analysis error;

// SNGに与えるseedを固定して
// 入力の全パターンを実行
for(int i = 1; i < N; i++) {
  for(int j = 1; j < N; j++) {
    // 入力SNを生成
    SN sn1 = SN(i, seed1, N);
    SN sn2 = SN(j, seed2, N);

    // 演算実行
    SN ans = AND(sn1, sn2);

    // 誤差の更新
    error.Update(ans.get_ans(), ans.get_val(), SCC(sn1, sn2))
  }
}

// 演算誤差などの結果を表示
error.print_Summary();
```

# Random
SNの生成時にSNGに与える整数の乱数を生成するためのクラス．C++のライブラリである`random`を用いた乱数生成の流れをクラスにまとめた．分布生成器は一様整数分布（`uniform_int_distribution`）を，疑似乱数生成器はメルセンヌ・ツイスター法（`mt19937`）を用いている．詳しくは[こちら](https://cpprefjp.github.io/reference/random.html)を参照．乱数生成のためのseed値は，コンストラクタの呼び出し時に`rnd()`で得られる値で初期化される．また，SNのビット長をNとすると，乱数の生成範囲は`1`から`N - 1`までに初期化される．

## メンバ関数
+ [構築・破壊・初期化](#構築破壊初期化-3)
  + Random()
  + Random(int)
  + Random(int, int)
  + ~Random() = default;
  + reset() : void
+ [生成](#生成)
  + operator() () : int;
+ [プロパティ](#プロパティ)
  + range(int, int) : void
  + seed(unsigned int) : void
  + max() : int
  + min() : int

## 構築・破壊・初期化
|   name    | description    |
| :-------: | :------------- |
| `Random`  | コンストラクタ |
| `~Random` | デストラクタ   |
|  `reset`  | 状態を初期化   |

## 生成
|     name     | description      |
| :----------: | :--------------- |
| `operator()` | 乱数を生成する． |

## プロパティ
|  name   | description                    |
| :-----: | :----------------------------- |
| `range` | 生成範囲を設定する．           |
| `seed`  | seed値を設定する．             |
|  `max`  | 生成し得る値の上限を取得する． |
|  `min`  | 生成し得る値の下限を取得する． |

## 使用例
```c++
int N;    // SNのビット長
int x,y;  // 定数（SNに変換する値）

// 乱数生成器を生成
// Define::MINからDefine::MAXまでの乱数を生成
// Define.hで定義されています．
auto randN = Random();
// 1からM-1までの乱数を生成
auto randM = Random(M);
// minからmaxまでの乱数を生成
auto rand = Random(min, max);

// 乱数を生成
int rnd1 = randN();
int rnd2 = randN();

// 乱数rndからSNを生成
SN sn1 = SN(x, rnd1);
SN sn2 = SN(y, rnd2);

// 相関
double scc = SCC(sn1, sn2);
```
これは，2つの乱数を生成してから，その乱数をもとに，2つのSNを生成している．
`sn2`と`sn2`の相関は`0`もしくは，`0`に近い値になる（はず…）．