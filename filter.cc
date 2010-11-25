#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <iterator>

using namespace std;

#include "Player.h"

PlayerList qbs;
PlayerList rbs;
PlayerList wrs;
PlayerList tes;
PlayerList ds;
PlayerList ks;
PlayerList players;

float pos_scale(std::string pos) {
    float scale = 1.0f;
    switch(pos.at(0)) {
        case 'Q': scale = 17.0f; break;
        case 'R': scale = 25.0f; break;
        case 'W': scale = 45.0f; break;
        case 'T': scale = 6.0f; break;
        case 'D': scale = 9.0f; break;
        case 'K': scale = 1.0f; break;
    }
    return scale;
}

int main(int argc, char** argv) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [data file]\n";
        return 1;
    }

    ifstream infile(argv[1]);
    string line;
    Player p;
    char posi;

    while (getline(infile, line)) {

        istringstream iss(line);
        string item;

        getline(iss, item, ',');
        istringstream i(item);
        i >> posi;
        p.position = item;

        getline(iss, item, ',');
        p.name = item;

        getline(iss, item, ',');
        istringstream j(item);
        j >> p.rank;

        getline(iss, item, ',');
        istringstream k(item);
        k >> p.cost;

        switch (posi) {

            case 'Q':
                qbs.push_back(p);
                break;
            case 'R':
                rbs.push_back(p);
                break;
            case 'W':
                wrs.push_back(p);
                break;
            case 'T':
                tes.push_back(p);
                break;
            case 'D':
                ds.push_back(p);
                break;
            case 'K':
                ks.push_back(p);
                break;
            default:
                throw std::runtime_error("Ahh -- new position??");
        }

    }

    /*
    Player::filter(qbs, 1);
    Player::filter(tes, 1);
    Player::filter(ds, 1);
    Player::filter(ks, 1);
    Player::filter(rbs, 2);
    Player::filter(wrs, 3);
    */

    players.insert(players.begin(), qbs.begin(), qbs.end());
    players.insert(players.begin(), tes.begin(), tes.end());
    players.insert(players.begin(), ds.begin(), ds.end());
    players.insert(players.begin(), ks.begin(), ks.end());
    players.insert(players.begin(), rbs.begin(), rbs.end());
    players.insert(players.begin(), wrs.begin(), wrs.end());

    //std::copy(players.begin(), players.end(), std::ostream_iterator<Player>(std::cout, "\n"));

    std::cout << "// Minimum score\nmin: ";
    PlayerListIterator pli = players.begin();
    std::cout << pli->rank << " " << pli->position << pli->rank;
    ++pli;

    for (; pli != players.end(); ++pli) {
        std::cout << " + " << pli->rank * pos_scale(pli->position) << " " << pli->position << pli->rank;
    }

    /*
    for (pli = tes.begin(); pli != tes.end(); ++pli) {
        std::cout << " + " << pli->rank << " " << pli->position << pli->rank;
    }

    for (pli = ds.begin(); pli != ds.end(); ++pli) {
        std::cout << " + " << pli->rank << " " << pli->position << pli->rank;
    }

    for (pli = ks.begin(); pli != ks.end(); ++pli) {
        std::cout << " + " << pli->rank << " " << pli->position << pli->rank;
    }

    for (pli = rbs.begin(); pli != rbs.end(); ++pli) {
        std::cout << " + " << pli->rank << " " << pli->position << pli->rank;
    }

    for (pli = wrs.begin(); pli != wrs.end(); ++pli) {
        std::cout << " + " << pli->rank << " " << pli->position << pli->rank;
    }
    */

    std::cout << " ; \n";

    std::cout << "// Limit QBs\n1 <= ";

    pli = qbs.begin();
    std::cout << pli->position << pli->rank;
    ++pli;

    for (; pli != qbs.end(); ++pli) {
        std::cout << " + " << pli->position << pli->rank;
    }

    std::cout << " <= 1;\n";

    std::cout << "// Limit TEs\n1 <= ";

    pli = tes.begin();
    std::cout << pli->position << pli->rank;
    ++pli;

    for (; pli != tes.end(); ++pli) {
        std::cout << " + " << pli->position << pli->rank;
    }

    std::cout << " <= 1;\n";

    std::cout << "// Limit Ds\n1 <= ";

    pli = ds.begin();
    std::cout << pli->position << pli->rank;
    ++pli;

    for (; pli != ds.end(); ++pli) {
        std::cout << " + " << pli->position << pli->rank;
    }

    std::cout << " <= 1;\n";

    std::cout << "// Limit Ks\n1 <= ";

    pli = ks.begin();
    std::cout << pli->position << pli->rank;
    ++pli;

    for (; pli != ks.end(); ++pli) {
        std::cout << " + " << pli->position << pli->rank;
    }

    std::cout << " <= 1;\n";

    std::cout << "// Limit RBs\n2 <= ";

    pli = rbs.begin();
    std::cout << pli->position << pli->rank;
    ++pli;

    for (; pli != rbs.end(); ++pli) {
        std::cout << " + " << pli->position << pli->rank;
    }

    std::cout << " <= 2;\n";

    std::cout << "// Limit WRs\n3 <= ";

    pli = wrs.begin();
    std::cout << pli->position << pli->rank;
    ++pli;

    for (; pli != wrs.end(); ++pli) {
        std::cout << " + " << pli->position << pli->rank;
    }

    std::cout << " <= 3;\n";

    std::cout << "// Salary constraint\ncost: ";
    pli = players.begin();
    std::cout << pli->cost << " " << pli->position << pli->rank;
    ++pli;

    for (; pli != players.end(); ++pli) {
        std::cout << " + " << pli->cost << " " << pli->position << pli->rank;
    }

    std::cout << " <= 600;\n";

    std::cout << "// Variables\nbin ";
    pli = players.begin();
    std::cout << pli->position << pli->rank;
    ++pli;

    for (; pli != players.end(); ++pli) {
        std::cout << ", " << pli->position << pli->rank;
    }

    std::cout << ";\n";

    return 0;

}
