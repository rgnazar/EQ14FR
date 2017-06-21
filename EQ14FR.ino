#include <Arduino.h>
#include <math.h>
#include <Time.h>
#include <AccelStepper.h>
#include <DueFlashStorage.h>
#include <DueTimer.h>
//#include <Scheduler.h>
///////////////Variavel sem funcao
int MinTimer;

/////////////////
int Led1Stado = LOW;
int Led2Stado = LOW;
int Led3Stado = LOW;
int Led4Stado = HIGH;
int Led1Pin = 47;
int Led2Pin = 49;
int Led3Pin = 51;
int Led4Pin = 53;


//Variaveis de persistencia e estrutura de dados ----------------------------------------------------------------------------------------------------------------
DueFlashStorage dueFlashStorage;
// The struct of the configuration.
struct Configuration {
  int32_t NumPassoHA;
  int32_t NumPassoDEC;
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
int NumPassoHA, NumPassoDEC, HAmount, DECmount, HAmountAlvo, DECmountAlvo, GotoQualidade, ManualManual = 0;
double ResolucaoeixoHAGrausDecimal, ResolucaoeixoDECGrausDecimal, eixoHAGrausDecimal, eixoDECGrausDecimal, DECAlvo, RAAlvo, HAAlvo, ALTAlvo, AZAlvo;
boolean SideralRate = false, SideralRateold = false, Acompanhamento = false, paramotorgeral = false, LESTEAlvo = true, LESTEMount = true;
//AccelStepper stepper1(AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);
AccelStepper MotorHA(AccelStepper::DRIVER, 31, 27);
AccelStepper MotorDEC(AccelStepper::DRIVER, 43, 39);

double FreqSideralHzDEC = 1, FreqSideralHzHA = 1, accel = 999999999;
#define PassoMotorDEC 200
#define MicroPassoDEC 64
#define Reducao1DEC 50
#define Reducao2DEC 7.5 //(90 coroa /12 piao)
#define PassoMotorHA 200
#define MicroPassoHA 64
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
double currentMillis, previousMillis, PCommadMillis, GotoQualidadeMillis;

//Variaveis de controle para ler comandos LX200 Serial ----------------------------------------------------------------------------------------------------------------
boolean cmdComplete = false, doispontos = true; // whether the string is complete
char buffercmd[30];
char inputcmd[30];// a string to hold incoming data
int pontBuffer = 0;
int pontCommand = 0;
int numCommand = 0;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
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
  ///////Botão de emergencia
  pinMode(12, INPUT); //EMERGENCIA BOTÂO
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
  currentMillis = millis();
  CalcPosicaoPasso();//Calcula a posicao da montagem em relacao aos motores
  SegundoFracaoFuncao();
  if (PCommadMillis < currentMillis) //execucao do camando inicial caso não haja outro comando em ação
  {
    printRAmount();
    PCommadMillis = PCommadMillis + 1001;
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
    Led4Stado = LOW;
  }
  else
  {
    movimentamotores();
    Led4Stado = HIGH;
  }
  digitalWrite(Led4Pin, Led4Stado);
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

/*  HAmountAlvo = 20000;
  DECmountAlvo = 20;
  MotorDEC.moveTo(DECmountAlvo);
  MotorHA.moveTo(HAmountAlvo);
  SideralRate = true;

 */
