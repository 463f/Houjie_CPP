#include <iostream>
#include <array>
#include <cstdio>   // snprintf()
#include <cstdlib>  // qsort, bsearch, NULL, RAND_MAX
#include <ctime>
#include <vector>
#include <string>
#include <cstring>  // strlen(), memcpy()

using namespace std;

// 接下来的几个 namespace 都是容器使用测试
// 建议 target 的值为打印出的最后一个值，既能找到，又能测试查找效率；
// 一般每次生成随机数都是相同的，第一个是 180428938，最后一个
// 699496062，可以直接用最后一个值
long get_a_target_long() {
    long target = 0;

    cout << "input a target in (0~" << RAND_MAX << "): ";
    cin >> target;
    return target;
}

string get_a_target_string() {
    long target = 0;
    char buf[10];

    cout << "input a target in (0~" << RAND_MAX << "): ";
    cin >> target;
    // 将 target 按照 %d 形式进行格式化，然后把前 10 个给buf
    // 如果格式化后的结果小于10，那么会补上 \0；反之会截断
    // 相比 sprintf 多了 n 代表不是全要，而是只要指定个数
    snprintf(buf, 10, "%ld", target);
    return string(buf);
}


// 这里传入的参数是空指针，内部再把指针转换为对应的类型；
int compareLongs(const void *a, const void *b) {
    return (*(long *)a - *(long *)b);
}


int compareStrings(const void *a, const void *b) {
    if (*(string *)a > *(string *)b)
        return 1;
    else if (*(string *)a < *(string *)b)
        return -1;
    else
        return 0;
}


//以下 MyString 是為了測試 containers with moveable elements 效果.
class MyString {
public:
    static size_t DCtor;  //累計 default-ctor 的呼叫次數
    static size_t Ctor;   //累計 ctor      的呼叫次數
    static size_t CCtor;  //累計 copy-ctor 的呼叫次數
    static size_t CAsgn;  //累計 copy-asgn 的呼叫次數
    static size_t MCtor;  //累計 move-ctor 的呼叫次數
    static size_t MAsgn;  //累計 move-asgn 的呼叫次數
    static size_t Dtor;   //累計 dtor 的呼叫次數
private:
    char *_data;
    size_t _len;
    // 把s拷贝到_data中
    void _init_data(const char *s) {
        _data = new char[_len + 1];
        memcpy(_data, s, _len);
        _data[_len] = '\0';
    }

public:
    // default ctor
    MyString() : _data(NULL), _len(0) { ++DCtor; }

    // ctor 普通构造函数
    MyString(const char *p) : _len(strlen(p)) {
        ++Ctor;
        _init_data(p);
    }

    // copy ctor
    MyString(const MyString &str) : _len(str._len) {
        ++CCtor;
        // 类的对象之间互为友元，所以MyString有权限访问str的私有变量
        _init_data(str._data);  // COPY
    }

    // move ctor, with "noexcept" 禁止抛出异常
    MyString(MyString &&str) noexcept : _data(str._data), _len(str._len) {
        ++MCtor;
        str._len = 0;
        // 移动构造是指针拷贝动作：MyString._data和str._data指向同一片内存空间；
        // 如果str调用析构则MyString的数据也没了，因为只需要把str._data指针本身废掉就可以了；
        str._data = NULL;  //避免 delete (in dtor)
    }

    // copy assignment
    MyString &operator=(const MyString &str) {
        ++CAsgn;
        // 自赋值判断
        if (this != &str) {
            if (_data) delete _data;
            _len = str._len;
            _init_data(str._data);  // COPY! 开辟新空间
        } else {
            // Self Assignment, Nothing to do.
        }
        return *this;
    }

    // move assignment 移动赋值
    MyString &operator=(MyString &&str) noexcept {
        ++MAsgn;
        if (this != &str) {
            if (_data) delete _data;
            _len = str._len;
            _data = str._data;  // MOVE! 直接复制指针
            str._len = 0;
            str._data = NULL;  // 避免 deleted in dtor 理由和之前相同
        }
        return *this;
    }

    // dtor
    virtual ~MyString() {
        ++Dtor;
        if (_data) {
            delete _data;
        }
    }

    bool operator<(const MyString &rhs) const  //為了讓 set 比較大小
    {
        return std::string(this->_data) <
               std::string(rhs._data);  //借用事實：string 已能比較大小.
    }
    bool operator==(const MyString &rhs) const  //為了讓 set 判斷相等.
    {
        return std::string(this->_data) ==
               std::string(rhs._data);  //借用事實：string 已能判斷相等.
    }

    // 复现string.data()方法
    char *get() const { return _data; }
};

// 类的静态变量，在类内声明，类外初始化
size_t MyString::DCtor = 0;
size_t MyString::Ctor = 0;
size_t MyString::CCtor = 0;
size_t MyString::CAsgn = 0;
size_t MyString::MCtor = 0;
size_t MyString::MAsgn = 0;
size_t MyString::Dtor = 0;

namespace std {
//必須放在std內：因为hash本身是模板类，所以需要在std内进行偏特化
template <>            // 模板偏特化
struct hash<MyString>  // 這是為了 unordered containers
{
    size_t operator()(const MyString &s) const noexcept {
        // 借用現有的 hash<string> (in /usr/include/c++/bits/basic_string.h)
        // 把 MyString 转为 string 类型，调用 hash<string>() 函数
        return hash<string>()(string(s.get()));
    }
};
}

// -----------------
// 没有移动构造和拷贝函数的类，剩余部分和 MyString 是相同的
// 以下 MyStrNoMove 是為了測試 containers with no-moveable elements 效果.
class MyStrNoMove {
   public:
    static size_t DCtor;  //累計 default-ctor 的呼叫次數
    static size_t Ctor;   //累計 ctor      的呼叫次數
    static size_t CCtor;  //累計 copy-ctor 的呼叫次數
    static size_t CAsgn;  //累計 copy-asgn 的呼叫次數
    static size_t MCtor;  //累計 move-ctor 的呼叫次數
    static size_t MAsgn;  //累計 move-asgn 的呼叫次數
    static size_t Dtor;   //累計 dtor 的呼叫次數
   private:
    char *_data;
    size_t _len;
    void _init_data(const char *s) {
        _data = new char[_len + 1];
        memcpy(_data, s, _len);
        _data[_len] = '\0';
    }

   public:
    // default ctor
    MyStrNoMove() : _data(NULL), _len(0) {
        ++DCtor;
        _init_data("jjhou");
    }

    // ctor
    MyStrNoMove(const char *p) : _len(strlen(p)) {
        ++Ctor;
        _init_data(p);
    }

    // copy ctor
    MyStrNoMove(const MyStrNoMove &str) : _len(str._len) {
        ++CCtor;
        _init_data(str._data);  // COPY
    }

    // copy assignment
    MyStrNoMove &operator=(const MyStrNoMove &str) {
        ++CAsgn;

        if (this != &str) {
            if (_data) delete _data;
            _len = str._len;
            _init_data(str._data);  // COPY!
        } else {
            // Self Assignment, Nothing to do.
        }
        return *this;
    }

    // dtor
    virtual ~MyStrNoMove() {
        ++Dtor;
        if (_data) {
            delete _data;
        }
    }

    bool operator<(const MyStrNoMove &rhs) const  //為了讓 set 比較大小
    {
        return string(this->_data) <
               string(rhs._data);  //借用事實：string 已能比較大小.
    }

    bool operator==(const MyStrNoMove &rhs) const  //為了讓 set 判斷相等.
    {
        return string(this->_data) ==
               string(rhs._data);  //借用事實：string 已能判斷相等.
    }

    char *get() const { return _data; }
};
size_t MyStrNoMove::DCtor = 0;
size_t MyStrNoMove::Ctor = 0;
size_t MyStrNoMove::CCtor = 0;
size_t MyStrNoMove::CAsgn = 0;
size_t MyStrNoMove::MCtor = 0;
size_t MyStrNoMove::MAsgn = 0;
size_t MyStrNoMove::Dtor = 0;

namespace std {
template <>               // 偏特化
struct hash<MyStrNoMove>  //這是為了 unordered containers
{
    size_t operator()(const MyStrNoMove &s) const noexcept {
        // 借用現有的 hash<string> (in /usr/include/c++/bits/basic_string.h)
        return hash<string>()(string(s.get()));
    }
};
}  // namespace std

//----------------------------------------------------
#include <algorithm>
#include <cstdio>   //snprintf()
#include <cstdlib>  //RAND_MAX
#include <forward_list>
#include <iostream>
#include <list>
#include <string>
using std::cin;
using std::cout;
using std::max;
using std::min;
using std::string;

namespace jj00 {
    bool strLonger(const string &s1, const string &s2) {
        return s1.size() < s2.size();
    }

    void test_misc() {
        cout << "jj00::test_misc().......... \n";

        // 以下這些是標準庫的眾多容器的 max_size() 計算方式
        // 右侧的结果都是32位系统下的，现代64位的结果远比右侧要大得多
        cout << "size_t(-1): " << size_t(-1) << endl;                 // 4294967295
        cout << size_t(-1) / sizeof(long) << endl;                    // 1073741823
        cout << size_t(-1) / sizeof(string) << endl;                  // 1073741823
        cout << size_t(-1) / sizeof(_List_node<string>) << endl;      // 357913941
        cout << size_t(-1) / sizeof(_Fwd_list_node<string>) << endl;  // 536870911
        cout << "RAND_MAX = " << RAND_MAX << endl;                    // 32767

        // 下面这个列表的写法有Python那味了
        cout << min({2, 5, 8, 9, 45, 0, 81}) << endl;  // 0
        cout << max({2, 5, 8, 9, 45, 0, 81}) << endl;  // 81
        vector<int> v{2, 5, 8, 9, 45, 0, 81};

        cout << "max of zoo and hello : " << max(string("zoo"), string("hello"))
            << endl;  // zoo
        // 使用泛型算法
        cout << "longest of zoo and hello : "
            << max(string("zoo"), string("hello"), strLonger) << endl;  // hello

        cout << "hash<MyString>函数测试：" << endl;
        cout << hash<MyString>()(MyString("Ace")) << endl;    // 1765813650
        cout << hash<MyString>()(MyString("Stacy")) << endl;  // 2790324277

        cout << "MyString(zoo) < MyString(hello) ==> "
            << (MyString("zoo") < MyString("hello")) << endl;  // 0
        cout << "MyString(zoo) == MyString(hello) ==> "
            << (MyString("zoo") == MyString("hello")) << endl;  // 0
        cout << "MyStrNoMove(zoo) < MyStrNoMove(hello) ==> "
            << (MyStrNoMove("zoo") < MyStrNoMove("hello")) << endl;  // 0
        cout << "MyStrNoMove(zoo) == MyStrNoMove(hello) ==> "
            << (MyStrNoMove("zoo") == MyStrNoMove("hello")) << endl;  // 0
    }
}  // namespace jj00
//--------------------------------------------------

#include <typeinfo>  //typeid()

// 输出 MyString/MyStringNoMove 内的静态变量内容
template <typename T>
void output_static_data(const T &myStr) {
    cout << typeid(myStr).name() << " -- " << endl;
    cout << " 拷贝构造=" << T::CCtor << " 移动构造=" << T::MCtor
         << " 拷贝赋值=" << T::CAsgn << " 移动赋值=" << T::MAsgn
         << " 析构=" << T::Dtor << " 普通构造=" << T::Ctor
         << " 默认构造=" << T::DCtor << endl;
}

#include <ctime>  //clock_t, clock()
// M: moveable; NM: no moveable
template <typename M, typename NM>
void test_moveable(M c1, NM c2, const long &value) {
    char buf[10];

    //測試 moveable
    cout << "\n\ntest, with moveable elements:" << endl;
    typedef typename iterator_traits<typename M::iterator>::value_type V1type;
    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        snprintf(buf, 10, "%d", rand());
        auto ite = c1.end();
        c1.insert(ite, V1type(buf));  // 把 buf 转成 V1type 类型
    }
    cout << "随机数填充用时："
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
    cout << "moveable.size() = " << c1.size() << endl;
    cout << "\nmoveable类型的构造情况：" << endl;
    output_static_data(*(c1.begin()));

    // 为了证明：移动构造远快于拷贝构造
    timeStart = clock();
    M c11(c1);
    cout << "拷贝构造："
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;

    timeStart = clock();
    M c12(std::move(c1));
    cout << "移动构造: "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;

    timeStart = clock();
    c11.swap(c12);
    cout << "swap: " << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC
         << " ms." << endl;

    //測試 non-moveable
    cout << "\n\ntest, with non-moveable elements" << endl;
    typedef typename iterator_traits<typename NM::iterator>::value_type V2type;
    timeStart = clock();
    for (long i = 0; i < value; ++i) {
        snprintf(buf, 10, "%d", rand());
        auto ite = c2.end();
        c2.insert(ite, V2type(buf));
    }

    cout << "随机数填充用时："
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
    cout << "non-moveable.size() = " << c2.size() << endl;
    cout << "\nnon-moveable类型的构造情况：" << endl;
    output_static_data(*(c2.begin()));

    timeStart = clock();
    NM c21(c2);
    cout << "拷贝构造: "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;

    timeStart = clock();
    NM c22(std::move(c2));
    cout << "移动构造: "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;

    timeStart = clock();
    c21.swap(c22);
    cout << "swap: " << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC
         << " ms." << endl;
}
//-----------------

//---------------------------------------------------
#include <iostream>
#include <list>
#include <memory>  //內含 std::allocator
#include <string>
//#include <bits\stl_tree.h>  //內含 _RB_tree (不需此行, 因為它被含入於 <set>
// and <map>)

//欲使用 std::allocator 以外的 allocator, 得自行 #include <ext\...>
// #include <ext/array_allocator.h>
#include <array>
#include <ext/bitmap_allocator.h>
#include <ext/debug_allocator.h>
#include <ext/malloc_allocator.h>
#include <ext/mt_allocator.h>
#include <ext/new_allocator.h>
#include <ext/pool_allocator.h>
