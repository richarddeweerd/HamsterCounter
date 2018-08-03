#define sensor_pin 14

unsigned long counter;
unsigned long lastpulse;

double lap_length = 0.40;

bool inter = false;

void count() {
  inter = true;
}

void setup() {
  Serial.begin(115200);
  pinMode ( sensor_pin, INPUT );
  counter = 0;
  lastpulse = 0;

  attachInterrupt(digitalPinToInterrupt(sensor_pin), count, FALLING);

}

void loop() {
  if (inter){
    unsigned long t = millis();
    unsigned long pulsetime = t - lastpulse ;
    if (pulsetime >= 50){
      counter++;
      double lap_speed = double(1000) / pulsetime;
      lap_speed *=lap_length;

      if (pulsetime < 30000){
        Serial.print(counter);
        Serial.print(" Speed: ");
        Serial.print(lap_speed);
        Serial.print(" m/s or ");
        Serial.print(lap_speed * 3.6);
        Serial.println(" km/h");        
      }
      
      lastpulse = t;
      
    }
    inter = false;
  
  }
}
