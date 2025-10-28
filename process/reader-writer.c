#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt;  // Semaphores: mutex for readCount, wrt for write access
int readCount = 0; // Number of active readers
int data = 0;      // Shared resource (e.g., a database value)

void *reader(void *arg) {
    int id = *((int *)arg);  // Reader ID

    sem_wait(&mutex);        // Lock mutex to update readCount
    readCount++;
    if (readCount == 1) {
        sem_wait(&wrt);      // First reader blocks writers
    }else if(readCount == 3){
	sem_post(&wrt); // Unlock writer when already 3 readers
    }
    sem_post(&mutex);        // Unlock mutex (other readers can now enter)

    // Critical section: Reading
    printf("Reader %d is reading data: %d\n", id, data);
    sleep(1);                // Simulate reading time

    sem_wait(&mutex);        // Lock mutex to update readCount
    readCount--;
    if (readCount == 0) {
        sem_post(&wrt);      // Last reader unblocks writers
	printf("Mutex wrt\n");
	} 
	sem_post(&mutex);        // Unlock mutex return NULL;
}

void *writer(void *arg) {
    int id = *((int *)arg);  // Writer ID

    sem_wait(&wrt);          // Wait for exclusive access

    // Critical section: Writing
    data++;                  // Modify the shared data
    printf("Writer %d is writing data: %d\n", id, data);
    sleep(1);                // Simulate writing time

    sem_post(&wrt);          // Release exclusive access

    return NULL;
}

int main() {
    sem_init(&mutex, 0, 1);  // Initialize mutex to 1 (unlocked)
    sem_init(&wrt, 0, 1);    // Initialize wrt to 1 (unlocked)

    pthread_t readers[6], writers[6];  // Thread arrays
    int ids[6] = {1, 2, 3, 4, 5,  6};      // IDs for threads

    // Create 5 readers and 5 writers
    for (int i = 0; i < 6; i++) {
        pthread_create(&readers[i], NULL, reader, &ids[i]);
        pthread_create(&writers[i], NULL, writer, &ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 6; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);     // Clean up semaphores
    sem_destroy(&wrt);

    return 0;
}
