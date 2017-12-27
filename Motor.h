#ifndef HEADER_MOTOR
  #define HEADER_MOTOR
  class Motor {
    private:
      int motorEnable;
      int pin1;
      int pin2;
    
    public:
      Motor(int mEnable, int mPin1, int mPin2); 
      void Forward(int speed); 
      void Reverse(int speed);  
      void Stop();
  };
#endif
