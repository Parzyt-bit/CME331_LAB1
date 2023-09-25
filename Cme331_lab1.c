
#define SYSCTL_RCGC2   (* ((volatile unsigned long *) 0x400FE108))  // 0x400FE108 is a 'memory address' of a register that has particular function in the 'microcontroller'
#define GPIO_PORTF_DEN (* ((volatile unsigned long *) 0x4002551C))
#define GPIO_PORTF_DIR (* ((volatile unsigned long *) 0x40025400))
#define GPIO_PORTF_AFSEL (* ((volatile unsigned long *) 0x40025420))
#define GPIO_PORTF_DATA (* ((volatile unsigned long *) 0x400253FC))
#define GPIO_PORTF_PUR (* ((volatile unsigned long *) 0x40025510))

int i_g = 0;

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
    gpio_portf_init();
    i_g = 0;
    while (i_g <= 1000000)
    {
        if ((GPIO_PORTF_DATA & 0x10) == 0x10)   // Switch is not pressed
        {
            i_g = i_g + 1;
        }
        else                        // Switch is pressed
        {
            i_g = -1;
            break;
        }

    }
}

void DELAY (void)
{
    i_g = 0;
    while (i_g <= 1000000)
    {
        i_g = i_g + 1;
    }

}
int main(void)
{
    gpio_portf_init();
    while (1)
    {

       GPIO_PORTF_DATA &= ~0x04; // Switched Blue LED off
       GPIO_PORTF_DATA &= ~0x08; // Switched Green LED off

       while (1)
       {
        if ((GPIO_PORTF_DATA & 0x10) == 0x10)
        {
            GPIO_PORTF_DATA ^= 0x02;
            delay();
            if (i_g == -1)
            {
                break;
            }

            else
            {
                break;
            }
        }
       }
       DELAY();

       GPIO_PORTF_DATA &= ~0x02; // Switched Red LED off
       GPIO_PORTF_DATA &= ~0x08; // Switched Green LED off

       while (1)
       {
        if ((GPIO_PORTF_DATA & 0x10) == 0x10)
        {
            GPIO_PORTF_DATA ^= 0x04;
            delay();
            if (i_g == -1)
            {
                break;
            }

            else
            {
                break;
            }
        }
       }
       DELAY();

       GPIO_PORTF_DATA &= ~0x02; // Switched Red LED off
       GPIO_PORTF_DATA &= ~0x04; // Switched Blue LED off

       while (1)
       {
        if ((GPIO_PORTF_DATA & 0x10) == 0x10)
        {
            GPIO_PORTF_DATA ^= 0x04;
            delay();
            if (i_g == -1)
            {
                break;
            }

            else
            {
                break;
            }
        }
       }
       DELAY();

    }
}
