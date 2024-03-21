#ifndef CONFIG_H
#define CONFIG_H

#define ROTARY_CK_PIN   2
#define ROTARY_DT_PIN   3
#define ROTARY_SW_PIN   4
#define ROTARY_DEBOUNCE 50

#define PEN_PIN         5
#define PEN_DEBOUNCE    50

#define CANVAS_1_NUM    256
#define CANVAS_1_PIN    6
#define CANVAS_1_SET    (NEO_GRB + NEO_KHZ800)

#define CANVAS_2_NUM    256
#define CANVAS_2_PIN    7
#define CANVAS_2_SET    (NEO_GRB + NEO_KHZ800)

#define CANVAS_3_NUM    256
#define CANVAS_3_PIN    8
#define CANVAS_3_SET    (NEO_GRB + NEO_KHZ800)

#define PREVIEW_NUM     1
#define PREVIEW_PIN     9
#define PREVIEW_SET     (NEO_GRB + NEO_KHZ800)

#define SENSE_PIN       A0
#define SENSE_LEVELS    0x01010101
#define SENSE_DURATION  3
#define SENSE_THRESHOLD <128

#define BUFFER_PIXELS   64

#define SD_CS           10
#define SD_MOSI         11
#define SD_MISO         12
#define SD_SCK          13

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   32
#define OLED_MOSI       11
#define OLED_CLK        13
#define OLED_RESET      A1
#define OLED_DC         A2
#define OLED_CS         A3

#define RTC_SDA         A4
#define RTC_SCL         A5

#endif
