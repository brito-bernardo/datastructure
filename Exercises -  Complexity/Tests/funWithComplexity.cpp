#include "funWithComplexity.h"

//=============================================================================
// Exercise 4: Analyzing a river
//=============================================================================
// TODO
int FunWithComplexity::river(const vector<int> & v, int k, int t)
{
   int count1 = 0;
   double div = k / 2.0;
   int half = ceil(div);

    for (int i = 0; i <= v.size() - k; ++i)
    {
        int count2 = 0;
        for (int j = i; j < i + k; ++j)
        {
            if (v[j] >= t)
            {
                count2++;
            }
        }
        if (count2 >= half)
        {
            count1++;
        }
    }
    return count1;
}

//=============================================================================
// Exercise 5: Spiral of Numbers
//=============================================================================
// TODO
pair<int, int> FunWithComplexity::spiral(int n) {
    pair<int, int> ans = {0, 0};
    return ans;
}


//=============================================================================
// Exercise 7: Squared notebook
//=============================================================================
// TODO
long long FunWithComplexity::gridSum(int a, int b) {
    return 0;
}