#include <Arduino.h>
#include <math.h>
#include <Time.h>
#include <AccelStepper.h>
#include <DueFlashStorage.h>
#include <DueTimer.h>
//#include <Scheduler.h>
///////////////Variavel sem funcao
int MinTimer;


//DEBUG
int flagDebug = 0;


//Variaveis do SETUP
int setupflag = 0;


/////////////////
//LEDs
#define LedB 49
#define LedR 51
#define LedG 53
int ledStateR = LOW;
int ledStateB = LOW;
int ledStateG = LOW;




//Variaveis de persistencia e estrutura de dados ----------------------------------------------------------------------------------------------------------------
DueFlashStorage dueFlashStorage;
// The struct of the configuration.
struct Configuration {
  int32_t NumPassoHA;
  int32_t NumPassoDEC;
  int32_t SentidoDEC;
  int32_t SentidoRA;
  int32_t MinTimer;
  uint32_t DataHora;
  double latitude;
  double longitude;
  int32_t UTC;
  String Local;
};
Configuration configuration;
Configuration configurationFromFlash; // create a temporary struct



//Relogio de segundofracao
int SegundoOld, Segundo;
double  milesimos, SegundoFracao, SegundoFracaoMillis;


//Variaveis de controle do MOTOR ----------------------------------------------------------------------------------------------------------------
int NumPassoHA, NumPassoDEC, HAmount, DECmount, HAmountAlvo, DECmountAlvo, GotoQualidade, ManualManual = 0, SentidoDEC = 0, SentidoRA = 1;
double ResolucaoeixoHAGrausDecimal, ResolucaoeixoDECGrausDecimal, eixoHAGrausDecimal, eixoDECGrausDecimal, DECAlvo, RAAlvo, HAAlvo, ALTAlvo, AZAlvo;
boolean SideralRate = false, SideralRateold = false, Acompanhamento = false, paramotorgeral = false, LESTEAlvo = true, LESTEMount = true, VelocidadeGoto = true;
//AccelStepper stepper1(AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);
#define MotorHA_Direcao 22
#define MotorHA_Passo 24
#define MotorHA_Sleep 26
#define MotorHA_Reset 28
#define MotorHA_M2 30
#define MotorHA_M1 32
#define MotorHA_M0 34
#define MotorHA_Ativa 36
#define MotorDEC_Direcao 38
#define MotorDEC_Passo 40
#define MotorDEC_Sleep 42
#define MotorDEC_Reset 44
#define MotorDEC_M2 46
#define MotorDEC_M1 48
#define MotorDEC_M0 50
#define MotorDEC_Ativa 52

AccelStepper MotorHA(AccelStepper::DRIVER, MotorHA_Passo, MotorHA_Direcao);
AccelStepper MotorDEC(AccelStepper::DRIVER, MotorDEC_Passo, MotorDEC_Direcao);


double FreqSideralHzDEC = 1, FreqSideralHzHA = 1, accel = NumPassoHA,  accelold = NumPassoHA, accelset=NumPassoHA;
#define PassoMotorDEC 200
#define MicroPassoDEC 32
#define Reducao1DEC 50
#define Reducao2DEC 7.5 //(90 coroa /12 piao)
#define PassoMotorHA 200
#define MicroPassoHA 32
#define Reducao1HA 50
#define Reducao2HA 7.5 //(90 coroa /12 piao)

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
  Serial.begin(9600);
  Serial3.begin(9600);
  SerialUSB.begin(9600);
  //Botão deboucing Pino 11 referencia e 12 leitura
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  NumPassoHA = PassoMotorHA * MicroPassoHA * Reducao1HA * Reducao2HA;
  NumPassoDEC = PassoMotorDEC * MicroPassoDEC * Reducao1DEC * Reducao2DEC;
  /* Flash is erased every time new code is uploaded. Write the default configuration to flash if first time
    // running for the first time?*/
  uint8_t codeRunningForTheFirstTime = dueFlashStorage.read(0); // flash bytes will be 255 at first run
  //Serial.print("Primeira Execucao: ");
  if (codeRunningForTheFirstTime) {
    //  Serial.println("yes");
    /* OK first time running, set defaults */
    configuration.NumPassoHA = NumPassoHA;
    configuration.NumPassoDEC = NumPassoDEC;
    configuration.MinTimer = 180;
    configuration.latitude = -25.40;;
    configuration.longitude = -49.20;
    setTime(0, 00, 00, 23, 03, 2015);
    configuration.SentidoDEC = 0;
    configuration.SentidoRA = 1;
    configuration.DataHora = now();
    configuration.UTC = 0;
    configuration.Local = "MINHA CASA";
    // write configuration struct to flash at adress 4 */
    byte b2[sizeof(Configuration)]; // create byte array to store the struct
    memcpy(b2, &configuration, sizeof(Configuration)); // copy the struct to the byte array
    dueFlashStorage.write(4, b2, sizeof(Configuration)); // write byte array to flash
    // write 0 to address 0 to indicate that it is not the first time running anymore
    dueFlashStorage.write(0, 0);
  }
  else {
    //Serial.println("no");
  }
  byte* b = dueFlashStorage.readAddress(4); // byte array which is read from flash at adress 4
  memcpy(&configurationFromFlash, b, sizeof(Configuration)); // copy byte array to temporary struct
  NumPassoHA = configurationFromFlash.NumPassoHA;
  NumPassoDEC = configurationFromFlash.NumPassoDEC;
  SentidoDEC =  configurationFromFlash.SentidoDEC;
  SentidoRA = configurationFromFlash.SentidoRA;
  MinTimer = configurationFromFlash.MinTimer;
  latitude = configurationFromFlash.latitude;
  longitude = configurationFromFlash.longitude;
  UTC = configurationFromFlash.UTC;
  setTime(configurationFromFlash.DataHora);
  //////Inicia calculos para operACAO DOS MOTORES.
  CalculaVelocidadeSideral();
  ResolucaoeixoHAGrausDecimal = 360.0 / NumPassoHA ;
  ResolucaoeixoDECGrausDecimal = 360.0 / NumPassoDEC ;
  iniciaosleds();
  iniciaosmotores();
  SentidodosMotores();
  ///////Botão de emergencia
  pinMode(12, INPUT); //EMERGENCIA BOTÂO
  GotoQualidadeMillis = 10;
  Timer3.attachInterrupt(loop1);
  Timer3.start(MinTimer);//Calls every 250ms
  delay(10);
  ////////////////////Rotina de definição do lado do pier
  currentMillis = millis();
  CalcPosicaoPasso();//Calcula a posicao da montagem em relacao aos motores
  SegundoFracaoFuncao();
  RAAlvo = Hours2DecDegrees(00, 00, 01);
  DECAlvo = DegMinSec2DecDeg(-89, 59, 59);
  double horadec = Hora2DecHora(hour(), minute(), second()) ;
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
  currentMillis = millis();
  CalcPosicaoPasso();//Calcula a posicao da montagem em relacao aos motores
  SegundoFracaoFuncao();
  if (SerialUSB.available() || Serial.available() || Serial3.available()) serialEvent();
  if ((numCommand != numCommandexec) && (flagCommand == 0))
  {
    cmdComplete = true;
    executecommand();
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
  if (GotoQualidadeMillis < currentMillis)
  {
GotoQualidadeMillis = currentMillis+2500;
    SerialPrintDebug("\n###VELOCIDADE######\n");
    SerialPrintDebug (String( accel)) ;

        SerialPrintDebug("\n###HA Alvo######\n");
    SerialPrintDebug (String( HAmountAlvo)) ;
    SerialPrintDebug("\n###HA Posicao######\n");
     SerialPrintDebug (String( MotorHA.currentPosition())) ;


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
  digitalWrite(LedR, ledStateR);
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


void SegundoFracaoFuncao()
{
  if (currentMillis > SegundoFracaoMillis)
  {
    SegundoFracaoMillis = currentMillis + 6;
    Segundo = second();
    if (SegundoOld == Segundo)
    {
      milesimos =  milesimos + 7;
      if (milesimos > 999)
      {
        milesimos = 999;
      }
      SegundoFracao = milesimos * 0.001;
      SegundoFracao = SegundoFracao + Segundo;
    }
    else
    {
      SegundoFracao = Segundo;
      SegundoOld = Segundo;
      milesimos = 0;
    }
  }
}



/*  HAmountAlvo = 20000;
  DECmountAlvo = 20;
  MotorDEC.moveTo(DECmountAlvo);
  MotorHA.moveTo(HAmountAlvo);
  SideralRate = true;

*/
