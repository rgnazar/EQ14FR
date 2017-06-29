#include <AccelStepper.h>
#include <Arduino.h>
#include <math.h>
#include <Time.h>
#include <TimeLib.h>
#include <DueTimer.h>
#include <DueFlashStorage.h>
//DEBUG
int flagDebug = 1;


//Criacao dos motores


#define MotorRA_Direcao 22
#define MotorRA_Passo 24
#define MotorRA_Sleep 26
#define MotorRA_Reset 28
#define MotorRA_M2 30
#define MotorRA_M1 32
#define MotorRA_M0 34
#define MotorRA_Ativa 36
#define MotorDEC_Direcao 38
#define MotorDEC_Passo 40
#define MotorDEC_Sleep 42
#define MotorDEC_Reset 44
#define MotorDEC_M2 46
#define MotorDEC_M1 48
#define MotorDEC_M0 50
#define MotorDEC_Ativa 52

AccelStepper MotorRA(AccelStepper::DRIVER, MotorRA_Passo, MotorRA_Direcao);
AccelStepper MotorDEC(AccelStepper::DRIVER, MotorDEC_Passo, MotorDEC_Direcao);

//LEDs
#define LedB 53
#define LedR 51
#define LedG 49
int ledStateR = LOW;
int ledStateB = LOW;
int ledStateG = LOW;


/*valores maximo para o passo (Valor ideal 1286400)*/
double dMaxPassoRA = 3844654;  /* valor de resolucao AR = Passo * MicroPasso * reducao  */
double dMaxPassoDEC = 3844654; /* valor de resolucao DEC = Passo * MicroPasso * reducao */
int dMinTimer = 500; /*/passo*/
double dMaxSpeedAlt = 3844654;
double dMaxSpeedAz = 3844654;



//Variaveis de persistencia e estrutura de dados ----------------------------------------------------------------------------------------------------------------
DueFlashStorage dueFlashStorage;

// The struct of the configuration.
struct Configuration {
  int32_t MaxPassoRA;
  int32_t MaxPassoDEC;
  int32_t MinTimer;
  int32_t SentidoDEC;
  int32_t SentidoRA;
  uint32_t DataHora;
  double latitude;
  double longitude;
  int32_t UTC;
  char* Local;
};
Configuration configuration;
Configuration configurationFromFlash; // create a temporary struct

int MaxSpeedAz = dMaxSpeedAz;
int MaxSpeedAlt = dMaxSpeedAlt;
int SentidoDEC = 0;
int SentidoRA = 0;
int MinTimer;


//Relogio de segundofracao
int SegundoOld, Segundo;
double  milesimos, SegundoFracaoMillis;
double Microssegundo = 0 , SegundoFracao = 0.0, MilissegundoSeg = 0.0, MilissegundoI = 0.0;

//Variaveis do SETUP
int setupflag = 0;


//Variaveis de controle do MOTOR ----------------------------------------------------------------------------------------------------------------
int MaxPassoRA, MaxPassoDEC, RAmount, DECmount, RAmountAlvo, DECmountAlvo, GotoQualidade, ManualManual = 0;
double ResolucaoeixoHAGrausDecimal, ResolucaoeixoDECGrausDecimal, eixoHAGrausDecimal, eixoDECGrausDecimal, DECAlvo, RAAlvo, HAAlvo, ALTAlvo, AZAlvo;
boolean SideralRate = false, SideralRateold = false, Acompanhamento = false, paramotorgeral = false, LESTEAlvo = true, LESTEMount = true;

double FreqSideralHzDEC = 1, FreqSideralHzHA = 1, accel = 999999999;

//Botão deboucing Pino 11 referencia e 12 leitura
int buttonState = 0;
int lastButtonState = LOW;
long lastDebounceTime = 0;
long debounceDelay = 500;

//Variaveis de Localizacao ----------------------------------------------------------------------------------------------------------------
double latitude, longitude;
double  UTC;

//Variaveis de controle do milis();
double currentMillis, previousMillis, PrimeiroCommanMillis, GotoQualidadeMillis;

//Variaveis de controle para ler comandos LX200 Serial ----------------------------------------------------------------------------------------------------------------
int numCommand = 0, numCommandexec = 0, flagCommand = 0;
char buffercmd[30];
int pontCommand = 0;
boolean cmdComplete = false, doispontos = true; // whether the string is complete
int pontBuffer = 0;
char Command[15][15];



void setup() {
  pinMode(LedR, OUTPUT);
  pinMode(LedG, OUTPUT);
  pinMode(LedB, OUTPUT);
  digitalWrite(LedR, ledStateR);
  digitalWrite(LedB, ledStateB);
  digitalWrite(LedG, ledStateG);

  if (ledStateR == LOW) {
    ledStateR = HIGH;
  } else {
    // ledStateR = LOW;
  }
  digitalWrite(LedR, ledStateR);

  Serial.begin(9600);
  Serial3.begin(9600);
  SerialUSB.begin(9600);

  ///////Botão de emergencia
  pinMode(12, INPUT); //EMERGENCIA BOTÂO
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);

  MaxPassoRA = PassoMotorRA * MicroPassoRA * Reducao1RA * Reducao2RA;
  MaxPassoDEC = PassoMotorDEC * MicroPassoDEC * Reducao1DEC * Reducao2DEC;

  /* Flash is erased every time new code is uploaded. Write the default configuration to flash if first time */
  // running for the first time?
  uint8_t codeRunningForTheFirstTime = dueFlashStorage.read(0); // flash bytes will be 255 at first run
  Serial.print("Primeira Execucao: ");
  if (codeRunningForTheFirstTime) {
    Serial.println("yes");
    /* OK first time running, set defaults */
    configuration.MaxPassoRA = MaxPassoRA;
    configuration.MaxPassoDEC = MaxPassoDEC;
    configuration.MinTimer = dMinTimer;
    configuration.latitude = -25.40;;
    configuration.longitude = -49.20;
    configuration.SentidoDEC = 0;
    configuration.SentidoRA = 0;
    setTime(22, 00, 00, 23, 03, 2015);
    MilissegundoSeg = second();
    configuration.DataHora = now();
    configuration.UTC = -2;
    strcpy (configuration.Local, "Minha Casa");
    // write configuration struct to flash at adress 4
    byte b2[sizeof(Configuration)]; // create byte array to store the struct
    memcpy(b2, &configuration, sizeof(Configuration)); // copy the struct to the byte array
    dueFlashStorage.write(4, b2, sizeof(Configuration)); // write byte array to flash
    // write 0 to address 0 to indicate that it is not the first time running anymore
    dueFlashStorage.write(0, 0);
  }
  else {
    Serial.println("no");
  }




  byte* b = dueFlashStorage.readAddress(4); // byte array which is read from flash at adress 4
  memcpy(&configurationFromFlash, b, sizeof(Configuration)); // copy byte array to temporary struct
  MaxPassoRA = configurationFromFlash.MaxPassoRA;
  MaxPassoDEC = configurationFromFlash.MaxPassoDEC;
  MinTimer = configurationFromFlash.MinTimer;
  latitude = configurationFromFlash.latitude;
  longitude = configurationFromFlash.longitude;
  UTC = configurationFromFlash.UTC;
  setTime(configurationFromFlash.DataHora);
  //////Inicia calculos para operACAO DOS MOTORES.
  CalculaVelocidadeSideral();
  ResolucaoeixoHAGrausDecimal = 360.0 / MaxPassoRA ;
  ResolucaoeixoDECGrausDecimal = 360.0 / MaxPassoDEC ;
  iniciaosmotores();

  GotoQualidadeMillis = 10;
  Timer3.attachInterrupt(loop1);
  Timer3.start(233);//Calls every 250ms
  delay(10);
  ////////////////////Rotina de definição do lado do pier
  ////////////////////Rotina de definição do lado do pier
  ////////////////////Rotina de definição do lado do pier
  currentMillis = millis();
  CalcPosicaoPasso();//Calcula a posicao da montagem em relacao aos motores
  SegundoFracaoFuncao();
  double horadec = Hora2DecHora(hour(), minute(), SegundoFracao) ;
  double jdia = JulianoDay (year(), month(), day(), horadec) ;
  double HST = HoraSideral(jdia);
  double HSL = HoraSiderallocal(longitude, HST) ;
  Radec2Azalt(HSL, latitude, RAAlvo, DECAlvo, &AZAlvo, &ALTAlvo);
  if (AZAlvo < 180)
  {
    LESTEAlvo = true;
  }
  else
  {
    LESTEAlvo = false;
  }
  if (LESTEAlvo != LESTEMount)
  {
    MotorTrocaLado();
  }
  synctelescopeString();
}

void loop() {
  if (ledStateR == LOW) {
    ledStateR = HIGH;
  } else {
    // ledStateR = LOW;
  }
  currentMillis = millis();
  CalcPosicaoPasso();//Calcula a posicao da montagem em relacao aos motores
  SegundoFracaoFuncao();
  if (SerialUSB.available() || Serial.available() || Serial3.available()) serialEvent();
  if ((numCommand != numCommandexec) && (flagCommand == 0))
  {
    SerialPrintDebug(String(numCommandexec));
    SerialPrintDebug(String(numCommand));
    cmdComplete = true;
    executecommand();
    SerialPrintDebug(String(numCommandexec));
    SerialPrintDebug(String(numCommand));
  }
  if ( setupflag == 0 )
  {
    if (PrimeiroCommanMillis < currentMillis)

    {
      PrintLocalHora();
      SerialPrintDebug(String(Hora2DecHora(hour(), minute(), SegundoFracao), 10)) ;
      PrimeiroCommanMillis = PrimeiroCommanMillis + 1001;
    }
  }
  if ( setupflag == 1 )
  {
    RotinadeSetup();
  }
  AtualizaGoto();
  acompanhamento();
  SetaVelocidadeSideral();
  LeBotao();

}

void loop1 ()
{
  if (paramotorgeral)
  {
    ParaMotoresHA();
    ParaMotoresDEC();
    ledStateR = LOW;
  }
  else
  {
    movimentamotores();
    ledStateR = HIGH;
  }
  digitalWrite(LedB, ledStateR);
}

void LeBotao() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(12);
  if (reading != lastButtonState) {
    lastDebounceTime = currentMillis;
  }

  if ((currentMillis - lastDebounceTime) > debounceDelay) {
    // Serial.println("deboucing");
    ParaMotoresHA();
    ParaMotoresDEC();
    paramotorgeral = true;
  }
}

