#include <iostream>
using namespace std;

typedef struct
{
  int status;
  void (*statusChange)();
}T_Device;

T_Device g_device;

void addCallbackFunc(void (*pstatusChange)(int status)) {
  g_device.statusChange = pstatusChange;
}

void run() {
  g_device.status = 10;
  if(g_device.status == 10) {
    if(g_device.statusChange != NULL) {
      g_device.statusChange(g_device.status);
    }
  }
}

void callback(int status) {
  cout << "callback status:" << status << endl;
}

int main() {
  addCallbackFunc(callback);
  run();

  system("pause");
  return 0;
}