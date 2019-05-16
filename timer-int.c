#include<lpc21xx.h>

#define T0CTCR          (*((volatile unsigned long *) 0xE0004070))
#define PRESCALE 60000
void timer_delay_ms_on_reset(unsigned int);
void timer_delay_ms_on_stop(unsigned int);
void BUZZER_LED_INIT(void);
void timer_init(void);
void timer_interrupt_init(void);
void isr_timer(void)__irq;
void delay(unsigned long time);

int main(void)
{
	BUZZER_LED_INIT();
	timer_init();
	timer_interrupt_init();
	
	
	
	while(1)
	{
		IO0CLR = 0x80000000;
		IO1CLR = 0x02000000;
		timer_delay_ms_on_reset(1000);
		//timer_delay_ms_on_reset(1000);
		
		IO0SET = 0x80000000; 				 //turn on the led
		IO1SET = 0x02000000; 			//turn off the buzzer
		
		timer_delay_ms_on_stop(1000);					//delay of 1 sec 1000*1ms = 1sec
	}
	
	
}
void BUZZER_LED_INIT(void)
{
	IO0DIR = 0X80000000;				 // set led output
	IO1DIR = 0X02000000; 				//set buzzer as a output
}
void timer_init(void)
{
	
	T0TCR = 0x02; 					//timer counter and prescaler are enable for counting
	T0TCR = 0x01;					//counter reset
	VPBDIV = 0x01;				 //divide the cclk by 1 for pclk = 60MHz
	T0CTCR = 0x00;			//select timer mode 
	T0PR = PRESCALE-1;			//SET 	prescaler value to 60000-1 for  60000/60MHz=1/1000=1ms
	
	T0PC = 0x00;		//count start from 0x00

	T0MCR = (1<<0);
}



	void timer_delay_ms_on_reset(unsigned int time)
	{
		T0MCR = (1<<1)|(1<<0);				 //MR0 set reset timer mode
		T0MR0 = time; 				// 1ms*1000=1sec delay
		T0TCR = 0x02;						//counter enable
		T0TCR = 0x01;						//counter reset
		while(T0TC != time); 			//wait untill time counter is overflow
	}
	void timer_delay_ms_on_stop(unsigned int time)
	{
		T0MCR = (1<<2)|(1<<0);				 // select MR0 in stop mode
		T0MR0 = time;					 // 1ms*1000=1sec delay
		T0TCR = 0x02; 			//timer counter and  prescaler are enable
		T0TCR = 0x02;					//counter enable
		T0TCR = 0x01; 					//counter reset
		
		while(!(T0TC == time)); 			//wait untill the timer count is overflow
	}
		
void timer_interrupt_init(void)
{
		VICVectAddr0 = (unsigned long)isr_timer;
	VICVectCntl0 = (1<<5)|(1<<2);
	VICIntEnable = (1<<4);
}
void isr_timer(void)__irq
{
	T0IR =(1<<0);

	IO1CLR = 0x02000000;
		IO0CLR = 0x80000000;
		
	delay(500);
		IO0SET = 0x80000000;
		IO1SET = 0x02000000;
	delay(400);
		
		//IO1CLR = 0x02000000;
		IO0CLR = 0x80000000;
		delay(400);
		IO0SET = 0x80000000;
		//IO1SET = 0x02000000;
		delay(400);
		
		//IO1CLR = 0x02000000;
		IO0CLR = 0x80000000;
		delay(400);
		IO0SET = 0x80000000;
		IO1SET = 0x02000000;
	delay(400);
	
VICVectAddr = 0x00;
	
	
}
void delay(unsigned long time)
{
	int i,j;
	for(i=0;i<10000;i++)
	for(j=0;j<time;j++);
}