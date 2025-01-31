#ifndef RECEIVER_H
#define RECEIVER_H

typedef struct {
    int sock;
    CommandBuffer *cb;
} ReceiverArgs;


void *recv_cmds(void *args);
int verify_cmd(int cmd);

#endif