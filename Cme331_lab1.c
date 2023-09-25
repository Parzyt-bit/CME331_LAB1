
#define SYSCTL_RCGC2   (* ((volatile unsigned long *) 0x400FE108))  // 0x400FE108 is a 'memory address' of a register that has particular function in the 'microcontroller'
#define GPIO_PORTF_DEN (* ((volatile unsigned long *) 0x4002551C))
#define GPIO_PORTF_DIR (* ((volatile unsigned long *) 0x40025400))
#define GPIO_PORTF_AFSEL (* ((volatile unsigned long *) 0x40025420))
#define GPIO_PORTF_DATA (* ((volatile unsigned long *) 0x400253FC))
#define GPIO_PORTF_PUR (* ((volatile unsigned long *) 0x40025510))


void gpio_portf_init(void)
{
    // This line sets the second bit (bit 3) high in the register at location 0x400FE108
    SYSCTL_RCGC2 |= 0x20; // enables 'clock' for PortF
    int delay = SYSCTL_RCGC2;

    // Configuration for Red LED
    GPIO_PORTF_DEN |= 0x02;  // set PF1 to be a digital pin
    GPIO_PORTF_DIR |= 0x02; // set PF1 to be an output pin
    GPIO_PORTF_AFSEL &= ~0x02; // disable alternate functions for PF1
    GPIO_PORTF_DATA |= 0x02;

   // Configuration for Blue LED
    GPIO_PORTF_DEN |= 0x04;  // set PF1 to be a digital pin
    GPIO_PORTF_DIR |= 0x04; // set PF1 to be an output pin
    GPIO_PORTF_AFSEL &= ~0x04; // disable alternate functions for PF1
    GPIO_PORTF_DATA |= 0x04;

    // Configuration for Green LED
    GPIO_PORTF_DEN |= 0x08;  // set PF1 to be a digital pin
    GPIO_PORTF_DIR |= 0x08; // set PF1 to be an output pin
   GPIO_PORTF_AFSEL &= ~0x08; // disable alternate functions for PF1
    GPIO_PORTF_DATA |= 0x08;

    // Configuration for SW1
    GPIO_PORTF_DEN |= 0x10;  // set PF4 to be a digital pin
    GPIO_PORTF_DIR &= ~0x10; // set PF4 to be an output pin
    GPIO_PORTF_AFSEL &= ~0x10; // disable alternate functions for PF4
    GPIO_PORTF_PUR |= 0x10;
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
        else                        // Switch is pressed
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
    while (1)
    {
        GPIO_PORTF_DATA &= ~0x04;
        GPIO_PORTF_DATA &= ~0x08;

        while (1)
        {
            GPIO_PORTF_DATA ^= 0x02;
            delay();
            if ((GPIO_PORTF_DATA & 0x10) == 0)
            {
                break;
            }
        }
        DELAY ();
        GPIO_PORTF_DATA &= ~0x02;
        GPIO_PORTF_DATA &= ~0x08;
        while (1)
        {
            GPIO_PORTF_DATA ^= 0x04;
            delay();
            if ((GPIO_PORTF_DATA & 0x10) == 0)
            {
                break;
            }
        }
        DELAY ();

        GPIO_PORTF_DATA &= ~0x02;
        GPIO_PORTF_DATA &= ~0x04;
        while (1)
        {
            GPIO_PORTF_DATA ^= 0x08;
            delay();
            if ((GPIO_PORTF_DATA & 0x10) == 0)
            {
                break;
            }
        }
        DELAY ();


    }
}
