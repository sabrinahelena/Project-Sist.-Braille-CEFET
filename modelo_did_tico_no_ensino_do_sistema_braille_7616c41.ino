#include <stdio.h>
#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>
#include <stdlib.h> //necessário p/ função rand

LiquidCrystal lcd(13, 12, 3, 5, 2, 4);

#define REDCOLOR 50
#define GREENCOLOR 0
#define BLUECOLOR 255
#define NUMERO_PIXELS 16
#define PIN 7 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMERO_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100; // timing delay in milliseconds
int redColor = 0, greenColor = 0, blueColor = 0, i=0, modoAnterior = 0;
int botao0, botao1, botao2, botao3, botao4, botao5;
bool interrup1, interrup2;
char teclapressionada, teclapressionadaAnterior;
int acertos=0, erros=0, digitos;

int teclado(int digitos);

void setup()
{
  Serial.begin(9600);
  pixels.begin();
  lcd.begin (16,2);
  lcd.print("MODELO DIDATICO"); 
  lcd.setCursor(0,1);
  lcd.print("DO SIST. BRAILLE");
  lcd.setCursor(1,1);

  pinMode (A0, INPUT);
  pinMode (A1, INPUT);
  pinMode (A2, INPUT);
  pinMode (A3, INPUT);
  pinMode (A4, INPUT);
  pinMode (A5, INPUT);
  pinMode(9, INPUT);
  pinMode(8, INPUT);
  
}

void loop()
{
  
  char letraSorteada = ' ';
  interrup1= digitalRead(9);
  interrup2= digitalRead(8);

  if (interrup1 == 0)
  { // Acesso aos modos
    if (interrup2 == 1)
    { // INÍCIO MODO 1
      if (modoAnterior!=1)
      { // para q a descrição do modo apareça só uma vez
        lcd.clear();
        modoAnterior = 1;
        lcd.setCursor(5,0);
        lcd.print("MODO 1:");
        lcd.setCursor(2,1);
        lcd.print("APRENDIZADO");
      }
       
      teclado(digitos);
      
      if (teclapressionada != teclapressionadaAnterior)
      { // só exibe a mensagem tecla pressionada quando o botão apertado
        // é diferente do que apertou, não atualizar sem necessidade
        teclapressionadaAnterior = teclapressionada; // atualiza a tecla anterior para a atual
       	letras(teclapressionada);
        lcd.clear();
 		lcd.setCursor(5,0);
		lcd.print("TECLA");
 		lcd.setCursor(0,1);
 		lcd.print("PRESSIONADA: ");
 		lcd.setCursor(14,1);
 		lcd.write(teclapressionada);
      }

     }// FINAL MODO 1

     else // INÍCIO MODO 2
     {
       if (modoAnterior!=2)
       { // para q a descrição do modo apareça só uma vez
         lcd.clear();
         modoAnterior = 2;
         lcd.setCursor(5,0);
       	 lcd.print("MODO 2:");
       	 lcd.setCursor(2,1);
       	 lcd.print("TREINAMENTO");
       }
       
       teclapressionada = ' '; //teclapressionada vazia (sem pressionar botão)
       letraSorteada=random(65,91); // gera uma letra aleatoria de A a Z
       Serial.println(letraSorteada);       
       letras(letraSorteada);
       
       while ((interrup2 == 0) && (teclapressionada == ' ')) 
       {// enquanto estiver no modo 2 e uma tecla não for pressionada repete a leitura de teclado até o usuário pressionar uma tecla
        
       	teclado(digitos); //leitura do teclado 
       }   
       
       if (teclapressionada == letraSorteada)//se pressionar uma tecla, e ela for = a letrasorteada a pessoa acerta
       {
         lcd.clear();
 		 lcd.setCursor(3,0);
		 lcd.print("PARABENS");
 		 lcd.setCursor(2,1);
 		 lcd.print("VOCE ACERTOU!");
         delay(1000);
		 acertos++;
       }
       else //se for diferente da letrasorteada, o usuário erra
       {
       	 lcd.clear();
 		 lcd.setCursor(4,0);
		 lcd.print("VOCE ERROU");
 		 lcd.setCursor(0,1);
 		 lcd.print("ERA A LETRA: ");
         lcd.setCursor(14,1);
         lcd.write(letraSorteada);
         delay(1000);
         erros++;
       }

       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("ACERTOS: ");
       lcd.setCursor(10,0);
       lcd.print(acertos);
       lcd.setCursor(0,1);
       lcd.print("ERROS: ");
       lcd.setCursor(10,1);
       lcd.print(erros);
     }

  } // FINAL MODO 2
     
  else // Fora dos modos
  {
    lcd.setCursor(0,0);
    lcd.print("MODELO DIDATICO"); 
    lcd.setCursor(0,1);
    lcd.print("DO SIST. BRAILLE");
  }
  
}// FINAL VOID LOOP

int teclado(int digitos)
{
  bool botaoPressionado;

  botao0= analogRead(A0);
  botao1= analogRead(A1);
  botao2= analogRead(A2);
  botao3= analogRead(A3);
  botao4= analogRead(A4);
  botao5= analogRead(A5);

  botaoPressionado = ((botao0 != 789)||(botao1 != 789)||(botao2 != 789)||(botao3 != 789)||(botao4 != 789)||(botao5 !=789));
  // 789 é o valor que um bloco tem quando nenhum botão está pressionado
  if (!botaoPressionado) //caso botão não seja pressionado, retorna teclapressionada
    return(teclapressionada);//se vier pro return, ignora a função abaixo

  //** BLOCO 0 **
  if(botao0>=0 && botao0<=41)
  {
    teclapressionada='Q';
    letras(teclapressionada);   
  }
  else if(botao0>=138 && botao0<=152)
  {
 	teclapressionada='W';
    letras(teclapressionada);
  }
  else if(botao0>=313 && botao0<=346)
  {
    teclapressionada='E';
    letras(teclapressionada);  
  }
  else if(botao0>=480 && botao0<=531)
  {
	teclapressionada='R';
    letras(teclapressionada);
  }
  else if(botao0>=704 && botao0<=747)
  {
    teclapressionada='T';
    letras(teclapressionada);    
  }
  
  //** BLOCO 1 **
  else if(botao1>=0 && botao1<=41)
  {
    teclapressionada='Y';
    letras(teclapressionada);   
  }
  else if(botao1>=138 && botao1<=152)
  {
    teclapressionada='U';
    letras(teclapressionada);   
  }
  else if(botao1>=313 && botao1<=346) 
  {
    teclapressionada='I';
    letras(teclapressionada);    
  }
  else if(botao1>=480 && botao1<=531)
  {
	teclapressionada='O';
    letras(teclapressionada);   
  }
  else if(botao1>=704 && botao1<=747) 
  {
    teclapressionada='P';
    letras(teclapressionada);   
  }
  
  //** BLOCO 2 **  
  else if(botao2>=0 && botao2<=41)
  {
    teclapressionada='A';
    letras(teclapressionada);   
  }
  else if(botao2>=138 && botao2<=152)
  {
 	teclapressionada='S';
    letras(teclapressionada);   
  } 
  else if(botao2>=313 && botao2<=346)
  {
    teclapressionada='D';
    letras(teclapressionada);   
  }
  else if(botao2>=480 && botao2<=531)
  {
	teclapressionada='F';
    letras(teclapressionada);   
  }
  else if(botao2>=704 && botao2<=747)
  {
    teclapressionada='G';
    letras(teclapressionada);   
  }
  
  //** BLOCO 3 **
  else if(botao3>=0 && botao3<=41)
  {
    teclapressionada='H';
    letras(teclapressionada);   
  }
  else if(botao3>=13 && botao3<=152)
  {
 	teclapressionada='J';
    letras(teclapressionada);   
  }
  else if(botao3>=313 && botao3<=346)
  {
    teclapressionada='K';
    letras(teclapressionada);      
  }
  else if(botao3>=480 && botao3<=531)
  {
	teclapressionada='L';
    letras(teclapressionada);   
  }
  else if(botao3>=704 && botao3<=747)
  {
    teclapressionada='Z';
    letras(teclapressionada);   
  }
    
  //** BLOCO 4 **
  else if(botao4>=0 && botao4<=41)
  {
    teclapressionada='X';
    letras(teclapressionada);     
  }
  else if(botao4>=138 && botao4<=152)
  {
 	teclapressionada='C';
    letras(teclapressionada);   
  }
  else if(botao4>=313 && botao4<=346)
  {
    teclapressionada='V';
    letras(teclapressionada);      
  }  
  else if (botao4>=480 && botao4<=531)
  {
	teclapressionada='B';
    letras(teclapressionada);    
  }  
  else if(botao4>=704 && botao4<=747)
  {
    teclapressionada='N';
    letras(teclapressionada);     
  }
  
  //** BLOCO 5 **
  else if(botao5>=0 && botao5<=41)
  {
    teclapressionada='M';
    letras(teclapressionada);   
  }
  
  return(teclapressionada);
}// Fim função teclado

void letras(char tecla)
{
  pixels.clear();
  
  if ((tecla >= 'A' && tecla <= 'H') || (tecla >= 'K' && tecla <= 'R') || (tecla == 'U') || (tecla == 'V') || (tecla >= 'X' && tecla <= 'Z'))
  {
    pixels.setPixelColor(0, pixels.Color(REDCOLOR, GREENCOLOR, BLUECOLOR));
  }
  
  if((tecla == 'B') || (tecla >= 'F'&& tecla <= 'J') || (tecla== 'L') || (tecla>= 'P' && tecla<= 'T') || (tecla== 'V') || (tecla== 'W'))
  {
    pixels.setPixelColor(1, pixels.Color(REDCOLOR, GREENCOLOR, BLUECOLOR));
  }
  
  if((tecla >= 'K' && tecla<= 'V') || (tecla>= 'X' && tecla <= 'Z'))
  {
    pixels.setPixelColor(2, pixels.Color(REDCOLOR, GREENCOLOR, BLUECOLOR));
  }
  
  if((tecla== 'C') || (tecla== 'D') || (tecla== 'F') || (tecla== 'G') || (tecla== 'I') || (tecla== 'J') || (tecla== 'M') || (tecla== 'N') || (tecla== 'P') || (tecla== 'Q') || (tecla== 'S') || (tecla== 'T') || (tecla>= 'W' && tecla<= 'Y'))
  {
    pixels.setPixelColor(7, pixels.Color(REDCOLOR, GREENCOLOR, BLUECOLOR));
  }
  
  if((tecla== 'D') || (tecla== 'E') || (tecla== 'G') || (tecla== 'H') || (tecla== 'J') || (tecla== 'N') || (tecla== 'O') || (tecla== 'Q') || (tecla== 'R') || (tecla== 'T') || (tecla== 'W') || (tecla== 'Y') || (tecla== 'Z'))
  {
    pixels.setPixelColor(6, pixels.Color(REDCOLOR, GREENCOLOR, BLUECOLOR));
  }
  
  if((tecla== 'U') || (tecla== 'V') || (tecla>= 'W' && tecla<= 'Z'))
  {
    pixels.setPixelColor(5, pixels.Color(REDCOLOR, GREENCOLOR, BLUECOLOR));
  }
  
  pixels.show();
} // Fim da função letras