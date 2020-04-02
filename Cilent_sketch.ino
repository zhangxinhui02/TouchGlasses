#include <Wire.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <SoftwareSerial.h>

SoftwareSerial ss(8,9); //RX,TX 蓝牙模块通过软串口连接

char Res;
char usart_rxcmd_flag;
char USART_RX_BUF[16];
char usart_rxcmd_cnt;
char usart_rx_timeout;

unsigned char ok_flag;
unsigned char fail_flag;

unsigned short lenth_val = 0;
unsigned char i2c_rx_buf[16];
unsigned char dirsend_flag=0;
int serial_putc( char c, struct __file * )
{
  Serial.write( c );
  return c;
}
void printf_begin(void)
{
  fdevopen( &serial_putc, 0 );
}

ISR(TIMER1_COMPA_vect)
{
   digitalWrite(7, !digitalRead(7)); 
  if(usart_rx_timeout>0)
  {
    usart_rx_timeout--;
    if(usart_rx_timeout==0)
    {
    }
  }
}

void SensorWrite(unsigned char addr,unsigned char* datbuf,unsigned char cnt) 
{
  unsigned short result=0;
  // step 1: instruct sensor to read echoes
  Wire.beginTransmission(82); // transmit to device #82 (0x52)
  // the address specified in the datasheet is 164 (0xa4)
  // but i2c adressing uses the high 7 bits so it's 82
  Wire.write(byte(addr));      // sets distance data address (addr)
  // step 2: wait for address to write
  delay(1);                   // datasheet suggests at least 30uS
  // step 3: send data to sensor
  Wire.write(datbuf, cnt);    // write cnt bytes to slave device
  Wire.endTransmission();      // stop transmitting
}
void SensorRead(unsigned char addr,unsigned char* datbuf,unsigned char cnt) 
{
  unsigned short result=0;
  // step 1: instruct sensor to read echoes
  Wire.beginTransmission(82); // transmit to device #82 (0x52)
  // the address specified in the datasheet is 164 (0xa4)
  // but i2c adressing uses the high 7 bits so it's 82
  Wire.write(byte(addr));      // sets distance data address (addr)
  Wire.endTransmission();      // stop transmitting
  // step 2: wait for readings to happen
  delay(1);                   // datasheet suggests at least 30uS
  // step 3: request reading from sensor
  Wire.requestFrom((int)82, (int)cnt);    // request cnt bytes from slave device #82 (0x52)
  // step 5: receive reading from sensor
  if (cnt <= Wire.available()) { // if two bytes were received
    *datbuf++ = Wire.read();  // receive high byte (overwrites previous reading)
    *datbuf++ = Wire.read(); // receive low byte as lower 8 bits
  }
}
void setup() {
  ss.begin(9600);
  Wire.begin();        // join i2c bus (address optional for master)
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  Serial.begin(9600,SERIAL_8N1); 
  printf_begin();
  printf("start\n\r");
  // 初始化timer1
  cli();          // 进制全局中断
  TCCR1A = 0;     //设置TCCR1A全为0
  TCCR1B = 0;     // [size=1em]设置TCCR1B全为0

  //设置比较的值得大小
  OCR1A = 15;
  // 开启CTC模式
  TCCR1B |= (1 << WGM12);
  // 设置 CS10和CS12位
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);
  // 允许比较中断
  TIMSK1 |= (1 << OCIE1A);
  sei();          // 允许全局中断
  printf("s5-1#");
}
void loop() {
 
    SensorRead(0x00,i2c_rx_buf,2);
    lenth_val=i2c_rx_buf[0];
    lenth_val=lenth_val<<8;
    lenth_val|=i2c_rx_buf[1];
	ss.write(lenth_val);	//将数据通过蓝牙模块发送给树莓派
    delay(100); 
    if(lenth_val>110)
    {
      if(dirsend_flag==0)
      {
        dirsend_flag=1;
        SensorWrite(0x09,&dirsend_flag,1);
        delay(100);
      }
    }
    else if(lenth_val<90)
    {
      if(dirsend_flag==1)
      {
        dirsend_flag=0;
        SensorWrite(0x09,&dirsend_flag,1);
        delay(100);
      }
    }
}
