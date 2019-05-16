#include<lpc214x.h>
#include<stdio.h>

//#define ADCR           (*((volatile unsigned long *) 0xE0034000))
void uart_init(void);
void adc_init(void);
void uart_tx_data(unsigned char);
unsigned char uart_rx_data(void);
void dealy(unsigned int);
int main(void)
{
	uart_init();
	adc_init();
	while(1)
	{
		unsigned int data = AD0DR3;
		if(data&(1<<31))// Taking data only if conversion is done which is tested by bit 31 which is DONE bit
	{
		unsigned int i, j;
		unsigned char ch[4]={'0','0','0','0'};
		data=(data>>6)&(0x3FF);//Extracting Result from bit 6 to 15
		sprintf(ch , "%d", data);//formatting data
		for(i=0;i<4;i++)
		{
			uart_tx_data(ch[i]);
		}
		for(i=0;i<1;i++)//some delay
			for(j=0;j<35;j++);
	}
}
}
void uart_init(void)
{
	VPBDIV = 0x02;
	PINSEL0 = 0x00050000; //enable rxd and txd pin of uart 1
	
	U1LCR = 0x83; //select 8 bit 1 stop bit  and dlab bit
	U1DLL = 0xc3; //9600 boud rate
	U1LCR = 0x03; //8 bit 1 stop bit disable dlab bit

}


void uart_tx_data(unsigned char data)
{
	while(!(U1LSR &(1<<5)));
	U1THR = data;
}


unsigned char uart_rx_data(void)
{
	while(!(U1LSR &(1<<0)));
	unsigned char data = U1RBR;
	return(data);
}

void adc_init(void)
{
	PINSEL1 = (1<<28);     //ADC 0 CHANNEL 3
	AD0CR = (1<<3)|(1<<16)|(1<<21)|(1<<8)|(1<<9)|(1<<10);    //SELECT CHANNEL AD0 CHANNEL 3 IN BURST MODE FOR CONTINEOUS CONVERSION BIT 16  . 
																													//BIT 21 FOR PDN 1 FOR ADC PIN IS OPERATIONAL 0 FOR ADC IN POWER DOUN MODE
																													//FOR 4.5MHz FRIQUENCY WE DIVIDE THE PCLK BY 7 MINCE 30MHz/7=4.7MHz
}
