
#define DEBUG false

#define COLUMNS 16
#define ROWS 4

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


#define ROW_0 A4
#define ROW_1 A3
#define ROW_2 A2
#define ROW_3 A1


#define LED_MUX_1 D6
#define LED_MUX_2 D7

#define NANO_MUX_1 D2
#define NANO_MUX_2 D3
#define NANO_MUX_3 D4
#define NANO_MUX_4 D5

bool g_ButtonDown;
bool g_ButtonPressed;
unsigned short g_Column;
unsigned short g_Row;


bool g_Led[5]= {false,false,false,false,false};


void setup() {
  // put your setup code here, to run once:
  pinMode(NANO_MUX_1,OUTPUT);
  pinMode(NANO_MUX_2,OUTPUT);
  pinMode(NANO_MUX_3,OUTPUT);
  pinMode(NANO_MUX_4,OUTPUT);
  
  pinMode(LED_MUX_1,OUTPUT);
  pinMode(LED_MUX_2,OUTPUT);
  
  pinMode(ROW_0,INPUT_PULLUP);
  pinMode(ROW_1,INPUT_PULLUP);
  pinMode(ROW_2,INPUT_PULLUP);
  pinMode(ROW_3,INPUT_PULLUP);

  Serial.begin(115200);

  g_Column = 0;
  g_Row=0;
}



void writeMux(unsigned short value)
{
      digitalWrite(NANO_MUX_1, value & 0x01);
      digitalWrite(NANO_MUX_2, value & 0x02);
      digitalWrite(NANO_MUX_3, value & 0x04);
      digitalWrite(NANO_MUX_4, value & 0x08);
}

#define DEFAULT_ROW 0xFF

unsigned short readRow()
{
   unsigned short row=DEFAULT_ROW;

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



void applyLeds(){
  if (g_Led[0]){
    digitalWrite(LED_MUX_1,LOW);
    digitalWrite(LED_MUX_2,LOW);  
  }

  if (g_Led[1]){
    digitalWrite(LED_MUX_1,HIGH);
    digitalWrite(LED_MUX_2,LOW);  
  }

  if (g_Led[2]){
    digitalWrite(LED_MUX_1,LOW);
    digitalWrite(LED_MUX_2,HIGH);  
  }

  if (g_Led[3]){
    digitalWrite(LED_MUX_1,HIGH);
    digitalWrite(LED_MUX_2,HIGH);  
  }
    
}

void loop() {



    
   unsigned short column = 0;
   g_ButtonPressed = false;
   
   for (column=START_COLUMN_COUNT;column<END_COLUMN_COUNT;column++) {
       unsigned short row=DEFAULT_ROW;

        writeMux(column);
        row = readRow();

        if ( row != g_Row )
        {
            g_ButtonDown = true;
            g_ButtonPressed = true;
            Serial.print("DOWN");
            g_Column = column;
            g_Row = row;
        }
        else
        {
         
          if ( row==0 && g_Row != 0 )
          { 
            Serial.print("UP");
            g_Row = 0;
            g_ButtonDown = false;
            g_ButtonPressed = true;
          }else {
             g_ButtonPressed = true;
          }
          
          //buttons is still pressed
            
        }
        
       
        if (DEBUG)
        {
            Serial.print("Column: ");
            Serial.print(column);
            Serial.print(", Row: ");
            Serial.print(row);
            Serial.println();
        }
        
        
        if (column == 8 && row == 8 )
        {
        
          g_Led[0] = !g_Led[0];
        }

        if (column == 8 && row == 4 )
        {
          g_Led[1] = !g_Led[1];
        }
        
        if (column == 8 && row == 2 )
        {
          g_Led[2] = !g_Led[2];
        }

       if (column == 8 && row == 1 )
        {
          g_Led[3] = !g_Led[3];
        }

        applyLeds();
        
        if (DEBUG)
          delay(1000);
   }
  
}
