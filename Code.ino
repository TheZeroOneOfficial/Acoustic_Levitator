/*
 * The code generates a 40kHz square wave on 2 output pins (PB0 & PB1) with 180 degrees phase shift between them.
 * Designed for the ATtiny13 microcontroller.
 * 
 * Pin Configuration:
 *  
 *  Physical Pin 1 == PB5: Unused. Set as Input w/ internal pull-up resistor enabled. 
 *  Physical Pin 2 == PB3: STBY Pin. Set as Output HIGH.
 *  Physical Pin 3 == PB4: Unused. Set as Input w/ internal pull-up resistor enabled.
 *  Physical Pin 4 == GND: GND Pin. Connect to GND.
 *  Physycal Pin 5 == PB0: 40kHz Pin. Set as Output.
 *  Physical Pin 6 == PB1: 40kHz Pin. Set as Output.
 *  Physical Pin 7 == PB2: Unused. Set as Input w/ internal pull-up resistor enabled.
 * 
 */

void setup() {
  
  // Disable all interrupts
  TIMSK0 |= (0 << OCIE0B) | (0 << OCIE0A) | (0 << TOIE0);
  
  // Define I/O pins (1 == output, 0 == input)
  DDRB = (0 << DDB5) | (0 << DDB4) | (1 << DDB3) | (0 << DDB2) | (1 << DDB1) | (1 << DDB0);

  // Define pullups (input pins) and output states (output pins)
  PORTB = (1 << PORTB5) | (1 << PORTB4) | (1 << PORTB3) | (1 << PORTB2);
  
  // Enable CTC Mode
  TCCR0A |= (1 << WGM01) | (0 << WGM00); 
  TCCR0B |= (0 << WGM02);
  
  // 120 scale factor gives 40.0kHz - 40.2kHz at 9.6MHz MCU frequency
  OCR0A = 120;
  OCR0B = 120;
  
  // Toggle pin states on compare match
  TCCR0A |= (0 << COM0A1) | (1 << COM0A0) | (0 << COM0B1) | (1 << COM0B0);
  
  // No prescaler
  TCCR0B |= (0 << CS02) | (0 << CS02) | (1 << CS00);

  // Make it start
  GTCCR |= (1 << PSR10);

  // Force one invert
  TCCR0B |= (1 << FOC0B);
}

void loop() {
}
