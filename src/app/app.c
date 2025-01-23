#include <stdbool.h>

#include "../engine/engine.h"
#include "app.h"

Engine engine;

static void appInit(void) { engine = engineCreate(); }

static void appMainLoop(void) {
  while (engineIsRunning(&engine)) {
    engineUpdate(&engine);
  }
}

static void appCleanup(void) { engineDestroy(&engine); }

void appRun(void) {
  appInit();
  appMainLoop();
  appCleanup();
}
