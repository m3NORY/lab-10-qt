#include <iostream>
#include "cache/cache.h"

int main() {
    Cache<int, std::string, LRUPolicy<int>> cache(2);

    cache.put(1, "A");
    cache.put(2, "B");
    cache.get(1);       // обновляем LRU
    cache.put(3, "C");  // вытеснит 2

    std::cout << "Contains 2: " << cache.contains(1) << "\n";
    std::cout << "Contains 2: " << cache.contains(2) << "\n";
    std::cout << "Contains 2: " << cache.contains(3) << "\n";
    std::cout << "Contains 1: " << cache.contains(1) << "\n";
    std::cout << "Contains 1: " << cache.contains(2) << "\n";
    std::cout << "Contains 1: " << cache.contains(3) << "\n";

    Cache<int, std::string, FIFOPolicy<int>> fifo(2);
    fifo.put(1, "A");
    fifo.put(2, "B");
    fifo.put(3, "C"); // вытеснит 1

    std::cout << "FIFO contains 1: " << fifo.contains(1) << "\n";

    Cache<int, std::string, LFUPolicy<int>> lfu(2);
    lfu.put(1, "A");
    lfu.put(2, "B");
    lfu.get(1);
    lfu.get(1);
    lfu.put(3, "C");

    std::cout << "LFU contains 2: " << lfu.contains(2) << "\n";

    return 0;
}
