void iniciaosmotores()
{
  //Iniciar as variaveis do motor de passo
  pinMode(MotorRA_Direcao, OUTPUT);
  pinMode(MotorRA_Passo, OUTPUT);
  pinMode(MotorRA_Sleep, OUTPUT);
  pinMode(MotorRA_Reset, OUTPUT);
  pinMode(MotorRA_M2, OUTPUT);
  pinMode(MotorRA_M1, OUTPUT);
  pinMode(MotorRA_M0, OUTPUT);
  pinMode(MotorRA_Ativa, OUTPUT);
  pinMode(MotorDEC_Direcao, OUTPUT);
  pinMode(MotorDEC_Passo, OUTPUT);
  pinMode(MotorDEC_Sleep, OUTPUT);
  pinMode(MotorDEC_Reset, OUTPUT);
  pinMode(MotorDEC_M2, OUTPUT);
  pinMode(MotorDEC_M1, OUTPUT);
  pinMode(MotorDEC_M0, OUTPUT);
  pinMode(MotorDEC_Ativa, OUTPUT);

  //Aciona os pinos por padrão
  digitalWrite(MotorRA_Direcao, LOW);
  digitalWrite(MotorRA_Passo, LOW);
  digitalWrite(MotorRA_Sleep, HIGH);
  digitalWrite(MotorRA_Reset, HIGH);
  digitalWrite(MotorRA_M2, HIGH);
  digitalWrite(MotorRA_M1, HIGH);
  digitalWrite(MotorRA_M0, HIGH);
  digitalWrite(MotorRA_Ativa, LOW);
  digitalWrite(MotorDEC_Direcao, LOW);
  digitalWrite(MotorDEC_Passo, LOW);
  digitalWrite(MotorDEC_Sleep, HIGH);
  digitalWrite(MotorDEC_Reset, HIGH);
  digitalWrite(MotorDEC_M2, HIGH);
  digitalWrite(MotorDEC_M1, HIGH );
  digitalWrite(MotorDEC_M0, HIGH);
  digitalWrite(MotorDEC_Ativa, LOW);
  
  //MotorRA.setPinsInverted   (   bool    directionInvert = false,     bool    stepInvert = false,     bool    enableInvert = false )
  MotorRA.setPinsInverted (true, false, false);
  MotorRA.setCurrentPosition(0);
  MotorRA.setMaxSpeed(FreqSideralHzHA);
  MotorRA.setSpeed(FreqSideralHzHA);
  MotorDEC.setPinsInverted (false, false, false);
  MotorDEC.setCurrentPosition(0);
  MotorDEC.setMaxSpeed(FreqSideralHzDEC);
  MotorDEC.setSpeed(FreqSideralHzDEC);
}

void CalculaVelocidadeSideral() {
  //dia estrelar em milis 86164098

  FreqSideralHzDEC = 86164.098903691 / MaxPassoDEC;
  FreqSideralHzHA = 86164.098903691 / MaxPassoRA;
  //FreqSideralHzHA=55.8;
}

void ParaMotoresHA()
{
  MotorRA.stop();
  MotorRA.setCurrentPosition(MotorRA.currentPosition());
}
void ParaMotoresDEC()
{
  MotorDEC.stop();
  MotorDEC.setCurrentPosition(MotorDEC.currentPosition());

}


void CalcPosicaoPasso()
{
  RAmount = MotorRA.currentPosition();
  DECmount = MotorDEC.currentPosition();
  eixoHAGrausDecimal = ResolucaoeixoHAGrausDecimal * RAmount;
  eixoDECGrausDecimal = ResolucaoeixoDECGrausDecimal * DECmount;
}

void SincronizaMotores()
{
  if (RAmountAlvo < (MaxPassoRA / 2)) //RTA para alterar o ZERO do HA
  {
    RAmountAlvo = RAmountAlvo + MaxPassoRA;
  }
  MotorRA.setCurrentPosition((int)RAmountAlvo);
  MotorDEC.setCurrentPosition((int)DECmountAlvo );
  CalcPosicaoPasso();
}

void SetAlvo()
{
  if (RAmountAlvo < (MaxPassoRA / 2))  //RTA para alterar o ZERO do HA
  {
    RAmountAlvo = RAmountAlvo + MaxPassoRA;
  }
  MotorRA.moveTo(RAmountAlvo);
  MotorDEC.moveTo(DECmountAlvo);
}

void movimentamotores()
{

  if (DECmountAlvo == DECmount)
  {
    MotorRA.runSpeed();
  } else
  {
    MotorDEC.runSpeed();
  }
  if (RAmountAlvo == RAmount)
  {
    MotorDEC.runSpeed();
  } else
  {
    MotorRA.runSpeed();
  }
}

void acompanhamento()
{
  if (Acompanhamento)
  {
    SideralRate = true;
    MotorRA.moveTo(-9999999);
    ledStateB = LOW;
  }
  else
  {
    SideralRate = false;
    MotorRA.setMaxSpeed(accel);
    MotorDEC.setMaxSpeed(accel);
    ledStateB = HIGH;
  }
  digitalWrite(LedB, ledStateB);
}

void SetaVelocidadeSideral()
{
  if (SideralRate != SideralRateold )
  {
    SideralRateold = SideralRate;
    if (SideralRate)
    {
      MotorDEC.setMaxSpeed(FreqSideralHzDEC);
      MotorRA.setMaxSpeed(FreqSideralHzHA);
    }
    else
    {
      MotorRA.setMaxSpeed(accel);
      MotorDEC.setMaxSpeed(accel);
    }
  }
}

void MotorTrocaLado()
{

  if (LESTEAlvo)
  {
    MotorRA.setCurrentPosition(MotorRA.currentPosition() - MaxPassoRA / 2);
    MotorDEC.setCurrentPosition((MotorDEC.currentPosition() * (-1)) - MaxPassoDEC / 2);
    flipDEC();
  }
  else
  {
    MotorRA.setCurrentPosition(MotorRA.currentPosition() + MaxPassoRA / 2);
    MotorDEC.setCurrentPosition((MotorDEC.currentPosition() * (-1)) - MaxPassoDEC / 2);
    flipDEC();
  }
}

void flipDEC()
{
  if (MotorRA.currentPosition() < MaxPassoRA)
  {
    MotorDEC.setPinsInverted (false, false, false);

  }
  else {
    MotorDEC.setPinsInverted (true, false, false);
  }
}

void SentidodosMotores()
{
  if (SentidoDEC == 1)
  {
    MotorDEC.setPinsInverted(true);
  }
  else
  {
    MotorDEC.setPinsInverted(false);

  }
  if (SentidoRA == 1)
  {
    MotorRA.setPinsInverted(true);

  }
  else
  {
    MotorRA.setPinsInverted(false);

  }


}

