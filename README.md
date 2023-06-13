# philo

## Introduction
This project is a multithreading and mutex application that simulates the dining philosophers problem.

The dining philosophers problem is a classic demonstration of a common computing problem - the problem of concurrency.

It demonstrates the challenges of designing a system where multiple processes need to access shared resources in a way that avoids deadlock.

## Project Overview
A certain number of philosophers sit around a round table with a large bowl of spaghetti.

Each philosopher can either eat, think or sleep. They cannot do more than one of these activities at the same time.

The philosophers have forks available to eat with, there are as many forks as philosophers.

To eat, a philosopher needs to have a fork in both hands.

After eating, philosophers put down their forks and start sleeping. Once awake, they start thinking again. The simulation ends when a philosopher dies of 

starvation.

Philosophers don’t speak with each other and don’t know if another philosopher is about to die.

## Global Rules

The application takes the following arguments:

number_of_philosophers: The number of philosophers and also the number of forks.

time_to_die (in milliseconds): If a philosopher didn’t start eating 'time_to_die' milliseconds after the start of their last meal or the start of the 
simulation, they die.

time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.

time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.

number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least 'number_of_times_each_philosopher_must_eat' times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

## Mandatory Part
Each philosopher should be a thread. There is one fork between each pair of philosophers,

so each philosopher has a fork on their left and a fork on their right.

To prevent philosophers from duplicating forks, the forks state is protected with a mutex for each of them.

## Instructions
```sh
git clone https://github.com/rkedida/philo.git
cd philo
```
Clone the repository to your local machine.

Navigate to the project directory.

## Build and Run
This project includes a Makefile for easy compilation.

Simply run the following commands to compile and run the project:
```sh
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
Replace 'number_of_philosophers', 'time_to_die', 'time_to_eat', 'time_to_sleep', and 'number_of_times_each_philosopher_must_eat' (optional)
with the desired values.
