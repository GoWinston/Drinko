/*
 * Drink-O 7A
 * December 27, 2008
 */
 
// control the pour times for winning here in 100's of a second
int prize1 = 5000;
int prize2 = 2500;
int prize3 = 0;
int prize4 = random(250,2500);
int prize5 = 5000;

// assign the pins here

//Lighting Control Relays
int lightRed = 13;          
int lightGreen = 10;
int lightBlue = 12;   
int lightYellow = 11;

// Scoring switches
int bucket1=2;
int bucket2=3;
int bucket3=4;
int bucket4=5;
int bucket5=6;

// Drink Dispensor Controls
int drink = 9;  // valve relay
int cup=7;  // cup sensor switch
int cupLight=8;  // LED indicating a cup is present

// Crude but satisfying sound effects
int buzzer=1;


// lets make some game control variables
boolean gameOn = false;
boolean gameClear = false;


// get the pins in setup
void setup()
{
pinMode(lightRed, OUTPUT); 
pinMode(lightGreen, OUTPUT); 
pinMode(lightBlue, OUTPUT); 
pinMode(lightYellow, OUTPUT); 
pinMode(bucket1, INPUT); 
pinMode(bucket2, INPUT); 
pinMode(bucket3, INPUT); 
pinMode(bucket4, INPUT); 
pinMode(bucket5, INPUT); 
pinMode(drink, OUTPUT); 
pinMode(cup, INPUT);
pinMode(cupLight, OUTPUT);
pinMode(buzzer, OUTPUT);
}


// the party starts here
void loop()
{
  if (fullBucket()) 
  {
  lights(4,50);
  gameOn = false;
  }
  else
  {
    gameOn = true;
    do // start of game loop - random lights until the puck lands
    {
      int randomlights = random(1,4);
      lights (randomlights, 250);
      checkCup();
      
      if (fullBucket()) //the puck is in a bucket, lets figure out what to do
      {
        if (landing(bucket5))
        {
          score (bucket5, 5, 50, 30, prize5);  // syntax = bucket#, light mode, delayTime, repeat times, drinkprize
          gameOn=false;
          break;
        }
        else if (landing(bucket4))
        {
          score (bucket4, 6, 50, 15, prize4);
          gameOn=false;
          break;
        }
        else if (landing(bucket3))
        {
          score (bucket3, 7, 500, 1, prize3);
          gameOn=false;
          break;
        }
        else if (landing(bucket2))
        {
          score (bucket2, 6, 50, 15, prize2);
          gameOn=false;
          break;
        }
         if (landing(bucket1))
        {
          score (bucket1, 5, 50, 30, prize1);
          gameOn=false;
          break;
        }
        else
        {
        //if this happens the puck has bounced and we should wait for it to land
        }
      }// no puck in basket, pick new random lights and check again
    } while (gameOn=true); // end of score loop
  }//end of the else statement that starts scoring
}//end of the whole program

boolean fullBucket()
{
  boolean isFull = false;
  if (digitalRead(bucket1) == HIGH || digitalRead(bucket2) == HIGH || digitalRead(bucket3) == HIGH || digitalRead(bucket4) == HIGH || digitalRead(bucket5) == HIGH)
  {
    isFull=true;
  }
  return isFull;
}

boolean landing(int bucket)
{
  boolean gameScore = false;
  if(digitalRead(bucket)==HIGH)
  {
    gameScore = true;  
  }
  return gameScore;
}

void score (int bucket, int lightMode, int delayTime, int repeatLights, int drinkprize)
{
  int i =repeatLights;
  do
  {
    lights(lightMode, delayTime);
    i--;
  }while (i >0);
  drinkomatic(drinkprize);
  lights (11, 50);
  boolean statusEnd= landing(bucket);
  do
  {
    delay(50);          // wait for the bucket to be cleared and restart the game
    statusEnd= landing(bucket);
    lights (4,50);
    checkCup();
  } while (statusEnd==true);
}

void drinkomatic(int pour)
{
  int cupStatus = digitalRead(cup);
  if (cupStatus==HIGH && pour>0)
  {
    do
    {
      digitalWrite(drink, HIGH);
      digitalWrite(buzzer, HIGH);
      int delaytimedrink=lights(1,50);
      int cupStatus = digitalRead(cup);
      if (cupStatus==LOW)
      {
        pour=0;
      }
      pour=pour-delaytimedrink;
    } while (pour > 0);
    digitalWrite(drink, LOW);
    digitalWrite(buzzer, LOW);
  }
  else
  {
    // no drink for you.
  }
}

void checkCup()
{
  int cupStatus = digitalRead(cup);
  if (cupStatus==HIGH)
  {
    digitalWrite(cupLight, HIGH);
  }
  else
  {
    digitalWrite(cupLight, LOW);
  }
}
    

int lights(int mode, int rate)
/*
 * 0 = all off
 * 1 = flash all
 * 2 = chase all
 * 3 = bounce all
 * 4 = red flash
 * 5 = flash all with buzzer
 * 6 = chase all with buzzer
 * 7 = bounce all with buzzer
 * 8 = red flash with buzzer
 * 9 = all on
 * 10 = double flash
 * 11 = around the world - reset sequence
 */
{
  if (mode==1)
  {
    digitalWrite(lightRed, HIGH);
    digitalWrite(lightGreen, HIGH);
    digitalWrite(lightBlue, HIGH);
    digitalWrite(lightYellow, HIGH);
    checkCup();
    delay(rate);         
    digitalWrite(lightRed, LOW);
    digitalWrite(lightGreen, LOW);
    digitalWrite(lightBlue, LOW);
    digitalWrite(lightYellow, LOW);
    checkCup();
    delay(rate);
    return (rate*2);
  }
  else if (mode == 2)
  {
    digitalWrite(lightRed, HIGH);
    delay(rate);
    digitalWrite(lightRed, LOW);
    digitalWrite(lightGreen, HIGH);
    delay(rate);
    digitalWrite(lightGreen, LOW);
    digitalWrite(lightBlue, HIGH);
    delay(rate);
    digitalWrite(lightBlue, LOW);
    digitalWrite(lightYellow, HIGH);
    delay(rate);         
    digitalWrite(lightYellow, LOW);
    return (rate*4);
  }
  else if (mode == 3)
  {
    digitalWrite(lightRed, HIGH);
    checkCup();
    delay(rate);
    digitalWrite(lightRed, LOW);
    digitalWrite(lightGreen, HIGH);
    checkCup();
    delay(rate);
    digitalWrite(lightGreen, LOW);
    digitalWrite(lightBlue, HIGH);
    checkCup();
    delay(rate);
    digitalWrite(lightBlue, LOW);
    digitalWrite(lightYellow, HIGH);
    checkCup();
    delay(rate);         
    digitalWrite(lightYellow, LOW);
    digitalWrite(lightBlue, HIGH);
    checkCup();
    delay(rate);
    digitalWrite(lightBlue, LOW);
    digitalWrite(lightGreen, HIGH);
    checkCup();
    delay(rate);
    digitalWrite(lightGreen, LOW);
    return (rate*6);
  }
  else if (mode == 4)
  {
    digitalWrite(lightRed, HIGH);
    checkCup();
    delay(rate);
    digitalWrite(lightRed, LOW);
    checkCup();
    delay(rate);
    return (rate*2);
  }
  
    if (mode==5) // with buzzer
  {
    digitalWrite(lightRed, HIGH);
    digitalWrite(lightGreen, HIGH);
    digitalWrite(lightBlue, HIGH);
    digitalWrite(lightYellow, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(rate);         
    digitalWrite(lightRed, LOW);
    digitalWrite(lightGreen, LOW);
    digitalWrite(lightBlue, LOW);
    digitalWrite(lightYellow, LOW);
    digitalWrite(buzzer, LOW);
    delay(rate);
    return (rate*2);
  }
  else if (mode == 6) // with buzzer
  {
    digitalWrite(lightRed, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(rate);
    digitalWrite(lightRed, LOW);
    digitalWrite(lightGreen, HIGH);
    digitalWrite(buzzer, LOW);
    delay(rate);
    digitalWrite(buzzer, HIGH);
    digitalWrite(lightGreen, LOW);
    digitalWrite(lightBlue, HIGH);
    delay(rate);
    digitalWrite(buzzer, LOW);
    digitalWrite(lightBlue, LOW);
    digitalWrite(lightYellow, HIGH);
    delay(rate);         
    digitalWrite(lightYellow, LOW);
    return (rate*4);
  }
  else if (mode == 7) // with buzzer
  {
    digitalWrite(lightRed, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(rate);
    digitalWrite(buzzer, LOW);
    digitalWrite(lightRed, LOW);
    digitalWrite(lightGreen, HIGH);
    delay(rate);
    digitalWrite(buzzer, HIGH);
    digitalWrite(lightGreen, LOW);
    digitalWrite(lightBlue, HIGH);
    delay(rate);
    digitalWrite(buzzer, LOW);
    digitalWrite(lightBlue, LOW);
    digitalWrite(lightYellow, HIGH);
    delay(rate);
    digitalWrite(buzzer, HIGH);    
    digitalWrite(lightYellow, LOW);
    digitalWrite(lightBlue, HIGH);
    delay(rate);
    digitalWrite(buzzer, LOW);
    digitalWrite(lightBlue, LOW);
    digitalWrite(lightGreen, HIGH);
    delay(rate);
    digitalWrite(lightGreen, LOW);
    return (rate*6);
  }
  else if (mode == 8) // with buzzer
  {
    digitalWrite(lightRed, HIGH);
    delay(rate);
    digitalWrite(lightRed, LOW);
    delay(rate);
    return (rate*2);
  }
  else if (mode == 9)
  {
    digitalWrite(lightRed, HIGH);
    digitalWrite(lightGreen, HIGH);
    digitalWrite(lightBlue, HIGH);
    digitalWrite(lightYellow, HIGH);
    return rate;
  }
  else if (mode == 10)
  {
    digitalWrite(lightRed, HIGH);
    digitalWrite(lightGreen, LOW);
    digitalWrite(lightBlue, HIGH);
    digitalWrite(lightYellow, LOW);
    delay(rate);         
    digitalWrite(lightRed, LOW);
    digitalWrite(lightGreen, HIGH);
    digitalWrite(lightBlue, LOW);
    digitalWrite(lightYellow, HIGH);
    delay(rate);
    digitalWrite(lightGreen, LOW);
    digitalWrite(lightYellow, LOW); 
    return (rate*2);
  }
  else if (mode == 11)
  {
    int worldDelay = rate;
    do
    {
    digitalWrite(lightRed, HIGH);
    worldDelay = worldDelay+rate;
    delay(worldDelay);
    digitalWrite(lightRed, LOW);
    digitalWrite(lightGreen, HIGH);
    worldDelay = worldDelay+rate;
    delay(worldDelay);
    digitalWrite(lightGreen, LOW);
    digitalWrite(lightBlue, HIGH);
    worldDelay = worldDelay+rate;
    delay(worldDelay);
    digitalWrite(lightBlue, LOW);
    digitalWrite(lightYellow, HIGH);
    worldDelay = worldDelay+rate;
    delay(worldDelay);         
    digitalWrite(lightYellow, LOW);
    } while ( worldDelay < 400);
    digitalWrite(lightRed, LOW);
    digitalWrite(lightGreen, LOW);
    digitalWrite(lightBlue, LOW);
    digitalWrite(lightYellow, LOW);
    
    digitalWrite(buzzer, HIGH);
    delay(rate*2); 
    digitalWrite(buzzer, LOW);
    delay(rate*2); 
    digitalWrite(buzzer, HIGH);
    delay(rate*2); 
    digitalWrite(buzzer, LOW);
    delay(rate*2);
    
    
    return (worldDelay);
  }
  else // no love or lights for you
  {
    digitalWrite(lightRed, LOW);
    digitalWrite(lightGreen, LOW);
    digitalWrite(lightBlue, LOW);
    digitalWrite(lightYellow, LOW);
    return rate;
  }
}// end of lights
