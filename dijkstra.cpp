#include <bits/stdc++.h>
using namespace std;

const double INF = numeric_limits<double>::infinity();

struct Edge{
    int to;
    double time;
};

struct Node{
    int station;
    double time;
    bool operator>(const Node& other) const{
        return time > other.time;
    }
};

vector<double> dijkstra(int start, int n, const vector<vector<Edge>>& graph, vector<int>& prev){
    vector<double> min_time(n, INF);
    min_time[start] = 0;
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({start, 0});
    prev.assign(n, -1);
    while (!pq.empty()){
        Node current = pq.top();
        pq.pop();
        if (current.time > min_time[current.station]) continue;
        for (const Edge& edge : graph[current.station]){
            double new_time = current.time + edge.time;
            if (new_time < min_time[edge.to]) {
                min_time[edge.to] = new_time;
                prev[edge.to] = current.station;
                pq.push({edge.to, new_time});
            }
        }
    }return min_time;
}

double calculate_flight_time(double distance, double speed){
    return distance / speed * 60;
}

double calculate_transfer_time(){
    return 10.0;
}

vector<int> restore_path(int start, int end, const vector<int>& prev){
    vector<int> path;
    for (int at = end; at != -1; at = prev[at]){
        path.push_back(at);
        
    }reverse(path.begin(), path.end());
    if (path.front() != start) {
        return {};
    }return path;
    
}int main(){
    
    
/* От сюда можно изменять значения для составления маршрута (то есть ввиде графа)*/
                                                                    //расстояния между док-станциями
                                                                    vector<pair<int, int>> connections = {
                                                                        {0, 1}, // начало до A
                                                                        {0, 2}, // начало до B
                                                                        {1, 2} //А до B
                                                                    };
                                                                    
                                                                    vector<double> distances = {
                                                                        3, 5, 1 //км
                                                                    };
                                                                    int n = 3;//кол of вершин
/* До сюда, дальше нельзя!!!!!!!! */ 



    vector<vector<Edge>> graph(n);
    double max_distance_empty = 10;
    double max_distance_full = 5;
    double speed = 30;
    double cargo_weight = 5;
    double max_distance = max_distance_empty - (cargo_weight * (max_distance_empty - max_distance_full) / 5);
    
    for (size_t i = 0; i < connections.size(); ++i){
        int from = connections[i].first;
        int to = connections[i].second;
        double distance = distances[i];
        if (distance <= max_distance) {
            double flight_time = calculate_flight_time(distance, speed);
            graph[from].push_back({to, flight_time + calculate_transfer_time()});
            graph[to].push_back({from, flight_time + calculate_transfer_time()});
        }
    }

    int start = 0;//начало
    int end = distances.size()-1;//индекс последней станции
    vector<int> prev;
    vector<double> min_time = dijkstra(start, n, graph, prev);
    if (min_time[end] == INF){
        cout << "Нет быстрой пути" << endl;
    }else{
        cout << "Время доставки по короткому маршруту: " << min_time[end] - 10 << " мин" << endl;
        vector<int> path = restore_path(start, end, prev);
        cout << "Маршрут быстрой пути: ";
        for (size_t i = 0; i < path.size(); ++i){
            cout << path[i]; //ответ выходит в МИНУТАХ, если ответ вышел не правильно наверно вы не перевели часы в МИНУТЫ!!!!!!
            if (i < path.size() - 1) cout << " - ";
        }cout << endl;
    }
    return 0;
}
