#include <jv_thread.h>

static volatile jv_uint_t count;
#define MAX_THRAD_SIZE 30

static void *test(void *arg) {
  pthread_t tid = pthread_self();
  jv_uint_t i = *(jv_uint_t *) arg;
  count++;
#ifdef PTHREAD_T_IS_STRUCT
  printf("%lu, %lu, %lu \n", (unsigned long) tid.p, i, count);
#else
  printf("%lu, %lu, %lu \n", (unsigned long) tid, i, count);
#endif
  fflush(stdout);
  return NULL;
}

static void test1(void) {
  jv_uint_t i;
  jv_thread_t *thread;

  printf("Start by jv-thread.\n");

  thread = jv_thread_create(10, 128, 0, NULL);

  for (i = 0; i < MAX_THRAD_SIZE; i++) {
    jv_thread_queue(thread, test, &i);
  }

  jv_thread_wait(thread);
  jv_thread_destroy(thread);

  printf("Execute finish by jv-thread.\n\n");
}

static void test2(void) {
  jv_uint_t i;

  pthread_t pid[MAX_THRAD_SIZE];

  printf("Start by original pthread.\n");

  for (i = 0; i < MAX_THRAD_SIZE; i++) {
    pthread_create(&pid[i], NULL, test, &i);
  }

  for (i = 0; i < MAX_THRAD_SIZE; i++) {
    pthread_join(pid[i], NULL);
  }

  printf("Execute finish by original pthread.\n");
}

int main(int argc, char *argv[]) {
  test1();
  test2();
  return 0;
}
