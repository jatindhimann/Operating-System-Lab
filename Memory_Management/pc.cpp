#include <iostream>
#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // For sleep()

using namespace std;

const int MaxBufferSize = 5;
static int size = 0;
queue<int> buffer;
sem_t mutex, empty, full;

void* producer(void* arg) {
    int item;
    while (true) {
        item = rand() % 100; // Generate a random item
        sem_wait(&empty);    // Wait if buffer is full
        sem_wait(&mutex);    // Wait for access to buffer
        buffer.push(item);
        size++;
          // Produce item and add to buffer
        cout << "Produced: " << item << endl;
         cout<<"current size: "<<size<<endl;
        sem_post(&mutex);    // Release access to buffer
        sem_post(&full);     // Signal that buffer is not empty
        sleep(1);            // Sleep to simulate production time
    }
}

void* consumer(void* arg) {
    int item;
    while (true) {
        sem_wait(&full);     // Wait if buffer is empty
        sem_wait(&mutex);    // Wait for access to buffer
        item = buffer.front(); // Consume item from buffer
        buffer.pop();
        size--;
        cout << "Consumed: " << item << endl;
        cout<<"current size: "<<size<<endl;
        sem_post(&mutex);    // Release access to buffer
        sem_post(&empty);    // Signal that buffer is not full
        sleep(1);            // Sleep to simulate consumption time
    }
}

int main() {
    pthread_t producerThread, consumerThread;
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, MaxBufferSize);
    sem_init(&full, 0, 0);

    // Create producer and consumer threads
    pthread_create(&producerThread, NULL, producer, &size);
    pthread_create(&consumerThread, NULL, consumer, &size);

    // Join threads
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
