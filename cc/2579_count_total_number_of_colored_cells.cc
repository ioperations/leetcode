/**/
class Solution {
   public:
    long long coloredCells(int n) {
        long long b = n;

        long long g = b * b;
        long long p = (b - 1) * (b - 1);

        return g + p;
    }
};
