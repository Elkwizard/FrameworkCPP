#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <windows.h>

#pragma comment(lib, "User32.lib")

namespace Utils {
    float CHAR_RATIO = 0.48f;
    short CHAR_WIDTH = 5;
    namespace Print {
        class Printable {
            private:
                std::string str;
            public:
                Printable() { }
                Printable(std::string str) {
                    this->str = str;
                }
                Printable(char str) {
                    this->str = str + "";
                }
                Printable(double str) {
                    this->str = std::to_string(str);
                }
                Printable(int str) {
                    this->str = std::to_string(str);
                }
                Printable(short str) {
                    this->str = std::to_string(str);
                }
                Printable(long str) {
                    this->str = std::to_string(str);
                }
                Printable(float str) {
                    this->str = std::to_string(str);
                }
                std::string getString() {
                    return this->str;
                }
                Utils::Print::Printable operator + (Utils::Print::Printable p) {
                    return {p.str + this->str};
                }
                Utils::Print::Printable operator + (char p) {
                    return {Utils::Print::Printable(p) + (*this)};
                }
                Utils::Print::Printable operator + (double p) {
                    return {Utils::Print::Printable(p) + (*this)};
                }
                Utils::Print::Printable operator + (int p) {
                    return {Utils::Print::Printable(p) + (*this)};
                }
                Utils::Print::Printable operator + (short p) {
                    return {Utils::Print::Printable(p) + (*this)};
                }
                Utils::Print::Printable operator + (long p) {
                    return {Utils::Print::Printable(p) + (*this)};
                }
                Utils::Print::Printable operator + (float p) {
                    return {Utils::Print::Printable(p) + (*this)};
                }
                Utils::Print::Printable operator + (std::string p) {
                    return {Utils::Print::Printable(p) + (*this)};
                }
                operator std::string() {
                    return this->getString();
                }
                Utils::Print::Printable toUpperCase() {
                    std::string str = "";
                    for (char c : this->str) {
                        str += (char)std::toupper(c);
                    }
                    Utils::Print::Printable p{str};
                    return p;
                }
                Utils::Print::Printable toLowerCase() {
                    std::string str = "";
                    for (char c : this->str) {
                        str += (char)std::tolower(c);
                    }
                    Utils::Print::Printable p{str};
                    return p;

                }
        };
        std::vector<Utils::Print::Printable> prints { };
        Utils::Print::Printable concat { "" };
        std::string print(std::string msg) {
            std::cout << msg;
            prints.push_back(Utils::Print::Printable(msg));
            return msg;
        }
        char print(char msg) {
            std::cout << msg;
            prints.push_back(Utils::Print::Printable(msg));
            return msg;
        }
        int print(int msg) {
            std::cout << msg;
            prints.push_back(Utils::Print::Printable((double)msg));
            return msg;
        }
        short print(short msg) {
            std::cout << msg;
            prints.push_back(Utils::Print::Printable((double)msg));
            return msg;
        }
        long print(long msg) {
            std::cout << msg;
            prints.push_back(Utils::Print::Printable((double)msg));
            return msg;
        }
        float print(float msg) {
            std::cout << msg;
            prints.push_back(Utils::Print::Printable((double)msg));
            return msg;
        }
        double print(double msg) {
            std::cout << msg;
            prints.push_back(Utils::Print::Printable((double)msg));
            return msg;
        }
        Utils::Print::Printable print(Utils::Print::Printable msg) {
            std::cout << msg.getString();
            prints.push_back(msg);
            return msg;
        }
        void clear() {
            Utils::Print::prints.clear();
        }
        std::string getCurrentOutput() {
            std::string result = "";
            for (Utils::Print::Printable p : Utils::Print::prints) {
                result += p.getString();
            }
            return result;
        }
    }
    namespace Input {
        namespace Keyboard {
            std::map<std::string, int> keyCodes {
                { "Tab", VK_TAB }, { "Backspace", VK_BACK }, { "Enter", VK_RETURN }, { "Shift", VK_SHIFT }, 
                { "Control", VK_CONTROL }, { "Alt", VK_MENU }, { "Escape", VK_ESCAPE }, { " ", VK_SPACE },
                { "ArrowUp", VK_UP }, { "ArrowDown", VK_DOWN }, { "ArrowLeft", VK_LEFT }, { "ArrowRight", VK_RIGHT },
                { "0", 0x0030 }, { "1", 0x0031 }, { "2", 0x0032 }, { "3", 0x0033 }, { "4", 0x0034 }, { "5", 0x0035 },
                { "6", 0x0036 }, { "7", 0x0037 }, { "8", 0x0038 }, { "1", 0x0039 },
                { "a", 0x0041 }, { "b", 0x0042 }, { "c", 0x0043 }, { "d", 0x0044 }, { "e", 0x0045 }, { "f", 0x0046 },
                { "g", 0x0047 }, { "h", 0x0048 }, { "i", 0x0049 }, { "j", 0x004A }, { "k", 0x004B }, { "l", 0x004C },
                { "m", 0x004D }, { "n", 0x004E }, { "o", 0x004F }, { "p", 0x0050 }, { "q", 0x0051 }, { "r", 0x0052 },
                { "s", 0x0053 }, { "t", 0x0054 }, { "u", 0x0055 }, { "v", 0x0056 }, { "w", 0x0057 }, { "x", 0x0058 },
                { "y", 0x0059 }, { "z", 0x005A }
            };
            std::map<std::string, bool> currentState;
            std::map<std::string, bool> lastState;
            void updateBefore() {
                for (std::map<std::string, int>::iterator i = keyCodes.begin(); i != keyCodes.end(); i++) {
                    currentState.insert_or_assign(i->first, GetAsyncKeyState(i->second));
                }
            }
            void updateAfter() {
                for (std::map<std::string, bool>::iterator i = currentState.begin(); i != currentState.end(); i++) {
                    lastState.insert_or_assign(i->first, i->second);
                }
            }
            int getKeyCode(std::string key) {
                return keyCodes.at(key);
            }
            bool justPressed(std::string key) {
                return !lastState.at(key) && currentState.at(key);
            }
            bool justReleased(std::string key) {
                return lastState.at(key) && !currentState.at(key);
            }
            bool pressed(std::string key) {
                return currentState.at(key);
            }
            void init() {
                updateBefore();
                updateAfter();
            }
        }
        namespace Mouse {
            std::map<std::string, int> keyCodes { 
                { "Left", VK_LBUTTON }, 
                { "Right", VK_RBUTTON },
                { "Middle", VK_MBUTTON }
            };
            std::map<std::string, bool> currentState;
            std::map<std::string, bool> lastState;
            int x = 0, y = 0;
            int lastX = 0, lastY = 0;
            void updateBefore() {
                POINT m;
                GetCursorPos(&m);
                ScreenToClient(GetConsoleWindow(), &m);
                x = m.x / (CHAR_WIDTH * CHAR_RATIO);
                y = m.y / (CHAR_WIDTH * CHAR_RATIO);
                for (std::map<std::string, int>::iterator i = keyCodes.begin(); i != keyCodes.end(); i++) {
                    currentState.insert_or_assign(i->first, GetAsyncKeyState(i->second));
                }
            }
            void updateAfter() {
                for (std::map<std::string, bool>::iterator i = currentState.begin(); i != currentState.end(); i++) {
                    lastState.insert_or_assign(i->first, i->second);
                }
                lastX = x;
                lastY = y;
            }
            int getKeyCode(std::string key) {
                return keyCodes.at(key);
            }
            bool justPressed(std::string key) {
                return !lastState.at(key) && currentState.at(key);
            }
            bool justReleased(std::string key) {
                return lastState.at(key) && !currentState.at(key);
            }
            bool pressed(std::string key) {
                return currentState.at(key);
            }
            void init() {
                updateBefore();
                updateAfter();
            }
        }
    }
    namespace Graphics {
        class Vector {
            public:
                float x, y;
                Vector(float x = 0.0f, float y = 0.0f) {
                    this->x = x;
                    this->y = y;
                }
                Vector(int x = 0, int y = 0) {
                    this->x = (float)x;
                    this->y = (float)y;
                }
                Vector operator + (Vector other) {
                    return { this->x + other.x, this->y + other.y };
                }
                Vector operator + (float other) {
                    return { this->x + other, this->y + other };
                }
                Vector operator += (Vector other) {
                    this->x += other.x;
                    this->y += other.y;
                    return *this;
                }
                Vector operator += (float other) {
                    this->x += other;
                    this->y += other;
                    return *this;
                }
                Vector operator - (Vector other) {
                    return { this->x - other.x, this->y - other.y };
                }
                Vector operator - (float other) {
                    return { this->x - other, this->y - other };
                }
                Vector operator -= (Vector other) {
                    this->x -= other.x;
                    this->y -= other.y;
                    return *this;
                }
                Vector operator -= (float other) {
                    this->x -= other;
                    this->y -= other;
                    return *this;
                }
                Vector operator * (Vector other) {
                    return { this->x * other.x, this->y * other.y };
                }
                Vector operator * (float other) {
                    return { this->x * other, this->y * other };
                }
                Vector operator *= (Vector other) {
                    this->x *= other.x;
                    this->y *= other.y;
                    return *this;
                }
                Vector operator *= (float other) {
                    this->x *= other;
                    this->y *= other;
                    return *this;
                }
                Vector operator / (Vector other) {
                    return { this->x / other.x, this->y / other.y };
                }
                Vector operator / (float other) {
                    return { this->x / other, this->y / other };
                }
                Vector operator /= (Vector other) {
                    this->x /= other.x;
                    this->y /= other.y;
                    return *this;
                }
                Vector operator /= (float other) {
                    this->x /= other;
                    this->y /= other;
                    return *this;
                }
                float dot(Vector v) {
                    return this->x * v.x + this->y * v.y;
                }
                float cross(Vector v) {
                    return this->x * v.y - this->y * v.x;
                }
                float mag() {
                    return sqrt(this->x * this->x + this->y * this->y);
                }
                Vector projectOnto(Vector v) {
                    float mag = this->mag();
                    return v * this->dot(v) / (mag * mag);
                }
                Vector get() {
                    return { this->x, this->y };
                }
                Vector normal() {
                    return { -this->y, this->x };
                }
                Vector normalize() {
                    float mag = this->mag();
                    this->x /= mag;
                    this->y /= mag;
                    return *this;
                }
        };
        namespace Color {
            short BLACK = 0,
                BLUE = 0x0001,
                LIGHT_BLUE = BLUE | 0x0008,
                GREEN = 0x0002,
                LIME = GREEN | 0x0008,
                RED = 0x0004,
                LIGHT_RED = RED | 0x0008,
                PURPLE = RED | BLUE,
                LIGHT_PURPLE = PURPLE | 0x0008,
                GRAY = RED | GREEN | BLUE,
                WHITE = RED | GREEN | BLUE | 0x0008,
                YELLOW = RED | GREEN,
                LIGHT_YELLOW = YELLOW | 0x0008;
            short rgb(float red, float green, float blue) {
                int bright = (max(red, max(green, blue)) > 128) ? 0x0008 : 0x0000;
                int red_v = (red > 20) ? 0x0004 : 0x0000;
                int green_v = (green > 20) ? 0x0002 : 0x0000;
                int blue_v = (blue > 20) ? 0x0001 : 0x0000;
                return bright | red_v | green_v | blue_v;
            }
        }
        namespace Symbol {
            char FULL = 219,
                QUARTER = 177,
                HALF = 178,
                EIGHTH = 176,
                EMPTY = 32;
        }
        float PI = 3.141592653589f,
            PI2 = PI * 2,
            PI_4 = PI / 4.0f,
            PI_2 = PI / 2.0f,
            PI_3 = PI / 3.0f,
            PI_6 = PI / 6.0f;
        int width = 0, height = 0;
        int r_width = 0, r_height = 0;

        float lineWidth = 1.0f;

        class Pixel {
            public:
                char symbol = ((std::string)"\xDB").at(0);
                short color = Color::BLACK;
                short background = -1;
                Pixel(char symbol, short color, short background) {
                    this->symbol = symbol;
                    this->color = color;
                    this->background = background;
                }
                Pixel(short color, short background) {
                    this->color = color;
                    this->background = background;
                }
                Pixel(short color) {
                    this->color = color;
                }
                Pixel(char symbol, short color) {
                    this->symbol = symbol;
                    this->color = color;
                }
                Pixel(char symbol) {
                    this->symbol = symbol;
                } 
                Pixel() {

                }
                static bool sortCols(std::pair<float, short> a, std::pair<float, short> b) {
                    return a.first > b.first;
                }
                static Pixel lerp(short a, short b, float t) {
                    Pixel result { Color::BLACK };
                    float seg = 1.0f / 7.0f;
                    if (t < 2 * seg) {
                        result.color = a;
                        result.background = a;
                    } else if (t < 4 * seg) {
                        result.color = a;
                        result.background = b;
                        result.symbol = Symbol::HALF;
                    } else if (t < 6 * seg) {
                        result.color = a;
                        result.background = b;
                        result.symbol = Symbol::QUARTER;
                    } else {
                        result.color = b;
                        result.background = b;
                    }
                    return result;
                }
                static Pixel rgb(float r, float g, float b) {
                    std::vector<std::pair<float,short>> cols { { r, Color::RED }, { g, Color::GREEN }, { b, Color::BLUE } };
                    std::sort(cols.begin(), cols.end(), Pixel::sortCols);
                    std::pair<float, short> pri = cols[0], sec = cols[1];
                    short A = sec.second;
                    short B = pri.second;
                    float total = pri.first + sec.first;
                    float f = pri.first / total;
                    if (sec.first < 10.0f) {
                        f = 0.0f;
                        A = Color::BLACK;
                    }

                    Pixel result = Pixel::lerp(A, A | B, 1 - 2 * (f - 0.5));
                    if (pri.first > 128) {
                        result.color |= 0x0008;
                        result.background |= 0x0008;
                    }
                
                    return result;
                }
                short getColor() {
                    short back = this->color * 16;
                    if (this->background >= 0x0000) back = this->background * 16; 
                    return this->color | back;
                }

        };
        Pixel FULL { };
        Pixel EMPTY { Color::WHITE };

        std::vector<std::vector<Pixel>> pixels { };
        //console buffer
        HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

        void setTitle(LPCSTR title) {
            SetConsoleTitleA(title);
        }

        class Image {
            public:
                int width = 0, height = 0;
                std::vector<std::vector<Pixel>> pixels;
                Image(int width, int height) {
                    this->width = width;
                    this->height = height;
                    for (int i = 0; i < width; i++) {
                        std::vector<Pixel> row { };
                        for (int j = 0; j < height / 2; j++) row.push_back({ Color::WHITE });
                        this->pixels.push_back(row);
                    }
                }
                void actSetPixel(int x, int y, Pixel col) {
                    y /= 2;
                    if (x < 0 || x > this->width - 1 || y < 0 || y > this->height / 2 - 1) return;
                    this->pixels[x][y] = col;
                }
                void clear() {
                    for (int i = 0; i < this->width; i++) for (int j = 0; j < this->height; j++) this->pixels[i][j / 2] = { Color::WHITE };
                }
        };
        Image* embodied;
        bool embodying = false;

        void embody(Image* e) {
            embodied = e;
            embodying = true;
        }
        void unembody() {
            embodying = false;
        }

        void init(int width, int height) {
            short fw = CHAR_WIDTH;
            Graphics::width = width;
            Graphics::height = height;
            Graphics::r_width = width;
            Graphics::r_height = height / 2;
            for (int i = 0; i < width; i++) {
                std::vector<Pixel> row { };
                for (int j = 0; j < height / 2; j++) {
                    row.push_back(EMPTY);
                }
                Graphics::pixels.push_back(row);
            }

            //font
            CONSOLE_FONT_INFOEX CFI;
            CFI.cbSize = sizeof(CONSOLE_FONT_INFOEX);
            GetCurrentConsoleFontEx(console_handle, true, &CFI);
            CFI.dwFontSize = { fw, fw };
            SetCurrentConsoleFontEx(console_handle, true, &CFI);
            GetCurrentConsoleFontEx(console_handle, true, &CFI);

            //center window
            RECT screen;
            HWND fullScreenWindow = GetDesktopWindow();
            GetWindowRect(fullScreenWindow, &screen);
            int screenWidth = screen.right;
            int screenHeight = screen.bottom;
            HWND consoleWindow = GetConsoleWindow();
            int windowWidth = (Graphics::r_width + 4) * fw * CHAR_RATIO + 20;
            int windowHeight = (Graphics::r_height) * fw * CHAR_RATIO * 2 + 30;
            int x = (screenWidth - windowWidth) / 2;
            int y = (screenHeight - windowHeight) / 2;
            MoveWindow(consoleWindow, x, y, windowWidth, windowHeight, true);


            //title
            Graphics::setTitle("Graphics");
            CONSOLE_CURSOR_INFO INFO { };
            INFO.bVisible = false;
            INFO.dwSize = 1;
            SetConsoleCursorInfo(console_handle, &INFO);
            DWORD prev;
            GetConsoleMode(console_handle, &prev);
            SetConsoleMode(console_handle, (~ENABLE_QUICK_EDIT_MODE | ENABLE_PROCESSED_INPUT | ENABLE_EXTENDED_FLAGS));
        }
        namespace Transform {
            class Transformation {
                public:
                    Transformation() { };
                    virtual Vector transform(Vector p) {
                        return { 0.0f, 0.0f };
                    }  
            };
            class Rotation : public Transformation {
                public:
                    float v_cos, v_sin;
                    Rotation(float angle = 0.0f) : Transformation() {
                        this->v_cos = cos(angle);
                        this->v_sin = sin(angle);
                    }
                    Vector transform(Vector p) {
                        return { this->v_cos * p.x - this->v_sin * p.y, this->v_sin * p.x + this->v_cos * p.y };
                    }
            };
            class Translation : public Transformation {
                public:
                    float v_x, v_y;
                    Translation(float x = 0.0f, float y = 0.0f) : Transformation() {
                        this->v_x = x;
                        this->v_y = y;
                    }
                    Vector transform(Vector p) {
                        return { p.x + this->v_x, p.y + this->v_y };
                    }
            };
            class Scale : public Transformation {
                public:
                    float v_x, v_y;
                    Scale(float x = 0.0f, float y = 0.0f) : Transformation() {
                        this->v_x = x;
                        this->v_y = y;
                    }
                    Vector transform(Vector p) {
                        return { p.x * this->v_x, p.y * this->v_y };
                    }
            };
            std::vector<Transform::Transformation*> transformStack { };
            Scale scale(float x, float y) {
                return { x, y };
            }
            Translation translate(float x, float y) {
                return { x, y };
            }
            Rotation rotate(float angle) {
                return { angle };
            }
            void transform(Transformation* p) {
                Graphics::Transform::transformStack.push_back(p);
            }
        }
        
        Graphics::Pixel getPixel(float x, float y) {
            int ax = (int)x;
            int ay = (int)y;
            if (ax < 0 || ax >Graphics::r_width - 1 || ay < 0 || ay > Graphics::r_height - 1) return EMPTY;
            return Graphics::pixels[ax][ay];
        }
        void noCheckSetPixel(int x, int y, Pixel col) {
            pixels[x][y] = col;
        } 
        void actSetPixel(int x, int y, Pixel col) {
            y /= 2;
            if (x < 0 || x > r_width - 1 || y < 0 || y > r_height - 1) return;
            noCheckSetPixel(x, y, col);
        }
        void setPixel(float x, float y, Graphics::Pixel col = FULL, bool line = false) {
            Vector p { x, y };
            for (Graphics::Transform::Transformation* pnt : Graphics::Transform::transformStack) {
                p = pnt->transform(p);
            }
            x = p.x;
            y = p.y;
            float lw = line ? lineWidth : 1.0f;
            float hw = lw / 2;
            for (int i = 0; i < lw; i++) for (int j = 0; j < lw; j++) {
                float Ax = x - hw + i + 1;
                float Ay = y - hw + j + 1;
                int ax = (int)Ax;
                int ay = (int)Ay;
                if (!embodying) actSetPixel(ax, ay, col);
                else embodied->actSetPixel(ax, ay, col);
            }
        }
        namespace Fill {
            void text(std::string text, float x, float y, Pixel col = FULL) {
                int len = text.size();
                for (int i = 0; i < len; i++) {
                    setPixel(x + i, y, { text.at(i), col.color, getPixel(x + i, y).color });
                }
            }
            void ellipse(float x, float y, float rx, float ry, Pixel col = FULL) {
                float radius = max(rx, ry);
                float div = PI * rx * ry;
                float dir = PI2 / div;
                std::vector<std::pair<float, float>> sin_cos { };
                for (float j = 0; j < PI2; j += dir) {
                    std::pair<float, float> pair { };
                    pair.first = cos(j);
                    pair.second = sin(j);
                    sin_cos.push_back(pair);
                }
                for (int i = 0; i < radius; i++) {
                    float circumference = rx * ry * PI;
                    float total = circumference;
                    float ratio = sin_cos.size() / total;
                    for (int j = 0; j < sin_cos.size(); j++) {
                        std::pair<float, float> pair = sin_cos[(int)(j * ratio)];
                        float ax = pair.first * rx * i / radius + x;
                        float ay = pair.second * ry * i / radius + y;
                        setPixel(ax, ay, col);
                    }
                }
            }
            void arc(float x, float y, float radius, float startAngle, float endAngle, Pixel col = FULL) {
                float div = PI * radius * radius;
                float dir = abs(endAngle - startAngle) / div;
                std::vector<std::pair<float, float>> sin_cos { };
                for (float j = 0; j < endAngle - startAngle; j += dir) {
                    std::pair<float, float> pair { };
                    pair.first = cos(j + startAngle);
                    pair.second = sin(j + startAngle);
                    sin_cos.push_back(pair);
                }
                for (int i = 0; i < radius; i++) {
                    int circumference = radius * radius * PI;
                    float total = (endAngle - startAngle) / (abs(endAngle - startAngle) / circumference);
                    float ratio = sin_cos.size() / total;
                    for (int j = 0; j < sin_cos.size(); j++) {
                        std::pair<float, float> pair = sin_cos[(int)(j * ratio)];
                        float ax = pair.first * i + x;
                        float ay = pair.second * i + y;
                        setPixel(ax, ay, col);
                    }
                }
            }
            void circle(float x, float y, float radius, Pixel col = FULL) {
                arc(x, y, radius, 0.0f, PI2, col);
            }
            void rect(float x, float y, float width, float height, Pixel col = FULL) {
                for (int i = 0; i < width; i++) for (int j = 0; j < height; j++) {
                    float ax = x + (float)i;
                    float ay = y + (float)j;
                    //test { Pixel::rgb(255*ax/200, 0.0f, 0 ) };
                    Utils::Graphics::setPixel(ax, ay, col);
                }
            }
            void triangle(Vector a, Vector b, Vector c, Pixel col = FULL) {
                Vector t_a = a - b;
                Vector t_c = c - b;
                float l_a = t_a.mag();
                float l_c = t_c.mag();
                float inc = 1.0f / (max(l_a, l_c));
                Vector d = c - a;
                float len = d.mag();
                d /= len;
                for (float i = 0; i < 1.0f; i += inc) {
                    Vector A = b + t_a * i;
                    float t_len = len * i;
                    for (int j = 0; j < t_len; j++) {
                        Vector p = A + d * j;
                        setPixel(p.x, p.y, col);
                    }
                }
            }
            void polygon(std::vector<Vector> points, Pixel col = FULL) {
                int size = points.size();
                for (int i = 1; i < size - 1; i++) {
                    Vector a = points[0];
                    Vector b = points[i];
                    Vector c = points[i + 1];
                    triangle(a, b, c, col);
                }
            }
            void image(Image f, float x = 0.0f, float y = 0.0f, float w = Graphics::width, float h = Graphics::height) {
                float wr = f.width / w;
                float hr = f.height / h;
                for (int i = 0; i < w; i++) for (int j = 0; j < h; j++) {
                    setPixel(x + i, y + j, f.pixels[(int)(i*wr)][(int)(j*hr / 2)]);
                }
            }
            void pixelOperation(Pixel operation(float, float), float sx = 0.0f, float sy = 0.0f, float sw = width, float sh = height) {
                for (int i = 0; i < sw; i++) for (int j = 0; j < sh; j++) {
                    float ax = sx + i;
                    float ay = sy + j;
                    setPixel(ax, ay, operation(ax, ay), false);
                }
            }
        }
        namespace Stroke {
            void ellipse(float x, float y, float rx, float ry, Pixel col = FULL) {
                float div = PI * rx * ry;
                float dir = PI2 / div;
                std::vector<std::pair<float, float>> sin_cos { };
                for (float j = 0; j < PI2; j += dir) {
                    std::pair<float, float> pair { };
                    pair.first = cos(j);
                    pair.second = sin(j);
                    sin_cos.push_back(pair);
                }
                for (int j = 0; j < sin_cos.size(); j++) {
                    std::pair<float, float> pair = sin_cos[j];
                    float ax = pair.first * rx + x;
                    float ay = pair.second * ry + y;
                    setPixel(ax, ay, col, true);
                }
            }
            void arc(float x, float y, float radius, float startAngle, float endAngle, Pixel col = FULL) {
                float div = PI * radius * radius;
                float dir = abs(endAngle - startAngle) / div;
                std::vector<std::pair<float, float>> sin_cos { };
                for (float j = 0; j < endAngle - startAngle; j += dir) {
                    std::pair<float, float> pair { };
                    pair.first = cos(j + startAngle);
                    pair.second = sin(j + startAngle);
                    sin_cos.push_back(pair);
                }
                for (int j = 0; j < sin_cos.size(); j++) {
                    std::pair<float, float> pair = sin_cos[j];
                    float ax = pair.first * radius + x;
                    float ay = pair.second * radius + y;
                    setPixel(ax, ay, col, true);
                }
            }
            void rect(float x, float y, float width, float height, Pixel col = FULL) {
                for (int i = 0; i < 2; i++) for (int j = 0; j < width; j++) setPixel(x + j, y + i * height, col, true);
                for (int i = 0; i < 2; i++) for (int j = 0; j < height; j++) setPixel(x + i * width, y + j, col, true);
            }
            void line(float x, float y, float x2, float y2, Pixel col = FULL) {
                float dx = x2 - x;
                float dy = y2 - y;
                float m = sqrt(dx * dx + dy * dy);
                dx /= m;
                dy /= m;
                for (int i = 0; i < m; i++) {
                    float ax = x + dx * i;
                    float ay = y + dy * i;
                    setPixel(ax, ay, col, true);
                }
            }
            void line(Vector a, Vector b, Pixel col = FULL) {
                line(a.x, a.y, b.x, b.y, col);
            }
            void triangle(Vector a, Vector b, Vector c, Pixel col = FULL) {
                line(a, b, col);
                line(b, c, col);
                line(c, a, col);
            }
            void polygon(std::vector<Vector> points, Pixel col = FULL) {
                int size = points.size();
                for (int i = 0; i < size; i++) {
                    line(points[i], points[(i + 1) % size]);
                }
            }
            void arrow(Vector a, Vector b, Pixel col = FULL) {
                line(a, b, col);
                Vector ax = (b - a).normalize();
                Vector opAx = (b - a).normal().normalize();
                Vector offAxis = opAx * lineWidth * 4;
                Fill::triangle(b + offAxis, b - offAxis, b + ax * lineWidth * 8, col);
            }
            void arrow(float x, float y, float x2, float y2, Pixel col = FULL) {
                arrow({ x, y }, { x2, y2 }, col); 
            }
            void circle(float x, float y, float radius, Pixel col = FULL) {
                arc(x, y, radius, 0.0f, PI2, col);
            }
        }
        void draw() {
            COORD bufferSize { (short)r_width, (short)r_height };
            COORD bufferStart { (short)0, (short)0 };
            SMALL_RECT write { bufferStart.X, bufferStart.Y, bufferSize.X, bufferSize.Y };
            std::vector<CHAR_INFO> chars { };
            for (int i = 0; i < bufferSize.X * bufferSize.Y; i++) chars.push_back({ });
            for (int j = 0; j < r_height; j++) for (int i = 0; i < r_width; i++) {
                Pixel pixel = getPixel((float)i, (float)j);
                CHAR_INFO ch { };
                ch.Char.AsciiChar = pixel.symbol;
                ch.Char.UnicodeChar = pixel.symbol;
                ch.Attributes = pixel.getColor();
                int inx = i + (j * bufferSize.X);
                chars[inx] = ch;
            }
            WriteConsoleOutput(console_handle, &chars[0], bufferSize, bufferStart, &write);
        }
        void clear() {
            Print::clear();
            for (int j = 0; j < r_height; j++) {
                for (int i = 0; i < r_width; i++) {
                    pixels[i][j] = EMPTY;
                }
            }
            Transform::transformStack.clear();
        }
    }
    namespace Program {
        void sleep(int ms) {
            std::this_thread::sleep_for(std::chrono::milliseconds(0));
        }
        class ProgramBase {
            private:

            public:
                int ImageDelay = 16;
                bool running = true;
                ProgramBase() { }
                virtual void init() {}
                virtual void update() {}
        };
        void start(Utils::Program::ProgramBase* program, short appliedFontSize = 5) {
            CHAR_WIDTH = appliedFontSize;
            Input::Mouse::init();
            Input::Keyboard::init();
            program->init();
            while (program->running) {
                Input::Mouse::updateBefore();
                Input::Keyboard::updateBefore();
                program->update();
                Input::Keyboard::updateAfter();
                Input::Mouse::updateAfter();
                Utils::Program::sleep(program->ImageDelay);
            }
        }
    }
};