#include <iostream>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include <unistd.h>

using namespace std;

int main() {
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        cout << "Ошибка , не удалось подключиться к экрану." << endl;
        return 1;
    }
    int delayMs;
    cout << "Введи частоту кликов в миллисекундах" << endl;
    cin >> delayMs;
    KeyCode keyX = XKeysymToKeycode(display, XK_x);
    KeyCode keyEsc = XKeysymToKeycode(display, XK_Escape);

    cout << "Кликер запущен!" << endl;
    cout << "Частота установлена на " << delayMs << " миллисекунд." << endl;
    cout << "Нажми 'x' в английской раскладке для Старта/Стопа." << endl;
    cout << "Нажми 'Esc' для выхода." << endl;

    bool isClicking = false;
    char keys_return[32];
    while (true) {
        XQueryKeymap(display, keys_return);
        if (keys_return[keyEsc / 8] & (1 << (keyEsc % 8))) {
            cout << "Выход из программы." << endl;
            break;
        
        }
        if (keys_return[keyX / 8] & (1 << (keyX % 8))) {
            isClicking = !isClicking;

            if (isClicking) cout << "Кликаю!" << endl;
            else cout << "Останавливаюсь!" << endl;
            
            usleep(200000);
        }
        if (isClicking) {
            XTestFakeButtonEvent(display, 1, True, 0);
            XTestFakeButtonEvent(display, 1, False, 0);
            XFlush(display);
            usleep(delayMs * 1000);
        } else {
            usleep(10000);
        }
    }
    XCloseDisplay(display);
    return 0;
}