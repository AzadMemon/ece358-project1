#include <iostream>
#include <random>
#include <math.h>

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0,1.0);

int calculate_arrival_time(double lambda) {

    double U = distribution(generator);
    
    // Arrival time in seconds
    int arrival_time = (-1 / lambda) * log (1 - U);

    // Currently assuming 1 tick = 100 millisecond (100 * 10^-3)
    return arrival_time * 10;

}


int main()
{
  std::cout << "Hello World!";

  // To create a new random uniform number:
  // double dirty_uniform_number =  distribution(generator);

  // Parameters that we need. This needs to become cmd line arguments later.__a
  int TICKS = 500;
  // According to p = lambda* L / C
  double lambda = 200;


  // Calculating first arrival time
  
  int arrival_time = calculate_arrival_time();


  for (int i=0; i < TICKS; i++) {


  }

}