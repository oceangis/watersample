//bottle number: 0     1  2  3  4  5  6  7  8  9  10
//command:      reset  1  2  3  4  5  6  7  8  9  10

#include <Servo.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

//software serial
#define RX 13
#define TX 7

//how much serial data we expect before a newline
const unsigned int MAX_INPUT = 50;
static char incoming[24];
static uint8_t index = 0;
static uint8_t value_index = 0;
const int MAX_STRING_LEN = 20;

//create servo object to control a servo
Servo myservo;
int pos = 0;

//控制采水
SoftwareSerial SERIALCMD(RX, TX); // RX, TX  //和pixhawk连接读取信号
int servoPin = 10;

int relayDrainPin = 11;                      //排水阀，用于排除废水
int relayPumpPin = 12;                       //水泵

int relayPin0 = 2;                           //继电器连接到数字3
int relayPin1 = 3;
int relayPin2 = 4;
int relayPin3 = 5;
int relayPin4 = 6;


int relayPin5 = 14;
int relayPin6 = 15;
int relayPin7 = 16;
int relayPin8 = 17;
int relayPin9 = 18;

long sampleTime = 45000;                    //灌装时间 45秒
long cmd, pBottleNum, pSampleDepth;

//************************************************clear eeprom*************************//
void EEPROMClear()
{
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  Serial.println("epprom has been cleared!!");
}

//*******************************************************************************************************************??
void WaterSample(int bottleNum, double depth)
{
  if (EEPROM.read(bottleNum) == 1)
  {
    Serial.println("已经采过水样");
    return;
  }

  //下放采水管
  for (pos = 1500; pos <= 2000; pos += 10)  // goes from 0 degrees to 90 degrees  // in steps of 1 degree
  {
    //myservo.write(pos);
    Serial.println(pos);
    myservo.writeMicroseconds(pos);
    delay(25);
  }
  ///Serial.println("jjjjjjjjjjjjjjjjjjjjjjjjjjjjjj");

  digitalWrite(relayDrainPin, HIGH);   //1.首先打开排水口继电器
  digitalWrite(relayPumpPin, HIGH);    //2.打开水泵继电器
  delay(10000);                        //排废水时间10秒

 // Serial.println("11111111111111ttttttttttttttttt");

  if (bottleNum == 1) //第一个采样瓶
  {
    digitalWrite(relayPin0, HIGH);        //3.首先打开采样管口，再关闭废水排放口
    digitalWrite(relayDrainPin, LOW);     //4.关闭排水口继电器

    delay(sampleTime);                    //灌装30秒

    digitalWrite(relayPumpPin, LOW);     //5.关闭水泵继电器
    digitalWrite(relayPin0, LOW);        //6.关闭采样管口
  }
  else if (bottleNum == 2) //第二个采样瓶
  {
    digitalWrite(relayPin1, HIGH);        //3.首先打开采样管口，再关闭废水排放口
    digitalWrite(relayDrainPin, LOW);     //4.关闭排水口继电器

    delay(sampleTime);                        //灌装30秒

    digitalWrite(relayPumpPin, LOW);     //5.关闭水泵继电器
    digitalWrite(relayPin1, LOW);        //6.关闭采样管口
  }
  else if (bottleNum == 3) //第三个采样瓶
  {


    digitalWrite(relayPin2, HIGH);        //3.首先打开采样管口，再关闭废水排放口
    digitalWrite(relayDrainPin, LOW);     //4.关闭排水口继电器

    delay(sampleTime);                        //灌装30秒

    digitalWrite(relayPumpPin, LOW);     //5.关闭水泵继电器
    digitalWrite(relayPin2, LOW);        //6.关闭采样管口
  }
  else if (bottleNum == 4) //第四个采样瓶
  {
    digitalWrite(relayPin3, HIGH);        //3.首先打开采样管口，再关闭废水排放口
    digitalWrite(relayDrainPin, LOW);     //4.关闭排水口继电器

    delay(sampleTime);                        //灌装30秒

    digitalWrite(relayPumpPin, LOW);     //5.关闭水泵继电器
    digitalWrite(relayPin3, LOW);        //6.关闭采样管口
  }
  else if (bottleNum == 5) //第五个采样瓶
  {
    digitalWrite(relayPin4, HIGH);        //3.首先打开采样管口，再关闭废水排放口
    digitalWrite(relayDrainPin, LOW);     //4.关闭排水口继电器

    delay(sampleTime);                        //灌装30秒

    digitalWrite(relayPumpPin, LOW);     //5.关闭水泵继电器
    digitalWrite(relayPin4, LOW);        //6.关闭采样管口
  }
  else if (bottleNum == 6) //第六个采样瓶
  {
    digitalWrite(relayPin5, HIGH);        //3.首先打开采样管口，再关闭废水排放口
    digitalWrite(relayDrainPin, LOW);     //4.关闭排水口继电器

    delay(sampleTime);                        //灌装30秒

    digitalWrite(relayPumpPin, LOW);     //5.关闭水泵继电器
    digitalWrite(relayPin5, LOW);        //6.关闭采样管口
  }
  else if (bottleNum == 7) //第七个采样瓶
  {
    digitalWrite(relayPin6, HIGH);        //3.首先打开采样管口，再关闭废水排放口
    digitalWrite(relayDrainPin, LOW);     //4.关闭排水口继电器

    delay(sampleTime);                        //灌装30秒

    digitalWrite(relayPumpPin, LOW);     //5.关闭水泵继电器
    digitalWrite(relayPin6, LOW);        //6.关闭采样管口
  }
  else if (bottleNum == 8) //第八个采样瓶
  {
    digitalWrite(relayPin7, HIGH);        //3.首先打开采样管口，再关闭废水排放口
    digitalWrite(relayDrainPin, LOW);     //4.关闭排水口继电器

    delay(sampleTime);                        //灌装30秒

    digitalWrite(relayPumpPin, LOW);     //5.关闭水泵继电器
    digitalWrite(relayPin7, LOW);        //6.关闭采样管口

  }
  else if (bottleNum == 9) //第九个采样瓶
  {
    digitalWrite(relayPin8, HIGH);        //3.首先打开采样管口，再关闭废水排放口
    digitalWrite(relayDrainPin, LOW);     //4.关闭排水口继电器

    delay(sampleTime);                        //灌装30秒

    digitalWrite(relayPumpPin, LOW);     //5.关闭水泵继电器
    digitalWrite(relayPin8, LOW);        //6.关闭采样管口

  }
  else if (bottleNum == 10) //第十个采样瓶  暂时不处理
  {

    digitalWrite(relayPin9, HIGH);        //3.首先打开采样管口，再关闭废水排放口
    digitalWrite(relayDrainPin, LOW);     //4.关闭排水口继电器

    delay(sampleTime);                    //灌装30秒

    digitalWrite(relayPumpPin, LOW);     //5.关闭水泵继电器
    digitalWrite(relayPin9, LOW);        //6.关闭采样管口

  }

  //标示采集成功
  EEPROM.write(bottleNum, 1);

  //收起采水管
  for (pos = 1500; pos >= 700; pos -= 10) // goes from 180 degrees to 0 degrees
  {
    myservo.writeMicroseconds(pos);  // tell servo to go to position in variable 'pos'
    delay(25);                       // waits 15ms for the servo to reach the position
  }
  myservo.writeMicroseconds(1000);
}



// ************************here to process incoming serial data after a terminator received**************************//
void process_data (const char * data)
{
  char *str;
  char *p;
  char index = 0;
  char stringBuffer[MAX_STRING_LEN + 1];

  strncpy(stringBuffer, data, MAX_STRING_LEN);
  for (str = strtok_r(stringBuffer, ",", &p); str; str = strtok_r(NULL, ",", &p))
  {

    if (index == 0) {
      cmd = strtol(str, NULL, 10);
    } else if (index == 1) {
      pBottleNum = strtol(str, NULL, 10);
    } else if (index == 2) {
      pSampleDepth = strtol(str, NULL, 10);
    }

    if (cmd == 2 && index == 2) //1:pwm value 2:water sample
    {
      Serial.println(pBottleNum);
      if (pBottleNum >= 1 && pBottleNum <= 10 && pSampleDepth >= 0 ) {
        Serial.print(pBottleNum);
        Serial.print("//" );
        Serial.println(pSampleDepth);
        //digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)

        //if the bottle num has sampled water
        if (pBottleNum == 0)
        {
          EEPROMClear();   //clear eeprom
        } else {
          WaterSample(pBottleNum, pSampleDepth);
        }
      }
    } else if (cmd == 1 && index == 2)
    {
      //Serial.println(pBottleNum);
    }
    index ++;
  }
}

//***********************************processIncomingByte*************************//
void processIncomingByte (const byte inByte)
{
  static char input_line [MAX_INPUT];
  static unsigned int input_pos = 0;

  switch (inByte)
  {
    case '\n':   // end of text
      input_line [input_pos] = 0;  // terminating null byte
      // terminator reached! process input_line here ...
      process_data (input_line);
      // reset buffer for next time
      input_pos = 0;
      break;
    case '\r':   // discard carriage return
      break;
    default:
      // keep adding if not full ... allow for terminating null byte
      if (input_pos < (MAX_INPUT - 1))
        input_line [input_pos++] = inByte;
      break;
  }
}






//***************************************set up*************************//
void setup() {
  pinMode(relayPin0, OUTPUT);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);
  pinMode(relayPin5, OUTPUT);
  pinMode(relayPin6, OUTPUT);
  pinMode(relayPin7, OUTPUT);
  pinMode(relayPin8, OUTPUT);
  pinMode(relayPin9, OUTPUT);
  pinMode(relayPumpPin, OUTPUT);  //pump
  pinMode(relayDrainPin, OUTPUT);

  digitalWrite(relayPin0, LOW);       // 设置电磁阀继电器的初始状态
  digitalWrite(relayPin1, LOW);       // 设置电磁阀继电器的初始状态
  digitalWrite(relayPin2, LOW);       // 设置电磁阀继电器的初始状态
  digitalWrite(relayPin3, LOW);       // 设置电磁阀继电器的初始状态
  digitalWrite(relayPin4, LOW);       // 设置电磁阀继电器的初始状态
  digitalWrite(relayPin5, LOW);       // 设置电磁阀继电器的初始状态
  digitalWrite(relayPin6, LOW);       // 设置电磁阀继电器的初始状态
  digitalWrite(relayPin7, LOW);       // 设置电磁阀继电器的初始状态
  digitalWrite(relayPin8, LOW);       // 设置电磁阀继电器的初始状态
  digitalWrite(relayPin9, LOW);       // 设置电磁阀继电器的初始状态
  digitalWrite(relayPumpPin, LOW);    // 设置水泵继电器的初始状态
  digitalWrite(relayDrainPin, LOW);   // 设置水泵继电器的初始状态

  Serial.begin(9600);
  SERIALCMD.begin(57600);

  //clear eeprom
  EEPROMClear();

  //servo position

  myservo.attach(servoPin);
  myservo.writeMicroseconds(2000);

  //开启看门狗，并设置溢出时间为两秒
  //wdt_enable(WDTO_2S);
}

//*************************************************main loop*************************//
void loop() {
  // if serial data available, process it
  while (SERIALCMD.available () > 0)
  {
    processIncomingByte(SERIALCMD.read ());
  }
  //wdt_reset(); //喂狗操作，使看门狗定时器复位
}

