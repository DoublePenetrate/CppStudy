// Line.hpp

class Line {
public:
    Line(int x1, int y1, int x2, int y2);
    ~Line();
    void printLine() const;
private:
    // 定义内部类
    class LineImpl;
    LineImpl * _pimpl;
};
