#include <Arduino.h> //thư viện cấu hình esp tương thích với arduino code
#include <IRremoteESP8266.h> //thư viện giải mã IR
#include <IRrecv.h>
#include <IRutils.h>
#include <WiFi.h> //Thư viện kết nối wifi
#include <HTTPClient.h>
const char* ssid     = "ESP32";  //khai báo tên wifi
const char* password = "123456789"; //khai báo mật khẩu wifi
const uint16_t kRecvPin = 14; //khai báo chân kết nối IR


IRrecv irrecv(kRecvPin); //khởi tạo đối tượng ir

decode_results results; //khởi tạo biến trả về của IR

const String api = "http://maker.ifttt.com/trigger/IR_update/with/key/lWK9CDDkuNCHD2HMbZnuFoBxQXMC47e1kVRAebPlaCa"; //API server webhook

WiFiClient client; //khởi tạo đối tượng client wifi
HTTPClient http;  //khởi tạo đối tượng http để gọi api
void setup() {
  Serial.begin(115200); //khởi tạo cổng serial 115200
  pinMode(13,OUTPUT);  //khai báo chân tín hiệu đèn led
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); //khởi tạo kết nối wifi

  while (WiFi.status() != WL_CONNECTED) { //chờ kết nối wifi
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); //in thông tin địa chỉ ipv4
  irrecv.enableIRIn();  // khởi tạo sự kiện lắng nghe IR
}
void setDataToGoogleSheet(String val1, String val2, String val3) {  //khởi tạo hàm gửi dữ liệu lên google sheet
  String parm = "value1=" + val1 + "&value2=" + val2 + "&value3=" + val3; // khởi tạo tham số của api
  if (WiFi.status() == WL_CONNECTED) { //kiểm tra kết nối wifi
    http.begin(client, api); // khởi tạo kết nối tới server
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //cài đặt header của request
    Serial.println(parm);
    int httpResponseCode = http.POST(parm);  //gọi api
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    if (httpResponseCode == 200) {  //kiểm tra giá trị trả về và thông báo qua led
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
    } else {
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(50);
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
    }
    http.end(); //kết thúc gọi api
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}
void loop() {
  if (irrecv.decode(&results)) {  // kiểm tra tìn hiệu của IR
    switch (results.value) {
      case 3772793023: 
        Serial.println("Nguồn");
        setDataToGoogleSheet("Nguồn", "E0E040BF", "3772793023"); //gọi function set giá trị lên google sheet
        break;
      case  3772809343:
        Serial.println("Source");
        setDataToGoogleSheet("source", "E0E0807F", "3772809343");
        break;
      case  3772784863  :
        setDataToGoogleSheet("1", "E0E020DF", "3772784863");
        Serial.println("1");
        break;
      case  3772817503  :
        setDataToGoogleSheet("2", "E0E0A05F", "3772817503");
        Serial.println("2");
        break;
      case  3772801183  :
        setDataToGoogleSheet("3", "E0E0609F", "3772801183");
        Serial.println("3");
        break;
      case  3772780783  :
        setDataToGoogleSheet("4", "E0E010EF", "3772780783");
        Serial.println("4");
        break;
      case  3772813423  :
        setDataToGoogleSheet("5", "E0E0906F", "3772813423");
        Serial.println("5");
        break;
      case  3772797103  :
        setDataToGoogleSheet("6", "E0E050AF", "3772797103");
        Serial.println("6");
        break;
      case  3772788943  :
        setDataToGoogleSheet("7", "E0E030CF", "3772788943");
        Serial.println("7");
        break;
      case  3772821583  :
        setDataToGoogleSheet("8", "E0E0B04F", "3772821583");
        Serial.println("8");
        break;
      case  3772805263  :
        setDataToGoogleSheet("9", "E0E0708F", "3772805263");
        Serial.println("9");
        break;
      case  3772811383  :
        setDataToGoogleSheet("0", "E0E08877", "3772811383");
        Serial.println("0");
        break;
      case  3772789963  :
        setDataToGoogleSheet("ttx/mix", "E0E034CB", "3772789963");
        Serial.println("ttx/mix");
        break;
      case  3772827703  :
        setDataToGoogleSheet("pre-ch", "E0E0C837", "3772827703");
        Serial.println("pre-ch");
        break;
      case  3772837903  :
        setDataToGoogleSheet("mute", "E0E0F00F", "3772837903");
        Serial.println("mute");
        break;
      case  3772833823  :
        setDataToGoogleSheet("volumn_UP", "E0E0E01F", "3772833823");
        Serial.println("vol +");
        break;
      case  3772829743  :
        setDataToGoogleSheet("volumn_DOWN", "E0E0D02F", "3772829743");
        Serial.println("vol -");
        break;
      case  3772795063  :
        setDataToGoogleSheet("page_UP", "E0E048B7", "3772795063");
        Serial.println("page +");
        break;
      case  3772778743  :
        setDataToGoogleSheet("page_DOWN", "E0E008F7", "3772778743");
        Serial.println("page -");
        break;
      case  3772831273  :
        setDataToGoogleSheet("chList", "E0E0D629", "3772831273");
        Serial.println("ch-List");
        break;
      case  3772789198  :
        setDataToGoogleSheet("media.p", "E0E031CE", "3772789198");
        Serial.println("Media.P");
        break;
      case  3772799143  :
        setDataToGoogleSheet("menu", "E0E058A7", "3772799143");
        Serial.println("Menu");
        break;
      case  3772829998  :
        setDataToGoogleSheet("hdmi", "E0E0D12E", "3772829998");
        Serial.println("hdmi");
        break;
      case  3772830253  :
        setDataToGoogleSheet("tools", "E0E0D22D", "3772830253");
        Serial.println("tools");
        break;
      case  3772839943  :
        setDataToGoogleSheet("info", "E0E0F807", "3772839943");
        Serial.println("info");
        break;
      case  3772778233  :
        setDataToGoogleSheet("top", "E0E006F9", "3772778233");
        Serial.println("top");
        break;
      case  3772810873  :
        setDataToGoogleSheet("down", "E0E08679", "3772810873");
        Serial.println("down");
        break;
      case  3772819033  :
        setDataToGoogleSheet("left", "E0E0A659", "3772819033");
        Serial.println("left");
        break;
      case  3772794553  :
        setDataToGoogleSheet("right", "E0E046B9", "3772794553");
        Serial.println("right");
        break;
      case  3772782313  :
        setDataToGoogleSheet("enter", "E0E016E9", "3772782313");
        Serial.println("enter");
        break;
      case  3772783333  :
        setDataToGoogleSheet("return", "E0E01AE5", "3772783333");
        Serial.println("return");
        break;
      case  3772822603  :
        setDataToGoogleSheet("exit", "E0E0B44B", "3772822603");
        Serial.println("exit");
        break;
      case  3772790473  :
        setDataToGoogleSheet("A", "E0E036C9", "3772790473");
        Serial.println("A");
        break;
      case  3772786903  :
        setDataToGoogleSheet("B", "E0E028D7", "3772786903");
        Serial.println("B");
        break;
      case  3772819543  :
        setDataToGoogleSheet("C", "E0E0A857", "3772819543");
        Serial.println("C");
        break;
      case  3772803223  :
        setDataToGoogleSheet("D", "E0E06897", "3772803223");
        Serial.println("D");
        break;
      case  3772781803  :
        setDataToGoogleSheet("p.Mode", "E0E014EB", "3772781803");
        Serial.println("p.Mode");
        break;
      case  3772808323  :
        setDataToGoogleSheet("p.Size", "E0E07C83", "3772808323");
        Serial.println("p.Size");
        break;
      case  3772806793  :
        setDataToGoogleSheet("SRS", "E0E07689", "3772806793");
        Serial.println("SRS");
        break;
      case  3772801693  :
        setDataToGoogleSheet("stop", "E0E0629D", "3772801693");
        Serial.println("stop");
        break;
      case  3772818013  :
        setDataToGoogleSheet("prev", "E0E0A25D", "3772818013");
        Serial.println("prev");
        break;
      case  3772834333  :
        setDataToGoogleSheet("play", "E0E0E21D", "3772834333");
        Serial.println("play");
        break;
      case  3772797613  :
        setDataToGoogleSheet("pause", "E0E052AD", "3772797613");
        Serial.println("pause");
        break;
      case  3772781293  :
        setDataToGoogleSheet("next", "E0E012ED", "3772781293");
        Serial.println("next");
        break;

    }
    irrecv.resume();  // nhận giá trị tiếp theo
  }
  delay(10); //delay tránh trường hợp bị crash
}
