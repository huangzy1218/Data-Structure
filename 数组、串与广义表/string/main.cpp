#include "String.h"

int main()
{
    String s;
    cout << "ÊäÈë£º" << endl;
    cin >> s;
    cout << "Êä³ö£º" << endl;
    cout << s << endl;
    cout << "³¤¶È£º" << endl;
    cout << s.length() << endl;
    cout << "×Ö·û´®Æ¥Åä£º" << endl;
    cout << "ÇëÊäÈëÆ¥Åä´®£º" << endl;
    String pattern;
    cin >> pattern;
    cout << s.find(pattern) << endl;

    return 0;
}