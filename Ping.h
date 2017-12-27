#ifndef HEADER_PING
  #define HEADER_PING
  class Ping {
    private:
      int pingPin;
        
    public:
      Ping(int pin);
      int ObstacleDistanceInCM();
};
#endif
