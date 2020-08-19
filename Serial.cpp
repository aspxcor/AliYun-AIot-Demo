REQUIRE("Arduino MEGA 2560");
void setup()
{
    // Initialize the serial and set the baud rate
    TL_Serial.begin(9600);
    // Your code's here
    int count = 4;	//定义循环变量count=4，用于让串口循环输出4次
    while (count--) {
        TL_Serial.println("e63186d502b5465eaa241d22a0976b04");
		//将数据作为ASCII文本打印到串行端口
        TL_Time.delayMillis(4000);	
//根据题意，利用delayMillis模块将程序暂停4000ms，也即4s
    }
    //========= End =========
    // print 'end' to complete judge
    TL_Serial.println("end");
}
void loop(){
    TL_Time.delayMillis(5000);
}
