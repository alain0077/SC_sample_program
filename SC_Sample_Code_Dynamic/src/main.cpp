#include "Random.h"
#include "AbsError.h"
//#include "Analysis.h"
#include "Calculation.h"

#include <time.h>
#include <bitset>
#include <fstream>
#include <iostream>

using namespace std;
using namespace SC;

int main()
{
    // ビット精度
    const int N = 256;

    // 演算誤差などを記録するクラス
    AbsError ERR_AND;

    // 乱数生成器  
    auto randN = Random(N);

    auto rnd1 = randN();
    auto rnd2 = randN();

    for(int i = 1; i < N; i++)
    {
        SN sn1 = SN(i, rnd1, N);

        for(int j = 1; j < N; j++)
        {
            SN sn2 = SN(j, rnd2, N);

            SN sn3 = AND(sn1, sn2);

            ERR_AND.Update(sn3.get_ans(), sn3.get_val());
        }
    }

    ERR_AND.print_Summary();
    
    return 0;
}