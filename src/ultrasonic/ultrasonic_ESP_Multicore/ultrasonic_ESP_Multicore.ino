

/* MACRO To Enable Multi Threading */
#define ENABLE_MULTITHREADING       0

/* MACRO To Enable Round Robin Polling */
#define ENABLE_ROUND_ROBIN_POLLING  1

/* MACRO To Define Delay Between Reads */
#define POLLING_DELAY_BETWEEN_READS 2

/* MACRO To Define Sensor Minimum Value */
#define ULTRASONIC_SENSOR_MIN_VALUE 3

/* MACRO To Define Sensor Maximum Value */
#define ULTRASONIC_SENSOR_MAX_VALUE 30

/* Task Handles For Multi Threading */
TaskHandle_t frontUltrasonicSensorTaskHandle;
TaskHandle_t rightUltrasonicSensorTaskHandle;
TaskHandle_t leftUltrasonicSensorTaskHandle;
TaskHandle_t rearUltrasonicSensorTaskHandle;

/* Pin Definitions For Connected Ultrasonic Sensors */
const int frontUltrasonicSensorPingPin = 25; // Front
const int rightUltrasonicSensorPingPin = 26; // Right
const int leftUltrasonicSensorPingPin  = 32; // Left
const int rearUltrasonicSensorPingPin  = 33; // Rear

/* Global Variables To Hold Read Sensor Values */
long sensorValFront = 0;
long sensorValRight = 0;
long sensorValLeft  = 0;
long sensorValRear  = 0;

void setup() {

  /* Initialize Serial Communication */
  Serial.begin(115200);

#if ENABLE_MULTITHREADING 

  xTaskCreatePinnedToCore (
    readFrontSensorVal,                          // Function to implement the task
    "Read Value From Front Ultrasonic Sensor",   // Name of the task
    10000,                                       // Stack size in words
    NULL,                                        // Task input parameter
    0,                                           // Priority of the task
    &frontUltrasonicSensorTaskHandle,            // Task handle.
    0                                            // Core where the task should run
  );

  delay(600);
  
  xTaskCreatePinnedToCore (
    readRightSensorVal,                          // Function to implement the task
    "Read Value From Right Ultrasonic Sensor",   // Name of the task
    10000,                                       // Stack size in words
    NULL,                                        // Task input parameter
    0,                                           // Priority of the task
    &rightUltrasonicSensorTaskHandle,            // Task handle.
    0                                            // Core where the task should run
  );

  delay(600);

  xTaskCreatePinnedToCore (
    readLeftSensorVal,                           // Function to implement the task
    "Read Value From Left Ultrasonic Sensor",    // Name of the task
    10000,                                       // Stack size in words
    NULL,                                        // Task input parameter
    0,                                           // Priority of the task
    &leftUltrasonicSensorTaskHandle,             // Task handle.
    0                                            // Core where the task should run
  );

  delay(600);

  xTaskCreatePinnedToCore (
    readRearSensorVal,                           // Function to implement the task
    "Read Value From Right Ultrasonic Sensor",   // Name of the task
    10000,                                       // Stack size in words
    NULL,                                        // Task input parameter
    0,                                           // Priority of the task
    &rearUltrasonicSensorTaskHandle,             // Task handle.
    0                                            // Core where the task should run
  );

  delay(600);

#endif

}
  

void loop() {

  /* Do Nothing! */
  /* For Future API Integration */ 

#if ENABLE_ROUND_ROBIN_POLLING

    Serial.print("Front Sensor: ");
    sensorValFront = getUltrasonicSensorValue(frontUltrasonicSensorPingPin);
    Serial.print(sensorValFront);
    Serial.println();

    delay(POLLING_DELAY_BETWEEN_READS);

    Serial.print("Right Sensor: ");
    sensorValRight = getUltrasonicSensorValue(rightUltrasonicSensorPingPin);
    Serial.print(sensorValRight);
    Serial.println();

    delay(POLLING_DELAY_BETWEEN_READS);

    Serial.print("Left Sensor:  ");
    sensorValLeft = getUltrasonicSensorValue(leftUltrasonicSensorPingPin);
    Serial.print(sensorValLeft);
    Serial.println();

    delay(POLLING_DELAY_BETWEEN_READS);

    Serial.print("Rear Sensor:  ");
    sensorValRear = getUltrasonicSensorValue(rearUltrasonicSensorPingPin);
    Serial.print(sensorValRear);
    Serial.println();

    delay(POLLING_DELAY_BETWEEN_READS);

#endif
 
}

void readFrontSensorVal (void* pvParameters) {
   
  while (1) {  
    
    sensorValFront = getUltrasonicSensorValue(frontUltrasonicSensorPingPin);
    Serial.print("Front Sensor: ");
    Serial.print(sensorValFront);
    Serial.println();
    delay(150);
  }
}

void readRightSensorVal (void* pvParameters) {

  while (1) {  
  
    sensorValRight = getUltrasonicSensorValue(rightUltrasonicSensorPingPin);
    Serial.print("Right Sensor: ");
    Serial.print(sensorValRight);
    Serial.println();
    delay(150);
  }
}

void readLeftSensorVal (void* pvParameters) {
  
  while (1) {  
  
    sensorValLeft = getUltrasonicSensorValue(leftUltrasonicSensorPingPin);
    Serial.print("Left Sensor:  ");
    Serial.print(sensorValLeft);
    Serial.println();
    delay(150);
  }  
}

void readRearSensorVal (void* pvParameters) {
  
  while (1) {  
  
    sensorValRear = getUltrasonicSensorValue(rearUltrasonicSensorPingPin);
    Serial.print("Rear Sensor:  ");
    Serial.print(sensorValRear);
    Serial.println();
    delay(150);
  }  
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

long getUltrasonicSensorValue(int pingPin)
{
  long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  cm = microsecondsToCentimeters(duration);

  /* TODO: Fix Handling Maximum and Minimum Values */
  return (cm < ULTRASONIC_SENSOR_MAX_VALUE) ? cm : ULTRASONIC_SENSOR_MAX_VALUE;
}
