
uint8_t pins[3]={0,2,4};
uint32_t color=0;
uint8_t nextState;
uint8_t incValue=1;
void setup() {
Serial.begin(115200);
for(int i=0; i<3; i++){
  pinMode(pins[i],OUTPUT);
  digitalWrite(pins[i], HIGH);
}


}

float glow=3;
unsigned long t=0;
void loop() {
  
  uint16_t red=(color &(0x3FF<<20))>>20;
  uint16_t green=(color &(0x3FF<<10))>>10;
  uint16_t blue=(color & 0x3FF);
  uint32_t colorP=color;
  color=(nextState&0b001)? ((blue>=0x3FF)? color: color+incValue) : (blue==0)? color : color-incValue;
  color=(nextState&0b010)? ((green>=0x3FF)? color: color+(incValue<<10)) : (green==0)? color : color-(incValue<<10);
  color=(nextState&0b100)? ((red>=0x3FF)? color: color+(incValue<<20)) : (red==0)? color : color-(incValue<<20);
  bool shiftValue= !(nextState&0b10);
  nextState=(color==colorP)? (nextState<<1)+shiftValue : nextState;
  nextState=nextState&0b111;
  Serial.print(nextState); Serial.print('\t'); Serial.print(red);Serial.print('\t'); Serial.print(green);Serial.print('\t'); Serial.println(blue);
  displayColors(red, green, blue);
  delay(1);
  if(millis()-t>1000){
    if(glow==1) glow=3;
    else glow-=0.1;
    t=millis();
  }
}

void displayColors(uint16_t red, uint16_t green, uint16_t blue){
  analogWrite(pins[0],(1023-(red/glow)));
  analogWrite(pins[1], (1023-(green/glow)));
  analogWrite(pins[2], (1023-(blue/glow)));
  
  
}
