# A moden, portable, easy use's thread pool using POSIX C

A moden, portable, easy use's thread pool using POSIX C

## Features

- No dependence
- ~400 LOC
- Very easy to use, just four functions
- Using POSIX C to compatible with current mainstream platforms

## Getting Started


### jv_thread_main.c

```c
#include <jv_thread.h>

static volatile jv_uint_t count;
#define MAX_THRAD_SIZE 30

static void *test(void *arg) {
  pthread_t tid = pthread_self();
  jv_uint_t i = *(jv_uint_t *)arg;
  count++;
  printf("%p, %lu, %lu \n",(void *)tid, i, count);
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
```

## Build

    $ make

## Run

    $ ./jv_thread_main

## Out Print

```
Start by jv-thread.
0x600048860, 1, 1
0x600048980, 2, 2
0x600058a90, 3, 3
0x600058b90, 3, 4
0x600048860, 5, 5
0x600048980, 7, 6
0x600078cb0, 11, 7
0x600058a90, 12, 8
0x600088e40, 12, 9
0x600088f40, 12, 10
0x600089040, 14, 11
0x600058b90, 15, 12
0x600048860, 15, 13
0x600099150, 15, 14
0x6000a9260, 16, 15
0x600048980, 17, 16
0x600078cb0, 17, 17
0x6000a9360, 30, 18
0x600088e40, 30, 19
0x600088f40, 30, 20
0x600089040, 30, 21
0x600058b90, 30, 22
0x600048860, 30, 23
0x600099150, 30, 24
0x6000a9260, 30, 25
0x600048980, 30, 26
0x600078cb0, 30, 27
0x6000a9360, 30, 28
0x600088e40, 30, 29
0x600088f40, 30, 30
Execute finish by jv-thread.

Start by original pthread.
0x600048840, 1, 31
0x600048940, 1, 32
0x600058a50, 2, 33
0x600058b50, 3, 34
0x600078c70, 5, 35
0x600048a40, 6, 36
0x600048b40, 7, 37
0x600048c40, 7, 38
0x600048d40, 9, 39
0x600048e40, 10, 40
0x600048f40, 10, 41
0x600049040, 12, 42
0x600049140, 13, 43
0x600049240, 13, 44
0x600049340, 14, 45
0x600049440, 15, 46
0x600049540, 17, 47
0x600049640, 18, 48
0x600049740, 18, 49
0x600049840, 20, 50
0x600049940, 20, 51
0x600049a40, 21, 52
0x600049b40, 22, 53
0x600049c40, 23, 54
0x600049d40, 24, 55
0x600049e40, 26, 56
0x600049f40, 27, 57
0x60004a040, 28, 58
0x60004a140, 28, 59
0x60004a240, 29, 60
Execute finish by original pthread.
```

## License

This project is under MIT License. See the [LICENSE](LICENSE) file for the full license text.

