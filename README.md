# kdtree

have test by pcl, support knn search and radius search

参考网站
http://www.whudj.cn/?p=920
https://zhuanlan.zhihu.com/p/53826008
https://zhuanlan.zhihu.com/p/45346117
https://www.joinquant.com/view/community/detail/c2c41c79657cebf8cd871b44ce4f5d97
https://cs.stackexchange.com/questions/123947/find-nearest-neighbour-in-a-radius

pcl build tree 1.64ms
build 6.17ms
改变随机选择维度 3.05ms 维度选择 -> 保证搜索效率

优化方向 flann近似中位数 -> 保证均匀二叉树 增加搜索效率 
https://www.youtube.com/watch?v=PzbZ52gy8Bc 计算中位数
https://www.google.com.hk/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwjp3cPLi6vyAhWUH3AKHfbsC9sQFnoECAMQAQ&url=https%3A%2F%2Fwww.dmi.unict.it%2F~battiato%2Fdownload%2FMedianLNCS.pdf&usg=AOvVaw1ZLG0njkfhilJF7pdhfgx-
