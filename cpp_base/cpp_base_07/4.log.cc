#include <iostream>
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Category.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/FileAppender.hh"

using namespace log4cpp;
using std::cout;
using std::endl;

int main()
{
    // 1.设置布局
    PatternLayout * ptn1 = new PatternLayout();
    ptn1->setConversionPattern("%d %c [%p] %m%n");
    PatternLayout * ptn2 = new PatternLayout();
    ptn2->setConversionPattern("%d %c [%p] %m%n");
    // 2.设置目的地
    OstreamAppender * pos = new OstreamAppender("console", &cout);
    pos->setLayout(ptn1);
    FileAppender * pfile = new FileAppender("file", "chienkang.log");
    pfile->setLayout(ptn2);

    // 3.创建记录器
    Category & cate = Category::getInstance("cate");
    cate.setPriority(Priority::WARN);
    cate.addAppender(pos);
    cate.addAppender(pfile);
    // 4.写入日志
    cate.emerg("This is an emerg msg");
    cate.fatal("This is a fatal msg");
    cate.alert("This is an alert msg");
    cate.crit("This is a crit msg");
    cate.error("This is an error msg");
    cate.warn("This is an warn msg");
    cate.notice("This is a notice msg");
    cate.info("This is an info msg");
    cate.debug("This is a debug msg");
    
    // 5.回收资源
    Category::shutdown();
    return 0;
}

