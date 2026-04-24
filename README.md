# LRU/FIFO кэш с настраиваемой политикой  
Описание  
Данная библиотека представляет собой **шаблонный кэш с политиками вытеснения**, реализованный в стиле **header-only**.  
Поддерживаются следующие политики:  
**LRU (Least Recently Used)** — удаляет давно неиспользуемый элемент  
**FIFO (First In First Out)** — удаляет самый старый добавленный элемент  
**LFU (Least Frequently Used)** — удаляет наименее часто используемый элемент  
##
**Пример использования**
*LRU Cache*  
Cache<int, std::string, LRUPolicy<int>> cache(2);  
cache.put(1, "A");  
cache.put(2, "B");  
cache.get(1); // обновляет использование  
cache.put(3, "C"); // вытесняет элемент 2  
std::cout << cache.contains(2); // 0 (false)  
  
*FIFO Cache*  
Cache<int, std::string, FIFOPolicy<int>> cache(2);  
cache.put(1, "A");  
cache.put(2, "B");  
cache.put(3, "C"); // удалится 1  
  
*LFU Cache*  
Cache<int, std::string, LFUPolicy<int>> cache(2);  
cache.put(1, "A");  
cache.put(2, "B");  
cache.get(1);  
cache.get(1); // увеличиваем частоту  
cache.put(3, "C"); // удалится 2  
  
*Сборка проекта*  
Требования:  
CMake 3.16+  
C++17  
Компилятор (GCC / Clang / MSVC)  
  
*Сборка*  
mkdir build  
cd build  
cmake ..  
cmake --build .  
##  

**Результаты тестирования**  
Все тесты проходят успешно:  
[==========] Running 10 tests from 3 test suites  
[----------] Global test environment set-up.  
[ RUN      ] LRU.EvictionWorks  
[       OK ] LRU.EvictionWorks (0 ms)  
[ RUN      ] FIFO.EvictionOrder  
[       OK ] FIFO.EvictionOrder (0 ms)  
[ RUN      ] LFU.LeastFrequentlyUsedEvicted  
[       OK ] LFU.LeastFrequentlyUsedEvicted (0 ms)  
...
[----------] 10 tests from 3 test suites ran.
[  PASSED  ] 10 tests.

