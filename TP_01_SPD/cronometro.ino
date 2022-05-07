
/*
 *	Trabajo Práctico 1: Cronómetro Binario
 *
 *	Al iniciar la simulacion, todos los led deben comenzar apagados.
 *	Cada 1 segundo que transcurra, se deben encender los led
 *	de acuerdo al numero que representan.
 *
 *	Ejemplo:
 *   
 *	El numero 15 (0000001111) se representaria encendiendo los 
 *	leds AMARILLO y NARANJA.
 *	Al pasar al numero 16 (0000010000), se deben apagar todos 
 *	los led anteriores y encenderse uno de los leds VERDES. 
 *	Notese, en el ejemplo los 0 representan los led apagados 
 *	y los 1 los led encendidos). 
 *   
 *	-------------------------------------------------------
 *   
 *	Al presionarse el boton START, debe iniciar el cronometro.
 *	Volver a presionarlo hace que la secuencia se detenga. 
 *  (Como si se hubiese presionado pausa).
 *	Al presionarse el boton RESET, el cronometro
 *	debe reiniciarse y arrancar de 0.
 *
 *	Tip: Modularizar la función que controla el encendido de los 
 *	LEDS y de ser posible, todo el código para evitar repetir lineas lo mas posible.
 *  Usar millis para controlar el tiempo del contador para que el cambio de los 
 *	leds encendidos sea perceptible para el ojo humano y 
 *	documentar cada función creada en el código. 
 *	Un breve comentario que diga que es lo que hace esa función
 *  y de corresponder, que retorna).
*/

//##### Una Ayudita #####
//--- Defines ---//
#define ZERO_TO_HERO 0          //? To start the counter from 0
#define BUTTON_START 2
#define BUTTON_RESET 3
#define FIRST_LED 4             //? First pin of the leds
#define LAST_LED 13             //? Last pin of the leds
#define BASE_MILLI_SECONDS 1000 //? Secods expresed in miliseconds
#define MAX_SECONDS 1023        //! Max amount of secods to show
//--- End Defines ---//

void setup(){
  pinMode(FIRST_LED,OUTPUT);
  for (int led = 5; led<=12; led++)
  {
    pinMode(led, OUTPUT);
  }
  pinMode(LAST_LED,OUTPUT);
  pinMode(BUTTON_START,INPUT);
  pinMode(BUTTON_RESET,INPUT);
  
  	
	Serial.begin(9600);
}

unsigned long millis_before=0;
int number= 0;
short button_start_before=LOW;
short flagPausa=HIGH;
short button_reset_before=LOW;
int flagInitial=0;


void heroic_Flag()
{
  if(flagInitial == 0)
  {
    Serial.print("Inicio del cronometro\n");
    Serial.print("0");
    Serial.print("\t\t0000000000");
    Serial.println("\n ");
    flagInitial = 1;
  }
}
int increaseNumber()
{
  
  unsigned long millis_now = millis();
 
  if(millis_now - millis_before >= BASE_MILLI_SECONDS)
  {
    if(flagPausa==LOW)
    {
      number--;
    }
    if(number<MAX_SECONDS)
    {
      number++;
    }
    else
    {
      number=0;
    }

    millis_before = millis_now;
  }

  return number;
}
  
void decimalToBinary()
{
    Serial.print(number);
  	Serial.print("\t\t");
  	for(int i=LAST_LED; i>=FIRST_LED; i--)
    {
      if(digitalRead(i)==HIGH)
      {
        Serial.print("1");
      }
      else
      {
        Serial.print("0");
      }
    }
  Serial.println("\n");
}

void converter( int number)
{
  if(flagPausa==HIGH)
  {
    for(int i=FIRST_LED; i<=LAST_LED; i++)
    {	
      digitalWrite(i,number%2);
      number=number/2;
    }
  	decimalToBinary();
  }

}
void botonReset()
{
	short button_reset_now = digitalRead(BUTTON_RESET);
	if (button_reset_now == HIGH && button_reset_before == LOW)
	{
		number=-1;
      	Serial.print("\n----RESETEO DEL PROGRAMA----\n");
	}
	button_reset_before = button_reset_now;
}
void botonPausa()
{
	short button_start_now = digitalRead(BUTTON_START);
	if (button_start_now == HIGH && button_start_before == LOW)
	{
		flagPausa= !flagPausa;
      	Serial.print("\n----PAUSA DEL PROGRAMA----\n");
	}

	button_start_before = button_start_now;
}
void Program()
{
  unsigned long millis_now = millis();
  if(millis_now - millis_before >= BASE_MILLI_SECONDS)
  {
     converter(increaseNumber());
   	 millis_before=millis_now;
  }
}
  

void loop()
{
  heroic_Flag();
  Program();     
  botonReset();
  botonPausa();
  delay(7);
}
