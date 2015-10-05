#include <vector>
#include <utility>
#include <cfloat>
#include <stdexcept>
using namespace std;

class BellmanFord {
public:
    int v_size;
    int e_size;
    vector<vector<pair<bool, double>>> edges;
    vector<double> distances;

    void find(int start) {
        fill(begin(distances), end(distances), DBL_MAX);
        distances[start] = 0.0;

        int cnt;
        for (int cnt = 0; cnt < v_size; cnt++) {
            if (!update()) {
                break;
            }
        }

        if (cnt == v_size) {
            throw logic_error("Found negative loop");
        }
    }

    bool update() {
        bool changed = false;
        for (int i = 0; i < v_size; i++) {
            for (int j = 0; j < v_size; j++) {
                if (!edges[i][j].first) {
                    continue;
                }
                double old_cost = distances[j];
                double new_cost = distances[i] + edges[i][j].second;
                if (new_cost < old_cost) {
                    distances[j] = new_cost;
                    changed = true;
                }
            }
        }
        return changed;
    }
};
