REQUIRE("Arduino MEGA 2560");
int port = 12353;
char serverName[] = ****PLEASE REPLACE WITH YOUR SERVER NAME****;;
char clientName[] = ****PLEASE REPLACE WITH YOUR CLIENT NAME****;;
char userName[] = ****PLEASE REPLACE WITH YOUR USERNAME****;;
char password[] = ****PLEASE REPLACE WITH YOUR PASSWORD****;;
char SSID[] = ****PLEASE REPLACE WITH YOUR SSID****;;
char Pass[] = ****PLEASE REPLACE WITH YOUR PASSWORD****;;
// fills your mqtt topic
char topicName[] = "judge/dca7";
//以上根据题意将与题目有关的相关信息存入不同变量中
// ======== End ========
void setup()
{
    // Initialize network
    TL_Serial.begin(9600);
    TL_WiFi.init();
    bool b = TL_WiFi.join(SSID,Pass);
    TL_MQTT mqtt = TL_WiFi.fetchMQTT();
mqtt.connect(serverName, port, clientName, userName, password);	
//从WiFi模块中获取一个MQTT客户端
    // Your code's here
    int count=2;//定义循环变量count=2，用于让串口循环输出2次
    while (count--){
         TL_Temperature.read();
         String data = String("{") + "\"temperature\":" + TL_Temperature.data() + String("}");	//读取MQTT报文中的温度数据
         char buf[100];
         data.toCharArray(buf, 100);
		 //利用String类的toCharArray()方法将字符串data转入buf数组
         TL_Serial.print("Temperature data is ");
         TL_Serial.println(TL_Temperature.data());	//按题设格式打印温度数据
         int res = mqtt.publish(topicName, buf, strlen(buf));	
//MQTT客户端publish数据到指定主题
         TL_Time.delayMillis(3000);	//根据题意延时3s
     }
    //========= End =========
    // print 'end' to complete judge
    TL_Serial.println("end");
}
void loop(){
    TL_Time.delayMillis(5000);
}
