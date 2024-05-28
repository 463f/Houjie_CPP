#include "0-useContainers.hpp"
using namespace std;
const long ASIZE = 500000L;

namespace jj25 {
void test_components_sizeof() {
    cout << "\ntest_components_size().......... \n";

    // containers
    cout << "sizeof(array<int,100>)= " << sizeof(array<int, 100>)
         << endl;                                                    // 400
    cout << "sizeof(vector<int>)= " << sizeof(vector<int>) << endl;  // 12
    cout << "sizeof(list<int>)= " << sizeof(list<int>) << endl;      // 8
    cout << "sizeof(forward_list<int>)= " << sizeof(forward_list<int>)
         << endl;                                                        // 4
    cout << "sizeof(deque<int>)= " << sizeof(deque<int>) << endl;        // 40
    cout << "sizeof(stack<int>)= " << sizeof(stack<int>) << endl;        // 40
    cout << "sizeof(queue<int>)= " << sizeof(queue<int>) << endl;        // 40
    cout << "sizeof(set<int>)= " << sizeof(set<int>) << endl;            // 24
    cout << "sizeof(map<int,int>)= " << sizeof(map<int, int>) << endl;   // 24
    cout << "sizeof(multiset<int>)= " << sizeof(multiset<int>) << endl;  // 24
    cout << "sizeof(multimap<int,int>)= " << sizeof(multimap<int, int>)
         << endl;  // 24
    cout << "sizeof(unordered_set<int>)= " << sizeof(unordered_set<int>)
         << endl;  // 28
    cout << "sizeof(unordered_map<int,int>)= "
         << sizeof(unordered_map<int, int>) << endl;  // 28
    cout << "sizeof(unordered_multiset<int>)= "
         << sizeof(unordered_multiset<int>) << endl;  // 28
    cout << "sizeof(unordered_multimap<int,int>)= "
         << sizeof(unordered_multimap<int, int>) << endl;  // 28
    cout << "sizeof(_Rb_tree<...>)= "
         << sizeof(_Rb_tree<int, int, _Identity<int>, less<int>>)
         << endl;  // 24

    // iterators
    cout << "sizeof(array<int,100>::iterator)= "
         << sizeof(array<int, 100>::iterator) << endl;  // 4
    cout << "sizeof(vector<int>::iterator)= " << sizeof(vector<int>::iterator)
         << endl;  // 4
    cout << "sizeof(list<int>::iterator)= " << sizeof(list<int>::iterator)
         << endl;  // 4
    cout << "sizeof(forward_list<int>::iterator)= "
         << sizeof(forward_list<int>::iterator) << endl;  // 4
    cout << "sizeof(deque<int>::iterator)= " << sizeof(deque<int>::iterator)
         << endl;  // 16
    //! cout << "sizeof(stack<int>::iterator)= " << sizeof(stack<int>::iterator)
    //! << endl;	//[Error] 'iterator' is not a member of 'std::stack<int>'
    //! cout
    //! << "sizeof(queue<int>::iterator)= " << sizeof(queue<int>::iterator) <<
    //! endl;	//[Error] 'iterator' is not a member of 'std::queue<int>
    cout << "sizeof(set<int>::iterator)= " << sizeof(set<int>::iterator)
         << endl;  // 4
    cout << "sizeof(map<int,int>::iterator)= "
         << sizeof(map<int, int>::iterator) << endl;  // 4
    cout << "sizeof(multiset<int>::iterator)= "
         << sizeof(multiset<int>::iterator) << endl;  // 4
    cout << "sizeof(multimap<int,int>::iterator)= "
         << sizeof(multimap<int, int>::iterator) << endl;  // 4
    cout << "sizeof(unordered_set<int>::iterator)= "
         << sizeof(unordered_set<int>::iterator) << endl;  // 4
    cout << "sizeof(unordered_map<int,int>::iterator)= "
         << sizeof(unordered_map<int, int>::iterator) << endl;  // 4
    cout << "sizeof(unordered_multiset<int>::iterator)= "
         << sizeof(unordered_multiset<int>::iterator) << endl;  // 4
    cout << "sizeof(unordered_multimap<int,int>::iterator)= "
         << sizeof(unordered_multimap<int, int>::iterator) << endl;  // 4
    cout << "sizeof(_Rb_tree<...>::iterator)= "
         << sizeof(_Rb_tree<int, int, _Identity<int>, less<int>>::iterator)
         << endl;  // 4

    // allocators
    cout << "sizeof(      std::allocator<string>)="
         << sizeof(std::allocator<string>) << endl;  // 1 (理論值 0)
    cout << "sizeof(__gnu_cxx::malloc_allocator<string>)= "
         << sizeof(__gnu_cxx::malloc_allocator<string>)
         << endl;  // 1 (理論值 0)
    cout << "sizeof(__gnu_cxx::new_allocator<string>)= "
         << sizeof(__gnu_cxx::new_allocator<string>) << endl;  // 1 (理論值 0)
    cout << "sizeof(__gnu_cxx::__pool_alloc<string>)= "
         << sizeof(__gnu_cxx::__pool_alloc<string>) << endl;  // 1 (理論值 0)
    cout << "sizeof(__gnu_cxx::bitmap_allocator<string>)= "
         << sizeof(__gnu_cxx::bitmap_allocator<string>)
         << endl;  // 1 (理論值 0)
    cout << "sizeof(__gnu_cxx::__mt_alloc<string>)= "
         << sizeof(__gnu_cxx::__mt_alloc<string>) << endl;  // 1 (理論值 0)
    cout << "sizeof(__gnu_cxx::array_allocator<int>)= "
         //  << sizeof(__gnu_cxx::array_allocator<int>)
         << endl;  // 8
                   //==> 因為它有一個 ptr 指向 array 和一個 size_t 表示消耗到
                   // array 哪兒
    cout << "sizeof(__gnu_cxx::debug_allocator<std::allocator<double>>)= "
         << sizeof(__gnu_cxx::debug_allocator<std::allocator<double>>)
         << endl;  // 8
}
}  // namespace jj25
//---------------------------------------------------
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
namespace jj30 {
void test_all_components() {
    cout << "\ntest_all_components().......... \n";

    int ia[7] = {27, 210, 12, 47, 109, 83, 40};
    vector<int, allocator<int>> vi(ia, ia + 7);

    cout << count_if(vi.begin(), vi.end(),
                     not1(bind2nd(less<int>(), 40)));  // 5
    cout << endl;
}
}  // namespace jj30
//---------------------------------------------------
#include <functional>
#include <iostream>
#include <set>
namespace jj31 {
void test_Rb_tree() {
    // G2.9 vs. G2.9 :
    // rb_tree => _Rb_tree,
    // identity<> => _Identity<>
    // insert_unique() => _M_insert_unique()
    // insert_equal() => _M_insert_equal()

    cout << "\ntest_Rb_tree().......... \n";

    _Rb_tree<int, int, _Identity<int>, less<int>> itree;
    cout << itree.empty() << endl;  // 1
    cout << itree.size() << endl;   // 0

    itree._M_insert_unique(3);
    itree._M_insert_unique(8);
    itree._M_insert_unique(5);
    itree._M_insert_unique(9);
    itree._M_insert_unique(13);
    itree._M_insert_unique(5);       // no effect, since using insert_unique().
    cout << itree.empty() << endl;   // 0
    cout << itree.size() << endl;    // 5
    cout << itree.count(5) << endl;  // 1

    itree._M_insert_equal(5);
    itree._M_insert_equal(5);
    cout << itree.size() << endl;    // 7, since using insert_equal().
    cout << itree.count(5) << endl;  // 3
}
}  // namespace jj31
//---------------------------------------------------
#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
namespace jj32 {
/*
//下面的 hash<string>, G2.9需要，G4.9不需要，因為 G4.9 basic_string.h 已提供
template<> struct hash<string>
{
  size_t operator()(string s) const {
      return __stl_hash_string(s.c_str());
  }
};
*/

void test_Hashtable() {
    cout << "\ntest_Hashtable().......... \n";

    // hashtable 的模板參數個數 6=>10 (增加 hash policy 吧大概)
    // 所以 G2.9的應用修改起來很麻煩。不改了, 以後再說.
}
}  // namespace jj32
//---------------------------------------------------
#include <iostream>  // std::cout
#include <iterator>  // std::iterator_traits
#include <typeinfo>  // typeid
namespace jj33 {
void _display_category(random_access_iterator_tag) {
    cout << "random_access_iterator" << endl;
}
void _display_category(bidirectional_iterator_tag) {
    cout << "bidirectional_iterator" << endl;
}
void _display_category(forward_iterator_tag) {
    cout << "forward_iterator" << endl;
}
void _display_category(output_iterator_tag) {
    cout << "output_iterator" << endl;
}
void _display_category(input_iterator_tag) { cout << "input_iterator" << endl; }

template <typename I>
void display_category(I itr) {
    typename iterator_traits<I>::iterator_category cagy;
    _display_category(cagy);

    cout << "typeid(itr).name()= " << typeid(itr).name() << endl << endl;
    // The output depends on library implementation.
    // The particular representation pointed by the
    // returned valueis implementation-defined,
    // and may or may not be different for different types.
}

void test_iterator_category() {
    cout << "\ntest_iterator_category().......... \n";

    display_category(array<int, 10>::iterator());
    display_category(vector<int>::iterator());
    display_category(list<int>::iterator());
    display_category(forward_list<int>::iterator());
    display_category(deque<int>::iterator());

    display_category(set<int>::iterator());
    display_category(map<int, int>::iterator());
    display_category(multiset<int>::iterator());
    display_category(multimap<int, int>::iterator());
    display_category(unordered_set<int>::iterator());
    display_category(unordered_map<int, int>::iterator());
    display_category(unordered_multiset<int>::iterator());
    display_category(unordered_multimap<int, int>::iterator());

    display_category(istream_iterator<int>());
    display_category(ostream_iterator<int>(cout, ""));
}
}  // namespace jj33
//---------------------------------------------------
#include <functional>  // std::minus
#include <iostream>    // std::cout
#include <numeric>     // std::accumulate
namespace jj34 {
int myfunc(int x, int y) { return x + 2 * y; }

struct myclass {
    int operator()(int x, int y) { return x + 3 * y; }
} myobj;

void test_accumulate() {
    cout << "\ntest_accumulate().......... \n";
    int init = 100;
    int nums[] = {10, 20, 30};

    cout << "using default accumulate: ";
    cout << accumulate(nums, nums + 3, init);  // 160
    cout << '\n';

    cout << "using functional's minus: ";
    cout << accumulate(nums, nums + 3, init, minus<int>());  // 40
    cout << '\n';

    cout << "using custom function: ";
    cout << accumulate(nums, nums + 3, init, myfunc);  // 220
    cout << '\n';

    cout << "using custom object: ";
    cout << accumulate(nums, nums + 3, init, myobj);  // 280
    cout << '\n';
}
}  // namespace jj34
//---------------------------------------------------
#include <algorithm>  // std::for_each
#include <iostream>   // std::cout
#include <vector>     // std::vector
namespace jj35 {
void myfunc(int i) { cout << ' ' << i; }

struct myclass {
    void operator()(int i) { cout << ' ' << i; }
} myobj;

void test_for_each() {
    cout << "\ntest_for_each().......... \n";

    vector<int> myvec;
    myvec.push_back(10);
    myvec.push_back(20);
    myvec.push_back(30);

    for_each(myvec.begin(), myvec.end(), myfunc);
    cout << endl;  // output: 10 20 30

    for_each(myvec.begin(), myvec.end(), myobj);
    cout << endl;  // output: 10 20 30

    // since C++11, range-based for- statement
    for (auto &elem : myvec) elem += 5;

    for (auto elem : myvec) cout << ' ' << elem;  // output: 15 25 35
}
}  // namespace jj35
//---------------------------------------------------
#include <algorithm>  // std::sort
#include <iostream>   // std::cout
#include <vector>     // std::vector
namespace jj36 {
bool myfunc(int i, int j) { return (i < j); }

struct myclass {
    bool operator()(int i, int j) { return (i < j); }
} myobj;

void test_sort() {
    cout << "\ntest_sort().......... \n";

    int myints[] = {32, 71, 12, 45, 26, 80, 53, 33};
    vector<int> myvec(myints, myints + 8);  // 32 71 12 45 26 80 53 33

    // using default comparison (operator <):
    sort(myvec.begin(), myvec.begin() + 4);  //(12 32 45 71)26 80 53 33

    // using function as comp
    sort(myvec.begin() + 4, myvec.end(), myfunc);  // 12 32 45 71(26 33 53 80)

    // using object as comp
    sort(myvec.begin(), myvec.end(), myobj);  //(12 26 32 33 45 53 71 80)

    // print out content:
    cout << "\nmyvec contains:";
    for (auto elem : myvec)   // C++11 range-based for statement
        cout << ' ' << elem;  // output: 12 26 32 33 45 53 71 80

    // using reverse iterators and default comparison (operator <):
    sort(myvec.rbegin(), myvec.rend());

    // print out content:
    cout << "\nmyvec contains:";
    for (auto elem : myvec)   // C++11 range-based for statement
        cout << ' ' << elem;  // output: 80 71 53 45 33 32 26 12

    // using explicitly default comparison (operator <):
    sort(myvec.begin(), myvec.end(), less<int>());

    // print out content:
    cout << "\nmyvec contains:";
    for (auto elem : myvec)   // C++11 range-based for statement
        cout << ' ' << elem;  // output: 12 26 32 33 45 53 71 80

    // using another comparision criteria (operator >):
    sort(myvec.begin(), myvec.end(), greater<int>());

    // print out content:
    cout << "\nmyvec contains:";
    for (auto elem : myvec)   // C++11 range-based for statement
        cout << ' ' << elem;  // output: 80 71 53 45 33 32 26 12
}
}  // namespace jj36
//---------------------------------------------------
#include <cstdlib>  //rand() and RAND_MAX
namespace jjxx {
void test_containers() {
    int choice;
    long value;

    srand(time(NULL));

    cout << "\n\ntest_containers()......... \n";
    cout << "select: \n";
    cout << "       (1)array (2)vector (3)list (4)forward_list (5)deque "
            "(6)multiset \n";
    cout << "       (7)multimap (8)unordered_multiset (9)unordered_multimap "
            "(10)slist \n";
    cout << "       (11)hash_multiset (12)hash_multimap (13)set (14)map "
            "(15)unordered_set \n";
    cout << "       (16)unordered_map (17)stack (18)queue \n";
    cout << " (2),(3),(5),(6),(8) will test also moveable elements. \n";
    cin >> choice;
    if (choice != 1) {  // 1 ==> array, use ASIZE
        cout << "how many elements: ";
        cin >> value;
    }

    switch (choice) {
        case 1:
            jj01::test_array();
            break;
        case 2:
            jj02::test_vector(value);
            // jj02::test_vector_with_move(value);
            break;
        case 3:
            jj03::test_list(value);
            break;
        case 4:
            jj04::test_forward_list(value);
            break;
        case 5:
            jj05::test_deque(value);
            break;
        case 6:
            jj06::test_multiset(value);
            break;
        case 7:
            jj07::test_multimap(value);
            break;
        case 8:
            jj08::test_unordered_multiset(value);
            break;
        case 9:
            jj09::test_unordered_multimap(value);
            break;
        case 10:
            jj10::test_slist(value);
            break;
        case 11:
            jj11::test_hash_multiset(value);
            break;
        case 12:
            jj12::test_hash_multimap(value);
            break;
        case 13:
            jj13::test_set(value);
            break;
        case 14:
            jj14::test_map(value);
            break;
        case 15:
            jj15::test_unordered_set(value);
            break;
        case 16:
            jj16::test_unordered_map(value);
            break;
        case 17:
            jj17::test_stack(value);
            break;
        case 18:
            jj18::test_queue(value);
            break;
        default:
            break;
    }
}
}  // namespace jjxx
//---------------------------------------------------
#include <cstdlib>  //rand() and RAND_MAX
int main(int argc, char **argv) {
    // jj00::test_misc();
    // jj01::test_array();
    // jj02::test_vector(ASIZE);
    // jj03::test_list(ASIZE);
    // jj04::test_forward_list(ASIZE);
    // jj05::test_deque(ASIZE);
    // jj06::test_multiset(ASIZE);
    // jj07::test_multimap(ASIZE);
    // jj08::test_unordered_multiset(ASIZE);
    // jj09::test_unordered_multimap(ASIZE);
    // jj10::test_slist(ASIZE);
    // jj11::test_hash_multiset(ASIZE);
    // jj12::test_hash_multimap(ASIZE);
    // jj13::test_set(ASIZE);
    // jj14::test_map(ASIZE);
    // jj15::test_unordered_set(ASIZE);
    // jj16::test_unordered_map(ASIZE);
    // jj17::test_stack(ASIZE);
    // jj18::test_queue(ASIZE);

    // jjxx::test_containers();

    // jj20::test_list_with_special_allocator();
    // jj25::test_components_sizeof();
    // jj30::test_all_components();
    // jj31::test_Rb_tree();
    // jj32::test_Hashtable();

    // jj33::test_iterator_category();
    // jj34::test_accumulate();
    // jj35::test_for_each();
    // jj36::test_sort();

    return 0;
}