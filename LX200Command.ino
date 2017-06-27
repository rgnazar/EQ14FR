void executecommand()
{
  flagCommand = 1;
  SerialPrintDebug(String(Command[numCommandexec][0])) ;

  SerialPrintDebug(String(Command[numCommandexec])) ;


  if (cmdComplete) {
    cmdComplete = false;
    if (ledStateG == LOW)
      ledStateG = HIGH;
    else
      ledStateG = LOW;
    digitalWrite(LedG, ledStateG);
    /*    Serial.print("LESTEMount:  ");
        Serial.println(LESTEMount);
        Serial.print("LESTEAlvo:  ");
        Serial.println(LESTEAlvo);

      Serial.print("ManualManual:  ");
      Serial.println(cmdComplete);

      Serial.println(Command[numCommandexec]);*/
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
          printlongitude();
          break;
        case 'G':
          printUTC();
          break;
        case 'h':
          //printAlturaLimite();
          break;
        case 'L':
          //PrintLocalHora();
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
          printlatitude();
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
          if (Command[numCommandexec][3] == 'd')//:HSd#Off DEBUG
          {
            flagDebug = 0;
          }
          if (Command[numCommandexec][3] == 'D')//:HSD#On DEBUG
          {
            flagDebug = 1;
          }
          if (Command[numCommandexec][4] == 'L') //:HSAL0000000#
          {
            setMaxPassoRA();
          }
          if (Command[numCommandexec][4] == 'Z') //:HSAZ0000000#
          {
            setMaxPassoDEC();//:HSRB0000000#
          }
          if (Command[numCommandexec][3] == 'T') //:HST0000000#
          {
            setMinTimer();
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
            //getMaxPassoRA();
          }
          if (Command[numCommandexec][4] == 'B')//:HGRB#
          {
            //getMaxPassoDEC();//:HGRB#
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

void printUTC() //sHH#
{
  char str[3];
  if (UTC < 0) {
    sprintf(str, "-%02d#", int(abs(UTC)));
  } else {
    sprintf(str, "+%02d#", int(abs(UTC)));
  }
  SerialPrint("str");
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

/////////////////////Funcoes GET

void printlongitude() // Get Current Site Longitude Returns: sDDD*MM#

{

  int Ddeg = abs((int)DecDegtoDeg(longitude));
  int Min = abs((int)DecDegtoMin(longitude));
  char str[8];
  if (longitude < 0) {
    sprintf(str, "-%03d*%02d#", int(Ddeg), int(Min));
  } else {
    sprintf(str, "+%03d*%02d#", int(Ddeg), int(Min));
  }
  SerialPrint(str);

}

void printlatitude()// :Gt# Get Current Site Latitude Returns: sDD*MM# The latitude of the current site. Positive inplies North latitude.
{

  int Ddeg = abs((int)DecDegtoDeg(latitude));
  int Min = abs((int)DecDegtoMin(latitude));
  char str[7];
  if (latitude < 0) {
    sprintf(str, "-%02d*%02d#", int(Ddeg), int(Min));
  } else {
    sprintf(str, "+%02d*%02d#", int(Ddeg), int(Min));
  }
  SerialPrint(str);
}

void printDataLocal() //Get date   :GC#   Reply: MM/DD/YY#
{
  int dia = day();
  int mes = month();
  int ano = (year() - 2000);
  char str[10];
  sprintf(str, "%02d/%02d/%02d#", int(mes), int(dia), int(ano));
  SerialPrint(str);

}

void printRAmount() //:GR# Get Telescope RA Returns: HH:MM.T# or HH:MM:SS#
{
  double horadec = Hora2DecHora(hour(), minute(), SegundoFracao) ;
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
  HAAlvo = RAtoHA(HSL, RAAlvo);
  ManualManual = 0;
  RAmountAlvo = int( HAAlvo / ResolucaoeixoHAGrausDecimal);
  DECmountAlvo = int( DECAlvo / ResolucaoeixoDECGrausDecimal);
  SincronizaMotores();
  Acompanhamento = true;
  SetAlvo();
  paramotorgeral = false;
  SerialPrint("0");

}
void synctelescopeString() //:CM# Synchronizes the telescope position with target. Returns static string: " M31 EX GAL MAG 3.5 SZ178.0'#", or "#" if error.
{
  double horadec = Hora2DecHora(hour(), minute(), SegundoFracao) ;
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
  RAmountAlvo = int( HAAlvo / ResolucaoeixoHAGrausDecimal);
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
  double horadec = Hora2DecHora(hour(), minute(), SegundoFracao) ;
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
  delay(250);
  paramotorgeral = false;
  Acompanhamento = false;
  ManualManual = 0;
  RAmountAlvo = int( HAAlvo / ResolucaoeixoHAGrausDecimal);
  DECmountAlvo = int( DECAlvo / ResolucaoeixoDECGrausDecimal);
  SetAlvo();
  SerialPrint("0");


}
void AtualizaGoto()  //Garante Atualizaçao do AlvoRA durante o delocamento e ativa o acompanhamento depois do alvo atingido
{
  ////////////////////Rotina de definição do lado do pier
  double horadec = Hora2DecHora(hour(), minute(), SegundoFracao) ;
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
  if ((RAmountAlvo == RAmount) && (DECmountAlvo == DECmount))
  {
    Acompanhamento = true;
    GotoQualidade = GotoQualidade + 1;

  }
  else
  {
    if (GotoQualidade == 0)
    {
      // Serial.println("segundo GOTO");
      double horadec = Hora2DecHora(hour(), minute(), SegundoFracao) ;
      double jdia = JulianoDay (year(), month(), day(), horadec) ;
      double HST = HoraSideral(jdia);
      double HSL = HoraSiderallocal(longitude, HST) ;
      HAAlvo = RAtoHA(HSL, RAAlvo);
      Acompanhamento = false;
      ManualManual = 0;
      int RAmountAlvotmp = int( HAAlvo / ResolucaoeixoHAGrausDecimal);
      int DECmountAlvotmp = int( DECAlvo / ResolucaoeixoDECGrausDecimal);
      int acertaerro = abs(MotorRA.distanceToGo())  + abs(MotorDEC.distanceToGo());
      /*
        Serial.print("acertaerro:  ");
        Serial.println(acertaerro);*/
      if (acertaerro < ((MaxPassoRA + MaxPassoDEC) / 200))
      {
        // Serial.println(acertaerro);
        RAmountAlvo = RAmountAlvotmp;
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
{ Acompanhamento = false;
  paramotorgeral = false;
  RAmountAlvo = (MaxPassoRA * -10);
  SetAlvo();
  ManualManual = ManualManual + 1;
}

//Move telescope west (at current rate)   :Mw#  Reply: [none]
void moveoeste()
{ Acompanhamento = false;
  paramotorgeral = false;
  RAmountAlvo = (MaxPassoRA * 10);
  SetAlvo();
  ManualManual = ManualManual + 1;
}

//Move telescope north (at current rate)  :Mn#  Reply: [none]
void movenorte()
{ Acompanhamento = false;
  paramotorgeral = false;
  DECmountAlvo = (MaxPassoDEC * -10);
  SetAlvo();
  ManualManual = ManualManual + 1;
}

//Move telescope south (at current rate)  :Ms#  Reply: [none]
void movesul()
{ Acompanhamento = false;
  paramotorgeral = false;
  DECmountAlvo = (MaxPassoDEC * 10);
  SetAlvo();
  ManualManual = ManualManual + 1;
}


void paraleste()                                 //:Qe# Reply: [none]
{
  RAmount = MotorRA.currentPosition();
  RAmountAlvo = RAmount;
  SetAlvo();
  ParaMotoresHA();
  ManualManual = ManualManual - 1;

}

//Move telescope west (at current rate)   :Qw#  Reply: [none]
void paraoeste()
{
  RAmount = MotorRA.currentPosition();
  RAmountAlvo = RAmount;
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
  configurationFromFlash.MaxPassoRA = SS;
  MaxPassoRA = configurationFromFlash.MaxPassoRA;
  // write configuration struct to flash at adress 4
  byte b2[sizeof(Configuration)]; // create byte array to store the struct
  memcpy(b2, &configurationFromFlash, sizeof(Configuration)); // copy the struct to the byte array
  dueFlashStorage.write(4, b2, sizeof(Configuration)); // write byte array to flash
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
  configurationFromFlash.MaxPassoDEC = SS;
  MaxPassoDEC = configurationFromFlash.MaxPassoDEC;
  byte b2[sizeof(Configuration)]; // create byte array to store the struct
  memcpy(b2, &configurationFromFlash, sizeof(Configuration)); // copy the struct to the byte array
  dueFlashStorage.write(4, b2, sizeof(Configuration)); // write byte array to flash
  SerialPrint("1");

}

void setMinTimer() //:HST00000#
{
  String str = "";
  str += Command[numCommandexec][4];
  str += Command[numCommandexec][5];
  str += Command[numCommandexec][6];
  str += Command[numCommandexec][7];
  str += Command[numCommandexec][8];
  unsigned int SS = str.toInt();
  configurationFromFlash.MinTimer = SS + 200;
  MinTimer = configurationFromFlash.MinTimer ;  //valor minimo
  byte b2[sizeof(Configuration)]; // create byte array to store the struct
  memcpy(b2, &configurationFromFlash, sizeof(Configuration)); // copy the struct to the byte array
  dueFlashStorage.write(4, b2, sizeof(Configuration)); // write byte array to flash
  Timer3.stop();
  Timer3.start(MinTimer);

  SerialPrint("1");
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


void getMaxPassoRA()  //:HGRA#
{
  char str[8];
  sprintf(str, "%07d#", int(MaxPassoRA));
  SerialPrint(str);
}

void getMaxPassoDEC() //:HGRB#
{
  char str[8];
  sprintf(str, "%07d#", int(MaxPassoDEC));
  SerialPrint(str);
}

void getMinTimer() //:HGT#
{
  char str[8];
  sprintf(str, "%07d#", int(MinTimer));
  SerialPrint(str);
}


void printOperatocao()
{
  SerialPrint("N#");
}



void printalinhamento() //:GW# with "AN0#"
{
  SerialPrint("AN0#");
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



/*std Autostars return "Autostar"
  LX200s return "LX2001"
  RCXs return "RCX400"
  LSs returned "ETX-LS" and now just "LS"
  LS/AutostarIII GVF response is (currently) only the firmware version: "1.6#"
  (the Autostar III responds to a :GW# with "AN0#" (if not aligned or tracking))
  After reading the excellent info on http://www.weasner.com   I learn that : " when typing a single control-F on the terminal  the Autostar should echo an "A" or "P" depending upon whether it's
  set up as Alt/Az or Polar mount status and when typing #:GVF#  it should respond with its identification string, including the word Autostar and a time and date (when that firmware version
  was built at Meade) ".
  Indeed  :
  Ctrl -F    ---> A
  #:GVF#   ---> #Autostar|A|12Ea #
*/

/*
  Here's a summary of the features/command set currently implemented for the On-Step controller:
  Return values generally indicate failure (0) or success (1).
  Command length is limited to 20 chars, 2 for the command frame ":#" + 2 for the code "CC" + a maximum of 16 for the parameter "P": ":CCPPP...#". Cr/lf chars can be sent along with your command, but are ignored.


  Date/time commands
  Set date   :SCMM/DD/YY#  Reply: 0 or 1
  Get date  :GC#  Reply: MM/DD/YY#
  Set time (Local)  :SLHH:MM:SS#  Reply: 0 or 1
  Get time (Local, 12hr format) :Ga#  Reply: HH:MM:SS#
  Get time (Local, 24hr format) :GL#  Reply: HH:MM:SS#
  Set time (Sidereal)   :SSHH:MM:SS#  Reply: 0 or 1
  Get time (Sidereal)   :GS#  Reply: HH:MM:SS#

  Site/Location commands
  Set UTC Offset(for current site)  :SGsHH#   Reply: 0 or 1
  Get UTC Offset(for current site)  :GG#  Reply: sHH#
  The UTC Offset value is the number of hours to add to your Local Time (Standard Time) to get Universal Time.
  Set Latitude (for current site) :StsDD*MM#  Reply: 0 or 1
  Get Latitude (for current site) :Gt#  Reply: sDD*MM#
  Set Longitude (for current site)  :SgDDD*MM#  Reply: 0 or 1
  Get Longitude (for current site)  :Gg#  Reply: DDD*MM#
  Set site 0 name   :SMsss...#  Reply: 0 or 1
  Set site 1 name   :SNsss...#  Reply: 0 or 1
  Set site 2 name   :SOsss...#  Reply: 0 or 1
  Set site 3 name   :SPsss...#  Reply: 0 or 1
  Get site 0 name   :GM#  Reply: sss...#
  Get site 1 name   :GN#  Reply: sss...#
  Get site 2 name   :GO#  Reply: sss...#
  Get site 3 name   :GP#  Reply: sss...#
  Select site n (0-3)   :Wn#  Reply: [none]

  Slewing/Movement commands
  Set target RA   :SrHH:MM:SS# *  Reply: 0 or 1
  Get target RA   :Gr#  Reply: HH:MM:SS# *
  Set target Dec  :SdsDD:MM:SS# * Reply: 0 or 1
  Get target Dec  :Gd#  Reply: sDD*MM'SS# *
  Set target Azm  :SzDDD:MM:SS# * Reply: 0 or 1
  Set target Alt  :SasDD:MM:SS# * Reply: 0 or 1
  Get telescope RA  :GR#  Reply: HH:MM:SS# *
  Get telescope Dec   :GD#  Reply: sDD*MM'SS# *
  Get telescope Azm   :GZ#  Reply: DDD*MM'SS# *
  Get telescope Alt   :GA#  Reply: sDD*MM'SS# *
  = Defaults to high precision mode, in low precision mode "HH:MM.M", "sDD*MM", or "DDD*MM" are used as appropriate.
  Set horizon limit   :ShsDD#   Reply: 0 or 1
  Get horizon limit   :GhsDD#   Reply: sDD#
  Set overhead limit  :SoDD#  Reply: 0 or 1
  Get overhead limit  :GoDD#  Reply: sDD#
  The horizon limit sets how far below (or above) the horizon the telescope will point for a goto:
  Valid range (in degrees) is +30 to -30.
  The overhead limit helps keep the telescope tube from hitting the tripod etc. during a goto:
  Valid range (in degrees) is 60 to 90.
  Move telescope (to current Equ target)  :MS#  Reply: e *2
  Move telescope (to current Hor target)  :MA#  Reply: e *2
  2 = Error codes for the MS and MA commands are as follows:
  e=0 (no error), e=1 (below horizon), e=2 (no object), e=4 (position unreachable), e=5 (not aligned), e=6 (outside limits)
  Stop telescope  :Q#   Reply: [none]
  Move telescope east (at current rate)   :Me#  Reply: [none]
  Move telescope west (at current rate)   :Mw#  Reply: [none]
  Move telescope north (at current rate)  :Mn#  Reply: [none]
  Move telescope south (at current rate)  :Ms#  Reply: [none]
  Stop moving east  :Qe#  Reply: [none]
  Stop moving west  :Qw#  Reply: [none]
  Stop moving north   :Qn#  Reply: [none]
  Stop moving south   :Qs#  Reply: [none]
  Pulse guide (at current rate):
  d=n,s,e,w
  nnnn=time in mS
  (from 20 to 16399mS)  :Mgdnnnn#   Reply: [none]
  Set rate to Guide   :RG#  Reply: [none]
  Set rate to Centering   :RC#  Reply: [none]
  Set rate to Move  :RM#  Reply: [none]
  Set rate to Slew  :RS#  Reply: [none]
  Set rate to n (0-9)*3 :Rn#  Reply: [none]
  3 = Slew rates are as follows.
  All values are in multipules of the sidereal rate:
  R0=0.25X, R1=0.5X, R2(RG)=1X, R3=2X, R4(RC)=4X, R5=8X(RM), R6=16X, R7(RS)=24X, R8=40X, R9=60X
  (for the -Dev-Alpha branch of OnStep:
  R0=0.25X, R1=0.5X, R2(RG)=1X, R3=2X, R4=4X, R5(RC)=8X, R6(RM)=24X, R7=48X, R8(RS)=1/2 MaxRate, R9=MaxRate)
  Get distance bars (indicates slew)  :D# Reply: \0x7F#
  Pier side   :Gm#  Reply: N#, E# or W#

  Tracking rate commands
  Set sidereal rate RA  :STdd.ddddd#  Reply: 0 or 1
  Get sidereal rate RA  :GT#  Reply: dd.ddddd#
  Track sidereal rate RA (default)  :TQ#  Reply: [none]
  Track sidereal rate reset   :TR#  Reply: [none]
  Track rate increase 0.02Hz  :T+#  Reply: [none]
  Track rate decrease 0.02Hz  :T-#  Reply: [none]
  Track solar rate RA   :TS#  Reply: [none]
  Track lunar rate RA   :TL#  Reply: [none]
  Track king rate RA  :TK#  Reply: [none]
  Tracking enable   :Te#  Reply: 0 or 1
  Tracking disable  :Td#  Reply: 0 or 1
  Refraction rate tracking  :Tr#  Reply: 0 or 1
  No refraction rate tracking   :Tn#  Reply: 0 or 1
  Tracking rate adjustment is as follows:
  The sidereal rate is default and is always selected on power-up. The T+ and T- commands can adjust any of the rates; however only the sidereal rate, if selected, remembers the adjusted rate through a power cycle.
  Refraction rate tracking adjusts the RA rate dynamically to best compensate for refraction in a given region of the sky; again this works for any of the rates. This setting isn't remembered between power cycles, but the OnStep firmware can be compiled so that this setting defaults to enabled.

  Sync. command
  Sync. with current target RA/Dec  :CS#  Reply: [none]
  Sync. with current target RA/Dec  :CM#  Reply: N/A#
  Note: Sync's are only valid if <=30 degrees from the current location, otherwise the command is ignored.

  Library commands
  Select catalog no.  :Lonn#  Reply: 0 or 1
  Move Back in catalog  :LB#  Reply: [none]
  Move to Next in catalog   :LN#  Reply: [none]
  Move to catalog item no.  :LCnnnn#  Reply: [none]
  Move to catalog name rec. :L$#  Reply: 1
  Get catalog item id.  :LI#  Reply: name,type#
  Read catalog item info.
  (also moves forward)  :LR#  Reply: name,type,RA,Dec#
  Write catalog item info.
  ssss=name, ttt=type code:
  UNK,OC,GC,PN,DN,SG,EG,IG,KNT,SNR,GAL,CN,STR,PLA,CMT,AST
  :LWssss,ttt#  Reply: 0 or 1
  Clear current record  :LD#  Reply: [none]
  Clear current cataLog   :LL#  Reply: [none]
  Clear all catalogs  :L!#  Reply: [none]
  The LI# and LW# commands also set/get target coordinates (as with :Gr#, :Sr#, :Gd#, :Sd#)
  Library record storage is in EEPROM. A catalog name record is like any other except the name must start with a '$'. A special search can then be done with the :L$# command to move to that record. It's up to the user to not waste EEPROM with more than one name record per catalog. When the default PEC table size of 824 bytes is used, the first 1024 bytes are devoted to settings. The remaining EEPROM is used for catalog records. Each record is 16 bytes. The Mega2560 has 4K of EEPROM so 3K is available (192 records) with the default PEC table size. The Teensy3.1 has 2K of EEPROM so 1K is available (64 records.)
  It's often best to divide up large Libraries into several smaller catalogs due to serial interface speed limitations.

  Anti-backlash commands
  Set RA (Azm) backlash amount (in ArcSec)  :$BRnnn#  Reply: 0 or 1
  Set Dec (Alt) backlash amount (in ArcSec) :$BDnnn#  Reply: 0 or 1

  Periodic error correction commands
  Turn PEC on   :$QZ+#  Reply: [none]
  Turn PEC off  :$QZ-#  Reply: [none]
  Clear PEC data  :$QZZ#  Reply: [none]
  Start recording PEC   :$QZ/#  Reply: [none]
  Save PEC data/settings to EEPROM  :$QZ!#  Reply: [none]
  Get PEC status returns:
  I-Ignore PEC,
  P-Playing PEC, p-Getting ready to play PEC,
  R-Record PEC, r-Getting ready to record PEC   :$QZ?#  Reply: s#
  Readout PEC data  :VRnnnn#  Reply: sddd#
  Readout PEC data at current index (while playing/recording),
  also returns index  :VR#  Reply: sddd,ddd#
  Write PEC data  :WRnnnn,sddd#   Reply: 0 or 1
  PEC works as follows:

  In-memory values are byte sized integers (corrections) that hold the number of steps to be applied (recorded/played) at a rate of one correction per second. Up to 824 bytes are available for storage (i.e. 824 seconds for a worm rotation). My G11 uses just 240 bytes (360 tooth worm gear, one revolution every 4 minutes).

  After the data buffer is cleared ($QZZ), the next record session stores the guiding corrections without averaging. Subsequent recording of the guiding corrections use a 2:1 weighted average favoring the buffer. Data in the buffer is played back one second before the record time in the cycle to help compensate for guiding correction latency.

  When reading and writing PEC data the units used are steps.

  The save to EEPROM command allows the results to be recovered after a power cycle. This command takes several seconds to complete and should only be issued after you park or home the mount (stop tracking). NOTE: PEC isn't supported in Alt/Azm mode, yet.

  Alignment commands
  Align, write model to EEPROM  :AW#  Reply: 0 or 1
  Align, one-star*4 :A1#  Reply: 0 or 1
  Align, two-star*4 :A2#  Reply: 0 or 1
  Align, three-star*4 :A3#  Reply: 0 or 1
  Align, accept*4   :A+#  Reply: 0 or 1
  4 = The one star alignment is implemented to correct RA/Dec offset. Two star alignment adds a second star to measure/correct for polar axis Altitude misalignment and cone error. Three star alignment adds a third star to measure/correct for polar axis Azimuth misalignment. These are saved when Set park is called and maintained when Parking/Unparking the mount. The sync. equatorial coordinates command refines the model for a local area of the sky, this refinement is lost when the power is cycled unless another Set park is called. The intended use of these commands is as follows...
  Call A1. {or A2/A3.}
  Set RA/Dec target (for A2/A3 near the Meridian/Celestial Equator, telescope west of the mount, for minimal offset in RA due to being Left/Right of the pole).
  Slew to target.
  Use move commands to center target.
  Call A+. (records offsets, corrects RA/Dec)

  Continue for 2 or 3 star:
  Set RA/Dec target (near the Meridian/Celestial Equator, telescope east of the mount, for minimal offset in RA due to being Left/Right of the pole).
  Slew to target.
  Use move commands to center target.
  Call A+. (records offset, corrects error in polar altitude and cone error)

  Continue for 3 star:
  Set RA/Dec target (near 45 deg. Dec. and +6 HA, telescope east of the mount, to isolate/maximize remaining effects).
  Slew to target.
  Use move commands to center target.
  Call A+. (records offset, corrects error in polar azimuth and RA/Dec axis perpendicularity error)

  Park commands
  Set park position   :hQ#  Reply: 0 or 1
  Move to park position   :hP#  Reply: 0 or 1
  Restore parked telescope to operation :hR#  Reply: 0 or 1

  Home commands
  Set home (CWD)  :hF#  Reply: [none]
  Move to home (CWD)  :hC#  Reply: [none]

  Reticule/Accessory Control
  Increase reticule Brightness  :B+#  Reply: [none]
  Decrease reticule Brightness  :B-#  Reply: [none]

  Misc. commands
  Set baud rate:
  1=56.7K, 2=38.4K, 3=28.8K,
  4=19.2K, 5=14.4K, 6=9600,
  7=4800, 8=2400, 9=1200  :SBn#   Reply: 0 or 1
  Precision toggle  :U#   Reply: [none]
  Get firmware date   :GVD#   Reply: MM DD YY#
  Get firmware time   :GVT#   Reply: HH:MM:SS#
  Get firmware number   :GVN#   Reply: 1.0b4#
  Get firmware name   :GVP#   Reply: On-Step#
  Get statUs returns:
  N-Not slewing, H-At Home position,
  P-Parked, p-Not parked, F-Park Failed,
  I-park In progress, R-PEC Recorded
  G-Guiding in progress, S-GPS PPS Synced   :GU#  Reply: sss#

*/





