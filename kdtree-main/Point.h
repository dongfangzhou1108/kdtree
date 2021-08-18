#ifndef POINT_INCLUDED
#define POINT_INCLUDED

#include <cmath>
#include <bits/stdc++.h>

template <size_t N>
class Point {
public:
	//  用数组指针作为迭代器
    typedef double* iterator;
    typedef const double* const_iterator;
    
	// 返回点的维度
    size_t size() const;
    
	//返回点index维度上的值
    double& operator[](size_t index);
    double operator[](size_t index) const;
    
	// 方便遍历点的各个维度
    iterator begin();
    iterator end();
    
    const_iterator begin() const;
    const_iterator end() const;

private:
    // 点实际存储在数组中
    double coords[N];
};

// 用于计算两点间的欧氏距离
template <size_t N>
double Distance(const Point<N>& one, const Point<N>& two);

// 判断两点是否相等
template <size_t N>
bool operator==(const Point<N>& one, const Point<N>& two);

template <size_t N>
bool operator!=(const Point<N>& one, const Point<N>& two);










template <size_t N>
size_t Point<N>::size() const {
    return N;
}

template <size_t N>
double& Point<N>::operator[] (size_t index) {
    return coords[index];
}

template <size_t N>
double Point<N>::operator[] (size_t index) const {
    return coords[index];
}

template <size_t N>
typename Point<N>::iterator Point<N>::begin() {
    return coords;
}

template <size_t N>
typename Point<N>::const_iterator Point<N>::begin() const {
    return coords;
}

template <size_t N>
typename Point<N>::iterator Point<N>::end() {
    return begin() + size();
}

template <size_t N>
typename Point<N>::const_iterator Point<N>::end() const {
    return begin() + size();
}

template <size_t N>
double Distance(const Point<N>& one, const Point<N>& two) {
    double result = 0.0;
    for (size_t i = 0; i < N; ++i)
        result += (one[i] - two[i]) * (one[i] - two[i]);
    
    return sqrt(result);
}

template <size_t N>
bool operator==(const Point<N>& one, const Point<N>& two) {
    return std::equal(one.begin(), one.end(), two.begin());
}

template <size_t N>
bool operator!=(const Point<N>& one, const Point<N>& two) {
    return !(one == two);
}

#endif