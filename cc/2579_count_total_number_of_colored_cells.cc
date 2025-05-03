/**/
class Solution {
   public:
    long long ColoredCells(int n) {
      long long const b = n;

      long long const g = b * b;
      long long const p = (b - 1) * (b - 1);

      return g + p;
    }
};
