/*
 * This file is part of myRTX.
 *
 * myRTX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * myRTX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with myRTX.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */
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
int change_priority(int new_priority, int target_pid);
int request_delay(int time_delay,  int wakeup_code, MessageEnvelope* env);
int send_console_chars(MessageEnvelope* env);
int get_console_chars(MessageEnvelope* env);
void set_wall_clock(int h, int m, int s);
void set_wall_clock_state(int s);
#endif


