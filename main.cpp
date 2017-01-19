#include <iostream>
#include <random>
#include <math.h>
#include <queue>   
#include <iomanip>

struct packet {
    int ticks_until_departure;
};

int arrival_time;

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0,1.0);

// int for now, change to packet struct later
std::queue<packet> router_queue;

// Parameters that we need. This needs to become cmd line arguments later.__a
int TICKS = 100000*1000;
int queue_size = -1;

// According to p = lambda* L / C
double lambda = 0;
int TICK_SIZE = 1 / 0.000001;
// wut is dis
int L_packet_size = 2000;
//rate in seconds
int C_transmission_rate = 1000000; 
int idle_counter = 0;

double num_of_packets_in_queue_total = 0;

int calculate_arrival_time() {

    double U = distribution(generator);
    
    // Arrival time in seconds
    double arrival_time = (-1 / lambda) * log (1 - U);

    // std::cout << "Arrival Time: " << arrival_time << std::endl;

    // Currently assuming 1 tick = 100 millisecond (100 * 10^-3)
    return arrival_time * TICK_SIZE;

}

void arrival(int current_time) {
    if (current_time > arrival_time) {
        arrival_time = current_time + calculate_arrival_time();

        if (queue_size == -1 || (queue_size > 0 && router_queue.size() < queue_size)) {
            //std::cout << "Added new packet at time " << current_time << std::endl;
            packet new_packet;
            new_packet.ticks_until_departure = (L_packet_size / C_transmission_rate / TICK_SIZE);
            router_queue.push(new_packet);
        }
    }

}

void server(int current_time) {
    if (router_queue.size() > 0) {
        // TODO: Does the first tick count, if so, this should check if == 1.
        if (router_queue.front().ticks_until_departure == 1) {
            //std::cout << "Removed packet at time " << current_time << std::endl;
            router_queue.pop();
        } else {
            router_queue.front().ticks_until_departure -= 1;
        }
    } else {
        idle_counter+=1;
    }
}


int yolo()
{
  // To create a new random uniform number:
  // double dirty_uniform_number =  distribution(generator);

  // Calculating first arrival time
  arrival_time = calculate_arrival_time();

  for (int i=0; i < TICKS; i++) {

      arrival(i);
      server(i);

      num_of_packets_in_queue_total += router_queue.size();
  }
}

int main() {
    for(double r0 = 0.2; r0 <= 0.9; r0+=0.1) {
        queue_size = -1;
        TICKS = 100000*1000;
        TICK_SIZE = 1 / 0.000001;
        L_packet_size = 2000;
        C_transmission_rate = 1000000;
        idle_counter = 0;
        num_of_packets_in_queue_total = 0;
        lambda = r0 * C_transmission_rate / L_packet_size;

        yolo();

        std::cout << "Idle counter: " << idle_counter  << std::endl;
        std::cout << "E[N] " << num_of_packets_in_queue_total / TICKS << std::endl;



    }

}