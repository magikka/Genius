
#define BTN_R 21
#define BTN_G 14
#define BTN_B 18
#define BTN_Y 22

#define LED_R 25
#define LED_G 4
#define LED_B 27
#define LED_Y 33

#define RODADAS 7
bool deBouncing(bool estado, int pin);
void ChecarBotoes();
void AcenderLeds();
void Perdeu();
void Ganhou();

int rodada;
int vetor_leds[RODADAS];
int vetor_pressionado[RODADAS];
int contador_cliques;
bool flag_btnR = false;
bool flag_btnG = false;
bool flag_btnB = false;
bool flag_btnY = false;
bool flag_inicio;
int led_speed = 500;

void setup()
{
  Serial.begin(115200);
  pinMode(BTN_R, INPUT_PULLUP);
  pinMode(BTN_G, INPUT_PULLUP);
  pinMode(BTN_B, INPUT_PULLUP);
  pinMode(BTN_Y, INPUT_PULLUP);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_Y, OUTPUT);

  for (int i = 0; i < RODADAS; i++)
  {
    vetor_leds[i] = random(0, 4);
    Serial.println(vetor_leds[i]);
  }

  flag_inicio = true;
  rodada = 1;
  contador_cliques = 0;
}

void loop()
{
  //Ganhou();
  if (flag_inicio == true)
  {
    AcenderLeds();
  }
  ChecarBotoes();
  if (contador_cliques == rodada)
  {
    rodada++;
    if (rodada == RODADAS + 1)
    {
      Ganhou();
    }
    contador_cliques = 0;
    flag_inicio = true;
  }

  digitalWrite(LED_R, flag_btnR);
  digitalWrite(LED_G, flag_btnG);
  digitalWrite(LED_B, flag_btnB);
  digitalWrite(LED_Y, flag_btnY);
}

void AcenderLeds()
{
  led_speed -= rodada * 15;

  for (int i = 0; i < rodada; i++)
  {
    delay(led_speed);
    if (vetor_leds[i] == 0)
    {
      digitalWrite(LED_R, HIGH);
    }
    else if (vetor_leds[i] == 1)
    {
      digitalWrite(LED_B, HIGH);
    }
    else if (vetor_leds[i] == 2)
    {
      digitalWrite(LED_G, HIGH);
    }
    else
    {
      digitalWrite(LED_Y, HIGH);
    }

    delay(led_speed);
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_Y, LOW);
    if (i < rodada - 1)
    {
      Serial.println("Fiz um delay");
    }
  }
  flag_inicio = false;
}

void ChecarBotoes()
{
  if (deBouncing(flag_btnB, BTN_B) == false)
  {
    flag_btnB = true;
  }
  if (deBouncing(flag_btnB, BTN_B) == true && flag_btnB == true)
  {
    Serial.println("Soltei o blue");
    vetor_pressionado[contador_cliques] = 1;
    if (vetor_pressionado[contador_cliques] != vetor_leds[contador_cliques])
    {
      Perdeu();
    }
    contador_cliques++;
    flag_btnB = false;
  }
  if (deBouncing(flag_btnR, BTN_R) == false)
  {
    flag_btnR = true;
  }
  if (deBouncing(flag_btnR, BTN_R) == true && flag_btnR == true)
  {
    Serial.println("Soltei do red");
    vetor_pressionado[contador_cliques] = 0;
    if (vetor_pressionado[contador_cliques] != vetor_leds[contador_cliques])
    {
      Perdeu();
    }
    contador_cliques++;
    flag_btnR = false;
  }
  if (deBouncing(flag_btnG, BTN_G) == false)
  {
    flag_btnG = true;
  }
  if (deBouncing(flag_btnG, BTN_G) == true && flag_btnG == true)
  {
    Serial.println("Soltei do green");
    vetor_pressionado[contador_cliques] = 2;
    if (vetor_pressionado[contador_cliques] != vetor_leds[contador_cliques])
    {
      Perdeu();
    }
    contador_cliques++;
    flag_btnG = false;
  }
  if (deBouncing(flag_btnY, BTN_Y) == false)
  {
    flag_btnY = true;
  }
  if (deBouncing(flag_btnY, BTN_Y) == true && flag_btnY == true)
  {
    Serial.println("Soltei do yellow");
    vetor_pressionado[contador_cliques] = 3;
    if (vetor_pressionado[contador_cliques] != vetor_leds[contador_cliques])
    {
      Perdeu();
    }
    contador_cliques++;
    flag_btnY = false;
  }
}

void Perdeu()
{
  Serial.println("PERDEU");

  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_Y, LOW);

  while(true)
  {
    digitalWrite(LED_R, !digitalRead(LED_R));
    delay(150);
  }
}

void Ganhou()
{
  bool leds[4];
  Serial.println("GANHOU...");
  while(true){
    for (int i = 0; i<4; i++)
    {

      leds[i % 4] = true;
      leds[(i % 4) - 1] = true;

      digitalWrite(LED_B, leds[0]);
      delay(30);
      //Zenitsu
      digitalWrite(LED_R, leds[1]);
      delay(30);
      digitalWrite(LED_G, leds[2]);
      delay(30);
      digitalWrite(LED_Y, leds[3]);
      delay(30);
      for (int j = 0; j < 4; j++)
      {
        leds[j] = 0;
      }
    }
    for (int i = 0; i<4; i++)
    {

      leds[i % 4] = true;
      leds[(i % 4) - 1] = true;

      digitalWrite(LED_Y, leds[0]);
      delay(30);
      //Zenitsu
      digitalWrite(LED_G, leds[1]);
      delay(30);
      digitalWrite(LED_R, leds[2]);
      delay(30);
      digitalWrite(LED_B, leds[3]);
      delay(30);
      for (int j = 0; j < 4; j++)
      {
        leds[j] = 0;
      }
    }
  }
}

bool deBouncing(bool flag, int pinBotao)
{
  bool estadoAtual = digitalRead(pinBotao);
  if (estadoAtual != flag)
  {
    delay(7);
    estadoAtual = digitalRead(pinBotao);
  }
  return estadoAtual;
}
