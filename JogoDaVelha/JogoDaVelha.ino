/*
 *   CÓDIGO:  Q0684
 *   AUTOR:   BrincandoComIdeias
 *   ACOMPANHE: https://www.youtube.com/brincandocomideias ; https://www.instagram.com/canalbrincandocomideias/
 *   APRENDA: https://cursodearduino.net/ ; https://cursoderobotica.net
 *   COMPRE:  https://www.arducore.com.br/
 *   SKETCH:  Verificar identificador  
 *   DATA:    15/09/2021
*/

// INCLUSÃO DE BIBLIOTECAS
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

#include "jorge.h"

// DEFINIÇÕES
#define WHITE          0xFFFF
#define YELLOW         0xFFE0
#define RED            0xF800
#define BLUE           0x001F
#define BLACK          0x0000

#define LIGADO         0x07E0
#define DESLIGADO      0xF800

#define MINPRESSURE 10
#define MAXPRESSURE 1000

/*____CALIBRAR TFT LCD_____*/
#define YP A3
#define XM A2
#define YM 9
#define XP 8

#define TS_LEFT 196
#define TS_RT   897
#define TS_TOP  170
#define TS_BOT  941
/*______FIM DA CALIBRAÇÃO______*/

// INSTANCIANDO OBJETOS
MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); //300 É A SENSITIVIDADE

int X, Y;
long corBot[3] = {DESLIGADO, DESLIGADO, DESLIGADO};

TSPoint waitTouch() {
  TSPoint p;
  do {
    p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
  } while ((p.z < MINPRESSURE ) || (p.z > MAXPRESSURE));
  
  p.x = map(p.x, TS_LEFT, TS_RT, 0, 240);
  p.y = map(p.y, TS_BOT, TS_TOP, 0, 320);
  
  return p;
}

void setup() {
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  
  Serial.print("Identificador do display: ");
  Serial.println(ID, HEX);
  
  tft.begin(ID);
  tft.setRotation(2);

  IntroScreen();
  draw_Buttons(0);
}

void loop() {
  TSPoint p = waitTouch();
  X = p.x; Y = 330 - p.y;
  Serial.print("Touch.y: ");
  Serial.println(Y);

  Serial.print("Touch.x: ");
  Serial.println(X);

  DetectButtons(); // DETECTA OS BOTOES

  delay(300);
}

void IntroScreen() {
  tft.fillScreen(BLACK);

  tft.setCursor (45, 80);
  tft.setTextSize (3);
  tft.setTextColor(WHITE);
  tft.println("JOGO DA VELHA");
  tft.setCursor (55, 110);
  tft.setTextSize (2);
  tft.setTextColor(BLUE);
  tft.println("Projeto de Oficinas");
  delay(3500);
}

void DetectButtons() {
  if (X < 200 && X > 40) {
    if (Y > 168 && Y < 240) { // LOGICA PARA O BOTAO 1
      Serial.println ("Button 1");
      if (corBot[0] == LIGADO) corBot[0] = DESLIGADO;
      else corBot[0] = LIGADO;
      draw_Buttons(1);
      Serial.print("teste: ");
      Serial.println(eduardo());
    }

    if (Y > 100 && Y < 161) { // LOGICA PARA O BOTAO 2
      Serial.println ("Button 2");
      if (corBot[1] == LIGADO) corBot[1] = DESLIGADO;
      else corBot[1] = LIGADO;
      draw_Buttons(2);
    }
  }
}

void draw_Buttons(int type) {
  switch (type) {
    case 1:
      tft.fillRect  (70, 145 , 180, 90, corBot[0]);

      tft.setTextColor(BLACK);
      tft.setTextSize (2);
      tft.setCursor(105, 180);
      tft.println("1 JOGADOR");
      break;

    case 2:
      tft.fillRect  (70, 245, 180, 90, corBot[1]);

      tft.setTextColor(BLACK);
      tft.setTextSize (2);
      tft.setCursor(95, 280);
      tft.println("2 JOGADORES");
      break;

    default:
      tft.fillRect  (70, 145 , 180, 90, corBot[0]);
      tft.fillRect  (70, 245, 180, 90, corBot[1]);

      tft.setTextColor(BLACK);
      tft.setTextSize (2);

      tft.setCursor(105, 180);
      tft.println("1 JOGADOR");

      tft.setCursor(95, 280);
      tft.println("2 JOGADORES");
  }

}
