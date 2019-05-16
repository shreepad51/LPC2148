#include<LPC21XX.h>
void uart_init(void);
char putchar(char ch);
char getchar(void);
unsigned char test;
int main(void)
{
	VPBDIV = 0X02;
	char *ptr="  uart coding";
	uart_init();
	
	while(1){
		while(*ptr)
	{
		putchar(*ptr++);
	}
	putchar(getchar());
	
		
		
	}
	
}
void uart_init(void)
{
	PINSEL0=0x00050000;
	U1LCR = 0x00000083;
	U1DLL = 0x00000000C3;
	U1LCR = 0x00000003;
	
	
}
char putchar(char ch)
{
	if(ch =='\n')
	{
		while(!(U1LSR & 0x20));//wait till char is received 
		U1THR = 0x0D;
	}
	while(!(U1LSR & 0x20));
	return(U1THR = ch);
	
}
char getchar(void)
{
	while(!(U1LSR & 0x01));
	return(U1RBR);
}
