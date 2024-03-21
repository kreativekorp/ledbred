#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <SD.h>
#include <SPI.h>
#include "digitalWriteFast.h"
#include "config.h"
#include "canvas.h"
#include "display.h"
#include "rotary.h"
#include "pen.h"

int sdok = 0;
int currentTask = 0;

void setup() {
  rotaryBegin();
  if (rotaryReadSwitch()) {
    pinMode(13, OUTPUT);
    for (;;) {
      digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);
      delay(1000);
    }
  }
  penBegin();
  canvasBegin();
  if (penReadSwitch()) {
    int a = 0;
    canvasDebug(a);
    for (;;) {
      int r = rotaryReadDirection();
      if (r) {
        a += r;
        canvasDebug(a);
      }
    }
  }
  displayBegin();
  sdok = SD.begin(SD_CS);
  if (sdok) {
    File sf = SD.open("STARTUP.LED", FILE_READ);
    if (sf) {
      canvasReadPreview(sf);
      sf.close();
      delay(2000);
    }
    sf = SD.open("BLANK.LED", FILE_READ);
    if (sf) {
      canvasRead(sf);
      sf.close();
    } else {
      canvasClear();
    }
  } else {
    displayMessage(23, "No SD card.");
    delay(2000);
  }
  currentTask = 0;
  colorTask();
}

void colorTask() {
  displayColorSelect(canvasGetColor());
  while (!rotaryReadSwitch()) {
    if (penReadSwitch()) {
      canvasPenDetect();
      penDebounce();
    }
    int r = rotaryReadDirection();
    if (r) {
      canvasChangeColor(r);
      displayColorSelect(canvasGetColor());
    }
  }
  rotaryDebounce();
}

void brightnessTask() {
  displayLevelSelect(canvasGetLevel());
  while (!rotaryReadSwitch()) {
    if (penReadSwitch()) {
      canvasPenDetect();
      penDebounce();
    }
    int r = rotaryReadDirection();
    if (r) {
      canvasChangeLevel(r);
      displayLevelSelect(canvasGetLevel());
    }
  }
  rotaryDebounce();
}

void messageTask(int icon, const char * str) {
  displayMessage(icon, str);
  while (!rotaryReadSwitch()) {
    if (penReadSwitch()) {
      canvasPenDetect();
      penDebounce();
    }
  }
  rotaryDebounce();
}

int confirmTask(const char * str, int i) {
  displayConfirmation(str, i);
  while (!rotaryReadSwitch()) {
    if (penReadSwitch()) {
      canvasPenDetect();
      penDebounce();
    }
    int r = rotaryReadDirection();
    if (r) {
      i = (r < 0);
      displayConfirmation(str, i);
    }
  }
  rotaryDebounce();
  return i;
}

int menuTask(int n, const int * icons, const char ** items, int i) {
  displayMenuSelect(n, icons, items, i);
  while (!rotaryReadSwitch()) {
    if (penReadSwitch()) {
      canvasPenDetect();
      penDebounce();
    }
    int r = rotaryReadDirection();
    if (r) {
      if ((i = (i + r) % n) < 0) i += n;
      displayMenuSelect(n, icons, items, i);
    }
  }
  rotaryDebounce();
  return i;
}

int isLedFile(File & entry) {
  if (!entry) return 0;
  if (entry.isDirectory()) return 0;
  int n = strlen(entry.name()) - 4;
  if (n < 0) return 0;
  if (entry.name()[n] != '.') return 0;
  if (entry.name()[n+1] != 'L') return 0;
  if (entry.name()[n+2] != 'E') return 0;
  if (entry.name()[n+3] != 'D') return 0;
  return 1;
}

File directoryTask(File & dir) {
  int n = 0;
  dir.rewindDirectory();
  File entry = dir.openNextFile();
  while (entry) {
    if (isLedFile(entry)) n++;
    entry.close();
    entry = dir.openNextFile();
  }
  int i = n;
  displayFileSelect(i, n, "Exit");
  while (!rotaryReadSwitch()) {
    int r = rotaryReadDirection();
    if (r) {
      if ((i = (i + r) % (n+1)) < 0) i += (n+1);
      if (entry) entry.close();
      r = 0;
      dir.rewindDirectory();
      entry = dir.openNextFile();
      while (entry) {
        if (isLedFile(entry)) {
          if (r == i) break;
          r++;
        }
        entry.close();
        entry = dir.openNextFile();
      }
      if (entry) {
        displayFileSelect(i, n, entry.name());
        canvasReadPreview(entry);
        entry.seek(0);
      } else {
        displayFileSelect(i, n, "Exit");
        canvasUpdate();
      }
    }
  }
  rotaryDebounce();
  return entry;
}

void clearTask() {
  if (confirmTask("Clear picture?", 0)) {
    if (sdok) {
      File sf = SD.open("BLANK.LED");
      if (sf) {
        canvasRead(sf);
        sf.close();
        return;
      }
    }
    canvasClear();
  }
}

void loadTask() {
  if (sdok) {
    File dir = SD.open("/SAVE/");
    if (dir) {
      if (dir.isDirectory()) {
        File entry = directoryTask(dir);
        if (entry) {
          canvasRead(entry);
          entry.close();
        }
        return;
      }
      dir.close();
    }
    dir = SD.open("/");
    if (dir) {
      if (dir.isDirectory()) {
        File entry = directoryTask(dir);
        if (entry) {
          canvasRead(entry);
          entry.close();
        }
        return;
      }
      dir.close();
    }
    messageTask(23, "I/O error.");
  } else {
    messageTask(23, "No SD card.");
  }
}

static const char save_path[] PROGMEM = "SAVE/SAVE0000.LED";
static const char save_msg[] PROGMEM = "Saved as";

void saveTask() {
  if (sdok) {
    if (confirmTask("Save picture?", 1)) {
      char path[24];
      strcpy_P(path, save_path);
      while (SD.exists(path)) {
        if ((++path[12]) <= '9') continue;
        path[12] = '0';
        if ((++path[11]) <= '9') continue;
        path[11] = '0';
        if ((++path[10]) <= '9') continue;
        path[10] = '0';
        if ((++path[9]) <= '9') continue;
        path[9] = '0';
      }
      File file = SD.open(path, FILE_WRITE);
      if (file) {
        canvasWrite(file);
        file.close();
        strcpy_P(path, save_msg);
        path[8] = ' ';
        path[14] = 0;
        messageTask(20, path);
        return;
      }
      while (SD.exists(&path[5])) {
        if ((++path[12]) <= '9') continue;
        path[12] = '0';
        if ((++path[11]) <= '9') continue;
        path[11] = '0';
        if ((++path[10]) <= '9') continue;
        path[10] = '0';
        if ((++path[9]) <= '9') continue;
        path[9] = '0';
      }
      file = SD.open(&path[5], FILE_WRITE);
      if (file) {
        canvasWrite(file);
        file.close();
        strcpy_P(path, save_msg);
        path[8] = ' ';
        path[14] = 0;
        messageTask(20, path);
        return;
      }
      messageTask(23, "I/O error.");
    }
  } else {
    messageTask(23, "No SD card.");
  }
}

#define MENU_ITEM_COUNT 5
static const int menu_icons[] PROGMEM = { 24, 17, 25, 21, 22 };
static const char menu_item_0[] PROGMEM = "Select Color";
static const char menu_item_1[] PROGMEM = "Set Brightness";
static const char menu_item_2[] PROGMEM = "Clear Picture";
static const char menu_item_3[] PROGMEM = "Load Picture";
static const char menu_item_4[] PROGMEM = "Save Picture";
static const char * const menu_items[] PROGMEM = {
  menu_item_0, menu_item_1, menu_item_2, menu_item_3, menu_item_4,
};

void loop() {
  currentTask = menuTask(MENU_ITEM_COUNT, menu_icons, menu_items, currentTask);
  switch (currentTask) {
    case 0: colorTask(); return;
    case 1: brightnessTask(); return;
    case 2: clearTask(); break;
    case 3: loadTask(); break;
    case 4: saveTask(); break;
  }
  currentTask = 0;
  colorTask();
}
