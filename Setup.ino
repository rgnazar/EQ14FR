void RotinadeSetup() //:HSETUPON#
{
  SerialPrint("\n ######################################################################### \n");
  SerialPrint(" \n Rotina inicial de Setup \n ");
  setupflag = 2;
  CalculaVelocidadeSideral();
  SerialPrint(" \n O valor atual FreqSideralHzHA :  (Varia conforme a reducao)");
  SerialPrint(String(FreqSideralHzHA));
  SerialPrint(" \n O valor atual FreqSideralHzDEC : (Varia conforme a reducao)");
  SerialPrint(String(FreqSideralHzDEC));
  SerialPrint("\n Valor maximo dos motores em X VelocidadeSideral : ");
  SerialPrint(String(MinTimer));
  SerialPrint(" \n (:HST00000# -> Quanto menor maior a velocidade maxima) \n ***QUANDO VALOR E EXAGERADO FIREGOTO TRAVA**** \n");

  SerialPrint(" \n O Sentido do motor RA/Alt e: ");
  if (SentidoRA == 0)
  {
    SerialPrint("Horario \n(:HSSRA0# -> Horario // :HSSRA1# -> AntiHorario)\n");
  }
  else
  {
    SerialPrint("Anti-Horario \n(:HSSRA0# -> Horario // :HSSRA1# -> AntiHorario)\n");
  }


  SerialPrint(" \n O Sentido do motor DEC/AZ e: ");
  if (SentidoDEC == 0)
  {
    SerialPrint("Horario \n (:HSSDEC0# -> Horario // :HSSDEC1# -> AntiHorario)\n");
  }
  else
  {
    SerialPrint("Anti-Horario \n(:HSSDEC0# -> Horario // :HSSDEC1# -> AntiHorario)\n ");
  }

  SerialPrint(" \n Total da Relacao de engrenagens de RA/ALT: ");
  SerialPrint(String(NumPassoHA));
  SerialPrint(" (:HSRA0000000# -> reducao * numero passos * micropasso)\n");
  SerialPrint(" \n Total da Relacao de engrenagens de DEC/AZ: ");
  SerialPrint(String(NumPassoDEC));
  SerialPrint(" (:HSDE0000000# -> reducao * numero passos * micropasso) \n");

  SerialPrint(" \n Para sair :HSETUPOFF# ");


  delay(1000);
  Acompanhamento = false;

  SerialPrint(" \n\n\n Acionamento do motor RA/ALT em velocidade maxima \n ");
  //  VelocidadeSecionadaRA = FreqSideralHzHA * MaxVel;
  //  VelocidadeSecionadaDEC = 0;
  //  SetVelocidade();
  MotorHA.setMaxSpeed(accel);
  MotorDEC.setMaxSpeed(0);

  MotorHA.moveTo(NumPassoHA);
  delay(10000);

  SerialPrint("\n\n \n Acionamento do motor DEC/AZ em velocidade maxima \n ");
  MotorHA.setMaxSpeed(0);
  MotorDEC.setMaxSpeed(accel);

  MotorDEC.moveTo(NumPassoDEC);
  //  VelocidadeSecionadaDEC = FreqSideralHzDEC * MaxVel;
  //  VelocidadeSecionadaRA = 0;
  //  SetVelocidade();
  delay(10000);

  //  VelocidadeSecionadaDEC = 0;
  //  VelocidadeSecionadaRA = 0;
  //  SetVelocidade();
  MotorHA.setMaxSpeed(0);
  MotorDEC.setMaxSpeed(0);
  setupflag = 1;
}
void RotinadeSetupOff()
{
  setupflag = 0;
  ParaMotoresHA();
  ParaMotoresDEC();
}





