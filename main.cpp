#include "iostream"
#include "map"
#include "hard_memory_allocator.h"
#include "container/include/container.h"

int main (int, char *[]) {
//    auto map_test = std::map<int, int, std::less<>, hard_memory_allocator<std::pair<const int, int>, 10, true>> {};
//    std::cout << map_test.size() << "xxxx" << std::endl;

    auto my_cont = Stack<int, hard_memory_allocator<int, 10, false, true>>{};
    my_cont.push_back(10);
    my_cont.push_back(20);
    my_cont.push_back(30);
    my_cont.push_back(40);
//    my_cont.push_back(50);
//    my_cont.push_back(60);
//    my_cont.push_back(70);
//    my_cont.push_back(80);
//    my_cont.push_back(90);
//    my_cont.push_back(100);

    for (int i = 0; i<my_cont.get_size(); i++) {
        std::cout << my_cont[i] << std::endl;
    }

//    decltype(my_cont) my_cont1(my_cont);
//    std::cout << "////////////////" << std::endl;
//    for (int i = 0; i<my_cont1.get_size(); i++) {
//        auto a = my_cont1[i];
//        std::cout << a << std::endl;
//    }
//
//    auto my_cont2 = Stack<int, hard_memory_allocator<int, 10, false, true>>{};
//    my_cont2.push_back(11);
//    my_cont2.push_back(21);
//    my_cont2.push_back(31);
//    my_cont2 = my_cont1;
//
//    auto b = my_cont.pop();
//    auto c = my_cont1.pop();
//    auto d = my_cont2.pop();
//    std::cout << "////////////////" << std::endl;
//    for (int i = 0; i<my_cont1.get_size(); i++) {
//        auto a = my_cont1[i];
//        std::cout << a << std::endl;
//    }
//    std::cout << "////////////////" << std::endl;
//    for (int i = 0; i<my_cont.get_size(); i++) {
//        auto a = my_cont[i];
//        std::cout << a << std::endl;
//    }
//    std::cout << "////////////////" << std::endl;
//    for (int i = 0; i<my_cont2.get_size(); i++) {
//        auto a = my_cont2[i];
//        std::cout << a << std::endl;
//    }
//    std::cout << "////////////////" << std::endl;
//    std::cout << b << std::endl;
//    std::cout << c << std::endl;
//    std::cout << d << std::endl;
    return 0;
}
