const int trigger1 = 2 ; //Trigger pin of 1st Sesnor
const int echo1 = 3; //Echo pin of 1st Sesnor
const int trigger2 = 4; //Trigger pin of 2nd Sesnor
const int echo2 = 5;//Echo pin of 2nd Sesnor

int mind=30;
int maxd=50;
int minl=15;
int maxl=20;
int minac=10;
int maxac=25;
long time_taken;
int dist,distL,distR;

void setup() {
  Serial.begin(9600);
  pinMode(trigger1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trigger2, OUTPUT);
  pinMode(echo2, INPUT);
}

/*###Function to calculate distance###*/
void calculate_distance(int trigger, int echo)
{
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  time_taken = pulseIn(echo, HIGH);
  dist= time_taken*0.034/2;
  if (dist>maxd)
  dist = 60;
}
void loop() { //infinite loopy
  calculate_distance(trigger1,echo1);
  distL =dist; //get distance of left sensor
  
  calculate_distance(trigger2,echo2);
  distR =dist; //get distance of right sensor
  // for debugging
  Serial.print("L=");
  Serial.println(distL );
  Serial.print("R=");
  Serial.println(distR);
  //Pause Modes -Hold
  if ((distL >mind && distR>mind) && (distL <maxd && distR <maxd)) //Detect both hands
    {Serial.println("Play/Pause"); delay (500);}
    calculate_distance(trigger1,echo1);
    distL =dist;
    calculate_distance(trigger2,echo2);
    
    distR =dist;
    //Serial.println(distL);
    //Serial.println(distR);
    //Control Modes
    //Lock Left - Control Mode
  if (distL>=5 && distL<=35)
  {
    delay(100); //Hand Hold Time
    calculate_distance(trigger1,echo1);
    distL =dist;
  if (distL>=10 && distL<=20)
  {
  Serial.println("Left Locked");
    while(distL<=40)
    {
      calculate_distance(trigger1,echo1);
      distL =dist;
      if (distL<7) //Hand pushed in
        {Serial.println ("Volume_down"); delay (300);}
      if (distL>25) //Hand pulled out
        {Serial.println ("Volume_up"); delay (300);}
     }
   }
  
  }
  //Lock Right - Control Mode
  if (distR>=5 && distR<=35)
  {
  delay(100); //Hand Hold Time
  calculate_distance(trigger2,echo2);
  distR =dist;
  if (distR>=10 && distR<=20)
  {
  Serial.println("Right Locked");
  while(distR<=40)
  {
  calculate_distance(trigger2,echo2);
  distR =dist;
  if (distR<7) //Right hand pushed in
  {Serial.println ("Rewind"); delay (300);}
  if (distR>15) //Right hand pulled out
  {Serial.println ("Forward"); delay (300);}
  }
  }
  }
  delay(200);
}
