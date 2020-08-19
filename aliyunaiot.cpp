REQUIRE("Arduino MEGA 2560");
TL_MQTT mqtt;
// remote wifi
char SSID[] = "AZFT";
char Pass[] = "AZFT123456";
int port = 1883;
// fills your Aliyun info
char serverName[] = "a1uw222JO83.iot-as-mqtt.cn-shanghai.aliyuncs.com";
char clientName[] = "FESA234FBDS24|securemode=3,signmethod=hmacsha1,timestamp=789|";
char topicName[] = "/sys/a1uw222JO83/OTyeaUft3q5f5q12LAZi/thing/event/property/post";
char userName[] = "OTyeaUft3q5f5q12LAZi&a1uw222JO83";
char password[] = "e8b8a93d7db68516c6afacde2243e4413be70a21";
// 根据技小新对阿里云激活凭证的计算结果填写信息，用于mqtt通信
void setup()
{
    // Initialize network
    TL_Serial.begin(9600);
    TL_WiFi.init();
    bool b = TL_WiFi.join(SSID,Pass);
    mqtt = TL_WiFi.fetchMQTT();
mqtt.connect(serverName, port, clientName, userName, password);
//从WiFi模块中获取一个MQTT客户端
    // Your code's here
    TL_Light.read();
    TL_Humidity.read();
TL_Temperature.read();  
//读取MQTT报文中的温度、湿度、亮度数据
    String data = "{\"id\" : \"123\", \"version\":\"1.0\", \"params\" : {";
    data += "\"CurrentTemperature\":";
    data += TL_Temperature.data();
    data += ", \"CurrentHumidity\":";
    data += TL_Humidity.data();
    data += ", \"mlux\":";
    data += TL_Light.data();
    data += ", \"key\":";
    data += "\"MTYsODMwLGYxN2VhZjc3\"";
data += "},\"method\":\"thing.event.property.post\"}";
//根据获取的数据，构造一个符合ALink协议规范的字符串，字符串为String类型
TL_Serial.println(data);
//在控制台打印该字符串
    char buf[500];
data.toCharArray( buf, 500 );
//利用String类的toCharArray()方法将字符串data转入buf数组
int res = mqtt.publish(topicName, buf, strlen(buf),0);
//MQTT客户端publish数据到指定主题
    TL_Serial.println(res);
  		TL_Time.delayMillis(1000);	//延时1s
    //========= End =========
    // print 'end' to complete judge
    TL_Serial.println("end");
}
void loop(){
    TL_Time.delayMillis(5000);
}
