#include "iostream"
#include "map"
#include "hard_memory_allocator.h"
#include "container/include/container.h"

int main (int, char *[]) {
    auto map_test = std::map<int, int, std::less<>, hard_memory_allocator<std::pair<const int, int>, 10, true>> {};
    std::cout << map_test.size() << "xxxx" << std::endl;

    auto my_cont = Stack<int>{};
    my_cont.push_back(10);
    my_cont.push_back(20);
    my_cont.push_back(30);
    decltype(my_cont) my_cont1(my_cont);

    auto my_cont2 = Stack<int>{};
    my_cont2.push_back(11);
    my_cont2.push_back(21);
    my_cont2.push_back(31);
    my_cont2 = my_cont1;

    auto b = my_cont.pop();
    for (int i = 0; i<2; i++) {
        auto a = my_cont[i];
    }
    std::cout << b << std::endl;
    return 0;
}
