#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include "DoublyLinkedList.hpp"
#include <unordered_map>
#include <iostream>
using namespace std;

template<typename K, typename V>
class LRUCache {
    private:
    int capacity;
    DoublyLinkedList<K,V> dll;
    unordered_map<K , Node<K,V>*> cache;

    public:
    LRUCache(int capacity) :capacity(capacity) {}

    V get(K key) {
        auto it = cache.find(key);

        if(it == cache.end()) {
            throw runtime_error("Key not found"); 
        }

        Node<K,V>* node = it -> second;
        dll.moveToFront(node);
        return node ->value;
    }

    void put(K key, V value) {
        auto it = cache.find(key);
        if(it != cache.end()) {
            Node<K,V>* node = it -> second;
            node -> value = value;
            dll.moveToFront(node);
        }
        else {
            if(cache.size() >= capacity) {
                // Node<K,V>* lastNode = dll.removeLast();
                // cache.erase(lastNode->key);

                Node<K,V>* lastNode = dll.getTail();
                cache.erase(lastNode -> key);
                dll.removeLast();

            }
        }

        Node<K,V> * newNode = dll.addTOFront(key,value);
        cache[key] = newNode;
    }


    bool contains(K key) const {
        return cache.find(key) != cache.end();
    }

    int getSize() const {
        return cache.size();
    }

    bool isEmpty() const {
        return cache.empty();
    }

    void clear(){
        while (!dll.isEmpty())
        {
            Node<K,V>* node = dll.removeLast();
            cache.erase(node->key);
            delete node;
            /* code */
        }
        
    }

    void display() const {
        std::cout << "Cache contents: " << std::endl;
        Node<K,V>* current = dll.getHead();
        while(current) {
            std::cout << "Key: " << current->key << ", Value: " << current->value << std::endl;
            current = current -> next;
        }
        std::cout << "-----------------" << std::endl;
    }
    
};
#endif