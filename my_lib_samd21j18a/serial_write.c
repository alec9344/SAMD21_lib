/*
 * CFile1.c
 *
 * Created: 1/9/2020 2:44:54 PM
 *  Author: jagnese2018
 */ 

#include "my_lib/include/serial_write.h"
#include <string.h>

static struct usart_module usart_mod;
#define BUF_LEN 5000
static char buf[BUF_LEN];
static int buf_pos;

void usart_set_module(struct usart_module * inst) {
	usart_mod = *inst;
}

void usart_write(char * str) {
	usart_write_buffer_wait(&usart_mod, str, strlen(str));
}

void usart_newline( void ) {
	usart_write("\r\n");
}

void flush_buf( void ) {
	buf_pos = 0;
}

void write_buf(const char * str) {
	if (buf_pos == BUF_LEN-1) return;
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		buf[buf_pos++] = str[i];
		if (buf_pos == BUF_LEN-1) {
			break;
		}
	}
	buf[buf_pos] = 0;
	if (buf_pos > (BUF_LEN/2)) xEventGroupSetBits(xUsartEventGroup, 0x01);	
}

void write_buf_int(int n) {
	char str[10];
	itoa(n, str, 10);
	write_buf(str);
}

void print_buf( void ) {
		SercomUsart *const usart_hw = &((&usart_mod)->hw->USART);	
		for (int i = 0; buf[i] != '\0'; i++) {
		/* Wait until synchronization is complete */
		_usart_wait_for_sync(&usart_mod);
		/* Write data to USART module */
		usart_hw->DATA.reg = buf[i];
		/* Wait until data is sent */
		while (!(usart_hw->INTFLAG.reg & SERCOM_USART_INTFLAG_TXC));
	}
	flush_buf();
}

void usart_write_int(int n) {
	char str[10];
	itoa(n, str, 10);
	usart_write(str);
}
