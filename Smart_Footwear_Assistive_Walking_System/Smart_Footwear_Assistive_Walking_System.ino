/* 
 * Modified by
 * Blue and Black Flame Master, BBFM15
 */

#define pingPin 2        // Trig pin of HC-SR04
#define echoPin 3        // Echo pin of HC-SR04

void setup() 
{ 
   Serial.begin(9600); // Start Serial Communication
   pinMode(pingPin, OUTPUT); 
   pinMode(echoPin, INPUT);
   pinMode(12, OUTPUT);   // Pin 12 used as extra GND for motor
   pinMode(A3, OUTPUT);   // Pin A3 drives the vibration motor
}

void loop() 
{ 
   long duration, cm;

   digitalWrite(12, LOW);   // Motor GND always LOW

   // Send ultrasonic pulse
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);    
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);

   duration = pulseIn(echoPin, HIGH);  // Measure echo time
   cm = microsecondsToCentimeters(duration);

   // Debug (optional)
   // Serial.print(cm); Serial.print(" cm"); Serial.println();

   // Distance-based vibration intensity
   if (cm < 30 && cm > 20) { 
      analogWrite(A3, 255); 
      delay(1000); 
      analogWrite(A3, 0); 
      delay(1000); 
   }    
   else if (cm < 20 && cm > 10) { 
      analogWrite(A3, 255); 
      delay(500); 
      analogWrite(A3, 0); 
      delay(500); 
   }   
   else if (cm < 10 && cm > 0) { 
      analogWrite(A3, 255); 
      delay(100); 
      analogWrite(A3, 0);
      delay(100); 
   }    
   else { 
      analogWrite(A3, 0);  // Stop motor
   }
}

// Convert echo time to distance in centimeters
long microsecondsToCentimeters(long microseconds) 
{ 
   return microseconds / 29 / 2;
}
