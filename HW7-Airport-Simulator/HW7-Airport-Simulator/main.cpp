#include "Simulator.h"

Simulator airport;

int main() {

	airport.enter_data();
	airport.run_simulation();
	airport.show_stats();

	system("pause"); //pauses execution to see results

	return 0;
}