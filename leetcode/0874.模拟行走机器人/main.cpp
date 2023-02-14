#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

//自定义哈希函数，元素类型为 pair<T1, T2> a(X1, X2);
struct pair_hash
{
    template <class T1, class T2>
    size_t operator () (pair<T1, T2> const &pair) const
    {
        size_t h1 = hash<T1>()(pair.first); //用默认的 hash 处理 pair 中的第一个数据 X1
        size_t h2 = hash<T2>()(pair.second);//用默认的 hash 处理 pair 中的第二个数据 X2
        return h1 ^ h2;
    }
};

int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
    unordered_set<pair<int, int>, pair_hash> hash1;
    for(auto ob : obstacles) hash1.insert({ob[0], ob[1]}); //存储所有障碍物坐标

    int x = 0, y = 0, distance = 0;	//起点(0,0)，距离初值 0
    int direction = 0;    			// 0:North, 1:East, 2:South, 3:West
    for(int tmp : commands) {
        if(tmp == -1) direction = (direction + 1) % 4; 		//向右转 90 度
        else if(tmp == -2) direction = (direction + 3) % 4;  	//向左转 90 度
        else {
        	//判断机器人方向
        	int x1 = 0, y1 = 0;		//x1表示X轴增量，y1表示y轴增量
            if(direction == 0) y1 = 1;			//向北走 1 格
            else if(direction == 1) x1 = 1;		//向东走 1 格
            else if(direction == 2) y1 = -1;	//向南走 1 格
            else x1 = -1;						//向西走 1 格
            //判断走过去会不会撞到障碍物    
            while(tmp--) {     
                if(hash1.find({x + x1, y + y1}) != hash1.end()) break;//撞到了原地停留
                x += x1, y += y1;								//没撞到，向前走
                //cout<<'('<<x<<','<<y<<')'<< endl;
                distance = max(distance, x * x + y * y);
            }
        }
    }
    return distance;
}

int main(){
    vector<int> a = {7,-2,-2,7,5};		//测试用例
    vector<vector<int>> obstacles = {{-3,2},{-2,1},{0,1},{-2,4},{-1,0},{-2,-3},{0,-3},{4,4},{-3,3},{2,2}};
    cout << "The max_distance is " << robotSim(a, obstacles) << endl;
    return 0;
}

