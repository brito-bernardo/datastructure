#include "funWithCycles.h"
#include <algorithm>

//=============================================================================
// Exercise 1: Palindromes
//=============================================================================
// TODO
bool FunWithCycles::palindrome(const std::string & s) {

    std::cout << s << std::endl;

    for (int i = 0; i < s.size(); i++ )
    {

        if (s[i] != s[s.size()-i-1])
        {
            return false;
        }

    }

    return true;
}


//=============================================================================
// Exercise 2: Palindrome Sentences
//=============================================================================
// TODO
bool FunWithCycles::palindromeSentence(const std::string & s) {

    // Juntar
    std::string res;
    char temp;

    for(char c : s)
    {
        if (isalpha(c))
        {
            temp = tolower(c);
            res.push_back(temp);
        }
    }
    return palindrome(res);

}


//=============================================================================
// Exercise 3: Interesting Numbers
//=============================================================================
// TODO
int FunWithCycles::nextInterestingNumber(int n, int sum) {

    int iterador = n;
    while(n > 0)
    {
        if (digitSum(iterador) == sum && iterador > n)
        {
         return iterador;
        }
        iterador++;
    }
    return 0;
}

// This auxiliary function should return the sum of the digits of n
// TODO
int FunWithCycles::digitSum(int n) {
    int sum = 0;
    std::string temp = to_string(n);
    for (int i = 0; i < temp.size(); ++i)
    {
        sum = sum + (n % 10);
        n = n / 10;
    }
    return sum;

}


//=============================================================================
// Exercise 4: Winter is coming
//=============================================================================
// TODO
int FunWithCycles::winter(const vector<int> & v) {

    int count = 0;
    int max = 0;
    for (int i = 0; i < v.size() - 1; ++i)
    {
        if (v[i] > v[i+1])
        {
            count++;
        }
        else
        {
            if (max < count)
            {
                max = count;
            }
            count = 0;

        }
        if (count > max) {
            max = count;
        }
    }

    return max;
}


//=============================================================================
// Exercise 5: Playing with vectors
//=============================================================================

// a) count
// TODO
int FunWithCycles::count(const vector<int> & v, int n) {
    int count = 0;
    for (int i = 0; i < v.size(); ++i)
    {
        if (v[i] == n)
        {
           count++;
        }
    }

    return count;
}

// b) hasDuplicates
// TODO
bool FunWithCycles::hasDuplicates(const vector<int> & v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        for (int j = i+1; j < v.size(); ++j)
        {
            if (v[i] == v[j])
            {
                return true;
            }
        }
    }


    return false;
}

// c) removeDuplicates
// TODO
void FunWithCycles::removeDuplicates(vector<int> & v)
{
    vector<int> res;
    bool find = false;

    for (int i = 0; i < v.size(); ++i)
    {
        find = false;
        for (int j = 0; j < res.size(); ++j)
        {

            if (v[i] == res[j])
            {
                find = true;
            }
        }

        if (find == false)
        {
            res.push_back(v[i]);
        }

    }

    v = res;

}

// d) merge
// TODO
bool comparator(int i, int j)
{
    if (i < j)
    {
        return true;
    }
    else
    {
        return false;
    }
}

vector<int> FunWithCycles::merge(const vector<int> & v1, const vector<int> & v2) {
    vector<int> ans;

    for(auto i: v1)
    {
        ans.push_back(i);
    }
    for(auto i:v2)
    {
        ans.push_back(i);
    }

    std::sort(ans.begin(), ans.end(), comparator);





    return ans;
}



//=============================================================================
// Exercise 6: Playing with prime numbers
//=============================================================================

// a) isPrime
// TODO
bool FunWithCycles::isPrime(int n)
{
    for (int i = 2; i <= n/2 ; ++i)
    {
        if (n % i == 0)
        {
            return false;
        }

    }
    return true;
}

// b) factorize
// TODO
vector<int> FunWithCycles::factorize(int n)
{
    vector<int> ans;
    int temp = n;

    for (int i = 2; i < n; ++i)
    {
        if (temp % i == 0)
        {
            temp = temp / i;
            ans.push_back(i);
            i--;
        }


    }

    if (ans.empty())
    {
        ans.push_back(n);
    }

    return ans;

}

// c) listPrimes
// TODO
vector<int> FunWithCycles::listPrimes(int n) {
    vector<int> ans;

    for(int i = 2; i <= n; ++i)
    {
        if (isPrime(i))
        {
            ans.push_back(i);
        }
    }

    return ans;
}
