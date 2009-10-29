#ifndef USER_API_H
#define USER_API_H
#include "global.h"
#include "kernel.h"


int terminate(void);
int atomic(int state);
void context_switch(jmp_buf p, jmp_buf n);
int send_message(int dpid, MessageEnvelope* env);
MessageEnvelope* receive_message(void);
void release_processor(void);
int get_trace_buffer(MessageEnvelope* env);
MessageEnvelope* request_message_envelope();
void release_message_envelope(MessageEnvelope* env);
int request_process_status(MessageEnvelope* env);
#endif

