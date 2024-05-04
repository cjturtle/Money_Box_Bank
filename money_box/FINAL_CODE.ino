
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

// Pin definitions
const int snooze_buttonMinPin = 5;     // Pin for minutes button
const int snooze_buttonSecPin = 6;     // Pin for seconds button
const int snooze_buttonStartPin = 7;   // Pin for start button

int snooze_minutes = 0;
int snooze_seconds = 0;
bool timerSet = false;

unsigned long snooze_startTime;
bool snooze_isTimerRunning = true;
const unsigned long snooze_timerDuration;
const int IR_PIN = 2;

unsigned long startTime = 0;  // Initialize the start time
bool isTimerRunning = true;   // Flag to track whether the timer is running
int ledPin =  3;

void(* resetFunc) (void) = 0;

void setup() {
  Serial.begin(9600);
  pinMode(IR_PIN, INPUT);
  pinMode(ledPin, OUTPUT);

  pinMode(snooze_buttonMinPin, INPUT_PULLUP);
  pinMode(snooze_buttonSecPin, INPUT_PULLUP);
  pinMode(snooze_buttonStartPin, INPUT_PULLUP);
  

  lcd.init();
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("M O N E Y");
  delay(2000);
  lcd.setCursor(8,1);
  lcd.print("B O X");
  delay(2000);
  lcd.clear();
  delay(2000);
  lcd.setCursor(3,0);
  lcd.print("M O N E Y");
  lcd.setCursor(5,1);
  lcd.print("B O X");
  lcd.clear();
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("SET SNOOZE ALARM:");
}

void loop() {

  if(timerSet == true){
    do{  
      day_timer();
    }
    while(timerSet == true);
  }else{
    snooze_setter();
  }
  
}


void day_timer(){
  snooze_isTimerRunning = true;
  if (isTimerRunning) {
    unsigned long elapsedTime = millis() - startTime;

    // Convert milliseconds to hours, minutes, and seconds
    int hours = elapsedTime / 3600000;
    int minutes = (elapsedTime % 3600000) / 60000;
    int seconds = ((elapsedTime % 3600000) % 60000) / 1000;

    // Display hours, minutes, and seconds on Serial Monitor
    Serial.print("Time: ");
    if (hours < 10) {
      Serial.print("0");
    }
    Serial.print(hours);
    Serial.print("h ");
    if (minutes < 10) {
      Serial.print("0");
    }
    Serial.print(minutes);
    Serial.print("m ");
    if (seconds < 10) {
      Serial.print("0");
    }
    Serial.print(seconds);
    Serial.println("s");

    lcd.setCursor(0,0);
    lcd.print("24 hours timer:");
    
    
    if(hours < 10){
       lcd.setCursor(0,1);
       lcd.print("0");
       lcd.setCursor(1,1);
       lcd.print(hours);
    }

    if(hours > 10){
       lcd.setCursor(0,1);
       lcd.print(hours);
    }
    
    if(minutes < 10){
       lcd.setCursor(3,1);
       lcd.print("0");
       lcd.setCursor(4,1);
       lcd.print(minutes);
    }
    if(minutes > 10){
       lcd.setCursor(3,1);
       lcd.print(minutes);
    }
    
    if(seconds < 10){
       lcd.setCursor(6,1);
       lcd.print("0");
       lcd.setCursor(7,1);
       lcd.print(seconds);
    }
    if(seconds > 10){
       lcd.setCursor(6,1);
       lcd.print(seconds);
    }

    lcd.setCursor(2,1);
    lcd.print(":");
    lcd.setCursor(5,1);
    lcd.print(":");

    
    

    // Check if the IR sensor is triggered
    if (isIRSensorTriggered()) {
      isTimerRunning = false;
      Serial.println("Timer stopped by IR sensor.");
      restart_time();
    }
    //hours == 24 && minutes == 59 && seconds == 59
    else if (hours == 00 && minutes == 00 && seconds == 10 ) {
    lcd.clear();
    isTimerRunning = false;
    buzzer();
    snoozeAlram();
    snooze_startTime = millis();
    do{
      startTimer();
    }while(isTimerRunning == false);
    
  }

       if (digitalRead(snooze_buttonStartPin) == LOW) {
        
      Serial.println("Restarting Arduino...");
      delay(1000); // Add a delay if needed
      resetFunc(); // Call the reset function
  } 
  
  }
}

void startTimer() {
  
  if (snooze_isTimerRunning) {
    // Calculate elapsed time
    
    unsigned long snooze_elapsedTime = millis() - snooze_startTime;
    long snooze_timerDuration = snooze_minutes * 60 * 1000UL;

    if (snooze_elapsedTime < snooze_timerDuration) {
      // Convert milliseconds to minutes and seconds
      int snooze_minutes = (snooze_timerDuration - snooze_elapsedTime) / 60000;
      int snooze_seconds = ((snooze_timerDuration - snooze_elapsedTime) % 60000) / 1000;

      // Display minutes and seconds on Serial Monitor
      Serial.print("Time: ");
      Serial.print(snooze_minutes);
      Serial.print("m ");
      Serial.print(snooze_seconds);
      Serial.println("s");

      
      lcd.setCursor(1,0);
      lcd.print("Snooze timer:");

      if(snooze_seconds < 10){
        
      lcd.setCursor(9,1);
      lcd.print(snooze_seconds);
      lcd.setCursor(8,1);
      lcd.print("0");
      
      }

      if(snooze_seconds > 10){
        
      lcd.setCursor(8,1);
      lcd.print(snooze_seconds);
      
      }

      lcd.setCursor(7,1);
      lcd.print(":");
      
      
      if(snooze_minutes < 10){
        lcd.setCursor(5,1);
        lcd.print("0");
        lcd.setCursor(6,1);
        lcd.print(snooze_minutes);
      }

      if(snooze_minutes > 10){
        
      lcd.setCursor(5,1);
      lcd.print(snooze_minutes);
      
      }

    }

    else{
      lcd.clear();
      buzzer();
      snooze_startTime = millis();
      
      
    }

    if (isIRSensorTriggered()) {
      lcd.clear();
      snooze_isTimerRunning = false;
      isTimerRunning = true;
      startTime = millis(); 
      Serial.println("Timer stopped by IR sensor.");
      do{
          
          day_timer();  
      }while(isTimerRunning == true);
    }

    if (digitalRead(snooze_buttonMinPin) == LOW) {
      lcd.clear();
      snooze_isTimerRunning = false;
      isTimerRunning = true;
      startTime = millis(); 
      Serial.println("Timer stopped by button!");
      do{
          day_timer();  
      }while(isTimerRunning == true);
      
    }

    if(snooze_minutes == 00 && snooze_seconds == 00){
      snooze_startTime = millis();
      do{
          startTimer();  
      }while(true);
    }

       if (digitalRead(snooze_buttonStartPin) == LOW) {
        
      Serial.println("Restarting Arduino...");
      delay(1000); // Add a delay if needed
      resetFunc(); // Call the reset function
  }

    
  }
  }
  


void snoozeAlram(){
  Serial.print("SNOOZE START");
  delay(1000);
}

void buzzer(){
  Serial.print("BUZZER");
  
  lcd.setCursor(3,0);
  lcd.print("BUZZER");
  lcd.setCursor(6,1);
  lcd.print("BUZZER");
  
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(500);
  
  
  lcd.clear();
}

void restart_time() {
  startTime = millis();
  isTimerRunning = true;
}

bool isIRSensorTriggered() {
  // Replace this with your actual code to check if the IR sensor is triggered
  // Example: return digitalRead(IR_PIN) == HIGH;
  return digitalRead(IR_PIN) == LOW;  // Adjust as needed based on your IR sensor output
}

void snooze_setter(){
  // Check if the minutes button is pressed
  if (digitalRead(snooze_buttonMinPin) == LOW) {
    for (int i = j; i < 1; i++) {
          lcd.clear();
         j = 2;
      }
    delay(400);  // Debounce
    snooze_minutes++;
    if (snooze_minutes > 99) {
      snooze_minutes = 0;
    }
    displayTime();
  }

  if (digitalRead(snooze_buttonSecPin) == LOW) {
    if(snooze_minutes < 11){
      lcd.setCursor(1, 1);
      lcd.print(" ");
    }
    for (int i = j; i < 1; i++) {
          lcd.clear();
         j = 2;
      }
    delay(400);  // Debounce
    snooze_minutes--;
    if (snooze_minutes > 99) {
      snooze_minutes = 0;
    }
    displayTime();
  }

  // Check if the start button is pressed
  if (digitalRead(snooze_buttonStartPin) == LOW) {
    delay(400);  // Debounce
    startTime = millis();
    timerSet = true;
    snooze_isTimerRunning = true;
    lcd.clear();
  }
}

void displayTime() {
  Serial.print("Time: ");
  Serial.print(snooze_minutes);
  Serial.print(" mins ");
  Serial.print(snooze_seconds);
  Serial.println(" secs");

  lcd.setCursor(0,0);
  lcd.print("SNOOZE ALARM:");
  lcd.setCursor(0,1);
  lcd.print(snooze_minutes);
  lcd.setCursor(2,1);
  lcd.print("minutes");
}
