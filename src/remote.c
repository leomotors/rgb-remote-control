#include "remote.h"

#include <fcntl.h>
#include <linux/input.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_DEVICES 20
#define DEVICE_NAME "gpio_ir_recv"

static int find_ir_device() {
    char device[64];
    char name[256];
    int fd;

    for (int i = 0; i < MAX_DEVICES; i++) {
        snprintf(device, sizeof(device), "/dev/input/event%d", i);
        fd = open(device, O_RDONLY);
        if (fd == -1) continue;

        ioctl(fd, EVIOCGNAME(sizeof(name)), name);
        if (strstr(name, DEVICE_NAME)) {
            return fd;
        }
        close(fd);
    }
    return -1;
}

int start_listening_remote(void (*handler)(signed int)) {
    struct input_event ev;
    int fd = find_ir_device();

    if (fd == -1) {
        fprintf(stderr, "Could not find IR device\n");
        return 1;
    }

    printf("Listening for IR events...\n");

    while (true) {
        if ((long unsigned int)read(fd, &ev, sizeof(struct input_event)) <
            sizeof(struct input_event)) {
            perror("Error reading event");
            break;
        }

        if (ev.type == EV_MSC && ev.code == MSC_SCAN) {
            printf("IR Code: 0x%x\n", ev.value);
            handler(ev.value);
        }
    }

    close(fd);
    return 0;
}
