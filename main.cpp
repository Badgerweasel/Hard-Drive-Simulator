#include "Request.hpp"
#include "Simulation.hpp"

using namespace std;

int main() {

    Simulation *sim = new Simulation();

    sim->run();

    delete sim;

    return 0;
}

