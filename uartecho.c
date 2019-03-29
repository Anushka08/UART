#include <stdint.h>
#include <stddef.h>
/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
/* Example/Board Header files */
#include "Board.h"
/*
* ======== mainThread ========
*/
void *mainThread(void *arg0)
{
// int a;
char input[1];
const char echoPrompt[] = "Echoing characters:\r\n";
const char echoPrompt1[] = "1 Echoing characters:\r\n";
UART_Handle uart, uart1;
UART_Params uartParams,uartParam1;
/* Call driver init functions */
GPIO_init();
UART_init();
/* Configure the LED pin */
GPIO_setConfig(Board_GPIO_LED0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
/* Turn on user LED */
GPIO_write(Board_GPIO_LED0, Board_GPIO_LED_ON);
/* Create a UART with data processing off. */
UART_Params_init(&uartParams);
uartParams.writeDataMode = UART_DATA_BINARY;
uartParams.readDataMode = UART_DATA_BINARY;
uartParams.readReturnMode = UART_RETURN_FULL;
uartParams.readEcho = UART_ECHO_ON;
uartParams.baudRate = 115200;
/* Create a UART with data processing off. */
UART_Params_init(&uartParam1);
uartParam1.writeDataMode = UART_DATA_BINARY;
uartParam1.readDataMode = UART_DATA_BINARY;
uartParam1.readReturnMode = UART_RETURN_FULL;
uartParam1.readEcho = UART_ECHO_ON;
uartParam1.baudRate = 115200;
uart = UART_open(Board_UART0, &uartParams);
uart1 = UART_open(Board_UART1, &uartParam1);
if (uart1 == NULL) {
/* UART1_open() failed */
//puts("s");
while (1);
}
if (uart == NULL) {
/* UART_open() failed */
while (1);
}
UART_write(uart, echoPrompt, sizeof(echoPrompt));
/* Loop forever echoing */
while (1)
{
UART_read(uart1, &input, 1);
UART_write(uart, input, sizeof(input));
}
}
