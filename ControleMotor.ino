void iniciaosmotores()
{
  pinMode(MotorHA_Direcao, OUTPUT);
  pinMode(MotorHA_Passo, OUTPUT);
  pinMode(MotorHA_Sleep, OUTPUT);
  pinMode(MotorHA_Reset, OUTPUT);
  pinMode(MotorHA_M2, OUTPUT);
  pinMode(MotorHA_M1, OUTPUT);
  pinMode(MotorHA_M0, OUTPUT);
  pinMode(MotorHA_Ativa, OUTPUT);
  pinMode(MotorDEC_Direcao, OUTPUT);
  pinMode(MotorDEC_Passo, OUTPUT);
  pinMode(MotorDEC_Sleep, OUTPUT);
  pinMode(MotorDEC_Reset, OUTPUT);
  pinMode(MotorDEC_M2, OUTPUT);
  pinMode(MotorDEC_M1, OUTPUT);
  pinMode(MotorDEC_M0, OUTPUT);
  pinMode(MotorDEC_Ativa, OUTPUT);

  //Aciona os pinos por padrão
  digitalWrite(MotorHA_Direcao, LOW);
  digitalWrite(MotorHA_Passo, LOW);
  digitalWrite(MotorHA_Sleep, HIGH);
  digitalWrite(MotorHA_Reset, HIGH);
  digitalWrite(MotorHA_M2, HIGH);
  digitalWrite(MotorHA_M1, HIGH);
  digitalWrite(MotorHA_M0, HIGH);
  digitalWrite(MotorHA_Ativa, LOW);
  digitalWrite(MotorDEC_Direcao, LOW);
  digitalWrite(MotorDEC_Passo, LOW);
  digitalWrite(MotorDEC_Sleep, HIGH);
  digitalWrite(MotorDEC_Reset, HIGH);
  digitalWrite(MotorDEC_M2, HIGH);
  digitalWrite(MotorDEC_M1, HIGH );
  digitalWrite(MotorDEC_M0, HIGH);
  digitalWrite(MotorDEC_Ativa, LOW);
  //MotorHA.setPinsInverted   (   bool    directionInvert = false,     bool    stepInvert = false,     bool    enableInvert = false )
  MotorHA.setAcceleration(NumPassoHA / 2000);
  MotorHA.setCurrentPosition(0);
  MotorHA.setMaxSpeed(FreqSideralHzHA);
  MotorHA.setSpeed(FreqSideralHzHA);
  MotorDEC.setAcceleration(NumPassoDEC / 2000);
  MotorDEC.setCurrentPosition(0);
  MotorDEC.setMaxSpeed(FreqSideralHzDEC);
  MotorDEC.setSpeed(FreqSideralHzDEC);
}

void CalculaVelocidadeSideral() {
  //dia estrelar em milis 86164098

  FreqSideralHzDEC = ( NumPassoDEC / 86164.098903691);
  FreqSideralHzHA = ( NumPassoDEC / 86164.098903691 );
  //FreqSideralHzHA=55.8;
}

void ParaMotoresHA()
{
  MotorHA.stop();
  MotorHA.setCurrentPosition(MotorHA.currentPosition());
}
void ParaMotoresDEC()
{
  MotorDEC.stop();
  MotorDEC.setCurrentPosition(MotorDEC.currentPosition());

}


void CalcPosicaoPasso()
{
  HAmount = MotorHA.currentPosition();
  DECmount = MotorDEC.currentPosition();
  eixoHAGrausDecimal = ResolucaoeixoHAGrausDecimal * HAmount;
  eixoDECGrausDecimal = ResolucaoeixoDECGrausDecimal * DECmount;
}

void SincronizaMotores()
{
  if (HAmountAlvo < (NumPassoHA / 2)) //RTA para alterar o ZERO do HA
  {
    HAmountAlvo = HAmountAlvo + NumPassoHA;
  }
  MotorHA.setCurrentPosition((int)HAmountAlvo);
  MotorDEC.setCurrentPosition((int)DECmountAlvo );
  CalcPosicaoPasso();
}

void SetAlvo()
{
  if  (ManualManual == 0)
  {
    if (HAmountAlvo < (NumPassoHA / 2))  //RTA para alterar o ZERO do HA
    {
      HAmountAlvo = HAmountAlvo + NumPassoHA;
    }
  }
  MotorHA.moveTo(HAmountAlvo);
  MotorDEC.moveTo(DECmountAlvo);
}

void movimentamotores()
{
  MotorDEC.run();
  MotorHA.run();
}

void acompanhamento()
{
  if (Acompanhamento)
  {
    SideralRate = true;
    MotorHA.moveTo(NumPassoHA * 2);
    ledStateB = HIGH;
  }
  else
  {
    SideralRate = false;
    SetAlvo();
    ledStateB = LOW;
  }
  digitalWrite(LedB, ledStateB);
  SetaVelocidadeSideral();
}

void SetaVelocidadeSideral()
{
  if  (ManualManual > 0)
  {
    accel = accelset;
  }
  if (VelocidadeGoto) {
    accel = NumPassoHA;
  }
  if (SideralRate)
  {
    accel = FreqSideralHzDEC;
  }
  if (accel != accelold)
  {
    accelold = accel;
    MotorDEC.setMaxSpeed(accel);
    MotorHA.setMaxSpeed(accel);
    MotorDEC.setSpeed(accel);
    MotorHA.setSpeed(accel);
    paramotorgeral = true;
    delay(50 + MinTimer);
    paramotorgeral = false;
  }
}

void MotorTrocaLado()
{

  if (LESTEAlvo)
  {
    MotorHA.setCurrentPosition(MotorHA.currentPosition() - NumPassoHA / 2);
    MotorDEC.setCurrentPosition((MotorDEC.currentPosition() * (-1)) - NumPassoDEC / 2);
    flipDEC();
  }
  else
  {
    MotorHA.setCurrentPosition(MotorHA.currentPosition() + NumPassoHA / 2);
    MotorDEC.setCurrentPosition((MotorDEC.currentPosition() * (-1)) - NumPassoDEC / 2);
    flipDEC();
  }
}

void flipDEC()
{
  if (MotorHA.currentPosition() < NumPassoHA)
  {
    if (SentidoDEC == 1)
    {
      MotorDEC.setPinsInverted(false);
    }
    else
    {
      MotorDEC.setPinsInverted(true);

    }
  }
  else {
    if (SentidoDEC == 1)
    {
      MotorDEC.setPinsInverted(true);
    }
    else
    {
      MotorDEC.setPinsInverted(false);

    }
  }
}

void SentidodosMotores()
{
  if (SentidoDEC == 1)
  {
    MotorDEC.setPinsInverted(true, false, false);
  }
  else
  {
    MotorDEC.setPinsInverted(false, false, false);

  }
  if (SentidoRA == 1)
  {
    MotorHA.setPinsInverted(true, false, false);

  }
  else
  {
    MotorHA.setPinsInverted(false, false, false);

  }
}


