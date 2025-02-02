#include "app/app.h"

int main(void) {
  App app = appCreate();
  appRun(&app);
  appDestroy(&app);
  return 0;
}
