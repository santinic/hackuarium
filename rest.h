YunServer server;

void digitalCmd(YunClient client) {
  int pin, value;
  // pin is "13" in this URL: fishes.local/arduino/digital/13/1
  pin = client.parseInt();
  if(client.read() == '/') {
    value = client.parseInt();
    digitalWrite(pin, value);
  }
  else {
    value = digitalRead(pin);
    client.print(value);
  }
}

void fishCmd(YunClient client) {
  // fish.local/arduino/fish-cmd/<fish index>/<fish command>/<millisec>
  // e.g. First fish, DOWN=0, 800 milisec: fish.local/arduino/fish-cmd/0/0/800 
  int index, cmd;
  unsigned long millisec;
  
  
  index = client.parseInt();
  if(client.read() == '/') {
    cmd = client.parseInt();
    if(client.read() == '/') {
      millisec = (long)client.parseInt();
      
      const Fish * fish = fishes[index];
      fish->command(cmd, millisec);
    }
  }
}

void fishAction(YunClient client) {
  // fish.local/arduino/fish-action/<fish-index>/<fish-action>/
  // e.g. fish.local/arduino/fish-action/0/flap/
  int index;
  String actionName;
  
  index = client.parseInt();
  if(client.read() == '/') {
    actionName = client.readStringUntil('/'); // dovrebbe finire senza il /
    const Fish * fish = fishes[index];
    fish->action(actionName);
  }
}

void processClient(YunClient client) {
  // cmd is "digital" in this URL: fish.local/arduino/digital/13
  String cmd = client.readStringUntil('/');
  if(cmd == "digital") {
    digitalCmd(client);
  }
  else if(cmd == "fish-cmd") {
    fishCmd(client);
  }
  else if(cmd == "fish-action") {
    fishAction(client);
  }
}

void restLoop() {
  YunClient client = server.accept();
  if(client) {
    processClient(client);
    client.stop();
  }
  //delay(50);
}
