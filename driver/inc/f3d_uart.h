/* f3d_uart.h --- 
 * 
 * Filename: f3d_uart.h
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Sep 26 07:05:43 2013
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* Copyright (c) 2004-2007 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */

//#include "../../lab10/queue.h"
#include <queue.h>
queue_t rxbuf;
queue_t txbuf;

void f3d_uart_init(void);
int putchar(int);
int getchar(void);
void putstring(char *);
void USART1_IRQHandler(void);
void flush_uart(void);

/* f3d_uart.h ends here */
