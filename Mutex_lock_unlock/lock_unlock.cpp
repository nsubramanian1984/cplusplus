#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <ctime>

pthread_mutex_t count_mutex;
pthread_cond_t cond_var;

void *function1(void *arg)
{
  pthread_mutex_lock( &count_mutex );
  std::time_t result = std::time(NULL);

  std::cout << "[" << __func__ << "]" << ", Acquired mutex" << std::endl;

  std::cout << "[" << __func__ << "]" << ", pthread_cond_wait "\
    "call will relinquish lock and block on condition variable." << std::endl;
  pthread_cond_wait( &cond_var, &count_mutex );
  std::cout << "[" << __func__ << "]" << ", Acquired mutex again." << std::endl;
  pthread_mutex_unlock( &count_mutex );

  return NULL;
}

void *function2(void *arg)
{

  // Introduced delay to avoid this thread from running first
  // before function1 thread, when program starts.
  sleep( 1 );

  pthread_mutex_lock( &count_mutex );
  std::cout << "[" << __func__ << "]" << ", Acquired mutex" << std::endl;

  std::cout << "[" << __func__ << "]" << ", \"pthread_cond_signal\" to be called after 10 seconds." << std::endl;

  sleep( 10 );

  pthread_cond_signal( &cond_var  );
  pthread_mutex_unlock( &count_mutex );

  return NULL;
}

int main(int argc, char **argv)
{
  pthread_attr_t pthread_custom_attr1,pthread_custom_attr2, pthread_custom_attr3;
  pthread_t myThread1, myThread2, myThread3;

  pthread_attr_init( &pthread_custom_attr1 );
  pthread_attr_init( &pthread_custom_attr2 );

  pthread_create( &myThread1, &pthread_custom_attr1, function1, NULL );
  pthread_create( &myThread2, &pthread_custom_attr2, function2, NULL );

  pthread_join(myThread1, NULL );
  pthread_join(myThread2, NULL );

  return 0;
}

