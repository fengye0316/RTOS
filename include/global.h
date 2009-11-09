#ifndef GLOBAL_H
#define GLOBAL_H
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <assert.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>
#define DEBUG 1
#define TRUE 1
#define FALSE 0
#define MESSAGE_SIZE 2048
#define MEMBLOCK_SIZE 256
#define NUM_PROCESS 3
#define NUM_UPROCESS 20
#define MIN_PRIORITY 3
#define MAX_PRIORITY 0
#define TIMER_INTERVAL 100000
#define TRACE_LENGTH 16
#define I_STACK_SIZE 4000
#define I_PROCS 3
#ifdef i386
#define STK_OFFSET 4//dword size (size of stack frame)
#endif
#ifdef __amd64
#define STK_OFFSET 4 //amd64 dword??
#endif
#ifdef __sparc
#define STK_OFFSET 4 //sparc dword??
#endif
#define MIN(X, Y)  ((X) < (Y) ? (X) : (Y))

#define KEYBOARD_FILE "kbd_mem"
#define CRT_FILE "crt_mem"
enum States {
  EXECUTING=0,
  READY=1,
  MESSAGE_WAIT=2,
  ENVELOPE_WAIT=3,
  SLEEP=4,
  INTERRUPTED=5
};

enum Priority {
  MAX=MAX_PRIORITY,
  MID=1,
  MIDLOW=2,
  LOW=MIN_PRIORITY
};

enum Event {
  SEND=0,
  RECEIVE=1
};


enum msg_type {
  WAKEUP,
  CONSOLE_OUTPUT,
  CONSOLE_INPUT,
  DEFAULT, //for user processes that do not explicitly set a type
};

enum shm_flag {
  MEM_READY=0,
  MEM_DONE=1
};
  


typedef struct MessageEnvelope {
  struct MessageEnvelope* next;
  int sender_pid, destination_pid;
  char data[MESSAGE_SIZE];
  int timeout_ticks;
  enum msg_type type;
} MessageEnvelope;

typedef struct message_queue {
  MessageEnvelope* head;
  MessageEnvelope* tail;
} message_queue;


typedef struct PCB {
  int pid; //process id
  enum States state; //process current state
  enum Priority priority; //process priority
  char* stack; //process stack pointer
  char* stack_head; //original stack allocation address
  int stack_size; //process stack limit
  struct PCB* q_next; //process queue reference
  struct PCB* p_next; //global process list reference
  void* process_code; //initial function for process
  jmp_buf context;
  message_queue* message_send; //send message queue
  message_queue* message_receive; // receiving message queue
  //enum bool i_process; //is this an i_process? PCB

} PCB;

typedef struct priority_process_queue {
  PCB* pq_head[MIN_PRIORITY + 1];
  PCB* pq_tail[MIN_PRIORITY + 1];
} priority_process_queue;

typedef struct process_queue {
  PCB* head;
  PCB* tail;
} process_queue;

typedef struct msg_event {
  int destination_pid, source_pid;
  int timestamp; //in absolute seconds since system start
  enum msg_type mtype; //type of message sent/rcv'd
  enum Event type; //type of msg event, (ie sent or received)
  struct msg_event *next;
} msg_event;

typedef struct trace_buffer {
  int send_length, receive_length; //to maintain fixed size
  msg_event* send, *send_tail;
  msg_event* receive, *receive_tail;
} trace_buffer;

typedef struct mem_buffer {
  int length;
  enum shm_flag flag;
  char data[MEMBLOCK_SIZE];
} mem_buffer;


//helper process data structures
caddr_t _kbd_mem_ptr, _crt_mem_ptr;
int _kbd_pid, _crt_pid;
int _kbd_fid, _crt_fid;

//signal masking
int masked;
sigset_t rtxmask;

#endif
