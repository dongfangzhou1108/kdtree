
#include <bits/stdc++.h>
#include "Point.h"
#include "BoundedPQueue.h"
using namespace std;

#define DEBUG

class node {
public:
    size_t idx;
    size_t dim;
    node* left;
    node* right;

    node(size_t idx_, size_t dim_) : 
        idx(idx_), dim(dim_) {}
};

template<size_t N, typename T>
class KDTree {
public:

    // 根据不同维度最大-最小差值选择树分割维度
    size_t SelectDimension(size_t& start, size_t& end) {
    
        struct cmpobj {
            size_t dim;
            vector<Point<N>>* pts;

            cmpobj(size_t dim_, vector<Point<N>>* pts_) : dim(dim_), pts(pts_) {}
    
            bool operator()(int i, int j) const {
                return (*pts)[i][dim] < (*pts)[j][dim]; 
            }
        };

        double span[N];
        for(size_t i=0; i<N; i++){
            auto pair =  std::minmax_element(indices.begin() + start, 
                indices.begin() + end, cmpobj(i, &points));
            span[i] = pair.second[i] - pair.first[i];
        }

        auto index = std::distance(span, std::max_element(span, span + N));
        return static_cast<size_t>(index);
    }



    // 寻找某个维度下的中位数，保证kd树分布均匀
    size_t Partition(size_t& start, size_t& end, size_t& dim) {

        struct cmpobj {
            size_t dim;
            vector<Point<N>>* pts;

            cmpobj(size_t dim_, vector<Point<N>>* pts_) : dim(dim_), pts(pts_) {}
    
            bool operator()(int i, int j) const {
                return (*pts)[i][dim] < (*pts)[j][dim]; 
            }
        };  

        if(end - start <= 0)
            return -1;
        size_t median = start + (end - start)/2;
        std::nth_element(indices.begin() + start, indices.begin()+median , indices.begin() + end, 
            cmpobj(dim, &points));
        double mid_val = points[indices[median]][dim];

        for(size_t i = median + 1; i < end; i++) {
            if (points[indices[i]][dim] == mid_val) {
                size_t tmp =indices[++median];
                indices[median] = indices[i];
                indices[i] = tmp;
            }
        }

        // for debug same value of median 
        #ifdef DEBUG
            for(size_t i = median + 1; i < end; i++)
                assert(points[indices[i]][dim] != mid_val);
        #endif

        return median;
    }



    // 建立树时的递归函数
    node* DivideTree(size_t& start, size_t& end) {

        if(end - start <= 0)
            return nullptr;
        else if(end - start <= 1 && end != count){
            node* res = new node(indices[start], 0); // 叶子节点任选一个平面分割方向
            return res;
        }

        size_t dim = SelectDimension(start, end);
        size_t median = Partition(start, end, dim);
        node* res = new node(indices[median], dim);

        res->left = DivideTree(start, median);
        res->right = DivideTree(++median,end);

        return res;
    }



    // 对象构造函数
    KDTree(vector<Point<N>> points_, vector<T> elements_)
    {

        points = points_;
        elements = elements_;
        count = points.size();

        indices.resize(points_.size());
        iota(indices.begin(),indices.end(),0);

        size_t start = 0, end = points.size();
        root = DivideTree(start, end);
    }



    // k近邻搜索递归函数
    void traverse(const node* n, const Point<N>& key_pt, BoundedPQueue<T>& pq_dist) const {
        if(n != nullptr){

            Point<N> cur_pt;
            double dist;
            cur_pt = points[n->idx];
            dist = Distance(cur_pt, key_pt);
            pq_dist.enqueue(elements[n->idx],dist);

            if(key_pt[n->dim] <= cur_pt[n->dim]){

                traverse(n->left, key_pt, pq_dist);

                if(pq_dist.size() < pq_dist.maxSize() ||
                    abs(key_pt[n->dim] - cur_pt[n->dim]) < pq_dist.worst() )
                    traverse(n->right, key_pt, pq_dist);

            }else{

                traverse(n->right, key_pt, pq_dist);

                if(pq_dist.size() < pq_dist.maxSize() ||
                    abs(key_pt[n->dim] - cur_pt[n->dim]) < pq_dist.worst())
                    traverse(n->left, key_pt, pq_dist);
                
            }
        }
        return;
    }



    // k近邻搜索
    BoundedPQueue<T> KNNSearch(const Point<N>& key, size_t k) const {
        BoundedPQueue<T> res(k);

        traverse(root, key, res);

        return res;
    }



    // radius search 递归函数
    void traverse(const node* n, const Point<N>& key_pt, const double radius, BoundedPQueue<T>& pq_dist) const {
        if(n != nullptr) {

            Point<N> cur_pt;
            double dist;
            cur_pt = points[n->idx];
            dist = Distance(cur_pt, key_pt);
            if(dist <= radius)
                pq_dist.enqueue(elements[n->idx],dist);
            
            // splite plane distance
            double sp_dist = cur_pt[n->dim] - key_pt[n->dim];
            if(sp_dist > 0 && sp_dist > radius)
                traverse(n->left, key_pt, radius, pq_dist);
            else if(sp_dist < 0 && -sp_dist > radius)
                traverse(n->right, key_pt, radius, pq_dist);
            else{
                traverse(n->left, key_pt, radius, pq_dist);
                traverse(n->right, key_pt, radius, pq_dist);
            }
            
        }
    }



    // radius search
    BoundedPQueue<T> RadiusSearch(const Point<N>& key, double radius) const {
        BoundedPQueue<T> res;

        traverse(root, key, radius, res);

        return res;
    }




    node* root;
    size_t count;
    vector<Point<N>> points;
    vector<T> elements;
    vector<size_t> indices;
    unordered_set<size_t> mSet;
};



