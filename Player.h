#pragma once

#include <list>
#include <string>

struct Player;

typedef std::list<Player> PlayerList;
typedef std::list<Player>::iterator PlayerListIterator;

struct Player {

    std::string position;
    std::string name;
    int rank;
    int cost;

    Player() {
        position = "unknown";
        name = "unknown";
        rank = 0;
        cost = 0;
    }

    Player(const Player& p) {
        position = p.position;
        name= p.name;
        rank = p.rank;
        cost = p.cost;
    }

    static bool better(Player lhs, Player rhs) {
        return (lhs.rank < rhs.rank && lhs.cost <= rhs.cost);
    }

    static void filter(PlayerList& players, int count) {
        for (PlayerListIterator p = players.begin(); p != players.end(); ) {
            if (count_if(players.begin(), players.end(), bind2nd(ptr_fun(&Player::better), *p)) >= count) {
                p = players.erase(p);
            } else {
                ++p;
            }
        }
    }

};

std::ostream& operator<<(std::ostream &os, const Player& p) {
    os << p.name << ": " << p.position << ", " << p.rank << ", " << p.cost;
    return os;
}
