#pragma once
#include <map>
#include <queue>
#include <memory>

template<class K, class V>
class ReusablePool {
    ReusablePool(){};

    V* construct(const K& key);
    std::map<K, std::queue<V*> > pool;
public:
    ReusablePool(const ReusablePool&) = delete;
    ReusablePool(ReusablePool&&) = delete;
    ReusablePool& operator=(const ReusablePool&) = delete;
    ReusablePool& operator=(ReusablePool&&) = delete;
    ~ReusablePool(){
        for(auto& key : pool) {
            auto& q = key.second;
            while(q.size()>0) {
                delete q.front();
                q.pop();
            }
        }
    }
    static ReusablePool& instance() {
        static ReusablePool<K,V> pool;
        return pool;
    }

    void reserve(size_t count, const K& key) {
        for(int i = 0; i < count; i++) {
            pool[key].push(construct(key));
        }
    }

    std::shared_ptr<V> make(const K& key) {
        if(pool.count(key) == 0) 
            reserve(1, key);
        // TODO MUTEX LOCK FRONT&POP;
        auto result = std::shared_ptr<V>(pool[key].front(), 
            [key](V *item) { ReusablePool<K,V>::instance().release(key, item); } // [key] must be captured by copy. 
        );
        pool[key].pop();
        return result;
    };

    void release(const K& key, V* item) {
        //std::cout<<"Release called!"<<key<<std::endl;
        pool[key].push(item);
    }

    size_t countFree(const K& key) const {
        if(pool.count(key) == 0)
            return 0;
        return pool.at(key).size();
    }
};