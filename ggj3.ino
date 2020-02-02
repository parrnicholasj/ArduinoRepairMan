
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int timer = 1000;
bool gameRunning = true;
bool win = false;


bool task2Done = false;
bool task1Done = false;
bool task3Done = false;




const int redPin = 3;
const int greenPin = 5;

void setup() {
    
  digitalWrite(greenPin, HIGH);
  digitalWrite(redPin, HIGH); // sets the digital pin 13 on

  randomSeed(analogRead(0));

  
  Serial.begin(9600);
  delay(200);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  
  display.clearDisplay();   // clears the screen and buffer  
  display.setTextColor(WHITE);  
  display.setTextSize(2); 
  
  display.display();
  display.setRotation(2);

    display.setTextSize(2); 
    display.setCursor(0,25);
    int reps= 0;
    while(reps < 10)
    {
      
      display.clearDisplay();
      display.setCursor(0,25);
      display.print("loading");
      display.display();
      delay(100);
      display.clearDisplay();

      display.setCursor(0,25);
      display.print("loading.");
      display.display();
      delay(100);
      display.clearDisplay();

      display.setCursor(0,25);  
      display.print("loading..");
      display.display();
      delay(100);
      display.clearDisplay();

      display.setCursor(0,25);   
      display.print("loading...");
      display.display();
      delay(100);

      reps++;
    }

      display.clearDisplay();
      display.setCursor(10,25);
      display.print("*ERROR*");
      display.display();
  
  pinMode(4, INPUT); 

  digitalWrite(greenPin, LOW);
  digitalWrite(redPin, LOW); // sets the digital pin 13 on

}

void loop() 
{

    int rightDial = analogRead(A0);
    int leftDial = analogRead(A1);
    int yAxis = analogRead(A2);
    int xAxis = analogRead(A3);

    if (gameRunning)
    {
      //==========================first task===========================
        bool leftcneter = false;
        bool rightcenter = false;
        
        while (!task1Done)
        {
          rightDial = analogRead(A0);
          leftDial = analogRead(A1);
          if (leftDial > 250 && leftDial < 350)
          {
            Serial.println("Left dial centered");
            leftcneter = true;
            digitalWrite(greenPin, HIGH); // sets the digital pin 13 on
          }
          else
          {
            leftcneter = false;
            digitalWrite(greenPin, LOW); // sets the digital pin 13 on

          }
      
          if (rightDial > 555 && rightDial < 666)
          {
            Serial.println("right dial centered");
            rightcenter = true;
            digitalWrite(redPin, HIGH); // sets the digital pin 13 on
          }    
          else
          {
            rightcenter = false;
            digitalWrite(redPin, LOW); // sets the digital pin 13 on

          }

          
          if (rightcenter && leftcneter)
          {
            task1Done = true;
          }
        }
        if (task1Done)
        {
          display.clearDisplay(); 
          display.setCursor(10,25);
          display.print("GOOD");
          display.display();

        }
  
        //==========================first task===========================
        int midx = random(10, 110);
        int midy = random(10, 50);

        int xpos = 10;
        int ypos = 10;
        int diffx = 0;
        int diffy=0;
        while (!task2Done)
        {
           diffx = xpos - midx;
           diffy = ypos- midy;

           diffx = abs(diffx);
           diffy = abs(diffy);
           
           display.clearDisplay(); 
           yAxis = analogRead(A2);
           xAxis = analogRead(A3);
             
           display.drawCircle(midx, midy, 7, WHITE);
           display.drawCircle(xpos, ypos, 7, WHITE);
           display.display();
           
           if (yAxis > 650)
           {
              ypos++;
           }
           if (xAxis > 650)
           {
              xpos++;
           }
           if (yAxis < 450)
           {
              ypos--;
           }
           if (xAxis < 450)
           {
              xpos--;
           }

           Serial.print(diffx);
           Serial.print("  ");
           Serial.println(diffy);
           if(diffx < 2 && diffy < 2)
           {
              task2Done = true;
              display.clearDisplay();
           }
        }
        

        //==========================third task===========================
        while (!task3Done)
        {
            display.setTextSize(3); 
           display.clearDisplay();
           timer--; 
           display.setCursor(0,25);  
           display.print(timer);
           display.display();
           delay(1);
           
           if (digitalRead(4)  == LOW)
           {
              task3Done = true;
              display.clearDisplay();
              display.setCursor(20,25);  
               display.print("END...");
                 display.display();
                  delay(100000);
           }
           if (timer < 0)
           {
            display.clearDisplay();
              display.print("BOOM"); 
              display.display(); 
              delay(10000000);      
           }
        }
        



        //======fourth task======

        //======fifth task======

        //======sixth task======
        
    }
    else
    {
        display.clearDisplay(); 
        
        display.setTextSize(2); 
        display.setCursor(0,25);
        if (win)
        {
            display.print("YOU WON");        
        }
        else
        {
            display.print("BOOM"); 
        }
        display.display(); //updates the display
        
    }

    if (timer < 0)
    {
        gameRunning = false;   
    }

    // print out the value you read:
    Serial.print(" left Dial:  ");    
    Serial.print(leftDial);
    Serial.print(" right Dial:  ");
    Serial.print(rightDial);
    Serial.print(" x axis:  ");
    Serial.print(xAxis);
    Serial.print(" y Axis ");
    Serial.print(yAxis);

    Serial.println();



    Serial.println(digitalRead(4)); 

    
}
