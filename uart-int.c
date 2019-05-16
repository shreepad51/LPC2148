#include<LPC21XX.h>
void uart_init(void);
char putchar(char ch);
char getchar(void);
void uart1_isr(void) __irq;
//unsigned char ch;
void isr_init(void);
void delay(unsigned long time);
//int flag = 0;
int main(void)
{
	IO0DIR = 0x80000000;
	IO1DIR = 0x02000000;
	
	
	VPBDIV = 0X02;
	char *ptr="  WELCOME TO DESD ";
	uart_init();
	isr_init();
	
	
	
	
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
	U1IER = 0x00000002;
	
	
	
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


void isr_init(void)
{
VICVectAddr0=(unsigned long)uart1_isr;
VICVectCntl0 = 0x27;                              //(1<<5)|(1<<0)|(1<<1)|(1<<2);
VICIntEnable|=(1<<7);
}
void uart2_isr(void) __irq
{
}


void uart1_isr(void) __irq
{	
	if(U1IIR==0x02)
	{
		
	}
	VICVectAddr=0x00;
}
void delay(unsigned long time)
{
	int i,j;
	for(i=0;i<10000;i++)
		for(j=0;j<time;j++);
}








