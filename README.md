## Philosophers

Philosophers is a 42 project where you simulate the dining philosophers problem using threads and mutexes. The goal is to implement a solution that prevents deadlock and starvation, allowing the philosophers to dine peacefully. This project helps reinforce your understanding of concurrency, synchronization, and parallel programming.

*For more information, please refer to the subject in the git.*

## Installation

To install Philosophers, clone the project from the Git repository:

```bash
git clone git@github.com:fZpHr/philosophers_42.git
cd philosophers_42
```

Then compile the executable using the provided Makefile:

```bash
make
```

## Usage

To run Philosophers, execute the following command:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Where:
- `number_of_philosophers` is the number of philosophers at the table.
- `time_to_die` is the time in milliseconds after which a philosopher dies if they have not started eating.
- `time_to_eat` is the time in milliseconds that a philosopher takes to eat.
- `time_to_sleep` is the time in milliseconds that a philosopher takes to sleep.
- `number_of_times_each_philosopher_must_eat` (optional) is the number of times each philosopher must eat before the simulation ends.

## Example

Here is an example of how to use Philosophers:

```bash
./philo 5 800 200 200
```

## Description

The program will simulate the dining philosophers problem with the specified parameters. Each philosopher will alternate between thinking, eating, and sleeping according to the provided time intervals. The simulation will end when a philosopher dies or when all philosophers have eaten the specified number of times (if provided).
