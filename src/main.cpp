#include <cstdlib>
#include <iostream>
#include <map>
#include <ostream>
#include <queue>
#include <sys/types.h>
#include <vector>

using namespace std;

class game_entity {
  public:
    string name;
    uint stand_point = 0;
    double speed;

    game_entity(string n, double sp) : name(n), speed(sp) {}
};

enum game_event {
    GAME_ROUND_START,
    GAME_ROUND_END,
    GAME_ENEMY_ROUND_START,
    GAME_ATTACKED
};

class game_process {

    map<game_event, vector<void (*)()>> feedbacks;

  public:
    // game_process() { feedbacks[GAME_ROUND_START] = vector<void (*)()>(); }
    void addListenner(game_event e, void (*oncall)()) {
        feedbacks[GAME_ROUND_START].push_back(oncall);
    }
    void call(game_event e) {
        for (void (*oncall)() : feedbacks.at(e)) {
            oncall();
        }
    }
};

class waiting_queue {
    queue<game_entity> _wq;

  public:
    void next_act() {
        auto &en = _wq.front();
        cout << en.speed << " " << en.name << endl;

        _wq.pop();
    }

    waiting_queue &push(game_entity e) {
        _wq.push(e);
        return *this;
    }

    bool empty() { return _wq.empty(); }
};

auto main() -> int {

    auto gprocess = game_process();

    gprocess.addListenner(GAME_ROUND_START,
                          [] { cout << "round start" << endl; });

    auto q = waiting_queue();

    q.push(game_entity("seele", 140)).push(game_entity("bronya", 120));

    while (!q.empty()) {
        gprocess.call(GAME_ROUND_START);
        q.next_act();
    }

    return EXIT_SUCCESS;
}
