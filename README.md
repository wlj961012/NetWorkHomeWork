# NetWorkHomeWork
计算机网络作业
初次涉及网络编程，多有不足之处。

题目一：
  实现最基础的Socket通信：客户端连接服务器端，双方互发文本
  
实现结果：

  程序说明:

    该程序主要分为两个部分服务端程序和客户端程序：
    服务端程序步骤主要如下：

        1. 初始化WSA
        2. 创建套接字
        3. 绑定IP和端口
        4. 创建监听事件
        5. 循环监听，接受客户端的文本,并且向客户端发送文本

    客户端程序的主要步骤如下:

        1. 初始化WSA
        2. 创建套接字
        3. 绑定IP和端口
        4. 设置服务器地址和端口
        5. 连接服务器
        6. 循环向服务器发送文本，并且接收服务器发送来的文本
    运行截图：
    
*****************************************************************************************************************************    
    
题目二：
  客户端可请求服务端可以提供的文件列表，客户端请求服务端的某个文件，服务端将该文件传输给客户端保存
  
  服务器端:
  
    主要分为以下部分：
      Message.h
      Server.h
      Source.h
      Server.cpp
      Source.cpp
    Messsage.h功能：
      定义文件信息
    Server实现功能:
        1. 初始化WSA
        2. 创建套接字
        3. 绑定IP和端口
        4. 创建监听事件
        5. 循环监听，接受客户端的文件,并且向客户端发送文件
    Source实现功能：
        处理文件路径
  客户端：
  
    主要有以下几个部分：
      Client.h
      Messgage.h
      Client.cpp
    Message.h:
      与服务器端相同，都是定义文件信息
    Client.h:
        1. 创建套接字
        2. 绑定服务器IP和端口
        3. 向服务器发送消息，并且接受服务器发送的消息
  
********************************************************************************************************************************
题目三：两个客户端通过服务端互发文本，支持离线发送，上线接收

  该作业主要分为三个部分：
  
    1.服务器端
    2.客户端1
    3.客户端2
  服务器端：
  
    创建两个线程，两个临界资源，分别为A传来的消息，B传来的消息
    用互斥信号量互锁消息。、
  客户端：
  
    当客户端与服务器相连时，服务器接受到消息，将客户端的消息，存到相应的缓冲区内。
    并且检查另一端是否向客户端发送了消息，
    如果是，则将消息发送该客户端，否则发空消息给客户端以指示服务器收到了消息。
