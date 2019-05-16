#include <LPC214x.H> 
void init_ext_interrupt(void);
void Ext_ISR(void)__irq;
static int flag=0;

 
int main (void) 
{
	
  init_ext_interrupt();   // initialize the external interrupt


	
  while (1)  
  { 
  }
	
}
 
void init_ext_interrupt()  //Initialize Interrupt
{
	  PINSEL0 |=(1<<31);// 0x80000000;    //Select Pin function P0.15 as EINT2
  EXTMODE = (1<<2);           //Edge sensitive mode on EINT2
  EXTPOLAR &= ~(1<<2);    //Falling Edge Sensitive

  
  /* initialize the interrupt vector */
  VICIntSelect &= ~(1<<16);        	// EINT2 selected as IRQ 16
  VICVectAddr0 = (unsigned int)Ext_ISR; // address of the ISR
  VICVectCntl0 = (1<<5) | 16; // 
  VICIntEnable = (1<<16); 	// EINT2 interrupt enabled
 
  EXTINT &=~(1<<2) ; //INT 2 IS SELECTED
}
 
void Ext_ISR(void)__irq // Interrupt Service Routine-ISR 
{
	IO0DIR |= (1<<31);
	if(flag==0)
	{
 
 IO0CLR |= (1<<31); // Turn ON LED
 EXTINT |=(1<<2); //clear interrupt
 VICVectAddr = 0; // End of interrupt execution
		flag=1;
	}
	else
	{
		IO0SET |=(1<<31);
		EXTINT |=(1<<2);
		VICVectAddr = 0x00;
		flag=0;
	}
}

