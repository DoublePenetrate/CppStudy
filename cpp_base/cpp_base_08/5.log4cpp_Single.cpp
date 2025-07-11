#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Appender.hh>
using namespace log4cpp;
using std::endl;
using std::cout;
using std::cin;

class Mylogger
{
public:
	void warn(const char *msg);
	void error(const char *msg);
	void debug(const char *msg);
	void info(const char *msg);

private:
	Mylogger();
	~Mylogger();

private:
    Category & _mycat;
    static Mylogger * _pInstance;
};

void test0()
{
    //第一步，完成单例模式的写法
    Mylogger *log = Mylogger::getInstance();

    log->info("The log is info message");
    log->error("The log is error message");
    log->fatal("The log is fatal message");
    log->crit("The log is crit message");

    //规范使用单例模式的写法
    Mylogger::getInstance()->info("The log is info message");
}

void test1()
{
    printf("hello,world\n");
    //第二步，像使用printf一样
    //只要求能输出纯字符串信息即可，不需要做到格式化输出
    LogInfo("The log is info message");
    LogError("The log is error message");
    LogWarn("The log is warn message");
    LogDebug("The log is debug message");
}

//最终希望的效果
 //LogDebug("The log is debug message");
//日期 记录器名字 [优先级] 文件名 函数名 行号 日志信息
