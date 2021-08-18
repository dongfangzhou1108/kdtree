#ifndef BOUNDED_PQUEUE_INCLUDED
#define BOUNDED_PQUEUE_INCLUDED

#include <map>
#include <algorithm>
#include <limits>

using namespace std;

template <typename T>
class BoundedPQueue {
public:
	// 不允许隐式转换
    explicit BoundedPQueue();
    explicit BoundedPQueue(size_t maxSize);
    
	//向优先队列中存储数据
    void enqueue(const T& value, double priority);
    
	// 将优先度最高的元素剔除队列
    T dequeueMin();
    
	// 返回优先队列元素大小
    size_t size() const;
    bool empty() const;
    
	// 返回优先队列最大容纳元素数量
    size_t maxSize() const;
    
	// 返回优先度最小/最大值
    double best()  const;
    double worst() const;
	//返回是否存在某个priority的值
    size_t count(const double key) const;

public:
	// 用于存储priority和附加值,priority从小到大,小的保留大的删除
    multimap<double, T> elems;
	// 优先队列最大数据量
    size_t maximumSize;
};










template <typename T>
BoundedPQueue<T>::BoundedPQueue() {
    maximumSize = UINT64_MAX;
}

template <typename T>
BoundedPQueue<T>::BoundedPQueue(size_t maxSize) {
    maximumSize = maxSize;
}

// 向elems存储priority和附加值
template <typename T>
void BoundedPQueue<T>::enqueue(const T& value, double priority) {
    elems.insert(make_pair(priority, value));
    
    if (size() > maxSize()) {
        typename multimap<double, T>::iterator last = elems.end();
        --last; // Now points to highest-priority element
        elems.erase(last);
    }
}

template <typename T>
T BoundedPQueue<T>::dequeueMin() {
    // Copy the best value.
    T result = elems.begin()->second;
    
    // Remove it from the map.
    elems.erase(elems.begin());
    
    return result;
}

template <typename T>
size_t BoundedPQueue<T>::size() const {
    return elems.size();
}

template <typename T>
bool BoundedPQueue<T>::empty() const {
    return elems.empty();
}

template <typename T>
size_t BoundedPQueue<T>::maxSize() const {
    return maximumSize;
}

template <typename T>
double BoundedPQueue<T>::best() const {
    return empty()? numeric_limits<double>::infinity() : elems.begin()->first;
}

template <typename T>
double BoundedPQueue<T>::worst() const {
    return empty()? numeric_limits<double>::infinity() : elems.rbegin()->first;
}

template <typename T>
size_t BoundedPQueue<T>::count(const double key) const{
    return elems.count(key);
}

#endif // BOUNDED_PQUEUE_INCLUDED
