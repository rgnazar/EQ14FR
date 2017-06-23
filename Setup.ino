void RotinadeSetup() //:HSETUPON#
{
  SerialPrint("\n ######################################################################### \n");
  if (setupflag == 0)
  {
    SerialPrint(" \n Rotina inicial de Setup \n ");
  digitalWrite(MotorRA_Direcao, LOW);
  digitalWrite(MotorRA_Passo, LOW);
  digitalWrite(MotorRA_Sleep, HIGH);
  digitalWrite(MotorRA_Reset, HIGH);
  digitalWrite(MotorRA_M2, LOW);
  digitalWrite(MotorRA_M1, LOW);
  digitalWrite(MotorRA_M0, LOW);
  digitalWrite(MotorRA_Ativa, LOW);
  digitalWrite(MotorDEC_Direcao, LOW);
  digitalWrite(MotorDEC_Passo, LOW);
  digitalWrite(MotorDEC_Sleep, HIGH);
  digitalWrite(MotorDEC_Reset, HIGH);
  digitalWrite(MotorDEC_M2, LOW);
  digitalWrite(MotorDEC_M1, LOW );
  digitalWrite(MotorDEC_M0, LOW);
  digitalWrite(MotorDEC_Ativa, LOW);
  }
  setupflag = 2;

  SerialPrint(" \n O valor atual timer e: ");
  SerialPrint(String(MinTimer - 200));
  SerialPrint(" (:HST00000# -> Quanto menor mais rapido ate o limite do motor ambos motores) \n");
  delay(1000);

  SerialPrint(" \n O Sentido do motor RA/Alt e: ");
  if (SentidoRA == 0)
  {
    SerialPrint("Horario (:HSSRA0# -> Horario // :HSSRA1# -> AntiHorario)\n");
  }
  else
  {
    SerialPrint("Anti-Horario (:HSSRA0# -> Horario // :HSSRA1# -> AntiHorario)\n");
  }
  delay(1000);

  SerialPrint(" \n Acionamento do motor RA/ALT em velocidade maxima \n ");
  MotorDEC.setSpeed(0);
  MotorRA.setSpeed(MinTimer * MinTimer);
  delay(6000);
  MotorRA.setSpeed(0);


  SerialPrint(" \n O Sentido do motor DEC/AZ e: ");
  if (SentidoDEC == 0)
  {
    SerialPrint("Horario (:HSSDEC0# -> Horario // :HSSDEC1# -> AntiHorario)\n");
  }
  else
  {
    SerialPrint("Anti-Horario (:HSSDEC0# -> Horario // :HSSDEC1# -> AntiHorario)\n ");
  }
  delay(1000);

  SerialPrint(" \n Acionamento do motor DEC/AZ em velocidade maxima \n ");
  MotorRA.setSpeed(0);
  MotorDEC.setSpeed(MinTimer * MinTimer);
  delay(6000);
  MotorDEC.setSpeed(0);

  MotorDEC.setSpeed(0);
  MotorRA.setSpeed(0);
  SerialPrint(" \n Total da Relacao de engrenagens de RA/ALT: ");
  SerialPrint(String(MaxPassoRA));
  SerialPrint(" (:HSAL0000000# -> reducao * numero passos * micropasso)\n");
  SerialPrint(" \n Total da Relacao de engrenagens de DEC/AZ: ");
  SerialPrint(String(MaxPassoDEC));
  SerialPrint(" (:HSAZ0000000# -> reducao * numero passos * micropasso) \n");

  SerialPrint(" \n Para sair :HSETUPOFF# ");
  setupflag = 1;
}

void RotinadeSetupOff() //:HSETUPOFF#
{
  setupflag = 0;
}

