#include <string>
#include <vector>

using namespace std;

class TruckBridge {
private:
    std::vector<int> on_bridge;
    std::vector<int> on_bridge_dist;
    std::vector<int> post_bridge;
    std::vector<int> pre_bridge;
    int max_weight = 0;
    int total_weight = 0;
    int bridge_length = 0;
    int answer = 0;

public:
    TruckBridge(int bridge_length, int weight, vector<int>& truck_weights);
    int get_answer();
    void push_truck();
    void pull_truck();
    void cross_dist(int distance);
    void add_one_sec();
    int is_bridge_empty();
    int is_waiting();
    int is_ok_to_go_in();
    int is_ok_to_go_in_and_out();
    int first_truck_distance();
};

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    TruckBridge tb(bridge_length, weight, truck_weights);
    do {
        if (tb.is_bridge_empty()) {
            tb.push_truck();
            tb.add_one_sec();
        }
        else if (tb.is_waiting()) {
            if (tb.is_ok_to_go_in()) {
                tb.cross_dist(1);
                tb.push_truck();
            }
            else if (tb.is_ok_to_go_in_and_out()) {
                tb.cross_dist(1);
                tb.push_truck();
                tb.pull_truck();
            }
            else {
                int dist = tb.first_truck_distance() - 1;
                tb.pull_truck();
                tb.cross_dist(dist);
            }
        }
        else {
            int dist = tb.first_truck_distance();
            tb.pull_truck();
            tb.cross_dist(dist);
        }
    } while (tb.is_waiting() || !tb.is_bridge_empty());
    return tb.get_answer();
}

int main() {
    printf("%d", solution(100, 100, { 10,10,10,10,10,10,10,10,10,10 }));
}

TruckBridge::TruckBridge(int bridge_length, int weight, vector<int>& truck_weights) {
    this->bridge_length = bridge_length;
    this->max_weight = weight;
    pre_bridge = truck_weights;
}
int TruckBridge::get_answer() {
    return answer;
}
void TruckBridge::push_truck() {
    on_bridge.push_back(pre_bridge.front());
    on_bridge_dist.push_back(bridge_length);
    total_weight += pre_bridge.front();
    pre_bridge.erase(pre_bridge.begin());
}
void TruckBridge::pull_truck() {
    total_weight -= on_bridge.front();
    post_bridge.push_back(on_bridge.front());
    on_bridge.erase(on_bridge.begin());
    on_bridge_dist.erase(on_bridge_dist.begin());
}
void TruckBridge::cross_dist(int distance) {
    for (int i = 0; i < on_bridge_dist.size(); i++)
        on_bridge_dist[i] -= distance;
    answer += distance;
}
void TruckBridge::add_one_sec() {
    answer++;
}
int TruckBridge::is_bridge_empty() {
    return on_bridge.empty();
}
int TruckBridge::is_waiting() {
    return !pre_bridge.empty();
}
int TruckBridge::is_ok_to_go_in() {
    return total_weight + pre_bridge.front() <= max_weight && on_bridge_dist.front() > 1;
}
int TruckBridge::is_ok_to_go_in_and_out() {
    return total_weight + pre_bridge.front() - on_bridge.front() <= max_weight && on_bridge_dist.front() == 1;
}
int TruckBridge::first_truck_distance() {
    return on_bridge_dist[0];
}