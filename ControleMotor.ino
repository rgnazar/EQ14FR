void iniciaosmotores()
{
  pinMode(26, OUTPUT); //DirecaoHA
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT); //EnableHA
  pinMode(29, OUTPUT);
  pinMode(30, OUTPUT); //pulsoHA
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  pinMode(38, OUTPUT); //DirecaoDEC
  pinMode(39, OUTPUT);
  pinMode(40, OUTPUT); //EnableDEC
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT); //pulsoDEC
  pinMode(43, OUTPUT);

  //Aciona os pinos por padrão
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
  digitalWrite(28, LOW);
  digitalWrite(29, LOW);
  digitalWrite(30, LOW);
  digitalWrite(31, LOW);
  digitalWrite(32, LOW);
  digitalWrite(33, LOW);
  digitalWrite(34, LOW);
  digitalWrite(35, LOW);
  digitalWrite(36, LOW);
  digitalWrite(37, LOW);
  digitalWrite(38, LOW);
  digitalWrite(39, LOW);
  digitalWrite(40, LOW);
  digitalWrite(41, LOW);
  digitalWrite(42, LOW);
  digitalWrite(43, LOW);
  //MotorHA.setPinsInverted   (   bool    directionInvert = false,     bool    stepInvert = false,     bool    enableInvert = false )
  MotorHA.setPinsInverted (true, false, false);
  MotorHA.setAcceleration(NumPassoHA / 2000);
  MotorHA.setCurrentPosition(0);
  MotorHA.setMaxSpeed(FreqSideralHzHA);
  MotorHA.setSpeed(FreqSideralHzHA);
  MotorDEC.setPinsInverted (false, false, false);
  MotorDEC.setAcceleration(NumPassoDEC / 2000);
  MotorDEC.setCurrentPosition(0);
  MotorDEC.setMaxSpeed(FreqSideralHzDEC);
  MotorDEC.setSpeed(FreqSideralHzDEC);
}

void CalculaVelocidadeSideral() {
  //dia estrelar em milis 86164098

  FreqSideralHzDEC = 1000 / (86164098.903691 / PassoMotorDEC / MicroPassoDEC / Reducao1DEC / Reducao2DEC);
  FreqSideralHzHA = 1000 / (86164098.903691 / PassoMotorHA / MicroPassoHA / Reducao1HA / Reducao2HA);
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
  if (HAmountAlvo < (NumPassoHA / 2))  //RTA para alterar o ZERO do HA
  {
    HAmountAlvo = HAmountAlvo + NumPassoHA;
  }
  MotorHA.moveTo(HAmountAlvo);
  MotorDEC.moveTo(DECmountAlvo);
}

void movimentamotores()
{

  if (DECmountAlvo == DECmount)
  {
    MotorHA.run();
  } else
  {
    MotorDEC.run();
  }
  if (HAmountAlvo == HAmount)
  {
    MotorDEC.run();
  } else
  {
    MotorHA.run();
  }
}

void acompanhamento()
{
     if (Acompanhamento)
    {
      SideralRate = true;
      MotorHA.moveTo(-999999999999);
      Led3Stado = LOW;    
    }
    else
    {
      SideralRate = false;
      MotorHA.setMaxSpeed(accel);
      MotorDEC.setMaxSpeed(accel);
      Led3Stado = HIGH;
    }
    digitalWrite(Led3Pin, Led3Stado);
}

void SetaVelocidadeSideral()
{
  if (SideralRate != SideralRateold )
  {
    SideralRateold = SideralRate;
    if (SideralRate)
    {
      MotorDEC.setMaxSpeed(FreqSideralHzDEC);
      MotorHA.setMaxSpeed(FreqSideralHzHA);
    }
    else
    {
      MotorHA.setMaxSpeed(accel);
      MotorDEC.setMaxSpeed(accel);
    }
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
    MotorDEC.setPinsInverted (false, false, false);

  }
  else {
    MotorDEC.setPinsInverted (true, false, false);
  }
}

