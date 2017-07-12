void SerialPrint(String str)
{
  Serial.print(str);
  Serial3.print(str);
  SerialUSB.print(str);


}
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if (inChar != ' ' )
    {
      Command[numCommand][pontBuffer] = inChar;
      pontBuffer = pontBuffer + 1;
    }
    if (inChar == ':'  && Command[numCommand][1] != 'S')
    {
      pontBuffer = 0;
      Command[numCommand][0] = inChar;
      pontBuffer = pontBuffer + 1;
    }
    if (inChar == '#')
    {
      pontBuffer = 0;
      numCommand = numCommand + 1;
    }
  }

  while (Serial3.available()) {
    // get the new byte:
    char inChar = (char)Serial3.read();
    if (inChar != ' ' )
    {
      Command[numCommand][pontBuffer] = inChar;
      pontBuffer = pontBuffer + 1;
    }
    if (inChar == ':'  && Command[numCommand][1] != 'S')
    {
      pontBuffer = 0;
      Command[numCommand][0] = inChar;
      pontBuffer = pontBuffer + 1;
    }
    if (inChar == '#')
    {
      pontBuffer = 0;
      numCommand = numCommand + 1;
    }
  }

  while (SerialUSB.available()) {
    // get the new byte:
    char inChar = (char)SerialUSB.read();
    if (inChar != ' ' )
    {
      Command[numCommand][pontBuffer] = inChar;
      pontBuffer = pontBuffer + 1;
    }
    if (inChar == ':'  && Command[numCommand][1] != 'S')
    {
      pontBuffer = 0;
      Command[numCommand][0] = inChar;
      pontBuffer = pontBuffer + 1;

    }
    if (inChar == '#' )
    {
      pontBuffer = 0;
      numCommand = numCommand + 1;
    }
  }
  if (numCommand > 14 )
  {
    numCommand = 0;
  }
  if (pontBuffer > 14)
  {
    pontBuffer = 0;
  }
}
void SerialPrintDebug(String str)
{
  if (flagDebug == 1)
  {
    Serial.println(str);
    // SerialUSB.println(str);
  }
}

