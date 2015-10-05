#include <iostream>
#include <vector>
#include <string>
#include <complex>
#include <queue>
#include <climits>
using namespace std;

void print_maze(const vector<string>& maze) {
    for (auto row : maze) {
        cout << row << endl;
    }
    cout << endl;
}

const vector<int> dx = {0, 1, 0, -1};
const vector<int> dy = {-1, 0, 1, 0};

typedef pair<int, int> ii;

void solve(vector<string>& maze, ii start, ii goal) {
    int h = maze.size();
    int w = maze[0].size();


    priority_queue<pair<int, ii>, vector<pair<int, ii>>, greater<pair<int, ii>>> q;
    q.push(make_pair(0, start));

    while (!q.empty()) {
        if (q.top().second == goal) {
            return;
        }

        int d = q.top().first;
        int x = q.top().second.first;
        int y = q.top().second.second;;
        q.pop();
        maze[y][x] = 'x';

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (0 <= nx && nx < w && 0 <= ny && ny < h && maze[ny][nx] == '.') {
                int dist2 = (goal.first - nx) * (goal.first - nx) + (goal.second - ny) * (goal.second - ny);
                q.push(make_pair(dist2, make_pair(nx, ny)));
            }
        }
    }
}

int main() {
    vector<string> maze = {
        "#####.####",
        "#........#",
        "#.###.#..#",
        "#...#.#..#",
        "###.#.#..#",
        "#...#.#..#",
        "#.###.#..#",
        "#...#.#..#",
        "###.###..#",
        "#.....#..#",
        "#####.####"
    };
    ii start(5, 0), goal(5, 10);

    print_maze(maze);
    solve(maze, start, goal);
    print_maze(maze);
}
