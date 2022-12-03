#include <algorithm>
#include <iostream>
#include <vector>

void OutFirst(std::vector<int>& v, int n) {
    std::sort(v.begin(), v.end());
    for (int i = 0; i < n; ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}
int main() {
    int n, should_out;

    std::vector<int> num_array{};
    while (std::cin >> n >> should_out) {
        for (int i = 0; i < n; i++) {
            int tmp;
            std::cin >> tmp;
            num_array.push_back(tmp);
        }

        OutFirst(num_array, should_out);

        num_array.erase(num_array.begin(), num_array.end());
    }
    return 0;
}
