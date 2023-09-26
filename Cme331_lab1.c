
#define SYSCTL_RCGC2       (* ((volatile unsigned long *) 0x400FE108)) 
#define GPIO_PORTF_DEN     (* ((volatile unsigned long *) 0x4002551C))
#define GPIO_PORTF_DIR     (* ((volatile unsigned long *) 0x40025400))
#define GPIO_PORTF_AFSEL   (* ((volatile unsigned long *) 0x40025420))
#define GPIO_PORTF_DATA    (* ((volatile unsigned long *) 0x400253FC))
#define GPIO_PORTF_PUR     (* ((volatile unsigned long *) 0x40025510))


void gpio_portf_init(void)
{
    // This line sets the sixth bit (bit 5) high in the register at location 0x400FE108
    SYSCTL_RCGC2 |= 0x20; // enables 'clock' for PortF
    int delay = SYSCTL_RCGC2;

    // Configuration for Red LED
    GPIO_PORTF_DEN |= 0x02;  // set PF1 to be a digital pin
    GPIO_PORTF_DIR |= 0x02; // set PF1 to be an output pin
    GPIO_PORTF_AFSEL &= ~0x02; // disable alternate functions for PF1
    GPIO_PORTF_DATA |= 0x02; // enable pullup resistor for PF1

   // Configuration for Blue LED
    GPIO_PORTF_DEN |= 0x04;  // set PF2 to be a digital pin
    GPIO_PORTF_DIR |= 0x04; // set PF2 to be an output pin
    GPIO_PORTF_AFSEL &= ~0x04; // disable alternate functions for PF2
    GPIO_PORTF_DATA |= 0x04; // enable pullup resistor for PF2

    // Configuration for Green LED
    GPIO_PORTF_DEN |= 0x08;  // set PF3 to be a digital pin
    GPIO_PORTF_DIR |= 0x08; // set PF3 to be an output pin
   GPIO_PORTF_AFSEL &= ~0x08; // disable alternate functions for PF3
    GPIO_PORTF_DATA |= 0x08; // enable pullup resistor for PF3

    // Configuration for SW1
    GPIO_PORTF_DEN |= 0x10;  // set PF4 to be a digital pin
    GPIO_PORTF_DIR &= ~0x10; // set PF4 to be an output pin
    GPIO_PORTF_AFSEL &= ~0x10; // disable alternate functions for PF4
    GPIO_PORTF_PUR |= 0x10; // enable pullup resistor for PF4
}
void delay (void)
{
    int i = 0;
    while (i <= 800000)
    {
        if ((GPIO_PORTF_DATA & 0x10) == 0x10)   // Switch is not pressed
        {
            i = i + 1;
        }
        else      // Switch is pressed
        {
            break;
        }
    }
}

void DELAY (void)
{
    int i = 0;
    while (i <= 800000)
    {
        i = i + 1;
    }

}
int main(void)
{
    gpio_portf_init();
    
    // Main loop
    while (1) 
    {
        GPIO_PORTF_DATA &= ~0x04;  // Turning off the Blue LED if switched ON
        GPIO_PORTF_DATA &= ~0x08;  // Turning off the Green LED if switched ON
        
        while (1)  // internal loop 1, for blinking Red LED
        {
            GPIO_PORTF_DATA ^= 0x02;  // Toggles the Red LED infinitely
            delay();
            if ((GPIO_PORTF_DATA & 0x10) == 0)
            {
                break;   
            }
        }
        DELAY ();
        
        GPIO_PORTF_DATA &= ~0x02;  // Turning off the Red LED if switched ON
        GPIO_PORTF_DATA &= ~0x08;  // Turning off the Green LED if switched ON
        
        while (1)  // internal loop 2, for blinking Blue LED
        {
            GPIO_PORTF_DATA ^= 0x04;  // Toggles the Blue LED infinitely
            delay();
            if ((GPIO_PORTF_DATA & 0x10) == 0)
            {
                break;
            }
        }
        DELAY ();

        GPIO_PORTF_DATA &= ~0x02;  // Turning off the Red LED if switched ON
        GPIO_PORTF_DATA &= ~0x04;  // Turning off the Blue LED if switched ON
        
        while (1)  // internal loop 3, for blinking Green LED
        {
            GPIO_PORTF_DATA ^= 0x08;  // Toggles the Green LED infinitely
            delay();
            if ((GPIO_PORTF_DATA & 0x10) == 0)
            {
                break;
            }
        }
        DELAY ();


    }
}
