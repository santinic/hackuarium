#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define STOP 4

IRsend irsend;
void sendCode (unsigned int * code, unsigned int codeLen) {
    irsend.sendRaw(code, codeLen, 38);
}

class Fish
{
  public:
    Fish (unsigned int *up, unsigned int *down, unsigned int * left, unsigned int *right, unsigned int * stopC, unsigned int codeLen);
    void command (unsigned int cmd, unsigned long duration) const;
    void action (String actionName) const;
    
  private:
    unsigned int * commands [5];
    unsigned int codeLen;
    void flap() const;
    void dive() const;
    void rise() const;
};


Fish::Fish(unsigned int *up, unsigned int *down, unsigned int * left, unsigned int *right,  unsigned int * stopC, unsigned int codeLen)
{
  this->commands[UP] = up;
  this->commands[DOWN] = down;
  this->commands[LEFT] = left;
  this->commands[RIGHT] = right;
  this->commands[STOP] = stopC;
  
  this->codeLen = codeLen;
}

void Fish::command (unsigned int cmd, unsigned long duration) const 
{
  unsigned long timeStart = millis();
  do {
    sendCode(this->commands[cmd], this->codeLen);
    delay(40);
  } while (millis() <= timeStart + duration);
  
  sendCode(this->commands[STOP], this->codeLen);
  delay(40);
}

void Fish::action(String name) const {
  if(name == "flap") {
    this->flap();
  }
  else if(name == "dive") {
    this->dive();
  }
  else if(name == "rise") {
    this->rise();
  }
}

void Fish::flap() const {
  this->command(LEFT, 400);
  this->command(RIGHT, 400);
}

void Fish::dive() const {
  this->command(UP, 500);
  this->flap();
  delay(100);
  this->command(DOWN, 500);
}

void Fish::rise() const {
}


