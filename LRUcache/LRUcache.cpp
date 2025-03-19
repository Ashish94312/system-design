#include "LRUCache.hpp"
#include <iostream>
using namespace std;


int main() {

    LRUCache<int, string> cache(3);

    cache.put(1, "One");
    cache.put(2, "Two");
    cache.put(3, "Three");

    cache.display();

    cout << "Getting value for key 2: " << cache.get(2) << endl;

    cache.display();

    cache.put(4, "Four");

    cache.display();

    cache.put(3, "Three Updated");

    cache.display();

    cache.put(5, "Five");

    cache.display();

   

    
    
    
}