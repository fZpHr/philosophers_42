#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// the initial balance is 0
int				balance = 100;
pthread_mutex_t	mutex;

// write the new balance (after as simulated 1/4 second delay)
void	write_balance(int new_balance)
{
	usleep(250000);
	balance = new_balance;
}

// returns the balance (after a simulated 1/4 seond delay)
int	read_balance(void)
{
	usleep(250000);
	return (balance);
}

// carry out a deposit
void	*deposit(void *amount)
{
	int	account_balance;

	// lock the mutex
	pthread_mutex_lock(&mutex);
	// retrieve the bank balance
	account_balance = read_balance();
	// make the update locally
	account_balance += *((int *)amount);
	printf("Depositing %d\n", *((int *)amount));
	// write the new bank balance
	write_balance(account_balance);
	// unlock to make the critical section available to other threads
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main(void)
{
	// output the balance before the deposits
	int before = read_balance();
	printf("Before: %d\n", before);

	// we'll create two threads to conduct a deposit using the deposit function
	pthread_t thread1;
	pthread_t thread2;

	// initialize the mutex
	pthread_mutex_init(&mutex, NULL);

	// the deposit amounts... the correct total afterwards should be 500
	int deposit1 = 300;
	int deposit2 = 200;

	// create threads to run the deposit function with these deposit amounts
	pthread_create(&thread1, NULL, deposit, (void *)&deposit1);
	pthread_create(&thread2, NULL, deposit, (void *)&deposit2);

	// join the threads
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	// destroy the mutex
	pthread_mutex_destroy(&mutex);

	// output the balance after the deposits
	int after = read_balance();
	printf("After: %d\n", after);

	return (0);
}


void	*check_death(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	ft_usleep(philo->info->t_die + 1);
	pthread_mutex_lock(&philo->info->m_eat);
	pthread_mutex_lock(&philo->info->m_stop);
	if (!is_dead(philo, 0) && timestamp() - \
			philo->last_eat >= (long)(philo->info->t_die))
	{
		pthread_mutex_unlock(&philo->info->m_eat);
		pthread_mutex_unlock(&philo->info->m_stop);
		print(philo, " died\n");
		is_dead(philo, 1);
	}
	pthread_mutex_unlock(&philo->info->m_eat);
	pthread_mutex_unlock(&philo->info->m_stop);
	return (NULL);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_l));
	print(philo, " has taken a fork\n");
	if (philo->info->n_philo == 1)
	{
		ft_usleep(philo->info->t_die * 2);
		return ;
	}
	pthread_mutex_lock((philo->fork_r));
	print(philo, " has taken a fork\n");
}

void	philo_eat(t_philo *philo)
{
	print(philo, " is eating\n");
	pthread_mutex_lock(&(philo->info->m_eat));
	philo->last_eat = timestamp();
	philo->m_count++;
	pthread_mutex_unlock(&(philo->info->m_eat));
	ft_usleep(philo->info->t_eat);
	pthread_mutex_unlock((philo->fork_r));
	pthread_mutex_unlock(&(philo->fork_l));
	print(philo, " is sleeping\n");
	ft_usleep(philo->info->t_sleep);
	print(philo, " is thinking\n");
}

void	*philo_life(void *phi)
{
	t_philo		*philo;
	pthread_t	t;

	philo = (t_philo *)phi;
	if (philo->n % 2 == 0)
		ft_usleep(philo->info->t_eat / 10);
	while (!is_dead(philo, 0))
	{
		pthread_create(&t, NULL, check_death, phi);
		take_fork(philo);
		philo_eat(philo);
		pthread_detach(t);
		if (philo->m_count == philo->info->n_eat)
		{
			pthread_mutex_lock(&philo->info->m_stop);
			if (++philo->info->philo_eat == philo->info->n_philo)
			{
				pthread_mutex_unlock(&philo->info->m_stop);
				is_dead(philo, 2);
			}
			pthread_mutex_unlock(&philo->info->m_stop);
			return (NULL);
		}
	}
	return (NULL);
}
