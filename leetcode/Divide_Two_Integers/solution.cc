#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Solution {
  public:
    static_assert(sizeof(int) < sizeof(long));

    int divide(int dividend, int divisor) {
        long p{dividend};
        long q{divisor};

        const long r = div_positive(abs(p), abs(q));
        const long r_signed = changes_sign(p, q) ? -r : r;

        if (r_signed < numeric_limits<int>::min())
            return numeric_limits<int>::min();

        if (r_signed > numeric_limits<int>::max())
            return numeric_limits<int>::max();

        return static_cast<int>(r_signed);
    }

  private:
    static long div_positive(long p, long q) {
        assert(p >= 0L);
        assert(q > 0L);
        if (p == q)
            return 1L;
        if (p < q)
            return 0L;
        if (p - q < q)
            return 1L;
        if (q == 1L)
            return p;

        pair<long, long> fprod = closest_doubled(p, q);
        if (fprod.second == p)
            return fprod.first;
        assert(fprod.second < p);

        fprod = closest_incremented(p, q, fprod);
        return fprod.first;
    }

    static pair<long, long> closest_doubled(long target, long q) {
        assert(q < target);
        long factor = 1L;
        long prod = q;

        while (true) {
            const long prod1 = prod + prod;
            if (prod1 > target)
                break;

            prod = prod1;
            factor = factor + factor;
        }

        return make_pair(factor, prod);
    }

    static pair<int, int>
    closest_incremented(long target, long q,
                        const pair<long, long> &start_with) {
        long factor = start_with.first;
        long prod = start_with.second;

        while (true) {
            const long prod1 = prod + q;
            if (prod1 > target)
                break;

            prod = prod1;
            ++factor;
        }

        return make_pair(factor, prod);
    }

    static bool changes_sign(long p, long q) {
        return !(p == 0L || (p > 0L && q > 0L) || (p < 0L && q < 0L));
    }
};

ostream &operator<<(ostream &os, pair<long, long> p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

int main() {
    const int dividend = 1026117192;
    const int divisor = -874002063;
    const int result = Solution().divide(dividend, divisor);

    cout << dividend << " / " << divisor << " = " << result << endl;

    return 0;
}
