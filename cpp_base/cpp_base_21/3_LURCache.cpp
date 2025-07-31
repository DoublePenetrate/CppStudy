#include <iostream>
#include <list>
#include <unordered_map>
using std::pair;
using std::list;
using std::unordered_map;
using std::endl;
using std::cout;

class LRUCache {
public:
    LRUCache(int capacity) 
    : _capacity(capacity)
    {}
    
    int get(int key) {
        auto it = _cache.find(key);
        if (it != _cache.end()) {
            // 找到目标元素
            _nodes.splice(_nodes.begin(), _nodes, it->second);
            return _nodes.begin()->second;
        }
        return -1;
    }
    
    void put(int key, int value) {
        auto it = _cache.find(key);
        if (it == _cache.end()) {
            // 插入新节点
            if (_capacity == _nodes.size()) {
                // list已满,需要删除最后一个节点
                auto deleteNode = _nodes.back();
                _nodes.pop_back();
                _cache.erase(deleteNode.first);
            }
            _nodes.push_front(pair<int, int>(key, value));
            _cache[key] = _nodes.begin();
        } else {
            // 在list中存在目标元素
            auto it2 = it->second;
            it2->second = value;
            _nodes.splice(_nodes.begin(), _nodes, it2);
            it->second = it2;
        }
    }

    void print() {
        for (auto it = _nodes.begin(); it != _nodes.end(); it++) {
            cout << "(" << it->first 
                << "," << it->second
                << ") ";
        }
        cout << endl;
    }

private:
    int _capacity;
    list<pair<int, int>> _nodes;
    unordered_map<int, list<pair<int, int>>::iterator> _cache;

};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

void test() {
    LRUCache lru(3);
    lru.put(1, 100);
    lru.print();

    lru.put(2, 200);
    lru.print();

    lru.get(1);
    lru.print();

    cout << lru.get(3) << endl;
    lru.put(3, 300);
    lru.print();

    lru.put(4, 400);
    lru.print();
}

int main()
{
    test();
    return 0;
}

