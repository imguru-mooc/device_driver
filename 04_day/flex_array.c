#if 1
#include <stdio.h>
#include <stdlib.h>
struct input_event
{
	int code;
	int value;
};

struct evdev_client
{
	int head;
	int tail;
	struct input_event buffer[];
};

int main()
{
	struct evdev_client *client;
	client = malloc( sizeof(struct evdev_client) + sizeof(struct input_event)*32 );
	client->buffer[32].code = 23;
	return 0;
}
#endif
#if 0
#include <stdio.h>
#include <stdlib.h>
struct input_event
{
	int code;
	int value;
};

struct evdev_client
{
	int head;
	int tail;
	struct input_event buffer[];
};

int main()
{
	struct evdev_client client;
	printf("sizeof(client)=%lu\n", sizeof(client));
	printf("&client      =%p\n", &client);
	printf("client.buffer=%p\n", client.buffer);
	return 0;
}
#endif
#if 0
#include <stdio.h>
#include <stdlib.h>
struct input_event
{
	int code;
	int value;
};

struct evdev_client
{
	int head;
	int tail;
	struct input_event *buffer;
};

int main()
{
	struct evdev_client client;
	client.buffer = malloc( sizeof(struct input_event)*32 );
	client.buffer[31].code = 23;
	return 0;
}
#endif
