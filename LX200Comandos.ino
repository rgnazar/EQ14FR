void executecommand()
{
  flagCommand = 1;
  if (cmdComplete) {
    SerialPrintDebug("\n#####################\n");
    SerialPrintDebug(String((Command[numCommandexec])));
    cmdComplete = false;
    if (ledStateG == LOW)
      ledStateG = HIGH;
    else
      ledStateG = LOW;
    digitalWrite(LedG, ledStateG);
    PrimeiroCommanMillis = currentMillis + 3000;  //adiciona 5000 milis no comoando inicial
    if (Command[numCommandexec][0] == 0x06)
    {
      SerialPrint("#");
      /*
        ACK <0x06> Query of alignment mounting mode.
        Returns:
        A If scope in AltAz Mode
        D If scope is currently engaged by the Autostar Updater Program [Autostar and Autostar II telescopes]
        L If scope in Land Mode
        P If scope in Polar Mode */
    }
    if (Command[numCommandexec][1] == '$') {
      switch (Command[numCommandexec][2]) {
        case 'B':
          switch (Command[numCommandexec][3]) {
            case 'D':
              //setDECbacklash();
              break;
            case 'R':
              //setHAbacklash();
              break;
          }
      }
    }
    if (Command[numCommandexec][1] == 'B') {
      SerialPrint("#");
    }

    if (Command[numCommandexec][1] == 'C') {
      switch (Command[numCommandexec][2]) {
        case 'S':
          synctelescope();
          break;
        case 'M':
          synctelescopeString();
          break;
      }
    }
    if (Command[numCommandexec][1] == 'D') {
      switch (Command[numCommandexec][2]) {
        case '#':
          CaracterControle();
          break;
      }
    }
    if (Command[numCommandexec][1] == 'G') {
      switch (Command[numCommandexec][2]) {
        case 'A':
          //printALTmount();
          break;
        case 'c':
          F12ou24Hour();
          break;
        case 'C':
          printDataLocal();
          break;
        case 'D':
          printDECmount();
          break;
        case 'g':
          //printlongitude();
          break;
        case 'G':
          printUTC();
          break;
        case 'h':
          //printAlturaLimite();
          break;
        case 'L':
          PrintLocalHora();
          break;
        case 'M':
          printObservatorioNome();
          break;
        case 'o':
          //printHorizonteLimite();
          break;
        case 'R':
          printRAmount();
          break;
        case 'S':
          printSideralHora();
          break;
        case 't':
          //printlatitude();
          break;
        case 'T':
          printSIderalRate();
          break;
        case 'U':
          printOperatocao();
          break;
        case 'W':
          printalinhamento();
          break;
        case 'Z':
          //printAZmount();
          break;
        case 'V':
          switch (Command[numCommandexec][3]) {
            case 'D':
              printFirmwareDate();
              break;
            case 'F':
              printFirmware();
              break;
            case 'N':
              printFirmwareNumber();
              break;
            case 'P':
              printFirmwareNamne();
              break;
            case 'T':
              printFirmwareTime();
              break;
          }
          break;
      }
    }

    if (Command[numCommandexec][1] == 'H') //set Hardware
    {
      switch (Command[numCommandexec][2]) {
        case 'S':
          if (Command[numCommandexec][3] == 'd')//:HSd# Off DEBUG
          {
            flagDebug = 0;
          }
          if (Command[numCommandexec][3] == 'D')//:HSD#  On DEBUG
          {
            flagDebug = 1;
          }
          if (Command[numCommandexec][4] == 'A') //:HSRA0000000#
          {
            setMaxPassoRA();
          }
          if (Command[numCommandexec][4] == 'E') //:HSDE0000000#
          {
            setMaxPassoDEC();
          }
          if (Command[numCommandexec][4] == 'L') //:HSAL0000000#
          {
            setMaxPassoRA();
          }
          if (Command[numCommandexec][4] == 'Z') //:HSAZ0000000#
          {
            setMaxPassoDEC();
          }
          if (Command[numCommandexec][3] == 'T') //:HST0000000#
          {
            setMaxVel();
          }
          if (Command[numCommandexec][8] == 'N') //:HSETUPON#
          {
            RotinadeSetup();
          }
          if (Command[numCommandexec][8] == 'F') //:HSETUPOFF#
          {
            RotinadeSetupOff();
          }
          if (Command[numCommandexec][5] == 'A') //:HSSRA0#
          {
            setSentidoRA(); //:HSSRA0#
          }
          if (Command[numCommandexec][5] == 'E') //:HSSDEC0#
          {
            setSentidoDEC(); //:HSSDEC0#
          }
          break;

        case 'G':
          if (Command[numCommandexec][4] == 'A')//:HGRA#
          {
            //getMaxPassoAlt();
          }
          if (Command[numCommandexec][4] == 'B')//:HGRB#
          {
            //getMaxPassoAz();//:HGRB#
          }
          if (Command[numCommandexec][3] == 'T')//:HGT#
          {
            //getMinTimer(); //:HGT#
          }
          break;
      }
    }

    if (Command[numCommandexec][1] == 'M') {
      switch (Command[numCommandexec][2]) {
        case 'S':
          gototeleEQAR();
          break;
        case 'M':
          synctelescopeString();
          break;
        case 's':
          movesul();
          break;
        case 'w':
          moveoeste();
          break;
        case 'n':
          movenorte();
          break;
        case 'e':
          moveleste();
          break;

      }
      if (ManualManual == 0)
      {
        Acompanhamento = true;
      }
      else
      {
        Acompanhamento = false;
      }
    }
    /* Set rate to Guide   :RG#  Reply: [none]
      Set rate to Centering   :RC#  Reply: [none]
      Set rate to Move  :RM#  Reply: [none]
      Set rate to Slew  :RS#  Reply: [none]
      Set rate to n (1-9)*3 :Rn#  Reply: [none]   */
    if (Command[numCommandexec][1] == 'R') {
      MoveRate();
    }

    if (Command[numCommandexec][1] == 'S') {
      switch (Command[numCommandexec][2]) {
        case 'C':
          setLocalData();
          break;
        case 'd':
          setDECAlvo();
          break;
        case 'G':
          setHoraparaUTC();
          break;
        case 'g':
          setlongitude();
          break;
        case 'h':
          //setAlturaLimite();
          break;
        case 'L':
          setLocalHora();
          break;
        case 'M':
          //setObservatorioNome(); // Set site 0 name   :SMsss...#
          break;
        case 'o':
          //setHorizonteLimite();
          break;
        case 'r':
          setRAAlvo();
          break;
        case 't':
          setlatitude();
          break;
        case 'T':
          //Setsidereal();
          break;
        case 'w':
          //setBufferGps();
          break;
      }
      /*
        :U# Toggle between low/hi precision positions
        Low - RA displays and messages HH:MM.T sDD*MM
        High - Dec/Az/El displays and messages HH:MM:SS sDD*MM:SS
        Returns Nothing */
    }
    if (Command[numCommandexec][1] == 'U') {
      //SerialPrint("00:00:00#");
    }

    if (Command[numCommandexec][1] == 'Q') {
      switch (Command[numCommandexec][2]) {
        case 's':
          parasul();
          break;
        case 'w':
          paraoeste();
          break;
        case 'n':
          paranorte();
          break;
        case 'e':
          paraleste();
          break;
        case '#':
          Stoptelescope();
          break;
          if (ManualManual == 0)
          {
            Acompanhamento = true;
          }
          else
          {
            Acompanhamento = false;
          }
      }
    }




    ///////////////////////////////////Finalizacao do comando
    delay(1);
  } else
  {}
  for (int j = 0; j < 15; j++) {
    Command[numCommandexec][j] = ' ';
  }
  //Passa para o proximo
  numCommandexec = numCommandexec  + 1;
  if (numCommandexec > 14 )
  {
    numCommandexec = 0;
  }

  flagCommand = 0;
  delay(1);
}



////////////////////Controle
void CaracterControle()//:Resposta :D#
{
  SerialPrint("#");
}

void F12ou24Hour()//:Resposta :Gc#
{
  SerialPrint("24#");
}

void printObservatorioNome() //Get site 0 name   :GM#  Reply: sss...#
{
  SerialPrint("Observatory Space#");
}

void printSIderalRate() {//:GT#
  SerialPrint("60.0000#");
}

void printSideralHora()  //:GS#
{
  double horadec = Hora2DecHora(hour(), minute(), second()) ;
  //Serial.println(horadec,10);
  double jdia = JulianoDay (year(), month(), day(), horadec) ;
  //Serial.println((jdia+2451545.0),10);
  double HST = HoraSideral(jdia);
  while (HST > 24.0) {
    HST = HST - 24.0;
  }
  char str[10];
  sprintf(str, "%02d:%02d:%02d#", int(DecHour2HoursHH(HST)), int(DecHour2HoursMM(HST)), int(DecHour2HoursSEC(HST)));
  SerialPrint(str);
}

void printUTC() //:GG# Get UTC offset time Returns: sHH# or sHH.H#
{
  char str[3];
  int tmp = abs(UTC);
  if (UTC < 0) {
    sprintf(str, "-%02d#", int(tmp));
  } else {
    sprintf(str, "+%02d#", int(tmp));
  }
  SerialPrint(str);

}


/////////////////////Funcoes GET

void printDataLocal() //Get date   :GC#   Reply: MM/DD/YY#
{
  int dia = day();
  int mes = month();
  int ano = (year() - 2000);
  char str[10];
  sprintf(str, "%02d/%02d/%02d#", int(mes), int(dia), int(ano));
  SerialPrint(str);

}

void PrintLocalHora()//:Get time (Local)   :GLHH:MM:SS#  Reply: HH:MM:SS#
{
  int hhl = int(hour());
  if (hhl > 23)
  {
    hhl = hhl - 24;
  }
  if (hhl < 0)
  {
    hhl = hhl + 24;
  }
  char str[10];
  sprintf(str, "%02d:%02d:%02d#", hhl, int(minute()), int(second()));
  SerialPrint(str);
}


void printRAmount() //:GR# Get Telescope RA Returns: HH:MM.T# or HH:MM:SS#
{
  double horadec = Hora2DecHora(hour(), minute(), second()) ;
  double jdia = JulianoDay (year(), month(), day(), horadec) ;
  double HST = HoraSideral(jdia);
  double HSL = HoraSiderallocal(longitude, HST) ;
  CalcPosicaoPasso();
  double RA = HAtoRA(HSL, eixoHAGrausDecimal);
  int HH = DecDeg2HoursHH(RA);
  int MM = DecDeg2HoursMM(RA);
  int SS = DecDeg2HoursSEC(RA);
  char str[9];
  sprintf(str, "%02d:%02d:%02d#", int(HH), int(MM), int(SS));
  SerialPrint(str);
}

void printDECmount() //:GD# Get Telescope Declination. Returns: sDD*MM# or sDD*MM'SS#
{ /*double tmpeixoDECGrausDecimal = eixoDECGrausDecimal;  //tmpeixoDECGrausDecimal correção do flip
    while (tmpeixoDECGrausDecimal < -180.0)
    tmpeixoDECGrausDecimal = tmpeixoDECGrausDecimal + 180.0;
    while (tmpeixoDECGrausDecimal > 180.0)
    tmpeixoDECGrausDecimal = tmpeixoDECGrausDecimal - 180.0;*/

  int Ddeg = abs((int)DecDegtoDeg(eixoDECGrausDecimal));
  int Min = abs((int)DecDegtoMin(eixoDECGrausDecimal));
  int Sec = abs((int)DecDegtoSec(eixoDECGrausDecimal));
  char str[9];
  if (eixoDECGrausDecimal < 0) {
    sprintf(str, "-%02d*%02d:%02d#", int(Ddeg), int(Min), int(Sec));
  } else {
    sprintf(str, "+%02d*%02d:%02d#", int(Ddeg), int(Min), int(Sec));
  }
  SerialPrint(str);

}
void printOperatocao()
{
  SerialPrint("N#");
}



void printalinhamento() //:GW# with "AN0#"
{
  SerialPrint("A");
}

void printFirmware() //Get firmware   :GVF#   Reply: "ETX Autostar"
{
  SerialPrint("ETX Autostar|A|43Eg|Apr 03 2007@11:25:53#");
  //SerialPrint("Version 2.0i");
}

void printFirmwareDate()
{
  printDataLocal();
}

void printFirmwareNumber() //Get firmware number   :GVN#   Reply: 0.99a5#
{
  SerialPrint("1.4#");
}

void printFirmwareNamne() //Get firmware name   :GVP#   Reply: On-Step#
{
  SerialPrint("On-Step#");

}

void printFirmwareTime()
{
  PrintLocalHora();

}

/////////////////FUNCOES SET
void setlatitude() //:StsDD*MM# Sets the current site latitude to sDD*MM# Returns: 0 ÃƒÂ¢Ã¢â€šÂ¬Ã¢â‚¬Å“ Invalid 1 - Valid
{

  String str = "";
  str += Command[numCommandexec][4];
  str += Command[numCommandexec][5];
  int DD = str.toInt();
  str = "";
  str += Command[numCommandexec][7];
  str += Command[numCommandexec][8];
  int MM = str.toInt();
  str = "";
  if (Command[numCommandexec][3] == '-')
  {
    DD = DD * (-1);
  }

  latitude = DegMinSec2DecDeg(DD, MM, 0.0);
  configurationFromFlash.latitude = latitude;
  SerialPrint("1");
  byte b2[sizeof(Configuration)]; // create byte array to store the struct
  memcpy(b2, &configurationFromFlash, sizeof(Configuration)); // copy the struct to the byte array
  dueFlashStorage.write(4, b2, sizeof(Configuration)); // write byte array to flash
}

void setlongitude() //:SgsDDD*MM# Set current site's longitude to DDD*MM an ASCII position string Returns:
//NO PROTOCOLO DA MEADE O SINAL E† AO CONTRARIO
{
  String str = "";
  str += Command[numCommandexec][4];
  str += Command[numCommandexec][5];
  str += Command[numCommandexec][6];
  int DD = str.toInt();
  str = "";
  str += Command[numCommandexec][8];
  str += Command[numCommandexec][9];
  int MM = str.toInt();
  str = "";
  if (Command[numCommandexec][3] != '-')
  {
    DD = DD * (-1);
  }
  longitude = DegMinSec2DecDeg(DD, MM, 0.0);
  configurationFromFlash.longitude = longitude;
  SerialPrint("1");
  byte b2[sizeof(Configuration)]; // create byte array to store the struct
  memcpy(b2, &configurationFromFlash, sizeof(Configuration)); // copy the struct to the byte array
  dueFlashStorage.write(4, b2, sizeof(Configuration)); // write byte array to flash
}

void setHoraparaUTC() //:SG-03# :SGsHH.H# Set the number of hours added to local time to yield UTC
{
  String str = "";
  str += Command[numCommandexec][4];
  str += Command[numCommandexec][5];
  UTC = str.toInt();
  if (Command[numCommandexec][3] == '-')
  {
    UTC = UTC * -1;
  }
  SerialPrint("1");
}

void setLocalHora()//:SLHH:MM:SS#  Set the local Time
{
  String str = "";
  str += Command[numCommandexec][3];
  str += Command[numCommandexec][4];
  int HH = str.toInt();
  str = "";
  str += Command[numCommandexec][6];
  str += Command[numCommandexec][7];
  int MM = str.toInt();
  str = "";
  str += Command[numCommandexec][9];
  str += Command[numCommandexec][10];
  int SS = str.toInt();
  str = "";
  int dia = day();
  int mes = month();
  int ano = year();
  setTime(HH, MM, SS, dia, mes, ano);
  int tmp = UTC * 60 * 60;
  adjustTime(tmp);
  SerialPrint("1");
  configurationFromFlash.DataHora =  now();
  byte b2[sizeof(Configuration)]; // create byte array to store the struct
  memcpy(b2, &configurationFromFlash, sizeof(Configuration)); // copy the struct to the byte array
  dueFlashStorage.write(4, b2, sizeof(Configuration)); // write byte array to flash
}

void setLocalData() //:SCMM/DD/YY# Change Handbox Date to MM/DD/YY #:SC 03/20/14#
{
  String str = "";
  str += Command[numCommandexec][3];
  str += Command[numCommandexec][4];
  int mes = str.toInt();
  str = "";
  str += Command[numCommandexec][6];
  str += Command[numCommandexec][7];
  int dia = str.toInt();
  str = "";
  str += Command[numCommandexec][9];
  str += Command[numCommandexec][10];
  int ano = str.toInt();
  str = "";
  ano = ano + 2000;
  int tmp = UTC * 60 * 60;
  adjustTime(-tmp);
  int HH = hour();
  int MM = minute();
  int SS = second();
  setTime(HH, MM, SS, dia, mes, ano);
  adjustTime(tmp);
  SerialPrint("1");
  configurationFromFlash.DataHora =  now();
  byte b2[sizeof(Configuration)]; // create byte array to store the struct
  memcpy(b2, &configurationFromFlash, sizeof(Configuration)); // copy the struct to the byte array
  dueFlashStorage.write(4, b2, sizeof(Configuration)); // write byte array to flash
}

void setRAAlvo() //:Sr03:43:56# Set target RA   :SrHH:MM:SS# *  Reply: 0 or 1#
{
  String str = "";
  str += Command[numCommandexec][3];
  str += Command[numCommandexec][4];
  int HH = str.toInt();
  str = "";
  str += Command[numCommandexec][6];
  str += Command[numCommandexec][7];
  int MM = str.toInt();
  str = "";
  str += Command[numCommandexec][9];
  str += Command[numCommandexec][10];
  int SS = str.toInt();
  str = "";
  RAAlvo = Hours2DecDegrees(HH, MM, SS);
  SerialPrint("1");

}

void setDECAlvo() //Set target Dec  :SdsDD:MM:SS# * Reply: 0 or 1#
{
  String str = "";
  str += Command[numCommandexec][4];
  str += Command[numCommandexec][5];
  int DD = str.toInt();
  str = "";
  str += Command[numCommandexec][7];
  str += Command[numCommandexec][8];
  int MM = str.toInt();
  str = "";
  str += Command[numCommandexec][10];
  str += Command[numCommandexec][11];
  int SS = str.toInt();
  DECAlvo = DegMinSec2DecDeg(DD, MM, SS);
  str = "";
  if (Command[numCommandexec][3] == '-')
  {
    DECAlvo = DECAlvo * (-1);
  }
  SerialPrint("1");
}


/////////////////FUNCOES SINCRONIZACAO e GOTO
void synctelescope() //Sync. with current target RA/Dec  :CS#  Reply: [none]
{
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
  HAAlvo = RAtoHA(HSL, RAAlvo);
  ManualManual = 0;
  HAmountAlvo = int( HAAlvo / ResolucaoeixoHAGrausDecimal);
  DECmountAlvo = int( DECAlvo / ResolucaoeixoDECGrausDecimal);
  SincronizaMotores();
  Acompanhamento = true;
  SetAlvo();
  paramotorgeral = false;
  SerialPrint("0");

}
void synctelescopeString() //:CM# Synchronizes the telescope position with target. Returns static string: " M31 EX GAL MAG 3.5 SZ178.0'#", or "#" if error.
{
  double horadec = Hora2DecHora(hour(), minute(), second()) ;
  double jdia = JulianoDay (year(), month(), day(), horadec) ;
  double HST = HoraSideral(jdia);
  double HSL = HoraSiderallocal(longitude, HST) ;
  Radec2Azalt(HSL, latitude, RAAlvo, DECAlvo, &AZAlvo, &ALTAlvo);
  ////////////////////Rotina de definição do lado do pier
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
  HAAlvo = RAtoHA(HSL, RAAlvo);
  ManualManual = 0;
  HAmountAlvo = int( HAAlvo / ResolucaoeixoHAGrausDecimal);
  DECmountAlvo = int( DECAlvo / ResolucaoeixoDECGrausDecimal);
  SincronizaMotores();
  SetAlvo();
  Acompanhamento = true;
  paramotorgeral = false;
  //SerialPrint("Sincronizado#");
  SerialPrint("0");
}


void gototeleEQAR ()// Move telescope (to current Equ target)  :MS#
{


  ////////////////////Rotina de definição do lado do pier
  double horadec = Hora2DecHora(hour(), minute(), second()) ;
  double jdia = JulianoDay (year(), month(), day(), horadec) ;
  double HST = HoraSideral(jdia);
  double HSL = HoraSiderallocal(longitude, HST) ;
  ////////////////////Rotina de definição do lado do pier
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
  HAAlvo = RAtoHA(HSL, RAAlvo);
  GotoQualidade = 0;
  paramotorgeral = true;
  delay(50);
  paramotorgeral = false;
  Acompanhamento = false;
  ManualManual = 0;
  HAmountAlvo = int( HAAlvo / ResolucaoeixoHAGrausDecimal);
  DECmountAlvo = int( DECAlvo / ResolucaoeixoDECGrausDecimal);
  SetAlvo();
  VelocidadeGoto = true;
  SerialPrint("0");


}
void AtualizaGoto()  //Garante Atualizaçao do AlvoRA durante o delocamento e ativa o acompanhamento depois do alvo atingido
{
  ////////////////////Rotina de definição do lado do pier
  double horadec = Hora2DecHora(hour(), minute(), second()) ;
  double jdia = JulianoDay (year(), month(), day(), horadec) ;
  double HST = HoraSideral(jdia);
  double HSL = HoraSiderallocal(longitude, HST) ;
  double RA = HAtoRA(HSL, eixoHAGrausDecimal);
  double AZ, ALT;
  Radec2Azalt(HSL, latitude, RA, eixoDECGrausDecimal, &AZ, &ALT);
  if (AZ < 180)
  {
    LESTEMount = true;
  }
  else
  {
    LESTEMount = false;
  }
  if ((HAmountAlvo == HAmount) && (DECmountAlvo == DECmount))
  {
    VelocidadeGoto = false;
    Acompanhamento = true;
    GotoQualidade =  1;

  }
  else
  {
    if (GotoQualidade == 0)
    {
      VelocidadeGoto = true;
      // Serial.println("segundo GOTO");
      double horadec = Hora2DecHora(hour(), minute(), second()) ;
      double jdia = JulianoDay (year(), month(), day(), horadec) ;
      double HST = HoraSideral(jdia);
      double HSL = HoraSiderallocal(longitude, HST) ;
      HAAlvo = RAtoHA(HSL, RAAlvo);
      Acompanhamento = false;
      ManualManual = 0;
      int HAmountAlvotmp = int( HAAlvo / ResolucaoeixoHAGrausDecimal);
      int DECmountAlvotmp = int( DECAlvo / ResolucaoeixoDECGrausDecimal);
      int acertaerro = abs(MotorHA.distanceToGo())  + abs(MotorDEC.distanceToGo());
      /*
        Serial.print("acertaerro:  ");
        Serial.println(acertaerro);*/
      if (acertaerro < ((NumPassoHA + NumPassoDEC) / 200))
      {
        // Serial.println(acertaerro);
        HAmountAlvo = HAmountAlvotmp;
        DECmountAlvo = DECmountAlvotmp;
        SetAlvo();
      }
    }
  }
}

///////////////////////////////////Define direcao

void Stoptelescope () // Stop telescope   :Q#   Reply: [none]
{
  ParaMotoresHA();
  ParaMotoresDEC();
  paramotorgeral = true;
  Acompanhamento = false;
}

//Move telescope east (at current rate)   :Me#  Reply: [none]
void moveleste()
{
  HAmountAlvo = (-NumPassoHA*2);
  SetAlvo();
  ManualManual = ManualManual + 1;
}

//Move telescope west (at current rate)   :Mw#  Reply: [none]
void moveoeste()
{
  HAmountAlvo = (NumPassoHA*2);
  SetAlvo();
  ManualManual = ManualManual + 1;
}

//Move telescope north (at current rate)  :Mn#  Reply: [none]
void movenorte()
{
  DECmountAlvo = (-NumPassoDEC*2);
  SetAlvo();
  ManualManual = ManualManual + 1;
}

//Move telescope south (at current rate)  :Ms#  Reply: [none]
void movesul()
{
  DECmountAlvo = (NumPassoDEC*2);
  SetAlvo();
  ManualManual = ManualManual + 1;

}


void paraleste()                                 //:Qe# Reply: [none]
{
  HAmount = MotorHA.currentPosition();
  HAmountAlvo = HAmount;
  SetAlvo();
  ParaMotoresHA();
  ManualManual = ManualManual - 1;

}

//Move telescope west (at current rate)   :Qw#  Reply: [none]
void paraoeste()
{
  HAmount = MotorHA.currentPosition();
  HAmountAlvo = HAmount;
  SetAlvo();
  ParaMotoresHA();
  ManualManual = ManualManual - 1;
}

//Move telescope north (at current rate)  :Qn#  Reply: [none]
void paranorte()
{
  DECmount = MotorDEC.currentPosition();
  DECmountAlvo = DECmount;
  SetAlvo();
  ParaMotoresDEC();
  ManualManual = ManualManual - 1;
}

//Move telescope south (at current rate)  :Qs#  Reply: [none]
void parasul()
{
  DECmount = MotorDEC.currentPosition();
  DECmountAlvo = DECmount;
  SetAlvo();
  ParaMotoresDEC();
  ManualManual = ManualManual - 1;
}


/////////////////////////////////////Define a velocidade
void MoveRate()
{
  switch (Command[numCommandexec][2]) {
    case '0':
      accel = FreqSideralHzHA * 2;
      break;
    case '1':
      accel = FreqSideralHzHA * 4;
      break;
    case '2':
      accel = FreqSideralHzHA * 16;
      break;
    case '3':
      accel = FreqSideralHzHA * 32;
      break;
    case '4':
      accel = FreqSideralHzHA * 64;
      break;
    case '5':
      accel = FreqSideralHzHA * 128;
      break;
    case '6':
      accel = FreqSideralHzHA * 256;
      break;
    case '7':
      accel = FreqSideralHzHA * 512;
      break;
    case '8':
      accel = FreqSideralHzHA * 10240;
      break;

    case 'G':
      accel = FreqSideralHzHA * 2;
      break;
    case 'C':
      accel = FreqSideralHzHA * 4;
      break;
    case 'M':
      accel = FreqSideralHzHA * 64;
      break;
    case 'S':
      accel = FreqSideralHzHA * 10240;
      break;
  }
  accelset = accel;
}

void setSentidoRA() //:HSSRA0#
{
  String str = "";
  str += Command[numCommandexec][6];
  unsigned int RA = str.toInt();
  configurationFromFlash.SentidoRA = RA;
  SentidoRA = configurationFromFlash.SentidoRA;
  byte b2[sizeof(Configuration)]; // create byte array to store the struct
  memcpy(b2, &configurationFromFlash, sizeof(Configuration)); // copy the struct to the byte array
  dueFlashStorage.write(4, b2, sizeof(Configuration)); // write byte array to flash
  SentidodosMotores();
  SerialPrint("1");
}
void setSentidoDEC() //:HSSDEC0#
{
  String str = "";
  str += Command[numCommandexec][7];
  unsigned int Dec = str.toInt();
  configurationFromFlash.SentidoDEC = Dec;
  SentidoDEC = configurationFromFlash.SentidoDEC;
  byte b2[sizeof(Configuration)]; // create byte array to store the struct
  memcpy(b2, &configurationFromFlash, sizeof(Configuration)); // copy the struct to the byte array
  dueFlashStorage.write(4, b2, sizeof(Configuration)); // write byte array to flash
  SentidodosMotores();
  SerialPrint("1");
}

void setMaxPassoRA()  //:HSRA0000000#
{
  String str = "";
  str += Command[numCommandexec][5];
  str += Command[numCommandexec][6];
  str += Command[numCommandexec][7];
  str += Command[numCommandexec][8];
  str += Command[numCommandexec][9];
  str += Command[numCommandexec][10];
  str += Command[numCommandexec][11];
  unsigned int SS = str.toInt();
  configurationFromFlash.NumPassoHA = SS;
  NumPassoHA = configurationFromFlash.NumPassoHA;
  // write configuration struct to flash at adress 4
  byte b2[sizeof(Configuration)]; // create byte array to store the struct
  memcpy(b2, &configurationFromFlash, sizeof(Configuration)); // copy the struct to the byte array
  dueFlashStorage.write(4, b2, sizeof(Configuration)); // write byte array to flash
  CalculaVelocidadeSideral();

  SerialPrint("1");

}

void setMaxPassoDEC() //:HSRB0000000#
{
  String str = "";
  str += Command[numCommandexec][5];
  str += Command[numCommandexec][6];
  str += Command[numCommandexec][7];
  str += Command[numCommandexec][8];
  str += Command[numCommandexec][9];
  str += Command[numCommandexec][10];
  str += Command[numCommandexec][11];
  unsigned int SS = str.toInt();
  configurationFromFlash.NumPassoDEC = SS;
  NumPassoDEC = configurationFromFlash.NumPassoDEC;
  byte b2[sizeof(Configuration)]; // create byte array to store the struct
  memcpy(b2, &configurationFromFlash, sizeof(Configuration)); // copy the struct to the byte array
  dueFlashStorage.write(4, b2, sizeof(Configuration)); // write byte array to flash
  CalculaVelocidadeSideral();

  SerialPrint("1");

}

void setMaxVel() //:HST00000#
{
  String str = "";
  str += Command[numCommandexec][4];
  str += Command[numCommandexec][5];
  str += Command[numCommandexec][6];
  str += Command[numCommandexec][7];
  str += Command[numCommandexec][8];
  unsigned int SS = str.toInt();
  configurationFromFlash.MinTimer = SS;
  MinTimer = configurationFromFlash.MinTimer ;  //valor minimo
  byte b2[sizeof(Configuration)]; // create byte array to store the struct
  memcpy(b2, &configurationFromFlash, sizeof(Configuration)); // copy the struct to the byte array
  dueFlashStorage.write(4, b2, sizeof(Configuration)); // write byte array to flash
  Timer3.stop();
  Timer3.start(MinTimer);
  SerialPrint("1");
}



