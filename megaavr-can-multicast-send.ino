
// LED to indicate heartbeat
const int led_pin = PB7;

//Counter and compare values for 1Hz timer interrupt
const uint16_t tl_comp = 15625;

void setup()
{
    setupOneHertzTimer();
}

// the loop function runs over and over again forever
void loop()
{
    delay(1000);
}

ISR(TIMER4_COMPA_vect)
{
    PORTB ^= (1 << led_pin);
}

void setupOneHertzTimer()
{
    cli();
    DDRB |= (1 << led_pin);

    // Reset Timer4 Control Reg A and B
    TCCR4A = 0;
    TCCR4B = 0;

    // Set CTC mode
    TCCR4B &= ~(1 << WGM43);
    TCCR4B |= (1 << WGM42);

    // Set to prescaler of 1024
    TCCR4B |= (1 << CS42);
    TCCR4B &= -(1 << CS41);
    TCCR4B |= (1 << CS40);

    // Reset Timer4 and set compare values
    TCNT4 = 0;
    OCR4A = tl_comp;

    // Enalble Timer4 and set compare value
    TIMSK4 = (1 << OCIE4A);
    sei();
}