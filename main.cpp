#include <iostream>
#include <Eigen/Dense>

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

    void reserve(const K& key, size_t count) {
        for(int i = 0; i < count; i++) {
            pool[key].push(construct(key));
        }
    }

    std::shared_ptr<V> get(const K& key) {
        if(pool.count(key) == 0) 
            reserve(key, 1);
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

    size_t count(const K& key) const {
        if(pool.count(key) == 0)
            return 0;

        return pool.at(key).size();
    }
};

template<>
Eigen::VectorXd* ReusablePool<size_t, Eigen::VectorXd>::construct(const size_t& size) {
    //std::cout<<"Hello there: "<<size<<std::endl;
    return new Eigen::VectorXd(size);
}

template<>
Eigen::MatrixXd* ReusablePool<std::pair<size_t, size_t>, Eigen::MatrixXd>::construct(const std::pair<size_t, size_t>& sizes) {
    //std::cout<<"Hello there: "<<sizes.first<<" "<<sizes.second<<std::endl;
    return new Eigen::MatrixXd(sizes.first, sizes.second);
}

template<class V>
std::shared_ptr<V> make_reusable(size_t width, size_t height) {
    return ReusablePool<std::pair<size_t, size_t>, V>::instance().get({width, height});
}

template<class V>
std::shared_ptr<V> make_reusable(size_t size) {
    return ReusablePool<size_t, V>::instance().get(size);
}

int main() {
    ReusablePool<size_t, Eigen::VectorXd>::instance().reserve(5,10);
    auto a = make_reusable<Eigen::VectorXd>(5); 
    {auto b = make_reusable<Eigen::VectorXd>(5); }
    std::cout<< ReusablePool<size_t, Eigen::VectorXd>::instance().count((size_t)5) << std::endl;
    ReusablePool<std::pair<size_t, size_t>, Eigen::MatrixXd>::instance().reserve({5,8},3);

    {
        auto r_d = make_reusable<Eigen::MatrixXd>(3,5); auto& d = *r_d.get();
        d.fill(1);
        std::cout<<d<<std::endl;
    } 

    std::cout<< ReusablePool<std::pair<size_t, size_t>, Eigen::MatrixXd>::instance().count({5,8}) << std::endl;
    std::cout<< ReusablePool<std::pair<size_t, size_t>, Eigen::MatrixXd>::instance().count({3,5}) << std::endl;
    return 0;
}