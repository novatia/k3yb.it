
#define DEBUG false

#define COLUMNS 16
#define ROWS 9




#define START_COLUMN_COUNT 0
#define END_COLUMN_COUNT 16

#define A1 15
#define A2 16
#define A3 17
#define A4 18

#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define D8 8


#define ROW_0 A4
#define ROW_1 A3
#define ROW_2 A2
#define ROW_3 A1


#define LED_MUX_1 D6
#define LED_MUX_2 D7
#define LED_OUTPUT D8

#define NANO_MUX_1 D2
#define NANO_MUX_2 D3
#define NANO_MUX_3 D4
#define NANO_MUX_4 D5

#define DEFAULT_DATA 0x00

#define DEFAULT_BUTTON_UP_COUNTER 1

char g_Keys[ROWS][COLUMNS] = { 
                                {'1','2','>' ,'4','5','6' ,'7','8',   '1','0','B','S'   ,'T','E','F','G' },  // 0
                                {'H','I','L' ,'M','N','O' ,'P','Q',   'A','B','C','D'   ,'U','V','0','X' },  // 1
                                {'Y','<','\\','|','?','\'','ì','^',   '3','6','9','#'   ,'£','$','%','&' },  // 2
                                {'/','(',')' ,'=','é','è' ,'{','}',   'Z','*','+',']'   ,'[','ç','°','§' },  // 3
                                {'/','(',')' ,'=','é','è' ,'{','}',   '2','5','8','0'   ,'[','ç','°','§' },  // 4
                                {'/','(',')' ,'=','é','è' ,'{','}',   'Z','*','+',']'   ,'[','ç','°','§' },  // 5
                                {'/','(',')' ,'=','é','è' ,'{','}',   'Z','*','+',']'   ,'[','ç','°','§' },  // 6
                                {'/','(',')' ,'=','é','è' ,'{','}',   'Z','*','+',']'   ,'[','ç','°','§' },  // 7
                                {'/','(',')' ,'=','é','è' ,'{','}',   '1','4','7','*'   ,'[','ç','°','§' }   // 8
                             };
char g_Key = '\0';

bool g_ButtonDown = false;
bool g_ButtonUp = false;
bool g_ButtonPressed = false;

unsigned short g_Column;
unsigned short g_Row;
short g_Data[COLUMNS];
unsigned short g_ButtonUpCounter = DEFAULT_BUTTON_UP_COUNTER;

bool g_Led[5]= {false,false,false,false,false};



void setup()
{
  // put your setup code here, to run once:
  pinMode(NANO_MUX_1,OUTPUT);
  pinMode(NANO_MUX_2,OUTPUT);
  pinMode(NANO_MUX_3,OUTPUT);
  pinMode(NANO_MUX_4,OUTPUT);
  
  pinMode(LED_MUX_1,OUTPUT);
  pinMode(LED_MUX_2,OUTPUT);
  pinMode(LED_OUTPUT,OUTPUT);
  
  pinMode(ROW_0,INPUT_PULLUP);
  pinMode(ROW_1,INPUT_PULLUP);
  pinMode(ROW_2,INPUT_PULLUP);
  pinMode(ROW_3,INPUT_PULLUP);

  Serial.begin(115200);

  g_Column = 0;
  g_Row = 0;
  
  for (int i=0; i<COLUMNS; i++)
    g_Data[i] = DEFAULT_DATA;
}

void writeMux(unsigned short value)
{
      digitalWrite(NANO_MUX_1, value & 0x01);
      digitalWrite(NANO_MUX_2, value & 0x02);
      digitalWrite(NANO_MUX_3, value & 0x04);
      digitalWrite(NANO_MUX_4, value & 0x08);
}

//returns row reading, 0 if nothing is pressed. or and shift row readings
unsigned short readRow()
{
   unsigned short row = DEFAULT_DATA;

   unsigned short row_0 = !digitalRead(ROW_0) << 0;
   unsigned short row_1 = !digitalRead(ROW_1) << 1;
   unsigned short row_2 = !digitalRead(ROW_2) << 2;
   unsigned short row_3 = !digitalRead(ROW_3) << 3;

   if (DEBUG){
     Serial.print("row 0 = ");
     Serial.println(row_0);
     Serial.print("row 1 = ");
     Serial.println(row_1);
     Serial.print("row 2 = ");
     Serial.println(row_2);
     Serial.print("row 3 = ");
     Serial.println(row_3);
   }
   
   row = row_0 | row_1 | row_2 | row_3 ;
   
 
   return row;
}

#define PROPAGATION_DELAY 300 //us 1 = 1000 ns  20ns t

void applyLeds()
{
  if (g_Led[0])
    digitalWrite(LED_OUTPUT, LOW);
  else     
    digitalWrite(LED_OUTPUT, HIGH);

  digitalWrite(LED_MUX_1,LOW);
  digitalWrite(LED_MUX_2,LOW);

  delayMicroseconds(PROPAGATION_DELAY);
  
  if (g_Led[1])
    digitalWrite(LED_OUTPUT,LOW);
  else     
    digitalWrite(LED_OUTPUT,HIGH);

  digitalWrite(LED_MUX_1,HIGH);
  digitalWrite(LED_MUX_2,LOW);  

  delayMicroseconds(PROPAGATION_DELAY);
  
  if (g_Led[2])
    digitalWrite(LED_OUTPUT,LOW);
  else     
    digitalWrite(LED_OUTPUT,HIGH);
 
  digitalWrite(LED_MUX_1,LOW);
  digitalWrite(LED_MUX_2,HIGH);  
  
  delayMicroseconds(PROPAGATION_DELAY);

  if (g_Led[3])
    digitalWrite(LED_OUTPUT,LOW);
  else     
    digitalWrite(LED_OUTPUT,HIGH);
 
  digitalWrite(LED_MUX_1,HIGH);
  digitalWrite(LED_MUX_2,HIGH);
  
  delayMicroseconds(PROPAGATION_DELAY);
 
}

void buttonDown()
{
  Serial.println("DOWN");
  g_ButtonUp = false;
  g_ButtonDown = true;
  g_ButtonPressed = true;
}

void buttonReset(){
  Serial.println("RESET");
  g_ButtonUp = false;
  g_ButtonDown = false;
  g_ButtonPressed = false;
  g_ButtonUpCounter = DEFAULT_BUTTON_UP_COUNTER;
  g_Key = '\0';
}

void buttonUp()
{
  Serial.println("UP");
  g_ButtonUp = true;
  g_ButtonDown = false;
  g_ButtonPressed = true;
}

void buttonPressed()
{
  Serial.print(g_Key);
  Serial.println(" PRESSED");
  g_ButtonDown = true;
  g_ButtonPressed = true;
}

void loop()
{

   unsigned short column = 0;

   g_ButtonPressed = false;
   
   for ( column=START_COLUMN_COUNT; column<END_COLUMN_COUNT; column++ )
   {

      writeMux(column);

      unsigned short row = DEFAULT_DATA;
      row = readRow();

      if (g_ButtonUp)
      {
            g_ButtonUpCounter--;
            if (g_ButtonUpCounter <= 0)
            {
              buttonReset();
            }
      }

        // if readings changed... and not pressed down
      if ( row != g_Data[column] && !g_ButtonDown)
        {
            buttonDown();
           
            g_Column = column;
            g_Row = row;
            g_Data[column] = row;
            g_Key = g_Keys[row][column];
        }
        else
        {
          // if reading is zero but before a button was pressed then up
          if ( row == DEFAULT_DATA && g_Data[column] != DEFAULT_DATA )
          {
            buttonUp();
            g_Data[column] = DEFAULT_DATA;
          }
          else 
          {
            if (g_Data[column] != DEFAULT_DATA)
              //button is still pressed
              buttonPressed();
          }
        }
        
       
        if (DEBUG)
        {
            Serial.print("Column: ");
            Serial.print(column);
            Serial.print(", Row: ");
            Serial.print(row);
            Serial.println();
        }
        
        if (DEBUG)
          delay(1000);






switch (g_Key)
    {
      case '1':
        if (g_ButtonUp)
        {
          g_Led[0] = !g_Led[0];
          g_Led[0] ? Serial.println("LED 0 ON"):  Serial.println("LED 0 OFF");
        }
        break;
      case '2':
        if (g_ButtonUp)
        {
          g_Led[1] = !g_Led[1];
          g_Led[1] ? Serial.println("LED 1 ON"):  Serial.println("LED 1 OFF");
        }
        break;
      case '3':
        if (g_ButtonUp) {
          g_Led[2] = !g_Led[2];
          g_Led[2] ? Serial.println("LED 2 ON"):  Serial.println("LED 2 OFF");
        }
        break;
      case 'A':
        if (g_ButtonUp){
          g_Led[3] = !g_Led[3];
          g_Led[3] ? Serial.println("LED 3 ON"):  Serial.println("LED 3 OFF");
        }
        break;
    };
  
    applyLeds();


   }
}
