const int ENABLE_1 = 1 << 6;
const int ENABLE_2 = 1 << 7;
const int OUTPUTS  = 0b1111 << 2;

const int STATES   = 0b11;

const int output[] { 
  0b1001 << 2,
  0b1010 << 2,
  0b0110 << 2,
  0b0101 << 2
};

void setup()
{
  DDRD = ENABLE_2 | ENABLE_1 | OUTPUTS; //Setting pins for output
}

void loop()
{
  static int state = 0;

  state = (++state) & STATES;
  PORTD = ENABLE_2 | ENABLE_1 | output[state];
  delay(1000); // Wait for 1000 millisecond(s)
}
