#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <string>
using namespace log4cpp;
using std::endl;
using std::cout;
using std::cin;
using std::string;

#define addPrefix(msg) string(" [ ").append(__FILE__).append(" : ").append(__func__).append(" : ")\
        .append(std::to_string(__LINE__)).append(" ] ").append(msg).c_str()

#define LogWarn(msg) Mylogger::getInstance()->warn(addPrefix(msg)) 
#define LogEmerg(msg) Mylogger::getInstance()->emerg(addPrefix(msg)) 
#define LogFatal(msg) Mylogger::getInstance()->fatal(addPrefix(msg)) 
#define LogCrit(msg) Mylogger::getInstance()->crit(addPrefix(msg)) 
#define LogAlert(msg) Mylogger::getInstance()->Alert(addPrefix(msg)) 
#define LogError(msg) Mylogger::getInstance()->error(addPrefix(msg)) 
#define LogNotice(msg) Mylogger::getInstance()->notice(addPrefix(msg)) 
#define LogDebug(msg) Mylogger::getInstance()->debug(addPrefix(msg)) 
#define LogInfo(msg) Mylogger::getInstance()->info(addPrefix(msg)) 

/*能够输出到终端，还能保存到文件。让其使用起来更方便
 *要求：可以像printf一样
 *同时输出的日志信息中最好能有文件的名字，函数的名字及其所在的行号
 */


class Mylogger
{
public:
    static Mylogger * getInstance()
    {
        if (nullptr == _pInstance) {
            _pInstance = new Mylogger();
        }
        return _pInstance;
    }
    static void destory() {
        if (_pInstance != nullptr) {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    void emerg(const char *msg) {
        _mycat.emerg(msg);
    }
    void fatal(const char *msg) {
        _mycat.fatal(msg);
    }
    void alert(const char *msg) {
        _mycat.alert(msg);
    }
    void crit(const char *msg) {
        _mycat.crit(msg);
    }
    void error(const char *msg) {
        _mycat.error(msg);
    }
    void warn(const char *msg) {
        _mycat.warn(msg);
    }
    void notice(const char *msg) {
        _mycat.notice(msg);
    }
    void info(const char *msg) {
        _mycat.info(msg);
    }
    void debug(const char *msg) {
        _mycat.debug(msg);
    }

private:
    Mylogger(const Mylogger & rhs) = delete;
    Mylogger & operator=(const Mylogger & rhs) = delete;

    // Mylogger() = default;
    Mylogger() 
        : _mycat(Category::getInstance("mycat"))
    {
        // 1.设置日志布局
        PatternLayout * ptn1 = new PatternLayout();
        ptn1->setConversionPattern("%d %c [%p] %m%n");
        PatternLayout * ptn2 = new PatternLayout();
        ptn2->setConversionPattern("%d %c [%p] %m%n");
        // 2.创建输出器对象
        OstreamAppender * pos = new OstreamAppender("console", &cout);
        pos->setLayout(ptn1);
        RollingFileAppender * rfPos = new RollingFileAppender("file", "test.log", 5 * 1024, 9);
        rfPos->setLayout(ptn2);
        // 3.创建日志记录器 已完成创建
        // 4.给Category设置优先级
        _mycat.setPriority(Priority::WARN);
        // 5.给Category设置输出器
        _mycat.addAppender(pos);
        _mycat.addAppender(rfPos);
        cout << "Mylogger()" << endl;
    }
    ~Mylogger()
    {
        Category::shutdown();
        cout << "~Mylogger" << endl;
    }

private:
    Category & _mycat;
    static Mylogger * _pInstance;
};

Mylogger * Mylogger::_pInstance = nullptr;

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



void test2() {
    cout << addPrefix("This is a msg") << endl;
}

void test3() {
    Mylogger::getInstance()->error(addPrefix("This is a arror msg"));
}

int main() {
    test1();
    //    test1();
    return 0;
}
