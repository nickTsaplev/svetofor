void on(const byte pin)
{
  digitalWrite(pin,HIGH);
}

void off(const byte pin)
{
  digitalWrite(pin,LOW);
}


int btime=3000;
int time1=5000;
int time2=5000;
int time3=5000;
int mtime=1000;
int bltime=1000;

enum lightCommand 
{
  Cgreen,
  Cyellow,
  Cred,
  CgreenAll
};

struct light
{
  byte red;
  byte yellow;
  byte green;
  byte arrow;
  bool blinking;

  
  void powerOff()
  {
    off(red);
    off(yellow);
    off(green);
    /*if(arrow<14)
      off(arrow);*/
    
  }

  
  void set(enum lightCommand p1,bool arrow=0)
  {
    powerOff();
    switch(p1)
    {
      case Cred:
        on(red);
      break;
      case Cyellow:
        on(yellow);
      break;
      case Cgreen:
        on(green);
      break;
      
    }
    if(this->arrow<14)
    {
      if(arrow)
        on(this->arrow);
      else
        off(this->arrow);
    }
  }

  
  
  
};


light sv[]={ {0,1,2,3,false} , {4,5,6,20,false} , {7,8,9,20,false}, };
#define PPG 11
#define PPR 10

void blinkA(int t)
{
  auto t1=millis();
  while(millis()-t1<t/bltime)
  {
    for(light u:sv)
      if(u.blinking)
        u.set(Cyellow);
    delay(bltime);
  
    for(light u:sv)
      if(u.blinking)
        u.powerOff();
  }

  for(light u:sv)
    u.blinking=false;
}


void setup()
{
  for(int i=0;i<12;i++)
    pinMode(i,OUTPUT);
}

void loop()
{
  on(PPR);
  
  sv[0].set(Cgreen,1);
  sv[1].set(Cgreen);
  sv[2].set(Cred);
   
  delay(time1);


  sv[0].blinking=true;
  sv[1].blinking=true;
  
  blinkA(btime);
  
  
  sv[0].set(Cred);
  sv[1].set(Cred);
  
  delay(mtime);
  
  sv[2].set(Cgreen);
  
  
  
  delay(time2);

  sv[2].blinking=true;
  
  blinkA(btime);

  sv[2].set(Cred);


  off(PPR);
  on(PPG);
  delay(time3);
  off(PPG);
}
