#include "Random.h"
#include "AbsError.h"
//#include "Analysis.h"
#include "Calculation.h"

#include <time.h>
#include <fstream>
#include <iostream>

using namespace std;
using namespace SC;

int main()
{
    clock_t start = clock();    // スタート時間
    
    // ビット精度
    const int N = 256;

    // 乱数生成器
    auto randN = Random(N);

    // 演算誤差などを記録するクラス
    AbsError ERR_ANDgate_Mult;
    AbsError ERR_ANDgate_Min;

    // 結果を書き込むファイルのストリーム
    // closeしなくてもプログラムが終われば閉じる
    std::ofstream ofs("rst/And_test_" + to_string(N) + "bit.csv");

    for(int t = 0; t < 1; t++) {
        randN.seed((unsigned int)time(NULL) + (unsigned int)t);

        // 乱数の生成
        int rn1 = randN();
        int rn2 = randN();

        // csvファイルのヘッダ
        ofs << "Mult" << "Min" << endl;

        for (int i = 1; i < N; i++) {
            SN sn1 = SN(i, rn1, N);
            for (int j = 1; j < N; j++) {
                
                // sn1と別の乱数で生成
                SN sn2 = SN(j, rn2, N);

                // sn2と同じ乱数で生成
                SN sn3 = SN(j, rn1, N);

                // 相関なし（のはず…）で AND
                SN ans1 = AND(sn1, sn2);

                // 正の相関で Min
                SN ans2 = Min::AND(sn1, sn3);

                // ファイルへの書き込み
                ofs << ans1.get_val() << ',' << ans2.get_val() << endl;

                // エラーの更新
                ERR_ANDgate_Mult.Update(ans1.get_ans(), ans1.get_val());
                ERR_ANDgate_Min.Update(ans2.get_ans(), ans2.get_val());
            }
        }
    }

    // 結果を標準出力
    cout << "AND gate (Mult)" << endl;
    ERR_ANDgate_Mult.print_Summary();
    cout << endl;
    cout << "AND gate (Min)" << endl;
    ERR_ANDgate_Min.print_Summary();
    cout << endl;

    clock_t end = clock();     // 終了時間
    cout << (double)(end - start) / CLOCKS_PER_SEC << endl;

    return 0;
}