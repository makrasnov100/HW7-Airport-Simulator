#include "Simulator.h"
Simulator airport;

int main() {

	airport.enter_data();
	airport.run_simulation();
	airport.show_stats();

	//Note to run AND see result use (Ctrl + F5) (VS IDE) 
	//or build and run .exe inside a command propmt

	return 0;
}