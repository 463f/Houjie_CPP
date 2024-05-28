#include "utils.hpp"
const long ASIZE = 500000L;

namespace jj01 {
void test_array() {
    cout << "test_array().......... \n";

    array<long, ASIZE> c;

    clock_t timeStart = clock();
    for (long i = 0; i < ASIZE; ++i) {
        c[i] = rand();
    }
    cout << "随机填充 ASIZE 个数耗时："
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms"
         << endl;
    cout << "array.size()= " << c.size() << endl;
    cout << "array.front()= " << c.front() << endl;
    cout << "array.back()= " << c.back() << endl;
    cout << "array.data()= " << c.data() << endl << endl;  // 返回地址

    long target = get_a_target_long();

    timeStart = clock();
    // 快排：从 c 开始的 ASIZE 个 long 类型数字；比较方法 compareLongs
    ::qsort(c.data(), ASIZE, sizeof(long), compareLongs);
    // 二分查找：从 c 开始的 ASIZE 个 long 类型数字中搜寻 target，比较方法
    // compareLongs
    long *pItem = (long *)::bsearch(&target, (c.data()), ASIZE, sizeof(long),
                                    compareLongs);
    cout << "快排+二分查找(qsort+bsearch)总耗时："
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms"
         << endl;
    if (pItem != NULL)
        cout << "found, " << *pItem << endl;
    else
        cout << "not found! " << endl;
}
}  // namespace jj01

//---------------------------------------------------
#include <algorithm>  //sort()
#include <cstdio>     //snprintf()
#include <cstdlib>    //abort()
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
namespace jj02 {
void test_vector(const long &value) {
    cout << "test_vector().......... \n";

    vector<string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            // 让随机数产生的范围控制在 [0,value] 内
            snprintf(buf, 10, "%d", rand());
            c.push_back(string(buf));
        } catch (exception &p) {
            cout << "i=" << i << " " << p.what() << endl;
            //曾經最高 i=58389486 then std::bad_alloc
            abort();
        }
    }
    cout << "随机填充耗时："
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
    cout << "vector.max_size()= " << c.max_size() << endl;  // 最大容量
    cout << "vector.size()= " << c.size() << endl;    // 现有多少个元素
    cout << "vector.front()= " << c.front() << endl;  // 第一个元素
    cout << "vector.back()= " << c.back() << endl;    // 最后一个元素
    cout << "vector.data()= " << c.data() << endl;    // 内存地址
    // vector是动态增长的，所以现有容量介于现有元素和最大容量之间
    cout << "vector.capacity()= " << c.capacity() << endl << endl;

    string target = get_a_target_string();
    {
        timeStart = clock();
        auto pItem = find(c.begin(), c.end(), target);
        cout << "std::find(): "
             << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
             << endl;

        if (pItem != c.end())
            cout << "found, " << *pItem << endl << endl;
        else
            cout << "not found! " << endl << endl;
    }

    {
        timeStart = clock();
        sort(c.begin(), c.end());
        cout << "sort(): "
             << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
             << endl;

        timeStart = clock();
        string *pItem = (string *)::bsearch(&target, (c.data()), c.size(),
                                            sizeof(string), compareStrings);
        cout << "bsearch(): "
             << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
             << endl;

        if (pItem != NULL)
            cout << "found, " << *pItem << endl << endl;
        else
            cout << "not found! " << endl << endl;
    }

    c.clear();
    test_moveable(vector<MyString>(), vector<MyStrNoMove>(), value);
}
}  // namespace jj02

//---------------------------------------------------
#include <algorithm>  //find()
#include <cstdio>     //snprintf()
#include <cstdlib>    //abort()
#include <ctime>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
namespace jj03 {
void test_list(const long &value) {
    cout << "\ntest_list().......... \n";

    list<string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.push_back(string(buf));
        } catch (exception &p) {
            cout << "i = " << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "随机填充耗时: "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
    cout << "list.size()= " << c.size() << endl;
    cout << "list.max_size()= " << c.max_size() << endl;  // 357913941
    cout << "list.front()= " << c.front() << endl;
    cout << "list.back()= " << c.back() << endl;

    string target = get_a_target_string();
    timeStart = clock();
    auto pItem = find(c.begin(), c.end(), target);
    cout << "std::find(): "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;

    if (pItem != c.end())
        cout << "found, " << *pItem << endl;
    else
        cout << "not found! " << endl;

    timeStart = clock();
    c.sort();
    cout << "c.sort(): "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;

    c.clear();
    test_moveable(list<MyString>(), list<MyStrNoMove>(), value);
}
}  // namespace jj03

//---------------------------------------------------
#include <cstdio>   //snprintf()
#include <cstdlib>  //abort()
#include <ctime>
#include <forward_list>
#include <iostream>
#include <stdexcept>
#include <string>
namespace jj04 {
void test_forward_list(const long &value) {
    cout << "\ntest_forward_list().......... \n";

    forward_list<string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.push_front(string(buf));
        } catch (exception &p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "随机填充耗时: "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
    cout << "forward_list.max_size()= " << c.max_size() << endl;  // 536870911
    cout << "forward_list.front()= " << c.front() << endl;

    string target = get_a_target_string();
    timeStart = clock();
    auto pItem = find(c.begin(), c.end(), target);
    cout << "std::find(): "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;

    if (pItem != c.end())
        cout << "found, " << *pItem << endl;
    else
        cout << "not found! " << endl;

    timeStart = clock();
    c.sort();
    cout << "c.sort(): "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;

    c.clear();
}
}  // namespace jj04
//---------------------------------------------------
#include <cstdio>   //snprintf()
#include <cstdlib>  //abort()
#include <ctime>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <string>
namespace jj05 {
void test_deque(const long &value) {
    cout << "\ntest_deque().......... \n";

    deque<string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.push_back(string(buf));
        } catch (exception &p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "随机填充耗时: "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
    cout << "deque.size()= " << c.size() << endl;
    cout << "deque.front()= " << c.front() << endl;
    cout << "deque.back()= " << c.back() << endl;
    cout << "deque.max_size()= " << c.max_size() << endl;  // 1073741821

    string target = get_a_target_string();
    timeStart = clock();
    auto pItem = find(c.begin(), c.end(), target);
    cout << "std::find(): "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;

    if (pItem != c.end())
        cout << "found, " << *pItem << endl;
    else
        cout << "not found! " << endl;

    timeStart = clock();
    sort(c.begin(), c.end());
    cout << "sort(): " << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC
         << " ms." << endl;

    c.clear();
    test_moveable(deque<MyString>(), deque<MyStrNoMove>(), value);
}
}  // namespace jj05

//---------------------------------------------------
#include <cstdio>   //snprintf()
#include <cstdlib>  //abort()
#include <ctime>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
namespace jj06 {
void test_multiset(const long &value) {
    cout << "\ntest_multiset().......... \n";

    multiset<string> c;
    char buf[10];
    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.insert(string(buf));
        } catch (exception &p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "随机填充耗时: "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
    cout << "multiset.size()= " << c.size() << endl;
    cout << "multiset.max_size()= " << c.max_size() << endl;  // 214748364

    string target = get_a_target_string();
    {
        timeStart = clock();
        auto pItem = find(c.begin(), c.end(), target);  //比 c.find(...) 慢很多
        cout << "std::find(): "
             << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
             << endl;
        if (pItem != c.end())
            cout << "found, " << *pItem << endl;
        else
            cout << "not found! " << endl;
    }

    {
        timeStart = clock();
        auto pItem = c.find(target);  //比 std::find(...) 快很多
        cout << "c.find(): "
             << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
             << endl;
        if (pItem != c.end())
            cout << "found, " << *pItem << endl;
        else
            cout << "not found! " << endl;
    }

    c.clear();
    test_moveable(multiset<MyString>(), multiset<MyStrNoMove>(), value);
}
}  // namespace jj06

//---------------------------------------------------
#include <cstdio>   //snprintf()
#include <cstdlib>  //abort()
#include <ctime>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
namespace jj07 {
void test_multimap(const long &value) {
    cout << "\ntest_multimap().......... \n";

    multimap<long, string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            // multimap 不可使用 [] 做 insertion
            c.insert(pair<long, string>(i, buf));
        } catch (exception &p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "随机填充耗时: "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
    cout << "multimap.size()= " << c.size() << endl;
    cout << "multimap.max_size()= " << c.max_size() << endl;

    long target = get_a_target_long();
    timeStart = clock();
    auto pItem = c.find(target);
    cout << "c.find(): "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
    if (pItem != c.end())
        cout << "found, value=" << (*pItem).second << endl;
    else
        cout << "not found! " << endl;

    c.clear();
}
}  // namespace jj07

//---------------------------------------------------
#include <cstdio>   //snprintf()
#include <cstdlib>  //abort()
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>
namespace jj08 {
void test_unordered_multiset(const long &value) {
    cout << "\ntest_unordered_multiset().......... \n";

    unordered_multiset<string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.insert(string(buf));
        } catch (exception &p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "随机填充耗时: "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
    cout << "unordered_multiset.size()= " << c.size() << endl;
    cout << "unordered_multiset.max_size()= " << c.max_size() << endl;
    cout << "unordered_multiset.bucket_count()= " << c.bucket_count() << endl;
    cout << "unordered_multiset.load_factor()= " << c.load_factor() << endl;
    cout << "unordered_multiset.max_load_factor()= " << c.max_load_factor()
         << endl;
    cout << "unordered_multiset.max_bucket_count()= " << c.max_bucket_count()
         << endl;
    for (unsigned i = 0; i < 20; ++i) {
        cout << "bucket #" << i << " has " << c.bucket_size(i)
             << " elements.\n";
    }

    string target = get_a_target_string();
    {
        timeStart = clock();
        cout << "std::find() 比容器内的 c.find() 慢很多。" << endl;
        auto pItem = find(c.begin(), c.end(), target);
        cout << "std::find(), milli-seconds : "
             << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
             << endl;
        if (pItem != c.end())
            cout << "found, " << *pItem << endl;
        else
            cout << "not found! " << endl;
    }

    {
        timeStart = clock();
        auto pItem = c.find(target);
        cout << "c.find(): "
             << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
             << endl;
        if (pItem != c.end())
            cout << "found, " << *pItem << endl;
        else
            cout << "not found! " << endl;
    }

    c.clear();
    test_moveable(unordered_multiset<MyString>(),
                  unordered_multiset<MyStrNoMove>(), value);
}
}  // namespace jj08

//---------------------------------------------------
#include <cstdio>   //snprintf()
#include <cstdlib>  //abort()
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
namespace jj09 {
void test_unordered_multimap(const long &value) {
    cout << "\ntest_unordered_multimap().......... \n";

    unordered_multimap<long, string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            // multimap 不可使用 [] 進行 insertion
            c.insert(pair<long, string>(i, buf));
        } catch (exception &p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "随机填充耗时: "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
    cout << "unordered_multimap.size()= " << c.size() << endl;
    cout << "unordered_multimap.max_size()= " << c.max_size() << endl;

    long target = get_a_target_long();
    timeStart = clock();
    auto pItem = c.find(target);
    cout << "c.find(): "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
    if (pItem != c.end())
        cout << "found, value=" << (*pItem).second << endl;
    else
        cout << "not found! " << endl;
}
}  // namespace jj09

//---------------------------------------------------
#include <ext/slist>
//注意, 上一行並沒有引發警告訊息如 #include <ext\hash_set> 所引發者：
//...\4.9.2\include\c++\backward\backward_warning.h
//[Warning] ...

#include <cstdio>   //snprintf()
#include <cstdlib>  //abort()
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
namespace jj10 {
void test_slist(const long &value) {
    cout << "\ntest_slist().......... \n";

    __gnu_cxx::slist<string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.push_front(string(buf));
        } catch (exception &p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "随机填充耗时: "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
}
}  // namespace jj10

//---------------------------------------------------
/*
以下測試 hash_multiset, hash_multimap 過程中遇到阻礙：
headers 在 <hash_set> 和 <hash_map> 各有兩個，
分別在 /usr/include/c++/backward 和 /usr/include/c++/ext，
不知要用哪一組!
用 <ext/...> 那一組會有問題
   /usr/include/c++/backward/hashtable.h
   [Error] no match for call to '(const hasher {aka const
__gnu_cxx::hash<std::basic_string<char> >}) (const key_type&)' 用 <backward/...>
那一組有相同的問題. so, 放棄測試 (no insertion or push_back or ...).
*/

#include <ext/hash_set>
// 会有下面的警告：
/// usr/include/c++/backward/backward_warning.h
//[Warning] #warning This file includes at least one deprecated or antiquated
// header which may be removed without further notice at a future date.
// Please
// use a non-deprecated interface with equivalent functionality instead. For
// a listing of replacement headers and interfaces, consult the file
// backward_warning.h. To disable this warning use -Wno-deprecated. [-Wcpp]

#include <cstdio>   //snprintf()
#include <cstdlib>  //abort()
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
namespace jj11 {
// 原版写法，就是现在的 unordered_multiset
void test_hash_multiset(const long &value) {
    cout << "\ntest_hash_multiset().......... \n";

    __gnu_cxx::hash_multiset<string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            //! c.insert(string(buf));
        } catch (exception &p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "随机填充耗时: "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
}
}  // namespace jj11
//---------------------------------------------------
#include <ext/hash_map>  // 同样会有警告
//...\4.9.2\include\c++\backward\backward_warning.h
//[Warning] #warning This file ... (如上個函數所言)
#include <cstdio>   //snprintf()
#include <cstdlib>  //abort()
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
namespace jj12 {
void test_hash_multimap(const long &value) {
    cout << "\ntest_hash_multimap().......... \n";

    __gnu_cxx::hash_multimap<long, string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            // c.insert(...
        } catch (exception &p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "随机填充耗时: "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
}
}  // namespace jj12
//---------------------------------------------------
#include <cstdio>   //snprintf()
#include <cstdlib>  //abort()
#include <ctime>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
namespace jj13 {
void test_set(const long &value) {
    cout << "\ntest_set().......... \n";

    set<string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.insert(string(buf));
        } catch (exception &p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "随机填充耗时: "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
    cout << "set.size()= " << c.size() << endl;
    cout << "set.max_size()= " << c.max_size() << endl;  // 214748364

    string target = get_a_target_string();
    {
        timeStart = clock();
        auto pItem = find(c.begin(), c.end(), target);  //比 c.find(...) 慢很多
        cout << "std::find(): "
             << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
             << endl;
        if (pItem != c.end())
            cout << "found, " << *pItem << endl;
        else
            cout << "not found! " << endl;
    }

    {
        timeStart = clock();
        auto pItem = c.find(target);  //比 std::find(...) 快很多
        cout << "c.find(): "
             << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
             << endl;
        if (pItem != c.end())
            cout << "found, " << *pItem << endl;
        else
            cout << "not found! " << endl;
    }
}
}  // namespace jj13
//---------------------------------------------------
#include <cstdio>   //snprintf()
#include <cstdlib>  //abort()
#include <ctime>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
namespace jj14 {
void test_map(const long &value) {
    cout << "\ntest_map().......... \n";

    map<long, string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c[i] = string(buf);
        } catch (exception &p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "随机填充耗时: "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
    cout << "map.size()= " << c.size() << endl;
    cout << "map.max_size()= " << c.max_size() << endl;

    long target = get_a_target_long();
    timeStart = clock();
    auto pItem = c.find(target);
    cout << "c.find(): "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms."
         << endl;
    if (pItem != c.end())
        cout << "found, value=" << (*pItem).second << endl;
    else
        cout << "not found! " << endl;

    c.clear();
}
}  // namespace jj14
//---------------------------------------------------
#include <cstdio>   //snprintf()
#include <cstdlib>  //abort()
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>
namespace jj15 {
void test_unordered_set(const long &value) {
    cout << "\ntest_unordered_set().......... \n";

    unordered_set<string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.insert(string(buf));
        } catch (exception &p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "随机填充耗时: "
         << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms." << endl;
    cout << "unordered_set.size()= " << c.size() << endl;
    cout << "unordered_set.max_size()= " << c.max_size() << endl;  // 357913941
    cout << "unordered_set.bucket_count()= " << c.bucket_count() << endl;
    cout << "unordered_set.load_factor()= " << c.load_factor() << endl;
    cout << "unordered_set.max_load_factor()= " << c.max_load_factor() << endl;
    cout << "unordered_set.max_bucket_count()= " << c.max_bucket_count()
         << endl;
    for (unsigned i = 0; i < 20; ++i) {
        cout << "bucket #" << i << " has " << c.bucket_size(i)
             << " elements.\n";
    }

    string target = get_a_target_string();
    {
        timeStart = clock();
        auto pItem = find(c.begin(), c.end(), target);  //比 c.find(...) 慢很多
        cout << "std::find(): "
             << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms." << endl;
        if (pItem != c.end())
            cout << "found, " << *pItem << endl;
        else
            cout << "not found! " << endl;
    }

    {
        timeStart = clock();
        auto pItem = c.find(target);  //比 std::find(...) 快很多
        cout << "c.find(): "
             << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms." << endl;
        if (pItem != c.end())
            cout << "found, " << *pItem << endl;
        else
            cout << "not found! " << endl;
    }
}
}  // namespace jj15
//---------------------------------------------------
#include <cstdio>   //snprintf()
#include <cstdlib>  //abort()
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
namespace jj16 {
void test_unordered_map(const long &value) {
    cout << "\ntest_unordered_map().......... \n";

    unordered_map<long, string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c[i] = string(buf);
        } catch (exception &p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "随机填充耗时: " << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms." << endl;
    cout << "unordered_map.size()= " << c.size() << endl;  // 357913941
    cout << "unordered_map.max_size()= " << c.max_size() << endl;

    long target = get_a_target_long();
    timeStart = clock();
    cout << "map 不能用 std::find()!!" << endl;
    // auto pItem = find(c.begin(), c.end(), target);	//map 不適用 std::find()
    auto pItem = c.find(target);

    cout << "c.find(): " << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms." << endl;
    if (pItem != c.end())
        cout << "found, value=" << (*pItem).second << endl;
    else
        cout << "not found! " << endl;
}
}  // namespace jj16
//---------------------------------------------------
#include <cstdio>   //snprintf()
#include <cstdlib>  //abort()
#include <ctime>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
namespace jj17 {
void test_stack(const long &value) {
    cout << "\ntest_stack().......... \n";

    stack<string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.push(string(buf));
        } catch (exception &p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "随机填充耗时: " << (clock() - timeStart) << endl;
    cout << "stack.size()= " << c.size() << endl;
    cout << "stack.top()= " << c.top() << endl;
    c.pop();
    cout << "弹栈：\nstack.size()= " << c.size() << endl;
    cout << "stack.top()= " << c.top() << endl;

    {
        cout << "\n设置底层容器为 list " << endl;
        stack<string, list<string>> c;
        for (long i = 0; i < 10; ++i) {
            snprintf(buf, 10, "%d", rand());
            c.push(string(buf));
        }
        cout << "stack.size()= " << c.size() << endl;
        cout << "stack.top()= " << c.top() << endl;
        c.pop();
        cout << "弹栈：\nstack.size()= " << c.size() << endl;
        cout << "stack.top()= " << c.top() << endl;
    }

    {
        cout << "\n设置底层容器为 vector " << endl;
        stack<string, vector<string>> c;  
        for (long i = 0; i < 10; ++i) {
            snprintf(buf, 10, "%d", rand());
            c.push(string(buf));
        }
        cout << "stack.size()= " << c.size() << endl;
        cout << "stack.top()= " << c.top() << endl;
        c.pop();
        cout << "弹栈：\nstack.size()= " << c.size() << endl;
        cout << "stack.top()= " << c.top() << endl;
    }

    {
        cout << "\n设置底层容器为 set 可以定义，但是无法使用" << endl;
        cout << "" << endl;
        stack<string, set<string>> c; 
        // for(long i=0; i< 10; ++i) {
        //     snprintf(buf, 10, "%d", rand());
        //     c.push(string(buf));
        // }
        // cout << "stack.size()= " << c.size() << endl;
        // cout << "stack.top()= " << c.top() << endl;
        // c.pop();
        // cout << "stack.size()= " << c.size() << endl;
        // cout << "stack.top()= " << c.top() << endl;

        //[Error] 'class std::set<std::basic_string<char> >' has no member named 'push_back'
        //[Error] 'class std::set<std::basic_string<char> >' has no member named 'back'
        //[Error] 'class std::set<std::basic_string<char> >' has no member named 'pop_back'
    }

    //! stack<string, map(string>> c5;	////以 map 為底層, 
    //! [Error] template argument 2 is invalid stack<string>::iterator ite1;  	
    //! [Error]: 'iterator' is not a member of 'std::stack<std::basic_string<char> >'
}
}  // namespace jj17

//---------------------------------------------------
#include <cstdio>   //snprintf()
#include <cstdlib>  //abort()
#include <ctime>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
namespace jj18 {
void test_queue(const long &value) {
    cout << "\ntest_queue().......... \n";

    queue<string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.push(string(buf));
        } catch (exception &p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "随机填充耗时: " << 1000 * (clock() - timeStart) / (double)CLOCKS_PER_SEC << " ms." << endl;
    cout << "queue.size()= " << c.size() << endl;
    cout << "queue.front()= " << c.front() << endl;
    cout << "queue.back()= " << c.back() << endl;
    c.pop();
    cout << "弹栈：\nqueue.size()= " << c.size() << endl;
    cout << "queue.front()= " << c.front() << endl;
    cout << "queue.back()= " << c.back() << endl;

    {
        cout << "\n设置底层容器为 list " << endl;
        queue<string, list<string>> c;
        for (long i = 0; i < 10; ++i) {
            snprintf(buf, 10, "%d", rand());
            c.push(string(buf));
        }
        cout << "queue.size()= " << c.size() << endl;
        cout << "queue.front()= " << c.front() << endl;
        cout << "queue.back()= " << c.back() << endl;
        c.pop();
        cout << "弹栈：\nqueue.size()= " << c.size() << endl;
        cout << "queue.front()= " << c.front() << endl;
        cout << "queue.back()= " << c.back() << endl;
    }

    {
        cout << "\n设置底层容器为 vector " << endl;
        queue<string, vector<string>> c;
        for (long i = 0; i < 10; ++i) {
            snprintf(buf, 10, "%d", rand());
            c.push(string(buf));
        }
        cout << "queue.size()= " << c.size() << endl;
        cout << "queue.front()= " << c.front() << endl;
        cout << "queue.back()= " << c.back() << endl;
        //! c.pop();  //[Error] 'class std::vector<std::basic_string<char> >'
        //! has no member named 'pop_front'
    }

    {
        cout << "\n设置底层容器为 set 可以定义，但是无法使用" << endl;
        queue<string, set<string>> c;  
        // for(long i=0; i< 10; ++i) {
        //     snprintf(buf, 10, "%d", rand());
        //     c.push(string(buf));
        // }
        // cout << "queue.size()= " << c.size() << endl;
        // cout << "queue.front()= " << c.front() << endl;
        // cout << "queue.back()= " << c.back() << endl;
        // c.pop();
        // cout << "queue.size()= " << c.size() << endl;
        // cout << "queue.front()= " << c.front() << endl;
        // cout << "queue.back()= " << c.back() << endl;
        //[Error] 'class std::set<std::basic_string<char> >' has no member named 'push_back'
        //[Error] 'class std::set<std::basic_string<char> >' has no member named 'front'
        //[Error] 'class std::set<std::basic_string<char> >' has no member named 'pop_front'
    }

    //! queue<string, map<string>> c5;	//以 map 為底層, [Error] template
    //! argument
    //! 2 is invalid queue<string>::iterator ite1;  	//[Error] 'iterator' is
    //! not a member of 'std::queue<std::basic_string<char> >'
}
}  // namespace jj18


//---------------------------------------------------
#include <algorithm>  //find()
#include <cstddef>
#include <cstdio>   //snprintf()
#include <cstdlib>  //abort()
#include <ctime>
#include <iostream>
#include <list>
#include <memory>  //內含 std::allocator
#include <stdexcept>
#include <string>

#ifdef __GNUC__
// 欲使用 std::allocator 以外的 allocator, 得自行 #include <ext\...>
// #include <ext/array_allocator.h>
#include <ext/bitmap_allocator.h>
#include <ext/debug_allocator.h>
#include <ext/malloc_allocator.h>
#include <ext/mt_allocator.h>
#include <ext/new_allocator.h>
#include <ext/pool_allocator.h>
#endif

namespace jj20 {
// pass A object to function template impl()，
//而 A 本身是個 class template, 帶有 type parameter T,
//那麼有無可能在 impl() 中抓出 T, 創建一個 list<T, A<T>> object?
//以下先暫時迴避上述疑問.

void test_list_with_special_allocator() {
#ifdef __GNUC__
    cout << "\ntest_list_with_special_allocator().......... \n";

    // 不能在 switch case 中宣告，只好下面這樣
    list<string, allocator<string>> c1;                    // 3140
    list<string, __gnu_cxx::malloc_allocator<string>> c2;  // 3110
    list<string, __gnu_cxx::new_allocator<string>> c3;     // 3156
    list<string, __gnu_cxx::__pool_alloc<string>> c4;      // 4922
    list<string, __gnu_cxx::__mt_alloc<string>> c5;        // 3297
    list<string, __gnu_cxx::bitmap_allocator<string>> c6;  // 4781

    int choice;
    long value;

    cout << "select: "
         << " (1) std::allocator "
         << " (2) malloc_allocator "
         << " (3) new_allocator "
         << " (4) __pool_alloc "
         << " (5) __mt_alloc "
         << " (6) bitmap_allocator ";

    cin >> choice;
    if (choice != 0) {
        cout << "how many elements: ";
        cin >> value;
    }

    char buf[10];
    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i) {
        try {
            snprintf(buf, 10, "%ld", i);
            switch (choice) {
                case 1:
                    c1.push_back(string(buf));
                    break;
                case 2:
                    c2.push_back(string(buf));
                    break;
                case 3:
                    c3.push_back(string(buf));
                    break;
                case 4:
                    c4.push_back(string(buf));
                    break;
                case 5:
                    c5.push_back(string(buf));
                    break;
                case 6:
                    c6.push_back(string(buf));
                    break;
                default:
                    break;
            }
        } catch (exception &p) {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "a lot of push_back(), milli-seconds : " << (clock() - timeStart)
         << endl;

    // test all allocators' allocate() & deallocate();
    int *p;
    allocator<int> alloc1;
    p = alloc1.allocate(1);
    // 需要指定分配的空间容量！这点不方便使用；
    alloc1.deallocate(p, 1);

    __gnu_cxx::malloc_allocator<int> alloc2;
    p = alloc2.allocate(1);
    alloc2.deallocate(p, 1);

    __gnu_cxx::new_allocator<int> alloc3;
    p = alloc3.allocate(1);
    alloc3.deallocate(p, 1);

    __gnu_cxx::__pool_alloc<int> alloc4;
    p = alloc4.allocate(2);
    alloc4.deallocate(p, 2);

    __gnu_cxx::__mt_alloc<int> alloc5;
    p = alloc5.allocate(1);
    alloc5.deallocate(p, 1);

    __gnu_cxx::bitmap_allocator<int> alloc6;
    p = alloc6.allocate(3);
    alloc6.deallocate(p, 3);
#endif
}
}  // namespace jj20

// int main() {
//     jj20::test_list_with_special_allocator();
//     return 0;
// }
