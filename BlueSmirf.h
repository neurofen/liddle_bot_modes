#ifndef HEADER_BLUESMIRF
  #define HEADER_BLUESMIRF
  class BlueSmirf {
    private:
      
    
    public:
      BlueSmirf(uint8_t txPin, uint8_t rxPin);
      /*
       * Before starting bluetooth, lower the baud rate
       * to 9600 so SoftwareSerial can reliably relay data
       */
      void Initialise();
      int Available(); 
      char Read();
  };
#endif
