#include <iostream>
#include <random>
#include <math.h>
#include <queue>   
#include <iomanip>

struct packet {
    int departure_time;
};

int arrival_time;

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0,1.0);

// int for now, change to packet struct later
std::queue<packet> router_queue;

// Parameters that we need. This needs to become cmd line arguments later.__a
int TICKS = 100000;
int queue_size = -1;

// According to p = lambda* L / C
double lambda = 200;
int TICK_SIZE = 10000;
// wut is dis
int packet_size = 2000;
//rate in seconds
int transmission_rate = 1000000 / TICK_SIZE;

int departure_time;


int calculate_arrival_time() {

    double U = distribution(generator);
    
    // Arrival time in seconds
    double arrival_time = (-1 / lambda) * log (1 - U);

    // Currently assuming 1 tick = 100 millisecond (100 * 10^-3)
    return arrival_time * TICK_SIZE;

}

void arrival(int current_time) {
    if (current_time > arrival_time) {
        arrival_time = current_time + calculate_arrival_time();

        if (router_queue.size() > 0) {
            departure_time = router_queue.back().departure_time + (packet_size / transmission_rate);
        } else {
            departure_time = current_time +  (packet_size / transmission_rate);
        }

        if (queue_size == -1 || (queue_size > 0 && router_queue.size() < queue_size)) {
            std::cout << "Added new packet at time " << current_time << std::endl;
            packet new_packet;
            new_packet.departure_time = departure_time;
            router_queue.push(new_packet);
        }
    }

}

void departure(int current_time) {
    if (router_queue.size() > 0 && current_time == router_queue.front().departure_time) {
        std::cout << "Removed packet at time " << current_time << std::endl ;
        router_queue.pop();
    }
}


int main()
{
  std::cout << "Hello!";


  // To create a new random uniform number:
  // double dirty_uniform_number =  distribution(generator);

  // Calculating first arrival time
  arrival_time = calculate_arrival_time();

  for (int i=0; i < TICKS; i++) {

      if (i % 1000 == 0) {
          std::cout << "Progress: " << i << "out of" << TICKS << "%" << std::endl;
      }

      arrival(i);
      departure(i);
  }

}