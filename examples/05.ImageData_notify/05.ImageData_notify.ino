#include <TridentTD_LineNotify.h>
#include <OV2640.h>     // ติดตั้ง library กล้องให้เรียบร้อย https://github.com/LilyGO/ESP32-Camera

#define SSID        "--------------------"
#define PASSWORD    "--------------------"
#define LINE_TOKEN  "--------------------"

OV2640 cam;

bool CameraLineNotify(String token);

void setup() {
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  

  LINE.setToken(LINE_TOKEN);

  camera_config_t camera_config;
      camera_config.ledc_channel = LEDC_CHANNEL_0;
      camera_config.ledc_timer = LEDC_TIMER_0;
      camera_config.pin_d0 = 17;
      camera_config.pin_d1 = 35;
      camera_config.pin_d2 = 34;
      camera_config.pin_d3 = 5;
      camera_config.pin_d4 = 39;
      camera_config.pin_d5 = 18;
      camera_config.pin_d6 = 36;
      camera_config.pin_d7 = 19;
      camera_config.pin_xclk = 27;
      camera_config.pin_pclk = 21;
      camera_config.pin_vsync = 22;
      camera_config.pin_href = 26;
      camera_config.pin_sscb_sda = 25;
      camera_config.pin_sscb_scl = 23;
      camera_config.pin_reset = 15;
      camera_config.xclk_freq_hz = 20000000;
      camera_config.pixel_format = CAMERA_PF_JPEG;
      camera_config.frame_size = CAMERA_FS_SVGA;
  cam.init(camera_config);

  CameraLineNotify();
}

void loop() {
}

bool CameraLineNotify(){
  cam.run();
  uint8_t *image_data = cam.getfb();
  size_t   image_size = cam.getSize();

  return LINE.notifyPicture( "Camera Capture", image_data, image_size);
}

