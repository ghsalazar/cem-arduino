/// @file   two-phase-inverter.ino
/// @author Gastón Hugo Salazar Silva <ghsalazar@ipn.mx>
/// @date   2021-06-03
/// @brief  Implementación de un inversor simple 
///         sobre la tarjeta Arduino UNO

const int ENABLE_1 = 1 << 6;
const int ENABLE_2 = 1 << 7;
const int OUTPUTS  = 0b1111 << 2;

const int output[] { 
  0b1001 << 2,
  0b1010 << 2,
  0b0110 << 2,
  0b0101 << 2
};

const int STATES   = 0b11;

void setup()
{
  DDRD = ENABLE_2 | ENABLE_1 | OUTPUTS;         //Setting pins for output
}

void loop()
{
  static int state = 0;

  state = (++state) & STATES;                   // State update
  PORTD = ENABLE_2 | ENABLE_1 | output[state];  // Output setting
  delay(1000);                                  // Waiting time in milliseconds
}
