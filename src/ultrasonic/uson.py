import time
import Jetson.GPIO as GPIO

SENSOR_MAX_DISTANCE = 30

# Use board based pin numbering
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

def ReadDistance(pin1):
   GPIO.setup(pin1, GPIO.OUT)
   GPIO.output(pin1, 0)

   time.sleep(0.000002)
   #send trigger signal
   GPIO.output(pin1, 1)
   time.sleep(0.000005)
   GPIO.output(pin1, 0)
   GPIO.setup(pin1, GPIO.IN)
   while GPIO.input(pin1)==0:
      starttime1=time.time()
   while GPIO.input(pin1)==1:
      endtime1=time.time()
   duration1=endtime1-starttime1
   # Distance is defined as time/2 (there and back) * speed of sound 34000 cm/s 
   distance=duration1*34000/2 
   if distance>30:
       distance=30
   return distance


while True:
   distance1 = ReadDistance(11)
   print("Sensor 1 - Distance to object is ",distance1," cm or ",distance1*.3937, " inches")
   time.sleep(.1)
   distance2 = ReadDistance(12)
   print("Sensor 2 - Distance to object is ",distance2," cm or ",distance2*.3937, " inches")
   time.sleep(.1)
   distance3 = ReadDistance(13)
   print("Sensor 3 - Distance to object is ",distance3," cm or ",distance3*.3937, " inches")
   time.sleep(.1)
   distance4 = ReadDistance(15)
   print("Sensor 4 - Distance to object is ",distance4," cm or ",distance4*.3937, " inches")
   
   time.sleep(.1)