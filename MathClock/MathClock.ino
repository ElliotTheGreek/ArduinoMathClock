#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// setup digital pin numbers and last state
const int revealPin = 12;
int lastRevealPin = 0;

const int refreshPin = 6;
int lastRefreshPin = 0;

const int hourPin = 10;   
int lastHourPin = 0;

const int minutePin = 8;   
int lastMinutePin = 0;

// initial Time display is 12:59:45 PM
int initialFunctionSpawn = 0;
int hour=11;
int minute=5;
int second=0;
int amPmFlag=0; //PM

String functionLeft = "()";
String functionRight = "()";
// For accurate Time reading, use Arduino Real Time Clock and not just delay()
static uint32_t last_time, now = 0; // RTC

void setup()
{
  pinMode(revealPin, INPUT_PULLUP);
  pinMode(refreshPin, INPUT_PULLUP);
  pinMode(hourPin, INPUT_PULLUP);
  pinMode(minutePin, INPUT_PULLUP);

  lcd.begin();
  lcd.backlight();
}

void show_math() {
  lcd.setCursor(0,0);
  lcd.print(functionLeft);
  lcd.print(":");
  lcd.print(functionRight);
  lcd.setCursor(0,1);
  int chunks = round((float) 16 * ((float) second / (float) 60));
  if (second >= 58) {
    show_time(false);  
  } else {
    int cols = 0;
    while ( cols < 16 ) {
      if (chunks == cols) {
        lcd.print(".");
      } else {
        lcd.print(" ");
      }
      cols += 1;
    }
  }

}

void show_time(bool show_seconds) {
  if(hour<10)lcd.print("0");// always 2 digits
  lcd.print(hour);
  lcd.print(":");
  if(minute<10)lcd.print("0");
  lcd.print(minute);
  if (show_seconds) {
    lcd.print(":");
    if(second<10)lcd.print("0");
    lcd.print(second);
  }
  
  if(amPmFlag==0) lcd.print(" AM");
  if(amPmFlag==1) lcd.print(" PM");
  
  lcd.print(" ");
  lcd.print(" ");
  lcd.print(" ");
  lcd.print(" ");
  lcd.print(" ");
  lcd.print(" ");
  lcd.print(" ");
  lcd.print(" ");
}

String makeFunction(int number) {
  int method = random(2); // 0 = add, 1 = subtract, 2 = multiply
  int r = random(9) + 1;
  String methodString = "";
  int leftNumber = 0;
  switch (method) {
    case 0:
      leftNumber = number + r;
//      return String((number + r)) + "-"+ String(r);
      break;
    case 1:
      leftNumber = number - r;
//      return String((number - r)) + "+"+ String(r);
      break;
    case 2:
      leftNumber = number * r;
//      return String((number * r)) + "/"+ String(r);
      break;
  }

  int r2 = random(9) + 1;
  int method2 = random(3); // 0 = add, 1 = subtract, 2 = multiply
  String leftSide = "";
  switch (method2) {
    case 0:
      leftSide = String((leftNumber + r2)) + "-"+ String(r2);
      break;
    case 1:
      leftSide = String((leftNumber - r2)) + "+"+ String(r2);
      break;
    case 2:
      leftSide = String((leftNumber * r2)) + "/"+ String(r2);
      break;
  }

  switch (method) {
    case 0:
      return leftSide + "-"+ String(r);
      break;
    case 1:
      return leftSide + "+"+ String(r);
      break;
    case 2:
      return leftSide + "/"+ String(r);
      break;
  }

  return methodString;
}

void spawnFunctions() {
  lcd.clear();
  functionLeft = makeFunction(hour);
  functionRight = makeFunction(minute);
}

void loop()
{
// make 5 time 200ms loop, for faster Button response
  for ( int i=0 ;i<5 ;i++) {
    while ((now-last_time)<200) { 
      now=millis();
    }
    last_time=now;

    // everything below occurs 5 times a second

    /* handle the refreshour button */
    int hourPinValue = digitalRead(hourPin);
    if(hourPinValue != lastHourPin) {
      if (hourPinValue != LOW) {
        hour++;
        spawnFunctions();
      }
      lastHourPin = hourPinValue;
    }

    /* handle the hour button */
    int refreshPinValue = digitalRead(refreshPin);
    if(refreshPinValue != lastRefreshPin) {
      if (refreshPinValue != LOW) {
        spawnFunctions();
      }
      lastRefreshPin = refreshPinValue;
    }

    /* handle the minute button */
    int minutePinValue = digitalRead(minutePin);
    if(minutePinValue != lastMinutePin) {
      if (minutePinValue != LOW) {
        minute++;
        second = 0;
        spawnFunctions();
      }
      lastMinutePin = minutePinValue;
    }

    /* ---- manage seconds, minutes, hours am/pm overflow ----*/
    int respawnFunctions = 0;
     if(second>=60) {
      second=0;
      minute=minute+1;
      respawnFunctions=1;
     }
     if(minute>=60) {
      minute=0;
      hour=hour+1;
      respawnFunctions=1;
     }
     if(hour>=13) {
      hour=1;
      amPmFlag=amPmFlag+1;
      if(amPmFlag==2)amPmFlag=0;
      respawnFunctions=1;
     }

     if(respawnFunctions == 1) {
      spawnFunctions();
     }
 
    int revealPinValue = digitalRead(revealPin);
    // if the reveal pin state has changed
    if (revealPinValue != lastRevealPin) {
      lcd.clear();
      lastRevealPin = revealPinValue;
    }

    if (revealPinValue == LOW) {
     lcd.setCursor(0,0);
     show_time(true);
    } else {
     show_math();
    }
    /* end of 5x a second loop */
  }

  second=second+1;

  if (initialFunctionSpawn == 0) {
    spawnFunctions();
    initialFunctionSpawn = 1;
  }
}
