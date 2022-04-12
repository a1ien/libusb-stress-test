#include <libusb.h>
#include <stdio.h>
#include <pthread.h>

/** Test that creates and destroys a single concurrent context
 * 10000 times. */
void* test_init_and_exit(void * arg)
{

	for (int i = 0; i < 1000; ++i) {
        libusb_context *ctx = NULL;
		int r;

		r = libusb_init(&ctx);
		if (r != LIBUSB_SUCCESS) {
			printf("Failed to init libusb on iteration %d: %d", i, r);
			return NULL;
		}
		libusb_exit(ctx);
	}
    printf("Thread done\n");
	return NULL;
}

int main() {

    pthread_t threadId1;
    pthread_t threadId2;
    // Create a thread that will function threadFunc()
    int err = pthread_create(&threadId1, NULL, &test_init_and_exit, NULL);
    // Create a thread that will function threadFunc()
    int err2 = pthread_create(&threadId2, NULL, &test_init_and_exit, NULL);
    err2 = pthread_join(threadId2, NULL);
    err = pthread_join(threadId1, NULL);
    printf("All Done\n");

    return 0;
}
