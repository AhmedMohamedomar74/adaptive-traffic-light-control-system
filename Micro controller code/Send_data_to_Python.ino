// Arduino Code
unsigned char * Puff;
unsigned char * randNumber_Arr_one (void);
void setup() {
    Serial.begin(9600);

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
}

void loop() {
  
  
  unsigned char* randArray = randNumber_Arr_one();
  Serial.write(randArray, 4);
  free(randArray); 

  //delay(50);
}

unsigned char * randNumber_Arr_one(void)
{
  unsigned char * Rand_arr = (unsigned char *) malloc(4*sizeof(unsigned char));
  if (Rand_arr != NULL)
  {
    for (unsigned int i = 0; i < 4; i++) {
      Rand_arr[i] = random(0, 15);
    }
    }
  return  Rand_arr;
}
