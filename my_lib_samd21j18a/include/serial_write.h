/*
 * serial_write.h
 *
 * Created: 1/9/2020 2:45:44 PM
 *  Author: jagnese2018
 */ 


#ifndef SERIAL_WRITE_H_
#define SERIAL_WRITE_H_


#include <usart.h>
#include "FreeRTOS.h"
#include "event_groups.h"

EventGroupHandle_t xUsartEventGroup;

void usart_set_module(struct usart_module * inst);

void usart_write(char * str);

void usart_newline( void );

void flush_buf( void );

void write_buf(const char * str);

void write_buf_int(int n);

void print_buf( void );

void usart_write_int(int n);

#endif /* SERIAL_WRITE_H_ */