#ifndef SIMULATE_H_
#define SIMULATE_H_

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <ios>
#include "LandingQueue.h"
#include "ServiceQueue.h"
#include "DepartureQueue.h"
#include "Random.h"

Random my_random;  // Global variable 

class Simulator
{
private:
	int total_time;  // total time to run simulation
	int clock;       // current time

					 // landing queue --> service queue --> departure queue
	LandingQueue *landing_queue;
	ServiceQueue *service_queue;
	DepartureQueue *departure_queue;

	// Remember me!
	int read_int(const std::string &prompt, int low, int high)
	{
		if (low >= high) // invalid range
			throw std::invalid_argument("invalid range specified");

		std::cin.exceptions(std::ios_base::failbit);
		int num = 0;
		while (true) {
			try {
				while (true) {
					std::cout << prompt;
					std::cin >> num;
					if (num >= low && num <= high) { // within the specified range
						std::cout << std::endl;
						return num;
					}
				}
			}
			catch (std::ios_base::failure) {
				std::cout << "Bad numeric string -- try again\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
		}
	}

public:

	Simulator() {
		landing_queue = new LandingQueue();
		service_queue = new ServiceQueue();
		departure_queue = new DepartureQueue();
	}

	void enter_data()
	{
		std::cout << "Welcome CS273 to the Simple Airport Simulator.\n\n";
		std::cout << "We are CS273ville, a small but feisty airport!\n";

		int rate = read_int("Please enter the plane arrival rate (planes/hour): ", 1, 59);
		double arrival_rate = rate / 60.0;

		int min_service = read_int("Please enter the minimum service time (mins): ", 0, INT_MAX);
		int max_service = read_int("Please enter the maximum service time (mins): ", 0, INT_MAX);
		int departure_time = read_int("Please enter the departure time (mins): ", 1, INT_MAX);
		int gates_amount = read_int("Please enter the amount of gates at your airport: ", 1, INT_MAX);

		total_time = read_int("Please enter the total simulation time (hours): ", 1, INT_MAX);
		total_time *= 60;

		// set the arrival_rate for the landing queue (planes a minute)
		landing_queue->set_arrival_rate(arrival_rate);

		// set the service times for the service queue 
		service_queue->set_service_times(min_service, max_service);
		// pass references to the landing and departure queue to the service queue
		service_queue->set_landing_queue(landing_queue);
		service_queue->set_departure_queue(departure_queue);

		// set the amount of gastes at the airport
		service_queue->set_gate_amount(gates_amount);

		// set the departure time for the departure queue
		departure_queue->set_departure_time(departure_time);
	}

	void run_simulation()
	{
		// run the simulation
		for (clock = 0; clock < total_time; ++clock)
		{
			// for each time interval ...
			landing_queue->update(clock);
			service_queue->update(clock);
			departure_queue->update(clock);
		}
	}

	//Shows the results of the simulation
	void show_stats()
	{
		std::cout << "[LANDINGS]" << std::endl;
		std::cout << "Number of planes served in the landing queue: " << landing_queue->get_num_served() << " plane(s)" << std::endl;
		std::cout << "Total wait time for all planes in landing queue: " << landing_queue->get_total_wait() << " minute(s)" << std::endl;
		std::cout << "Average wait time for landing queue: " << landing_queue->get_total_wait() / landing_queue->get_num_served() << " minute(s)" << std::endl;
		std::cout << std::endl;

		std::cout << "[DEPARTURES]" << std::endl;
		std::cout << "Number of planes served in the departure queue: " << departure_queue->get_num_served() << " plane(s)" << std::endl;
		std::cout << "Total wait time for all planes in departure queue: " << departure_queue->get_total_wait() << " minute(s)"<< std::endl;
		std::cout << "Average wait time for departure queue: " << departure_queue->get_total_wait() / departure_queue->get_num_served() << " minute(s)" << std::endl;
		std::cout << std::endl;

		std::cout << "[END STATUS]" << std::endl;
		std::cout << landing_queue->getQueueSize() << " plane(s) are still circling the airport waiting to land..." << std::endl;
		std::cout << service_queue->getGateStatus() << " planes are still being serviced at the airport gates..." << std::endl;
		std::cout << departure_queue->getQueueSize() << " plane(s) are at the airport waiting to liftoff..." << std::endl;
		std::cout << std::endl;
	}


};

#endif