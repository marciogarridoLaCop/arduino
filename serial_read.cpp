/**
Programa de Pós Graduação em Engenharia Elétrica e Telecomunicações
LACOP - Laboratório de Comunicações Óticas - UFF
Aluno : Márcio Alexandre Dias Garrido
**/

int flag.ctr,ctr_arr = 0;
char ReadReq;

unsigned int a, b, c, d 0;

unsigned int sensor1[200];
unsigned int sensor2[200];
unsigned int sensor3[200];
unsigned int sensor4[200];

void setup() {

  Serial.begin(230400);
  
  //set timer1 interrupt at 100 Hz
  cli();      
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 1999;// = (16*10^6) / (1000*8) - 1
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS11);
  TIMSK1 |= (1 << OCIE1A);
  sei();    //allow interrupts

}

void loop() {
  if (Serial.available() > 0) { 
    
    // Check if any data has been sent by the PC
    ReadReq = Serial.read();

    // Use character R to indicate starting of Readings
    if ((ReadReq == 'R') && (flag == 0)) {
      ctr = 0;
      flag = 1;    // go to Interrupt Service Routine
    } 
  }
}
ISR(TIMER1_COMPA_vect) {  // FREQ 1 KHz.
  if (flag == 1)
  { // takes 200 samples and send it to the MATLAB through serial
    a = analogRead(A0); 
    b = analogRead(A1); 
    c = analogRead(A2); 
    d = analogRead(A3); 

    sensor1[ctr] = a;
    sensor1[ctr] = b;
    sensor1[ctr] = c;
    sensor1[ctr] = d;

    ctr = ctr + 1;
    if (ctr == 200) // means we had it 200 times
    {
      flag = 0;
      ctr = 0;
      Serial.println("D");    // means DONE Reading. Now we proceed sending.
      SendData();
    }
  }
};

  void SendData(){
  
  for (int i=0; i<200; i++){  
    // Send arrays of sensor reading to MATLAB
    
    Serial.print(sensor1[i]);
    Serial.print(",");
    Serial.print(sensor1[i]);
    Serial.print(",");
    Serial.print(sensor1[i]);
    Serial.print(",");
    Serial.print(sensor1[i]);
    Serial.print("\n");
    
    }

  }
