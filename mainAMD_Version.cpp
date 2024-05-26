#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp> 
#include <iostream>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <iostream>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <d3d11.h>
#include <stdlib.h>
#include <fstream>
#include <chrono>
#include <mmsystem.h>
#include <intrin.h>
#include <tchar.h>
#include <thread>
#include <mutex>
#include <wrl/client.h>
#include "database.h"
#include "skStr.h"
#include "protect/protectmain.h"


#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d11.lib")
bool crouchControl = false;
void CreateFileSettings(const std::string& filename, int userKey2) {
    std::ofstream outputFile(filename + ".txt");
    if (outputFile.is_open()) {
        outputFile << std::hex << userKey2;
        outputFile.close();
        std::cout << std::endl;
        std::cout << "File created with the user-defined key." << std::endl;
    }
    else {
        std::cerr << "Error creating the file!" << std::endl;
    }
}
void CreateFileSettings2(const std::string& filename, double userKey2) {
    std::ofstream outputFile(filename + ".txt");
    if (outputFile.is_open()) {
        outputFile << std::hex << userKey2;
        outputFile.close();
        std::cout << std::endl;
        std::cout << "File created with the user-defined key." << std::endl;
    }
    else {
        std::cerr << "Error creating the file!" << std::endl;
    }
}


int GetPreferredKeyFromFileSettings(const std::string& filename) {
    std::ifstream inputFile(filename + ".txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 0;
    }

    int userKey;
    inputFile >> std::hex >> userKey;
    inputFile.close();
    return userKey;
}
int GetPreferredKeyFromFileSettings2(const std::string& filename) {
    std::ifstream inputFile(filename + ".txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return false; // Return false indicating failure
    }

    int userKey;
    inputFile >> std::hex >> userKey;
    inputFile.close();

    // Check if extraction was successful
    if (inputFile.fail()) {
        std::cerr << "Error reading key from file!" << std::endl;
        return false; // Return false indicating failure
    }

    return true; // Return true indicating success
}

using namespace std;
using Microsoft::WRL::ComPtr;
int status1 = 1;
int status2 = 1;
int centerX = 0;
int centerY = 0;
int colorNumber = 2; //1-Purple........2-Yellow.........3-Red
int shotMove = 2;
bool newWindowOpened = false;
int toggleShot = 0;
double pixelOriginal = 0;
bool optionFile = false;
bool sparoHook = false;
bool optionButton = false;
int aimLockInt = 1;
bool lockON = false;
int aimValue = 0;
int algoValue = 0;
bool licenseGood = true;
std::string nameFile = "buttonShoot";

std::string name = skCrypt("ExodusAssister").decrypt();
std::string ownerid = skCrypt("CIxFtyt6uw").decrypt();
std::string secret = skCrypt("32f3f717e594a79d5ea5dea54d833c3cc4d3343f337d900d5a18ad4db540c1c2").decrypt();

void createLicenseFile(const std::string& filename, const std::string& licenseText) {
    std::ofstream file("license.txt"); // Create/open the file
    if (file.is_open()) {
        file << licenseText; // Write the license text to the file
        Sleep(500);
        std::cout << std::endl << " License file created successfully: " << "license.txt" << "\n";
        Sleep(1500);
        file.close(); // Close the file
    }
    else {
        std::cerr << " Unable to create/open file '" << "license" << "'.\n";
    }
}
std::string readLicenseFromFile(const std::string& filename) {
    std::ifstream file(filename); // Open the file for reading
    std::string licenseText; // String to hold the license text

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            licenseText += line + "\n"; // Read each line and append it to licenseText
        }
        file.close(); // Close the file
    }
    else {
        std::cerr << "File '" << filename << "' not found.\n"; // Print "not found" error message
    }

    return licenseText;
}
enum class Key {
    A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
    Escape, LControl, LShift, LAlt, LSystem, RControl, RShift, RAlt, RSystem,
    Menu, LBracket, RBracket, SemiColon, Comma, Period, Quote, Slash, BackSlash,
    Tilde, Equal, Dash, Space, Return, BackSpace, Tab, PageUp, PageDown, End,
    Home, Insert, Delete, Add, Subtract, Multiply, Divide, Left, Right, Up, Down,
    Numpad0, Numpad1, Numpad2, Numpad3, Numpad4, Numpad5, Numpad6, Numpad7, Numpad8, Numpad9,
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, Pause
};

enum class MouseButton {
    Left, Right, Middle, XButton1, XButton2
};

std::string getKeyString2(Key key) {
    static std::map<Key, std::string> keyStrings = {
        {Key::A, "A"}, {Key::B, "B"}, {Key::C, "C"}, {Key::D, "D"}, {Key::E, "E"},
        {Key::F, "F"}, {Key::G, "G"}, {Key::H, "H"}, {Key::I, "I"}, {Key::J, "J"},
        {Key::K, "K"}, {Key::L, "L"}, {Key::M, "M"}, {Key::N, "N"}, {Key::O, "O"},
        {Key::P, "P"}, {Key::Q, "Q"}, {Key::R, "R"}, {Key::S, "S"}, {Key::T, "T"},
        {Key::U, "U"}, {Key::V, "V"}, {Key::W, "W"}, {Key::X, "X"}, {Key::Y, "Y"},
        {Key::Z, "Z"}, {Key::Num0, "Num0"}, {Key::Num1, "Num1"}, {Key::Num2, "Num2"},
        {Key::Num3, "Num3"}, {Key::Num4, "Num4"}, {Key::Num5, "Num5"}, {Key::Num6, "Num6"},
        {Key::Num7, "Num7"}, {Key::Num8, "Num8"}, {Key::Num9, "Num9"}, {Key::Escape, "Escape"},
        {Key::LControl, "LControl"}, {Key::LShift, "LShift"}, {Key::LAlt, "LAlt"}, {Key::LSystem, "LSystem"},
        {Key::RControl, "RControl"}, {Key::RShift, "RShift"}, {Key::RAlt, "RAlt"}, {Key::RSystem, "RSystem"},
        {Key::Menu, "Menu"}, {Key::LBracket, "LBracket"}, {Key::RBracket, "RBracket"}, {Key::SemiColon, "SemiColon"},
        {Key::Comma, "Comma"}, {Key::Period, "Period"}, {Key::Quote, "Quote"}, {Key::Slash, "Slash"},
        {Key::BackSlash, "BackSlash"}, {Key::Tilde, "Tilde"}, {Key::Equal, "Equal"}, {Key::Dash, "Dash"},
        {Key::Space, "Space"}, {Key::Return, "Return"}, {Key::BackSpace, "BackSpace"}, {Key::Tab, "Tab"},
        {Key::PageUp, "PageUp"}, {Key::PageDown, "PageDown"}, {Key::End, "End"}, {Key::Home, "Home"},
        {Key::Insert, "Insert"}, {Key::Delete, "Delete"}, {Key::Add, "Add"}, {Key::Subtract, "Subtract"},
        {Key::Multiply, "Multiply"}, {Key::Divide, "Divide"}, {Key::Left, "Left"}, {Key::Right, "Right"},
        {Key::Up, "Up"}, {Key::Down, "Down"}, {Key::Numpad0, "Numpad0"}, {Key::Numpad1, "Numpad1"},
        {Key::Numpad2, "Numpad2"}, {Key::Numpad3, "Numpad3"}, {Key::Numpad4, "Numpad4"}, {Key::Numpad5, "Numpad5"},
        {Key::Numpad6, "Numpad6"}, {Key::Numpad7, "Numpad7"}, {Key::Numpad8, "Numpad8"}, {Key::Numpad9, "Numpad9"},
        {Key::F1, "F1"}, {Key::F2, "F2"}, {Key::F3, "F3"}, {Key::F4, "F4"}, {Key::F5, "F5"},
        {Key::F6, "F6"}, {Key::F7, "F7"}, {Key::F8, "F8"}, {Key::F9, "F9"}, {Key::F10, "F10"},
        {Key::F11, "F11"}, {Key::F12, "F12"}, {Key::F13, "F13"}, {Key::F14, "F14"}, {Key::F15, "F15"},
        {Key::Pause, "Pause"}
    };

    auto it = keyStrings.find(key);
    if (it != keyStrings.end()) {
        return it->second;
    }
    return "Unknown";
}

int getKeyString3(Key button) {
    static std::map<Key, int> buttonHexValues = {
        {Key::A, 0x41}, {Key::B, 0x42}, {Key::C, 0x43}, {Key::D, 0x44}, {Key::E, 0x45},
        {Key::F, 0x46}, {Key::G, 0x47}, {Key::H, 0x48}, {Key::I, 0x49}, {Key::J, 0x4A},
        {Key::K, 0x4B}, {Key::L, 0x4C}, {Key::M, 0x4D}, {Key::N, 0x4E}, {Key::O, 0x4F},
        {Key::P, 0x50}, {Key::Q, 0x51}, {Key::R, 0x52}, {Key::S, 0x53}, {Key::T, 0x54},
        {Key::U, 0x55}, {Key::V, 0x56}, {Key::W, 0x57}, {Key::X, 0x58}, {Key::Y, 0x59},
        {Key::Z, 0x5A}, {Key::Num0, 0x30}, {Key::Num1, 0x31}, {Key::Num2, 0x32}, {Key::Num3, 0x33},
        {Key::Num4, 0x34}, {Key::Num5, 0x35}, {Key::Num6, 0x36}, {Key::Num7, 0x37}, {Key::Num8, 0x38},
        {Key::Num9, 0x39}, {Key::Escape, 0x1B}, {Key::LControl, 0xA2}, {Key::LShift, 0xA0}, {Key::LAlt, 0xA4},
        {Key::LSystem, 0x5B}, {Key::RControl, 0xA3}, {Key::RShift, 0xA1}, {Key::RAlt, 0xA5}, {Key::RSystem, 0x5C},
        {Key::Menu, 0x5D}, {Key::LBracket, 0xDB}, {Key::RBracket, 0xDD}, {Key::SemiColon, 0xBA}, {Key::Comma, 0xBC},
        {Key::Period, 0xBE}, {Key::Quote, 0xDE}, {Key::Slash, 0xBF}, {Key::BackSlash, 0xDC}, {Key::Tilde, 0xC0},
        {Key::Equal, 0xBB}, {Key::Dash, 0xBD}, {Key::Space, 0x20}, {Key::Return, 0x0D}, {Key::BackSpace, 0x08},
        {Key::Tab, 0x09}, {Key::PageUp, 0x21}, {Key::PageDown, 0x22}, {Key::End, 0x23}, {Key::Home, 0x24},
        {Key::Insert, 0x2D}, {Key::Delete, 0x2E}, {Key::Add, 0x6B}, {Key::Subtract, 0x6D}, {Key::Multiply, 0x6A},
        {Key::Divide, 0x6F}, {Key::Left, 0x25}, {Key::Right, 0x27}, {Key::Up, 0x26}, {Key::Down, 0x28},
        {Key::Numpad0, 0x60}, {Key::Numpad1, 0x61}, {Key::Numpad2, 0x62}, {Key::Numpad3, 0x63}, {Key::Numpad4, 0x64},
        {Key::Numpad5, 0x65}, {Key::Numpad6, 0x66}, {Key::Numpad7, 0x67}, {Key::Numpad8, 0x68}, {Key::Numpad9, 0x69},
        {Key::F1, 0x70}, {Key::F2, 0x71}, {Key::F3, 0x72}, {Key::F4, 0x73}, {Key::F5, 0x74},
        {Key::F6, 0x75}, {Key::F7, 0x76}, {Key::F8, 0x77}, {Key::F9, 0x78}, {Key::F10, 0x79},
        {Key::F11, 0x7A}, {Key::F12, 0x7B}, {Key::F13, 0x7C}, {Key::F14, 0x7D}, {Key::F15, 0x7E},
        {Key::Pause, 0x13},
    };

    auto it = buttonHexValues.find(button);
    if (it != buttonHexValues.end()) {
        return it->second;
    }
    return 0;
}

std::string getMouseButtonString(MouseButton button) {
    static std::map<MouseButton, std::string> buttonStrings = {
        {MouseButton::Left, "Left Mouse"},
        {MouseButton::Right, "Right Mouse"},
        {MouseButton::Middle, "Middle"},
        {MouseButton::XButton1, "XButton1"},
        {MouseButton::XButton2, "XButton2"}
    };

    auto it = buttonStrings.find(button);
    if (it != buttonStrings.end()) {
        return it->second;
    }
    return "Unknown";
}

std::pair<std::string, int> getKeyString(Key key) {
    static std::map<Key, std::pair<std::string, int>> keyStrings = {
        {Key::A, {"A", 0x41}}, {Key::B, {"B", 0x42}}, {Key::C, {"C", 0x43}}, {Key::D, {"D", 0x44}}, {Key::E, {"E", 0x45}},
        {Key::F, {"F", 0x46}}, {Key::G, {"G", 0x47}}, {Key::H, {"H", 0x48}}, {Key::I, {"I", 0x49}}, {Key::J, {"J", 0x4A}},
        {Key::K, {"K", 0x4B}}, {Key::L, {"L", 0x4C}}, {Key::M, {"M", 0x4D}}, {Key::N, {"N", 0x4E}}, {Key::O, {"O", 0x4F}},
        {Key::P, {"P", 0x50}}, {Key::Q, {"Q", 0x51}}, {Key::R, {"R", 0x52}}, {Key::S, {"S", 0x53}}, {Key::T, {"T", 0x54}},
        {Key::U, {"U", 0x55}}, {Key::V, {"V", 0x56}}, {Key::W, {"W", 0x57}}, {Key::X, {"X", 0x58}}, {Key::Y, {"Y", 0x59}},
        {Key::Z, {"Z", 0x5A}}, {Key::Num0, {"Num0", 0x30}}, {Key::Num1, {"Num1", 0x31}}, {Key::Num2, {"Num2", 0x32}},
        {Key::Num3, {"Num3", 0x33}}, {Key::Num4, {"Num4", 0x34}}, {Key::Num5, {"Num5", 0x35}}, {Key::Num6, {"Num6", 0x36}},
        {Key::Num7, {"Num7", 0x37}}, {Key::Num8, {"Num8", 0x38}}, {Key::Num9, {"Num9", 0x39}}, {Key::Escape, {"Escape", 0x1B}},
        {Key::LControl, {"LControl", 0xA2}}, {Key::LShift, {"LShift", 0xA0}}, {Key::LAlt, {"LAlt", 0xA4}}, {Key::LSystem, {"LSystem", 0x5B}},
        {Key::RControl, {"RControl", 0xA3}}, {Key::RShift, {"RShift", 0xA1}}, {Key::RAlt, {"RAlt", 0xA5}}, {Key::RSystem, {"RSystem", 0x5C}},
        {Key::Menu, {"Menu", 0x5D}}, {Key::LBracket, {"LBracket", 0xDB}}, {Key::RBracket, {"RBracket", 0xDD}}, {Key::SemiColon, {"SemiColon", 0xBA}},
        {Key::Comma, {"Comma", 0xBC}}, {Key::Period, {"Period", 0xBE}}, {Key::Quote, {"Quote", 0xDE}}, {Key::Slash, {"Slash", 0xBF}},
        {Key::BackSlash, {"BackSlash", 0xDC}}, {Key::Tilde, {"Tilde", 0xC0}}, {Key::Equal, {"Equal", 0xBB}}, {Key::Dash, {"Dash", 0xBD}},
        {Key::Space, {"Space", 0x20}}, {Key::Return, {"Return", 0x0D}}, {Key::BackSpace, {"BackSpace", 0x08}}, {Key::Tab, {"Tab", 0x09}},
        {Key::PageUp, {"PageUp", 0x21}}, {Key::PageDown, {"PageDown", 0x22}}, {Key::End, {"End", 0x23}}, {Key::Home, {"Home", 0x24}},
        {Key::Insert, {"Insert", 0x2D}}, {Key::Delete, {"Delete", 0x2E}}, {Key::Add, {"Add", 0x6B}}, {Key::Subtract, {"Subtract", 0x6D}},
        {Key::Multiply, {"Multiply", 0x6A}}, {Key::Divide, {"Divide", 0x6F}}, {Key::Left, {"Left", 0x25}}, {Key::Right, {"Right", 0x27}},
        {Key::Up, {"Up", 0x26}}, {Key::Down, {"Down", 0x28}}, {Key::Numpad0, {"Numpad0", 0x60}}, {Key::Numpad1, {"Numpad1", 0x61}},
        {Key::Numpad2, {"Numpad2", 0x62}}, {Key::Numpad3, {"Numpad3", 0x63}}, {Key::Numpad4, {"Numpad4", 0x64}}, {Key::Numpad5, {"Numpad5", 0x65}},
        {Key::Numpad6, {"Numpad6", 0x66}}, {Key::Numpad7, {"Numpad7", 0x67}}, {Key::Numpad8, {"Numpad8", 0x68}}, {Key::Numpad9, {"Numpad9", 0x69}},
        {Key::F1, {"F1", 0x70}}, {Key::F2, {"F2", 0x71}}, {Key::F3, {"F3", 0x72}}, {Key::F4, {"F4", 0x73}}, {Key::F5, {"F5", 0x74}},
        {Key::F6, {"F6", 0x75}}, {Key::F7, {"F7", 0x76}}, {Key::F8, {"F8", 0x77}}, {Key::F9, {"F9", 0x78}}, {Key::F10, {"F10", 0x79}},
        {Key::F11, {"F11", 0x7A}}, {Key::F12, {"F12", 0x7B}}, {Key::F13, {"F13", 0x7C}}, {Key::F14, {"F14", 0x7D}}, {Key::F15, {"F15", 0x7E}},
        {Key::Pause, {"Pause", 0x13}}
    };

    auto it = keyStrings.find(key);
    if (it != keyStrings.end()) {
        return it->second;
    }
    return { "Unknown", 0 };
}

int getMouseButtonString2(MouseButton button) {
    static std::map<MouseButton, int> buttonHexValues = {
        {MouseButton::Left, 0x01},
        {MouseButton::Right, 0x02},
        {MouseButton::Middle, 0x04},
        {MouseButton::XButton1, 0x05},
        {MouseButton::XButton2, 0x06}
    };

    auto it = buttonHexValues.find(button);
    if (it != buttonHexValues.end()) {
        return it->second;
    }
    return 0;
}
class Button {
public:
    sf::RectangleShape shape;
    sf::Text text;
    static sf::Font font;
    std::vector<std::string> options;
    bool menuVisible;
    sf::RectangleShape menuBackground;
    std::vector<sf::Text> menuOptions;
    int highlightedOption;

public:
    Button(float x, float y, float width, float height, std::vector<std::string> buttonTexts)
        : options(buttonTexts), menuVisible(false), highlightedOption(-1) {
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(sf::Color(114, 85, 85, 175)); // Initial background color
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color(0, 255, 255, 175));

        if (!font.loadFromFile("Font2.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
            exit(1);
        }
        text.setFont(font);
        text.setCharacterSize(17);
        text.setFillColor(sf::Color::White);
        text.setString("SETTINGS");
        centerText();
        text.setPosition(sf::Vector2f(x + width / 2.0f, y + height / 2.0f));


        menuBackground.setSize(sf::Vector2f(width, height * options.size()));
        menuBackground.setFillColor(sf::Color(204, 255, 255, 150));
        menuBackground.setOutlineThickness(2);

        menuBackground.setPosition(x, y + height);

        menuOptions.resize(options.size());
        for (size_t i = 0; i < options.size(); ++i) {
            menuOptions[i].setFont(font);
            menuOptions[i].setCharacterSize(14);
            menuOptions[i].setFillColor(sf::Color::Black);
            menuOptions[i].setString(options[i]);
            sf::FloatRect optionRect = menuOptions[i].getLocalBounds();


            optionRect.width += 10;
            optionRect.height += 0;

            menuOptions[i].setOrigin(optionRect.left + optionRect.width / 2.2f,
                optionRect.top + optionRect.height / 2.0f);
            menuOptions[i].setPosition(sf::Vector2f(x + width / 2.0f, y + height * (i + 1.5f)));
        }
    }
    void changeBackgroundColor(const sf::Color& color) {
        shape.setFillColor(color);
    }
    // Function to update the outline color
    void updateOutlineColor(const sf::Color& color) {
        shape.setOutlineColor(color);
    }


    void toggleOption() {

        if (text.getString() == "STATUS: ON") {
            text.setString("STATUS: OFF");

        }
        else {
            text.setString("STATUS: ON");
        }
    }


    bool contains(sf::Vector2f point) {
        return shape.getGlobalBounds().contains(point);
    }
    bool contains(sf::Vector2f point) const {
        return shape.getGlobalBounds().contains(point);
    }
    bool highlightable = true;
    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
        window.draw(text);


        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (highlightable && contains(mousePos)) {

            sf::RectangleShape highlightRect(shape.getSize());
            highlightRect.setFillColor(sf::Color(0, 204, 204, 50));
            highlightRect.setPosition(shape.getPosition());
            window.draw(highlightRect);
        }

        if (menuVisible) {
            window.draw(menuBackground);
            for (size_t i = 0; i < menuOptions.size(); ++i) {
                if (i == highlightedOption) {
                    sf::RectangleShape highlightRect(sf::Vector2f(shape.getSize().x - 4, shape.getSize().y));
                    highlightRect.setFillColor(sf::Color(153, 204, 255));
                    highlightRect.setPosition(menuOptions[i].getPosition().x - shape.getSize().x / 2 + 2,
                        menuOptions[i].getPosition().y - shape.getSize().y / 2);
                    window.draw(highlightRect);
                }
                window.draw(menuOptions[i]);

                // Linea sotto le opzioni 
                if (i > 0) {
                    float startY = menuOptions[i - 1].getPosition().y + menuOptions[i - 1].getLocalBounds().height / 2;
                    float endY = menuOptions[i].getPosition().y - menuOptions[i].getLocalBounds().height / 2;
                    float startX = menuBackground.getPosition().x;
                    float endX = startX + menuBackground.getSize().x;

                    sf::RectangleShape line(sf::Vector2f(endX - startX, 1));
                    line.setFillColor(sf::Color::Black);
                    line.setPosition(startX, startY + ((endY - startY) / 2));
                    window.draw(line);
                }
            }
        }
    }

    void toggleMenu() {
        menuVisible = !menuVisible;
        highlightedOption = -1;
    }

    bool isMenuVisible() const {
        return menuVisible;
    }

    void updateText(std::string newText) {
        text.setString(newText);
        centerText();


                if (newText == "RED") {
                   // shape.setFillColor(sf::Color(185, 100, 100, 175));
                    colorNumber = 3;
                }
                else if (newText == "YELLOW") {
                   // shape.setFillColor(sf::Color(234, 240, 176, 175));
                    colorNumber = 2;
                }
                else if (newText == "PURPLE") {
                    //shape.setFillColor(sf::Color(222, 115, 228, 175));
                    colorNumber = 1;
                }

    }

    std::string getOption(sf::Vector2f point) {
        std::string currentText = text.getString();
        for (size_t i = 0; i < menuOptions.size(); ++i) {
            sf::FloatRect optionBounds = menuOptions[i].getGlobalBounds();


            float expansion = 10.0f;
            optionBounds.left -= expansion;
            optionBounds.top -= expansion;
            optionBounds.width += 2 * expansion;
            optionBounds.height += 2 * expansion;

            if (optionBounds.contains(point)) {
                if (options[i] != currentText) {
                    return options[i];
                }
            }
        }
        return "";
    }
    void setHighlightedOption(sf::Vector2f point) {
        sf::Vector2f backgroundTopLeft = menuBackground.getPosition();
        sf::Vector2f relativePoint = point - backgroundTopLeft;

        // Check if the cursor is within the menu background
        if (relativePoint.x >= 0 && relativePoint.x <= menuBackground.getSize().x &&
            relativePoint.y >= 0 && relativePoint.y <= menuBackground.getSize().y) {

            float optionHeight = menuBackground.getSize().y / menuOptions.size();
            highlightedOption = static_cast<int>(relativePoint.y / optionHeight);
        }
        else {

            highlightedOption = -1;
        }
    }


private:
    void centerText() {
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f,
            textBounds.top + textBounds.height / 2.0f);
    }
};

class MyWindow {
public:
    MyWindow() {
        // Load font
        if (!font.loadFromFile("Font2.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
            exit(1);
        }

        // Initialize label text
        label.setFont(font);
        label.setCharacterSize(16);
        label.setString("Label Text");
        label.setPosition(10, 10); // Set position as needed

        // Set background rectangle properties
        background.setFillColor(sf::Color(200, 200, 200, 128)); // White color with 50% opacity
        updateBackgroundPosition(); // Update background position based on label position and size
    }

    void setLabelText(const std::string& text) {
        label.setString(text);
        updateBackgroundPosition(); // Update background position based on new label text
    }

    // Set character size for the label
    void setLabelCharacterSize(unsigned int size) {
        label.setCharacterSize(size);
        updateBackgroundPosition(); // Update background position based on new label text size
    }

    // Set position for the label
    void setLabelPosition(float x, float y) {
        label.setPosition(x, y);
        updateBackgroundPosition(); // Update background position based on new label position
    }

    void draw(sf::RenderWindow& window) {
        window.draw(background);
        window.draw(label);
    }

private:
    void updateBackgroundPosition() {
        sf::FloatRect labelBounds = label.getLocalBounds();
        background.setSize(sf::Vector2f(labelBounds.width + 45, labelBounds.height + 24)); // Adjust size based on text
        background.setPosition(label.getPosition() - sf::Vector2f(03, 06)); // Set position behind label
    }

public:
    sf::Font font;
    sf::Text label;
    sf::RectangleShape background;
};

sf::Font Button::font;
ComPtr<ID3D11Device> lDevice;
ComPtr<ID3D11DeviceContext> lImmediateContext;
D3D11_TEXTURE2D_DESC desc;

D3D_DRIVER_TYPE gDriverTypes[] = {
    D3D_DRIVER_TYPE_HARDWARE
};
UINT gNumDriverTypes = ARRAYSIZE(gDriverTypes);


D3D_FEATURE_LEVEL gFeatureLevels[] = {
    D3D_FEATURE_LEVEL_11_0,
    D3D_FEATURE_LEVEL_10_1,
    D3D_FEATURE_LEVEL_10_0,
    D3D_FEATURE_LEVEL_9_1
};

UINT gNumFeatureLevels = ARRAYSIZE(gFeatureLevels);
void handleSettingsMenu(sf::RenderWindow& window) {
    sf::RenderWindow settingsWindow(sf::VideoMode(200, 200), "Settings");

    while (settingsWindow.isOpen()) {
        sf::Event event;
        while (settingsWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                settingsWindow.close();
            }
        }

        settingsWindow.clear(sf::Color::White);
        settingsWindow.display();
    }
}

void MouseClick() {
    keybd_event(0x4C, 0, 0, 0); // Press 'L'
    keybd_event(0x4C, 0, KEYEVENTF_KEYUP, 0); // Release 'L'
}

void saveToFile(const std::string& filename, int var1, int var2, int var3, int var4, int var5) {
    std::ofstream outFile(filename + ".txt");
    if (outFile.is_open()) {
        outFile << var1 << std::endl;
        outFile << var2 << std::endl;
        outFile << var3 << std::endl;
        outFile << var4 << std::endl;
        outFile << var5 << std::endl;
        outFile.close();
        std::cout << "Variables saved to file." << std::endl;
    }
    else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
}
void saveToFile2(const std::string& filename, int var1, int var2, int var3, int var4, int var5) {
    std::ofstream outFile(filename + ".txt");
    if (outFile.is_open()) {
        outFile << var1 << std::endl;
        outFile << var2 << std::endl;
        outFile << var3 << std::endl;
        outFile << var4 << std::endl;
        outFile << var5 << std::endl;
        outFile.close();
        std::cout << "Variables saved to file." << std::endl;
    }
    else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
}
int getVariableFromFile(const std::string& filename, int variableIndex) {
    std::ifstream inFile(filename + ".txt");
    if (inFile.is_open()) {
        int variableValue;
        for (int i = 0; i < variableIndex; ++i) {
            // Skip lines until reaching the desired variable
            inFile >> variableValue;
        }
        inFile >> variableValue; // Read the desired variable
        inFile.close();
        return variableValue;
    }
    else {
        std::cerr << "Unable to open file for reading." << std::endl;
        return -1; // Return a default value indicating failure
    }
}

bool isKeyPressed(int virtualKey) {
    return (GetAsyncKeyState(virtualKey)) != 0;  // Check for key state including toggle state
}
void pressKey(int key, int key2) {
    if (isKeyPressed(key2)) {

        keybd_event(key, MapVirtualKey(key, 0), 0, 0);  // Key down
    }
    else {
        keybd_event(key, MapVirtualKey(key, 0), KEYEVENTF_KEYUP, 0);  // Key up
    }
}

void pressKey2(int key) {
    keybd_event(key, MapVirtualKey(key, 0), KEYEVENTF_KEYUP, 0);  // Key up

}
void ctrl1() {
    INPUT input;

    // Press Ctrl key
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_CONTROL;
    input.ki.dwFlags = 0;
    SendInput(1, &input, sizeof(INPUT));
}

void ctrl2() {
    INPUT input;

    // Release Ctrl key
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_CONTROL;
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}
void stopMovement() {
    pressKey(0x53, 0x57);  // W-S
    pressKey(0x57, 0x53);  // S-W
    pressKey(0x44, 0x41);  // A-D
    pressKey(0x41, 0x44);  // D-A
}

void stopMovement2() {
    pressKey2(0x53);  // W-S
    pressKey2(0x57);  // S-W
    pressKey2(0x44);  // A-D
    pressKey2(0x41);  // D-A
}

struct HSV {
    double h; // Hue
    double s; // Saturation
    double v; // Value
};

struct RGB {
    unsigned char r; // Red
    unsigned char g; // Green
    unsigned char b; // Blue
};

void RGBtoHSV(RGB rgb, HSV& hsv) {
    double r = rgb.r / 255.0;
    double g = rgb.g / 255.0;
    double b = rgb.b / 255.0;

    double cmax = std::max({ r, g, b });
    double cmin = std::min({ r, g, b });
    double delta = cmax - cmin;

    if (delta == 0) {
        hsv.h = 0;
    }
    else if (cmax == r) {
        hsv.h = 60 * fmod(((g - b) / delta), 6);
    }
    else if (cmax == g) {
        hsv.h = 60 * (((b - r) / delta) + 2);
    }
    else if (cmax == b) {
        hsv.h = 60 * (((r - g) / delta) + 4);
    }

    if (cmax == 0) {
        hsv.s = 0;
    }
    else {
        hsv.s = delta / cmax;
    }

    hsv.v = cmax;
}

bool stat2 = false;
bool permissionShot = false;
bool moveShoot() {
    if (shotMove % 2 == 0) {//status1 % 2 == 0
        if (GetAsyncKeyState(0x041) || GetAsyncKeyState(0x053) || GetAsyncKeyState(0x044) || GetAsyncKeyState(0x057)) {
            return false;
        }
        return true;
    }
    return true;
}

class Timer {
public:
    Timer() : startTime(std::chrono::steady_clock::now()) {}

    bool moreThanOneSecondPassed(int ms) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);

        if (elapsedTime.count() >= ms) {
            startTime = currentTime; // Reset start time
            return true;
        }

        return false;
    }

private:
    std::chrono::steady_clock::time_point startTime;
};

bool moreThanOneSecondPassed2() {
    static auto startTime = std::chrono::steady_clock::now();

    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

    if (elapsedTime.count() >= 5) { // 1500 milliseconds = 1.5 seconds
        startTime = std::chrono::steady_clock::now(); // Reset start time
        return true;
    }

    return false;
}

bool IsPurple(unsigned char red, unsigned char green, unsigned char blue) {
    bool isRedInRange = (red >= 140 && red <= 255);
    bool isGreenInRange = (green >= 35 && green <= 200);
    bool isBlueInRange = (blue >= 165 && blue <= 255);

    bool isRedInRange2 = (red >= 100 && red <= 130);
    bool isGreenInRange2 = (green >= 40 && green <= 70);
    bool isBlueInRange2 = (blue >= 120 && blue <= 150);

    if (!isRedInRange || !isGreenInRange || !isBlueInRange) {
        false;
    }
    // stat2 = true;


    RGB rgb = { red, green, blue };
    HSV hsv;
    RGBtoHSV(rgb, hsv);

    bool isHueInRange = ((hsv.h >= 277.0f && hsv.h <= 320.0f) || (hsv.h == -60.f));
    bool isSaturationInRange = (hsv.s >= 0.270f && hsv.s <= 0.800f);
    bool isValueInRange = (hsv.v >= 0.7f && hsv.v <= 1.0f);
    bool isNotEdgeCase = !(red <= 224 && green >= 90);
    bool isNotEdgeCase2 = !(red <= 160 && red >= 140 && green >= 45 && green <= 60);
    bool isNotEdgeCase3 = !(red <= 160 && red >= 140 && green >= 80 && green <= 89);

    bool isValueInRange2 = (hsv.v >= 0.49f && hsv.v <= 0.63f);
    bool isSaturationInRange2 = (hsv.s >= 0.270f && hsv.s <= 0.69f);

    bool variableReturn = (red >= 120 && red <= 130 && blue >= 130 && blue <= 155 && green >= 30 && green <= 45);  // ENEMY 286 / 0.66 / 0.6 || ASTRA  

    if ((isHueInRange && isSaturationInRange && isValueInRange &&
        isNotEdgeCase && isNotEdgeCase2)) {
        return true;
    }
    return false;
}

bool isRed(unsigned char red, unsigned char green, unsigned char blue) {
    bool isRedInRange = (red >= 170 && red <= 255);
    bool isGreenInRange = (green >= 17 && green <= 60);
    bool isBlueInRange = (blue >= 18 && blue <= 60);

    if (!isRedInRange || !isGreenInRange || !isBlueInRange) {
        false;
    }
    // stat2 = true;


    RGB rgb = { red, green, blue };
    HSV hsv;
    RGBtoHSV(rgb, hsv);

    bool isHueInRange = ((hsv.h >= -2.0f && hsv.h <= 5.0f));
    bool isSaturationInRange = (hsv.s >= 0.70f && hsv.s <= 1.0f);
    bool isValueInRange = (hsv.v >= 0.7f && hsv.v <= 1.0f);



    if (isHueInRange && isSaturationInRange && isValueInRange) {
        return true;
    }
    return false;
}

bool isYellow(unsigned char red, unsigned char green, unsigned char blue) {
    bool isRedInRange = (red >= 200 && red <= 255);
    bool isGreenInRange = (green >= 200 && green <= 255);
    bool isBlueInRange = (blue >= 25 && blue <= 130);

    if (!isRedInRange || !isGreenInRange || !isBlueInRange) {
        false;
    }
    // stat2 = true;


    RGB rgb = { red, green, blue };
    HSV hsv;
    RGBtoHSV(rgb, hsv);

    bool isHueInRange = ((hsv.h >= 59.0f && hsv.h <= 60.0f));
    bool isSaturationInRange = (hsv.s >= 0.40f && hsv.s <= 1.0f);
    bool isValueInRange = (hsv.v >= 0.9f && hsv.v <= 1.0f);



    if (isHueInRange && isSaturationInRange && isValueInRange) {
        return true;
    }
    return false;
}

bool blackColor(unsigned char red, unsigned char green, unsigned char blue, const char* data, int width, int height, bool color) {
    bool isRedInRange = (red >= 0 && red <= 70);
    bool isGreenInRange = (green >= 0 && green <= 70);
    bool isBlueInRange = (blue >= 0 && blue <= 70);
    if (!isRedInRange || !isGreenInRange || !isBlueInRange) {
        return false;
    }
    RGB rgb = { red, green, blue };
    HSV hsv;
    RGBtoHSV(rgb, hsv);
    bool isHueInRange = ((hsv.h >= 200.0f && hsv.h <= 345.0f));
    bool isSaturationInRange = (hsv.s >= 0.100f && hsv.s <= 0.400f);
    bool isValueInRange = (hsv.v >= 0.050f && hsv.v <= 0.40f);


    if ((isHueInRange && isSaturationInRange && isValueInRange)) {
        int centerX = width / 2;
        int centerY = height / 2;
        for (int y = centerY - 5; y <= centerY + 25; ++y) { //-5    -1 
            for (int x = centerX - 10; x <= centerX + 10; ++x) {
                int base = (x + y * width) * 4;
                unsigned char red = data[base + 2];
                unsigned char green = data[base + 1];
                unsigned char blue = data[base];
                if (color) {
                    return true;
                }

            }
        }
    }
    return false;
}

void checkColors(const char* data, int width, int height, int pixel) {
    int centerX = width / 2;
    int centerY = height / 2;
    for (int y = centerY - 6; y <= centerY - 2; ++y) {
        for (int x = centerX - pixel; x <= centerX + pixel; ++x) {
            int base = (x + y * width) * 4;
            unsigned char red = data[base + 2];
            unsigned char green = data[base + 1];
            unsigned char blue = data[base];


            RGB rgb = { red, green, blue };
            HSV hsv;
            RGBtoHSV(rgb, hsv);
            if (GetAsyncKeyState(0x61)) {
                printf("Detected PURPLE Pixel:\n");
                printf("RGB: (%d, %d, %d)\n", red, green, blue);
                printf("HSV: (%f, %f, %f)\n", hsv.h, hsv.s, hsv.v);
            }
            if (GetAsyncKeyState(0x62)) {
                system("cls");
            }

            if (blackColor(red, green, blue, data, width, height, IsPurple(red, green, blue))) {
                printf("Detected PURPLE Pixel:\n");
                printf("RGB: (%d, %d, %d)\n", red, green, blue);
                printf("HSV: (%f, %f, %f)\n", hsv.h, hsv.s, hsv.v);
                MouseClick();
                Sleep(3);
                return;
            }
        }
    }
}


bool delayShoting = false;
void CheckForPurple(const char* data, int width, int height, int pixel) {
    int centerX = width / 2;
    int centerY = height / 2;

    // std::cout << "pixel: " << pixel << endl;
    for (int y = centerY - 5; y <= centerY - 1; ++y) {
        for (int x = centerX - pixel; x <= centerX + pixel; ++x) {
            //  std::cout << pixel << endl;
            int base = (x + y * width) * 4;
            unsigned char red = data[base + 2];
            unsigned char green = data[base + 1];
            unsigned char blue = data[base];
            if (IsPurple(red, green, blue) || blackColor(red, green, blue, data, width, height, IsPurple(red, green, blue))) {

                if (permissionShot && moveShoot())
                {
                   // std::cout << "sparo1: " << pixel << endl;
                    MouseClick();
                    Sleep(3);
                    pixel = 2;
                    permissionShot = false;
                    return;
                }
                if (moveShoot()) {
                    if (!crouchControl) {
                        MouseClick();
                       // std::cout << "sparo2: " << pixel << endl;
                        delayShoting = false;
                        Sleep(3);
                        pixel = 2;
                        return;
                    }
                    if (crouchControl) {
                        MouseClick();
                        Sleep(3);
                        crouchControl = false;
                        return;
                    }
                }
                if (!moveShoot()) {
                    permissionShot = true;
                }
                // std::cout << "1_ALGOVALUE: " << algoValue << endl;
               // std::cout << "2_PIXEL: " << pixel << endl;
            }
        }
    }
}

void CheckForYellow(const char* data, int width, int height, int pixel) {
    centerX = width / 2;
    centerY = height / 2;

    for (int y = centerY - 5; y <= centerY + 1; ++y) {
        for (int x = centerX - pixel; x <= centerX + pixel; ++x) {
            int base = (x + y * width) * 4;
            unsigned char red = data[base + 2];
            unsigned char green = data[base + 1];
            unsigned char blue = data[base];
            if (isYellow(red, green, blue) || blackColor(red, green, blue, data, width, height, isYellow(red, green, blue)) || permissionShot) {
                if (permissionShot && moveShoot())
                {
                    std::cout << "sparo1: " << pixel << endl;
                    Sleep(110);
                    MouseClick();
                    Sleep(3);
                    pixel = 2;
                    permissionShot = false;
                    return;
                }
                if (moveShoot()) {
                    if (delayShoting && !crouchControl) {
                        MouseClick();
                        std::cout << "sparo2: " << pixel << endl;
                        delayShoting = false;
                        Sleep(3);
                        pixel = 2;
                        return;
                    }
                    if (crouchControl) {
                        MouseClick();
                        Sleep(3);
                        crouchControl = false;
                        return;
                    }
                }
                if (!moveShoot()) {
                    permissionShot = true;
                }
                // std::cout << "1_ALGOVALUE: " << algoValue << endl;
               // std::cout << "2_PIXEL: " << pixel << endl;
            }
        }
    }
}

void CheckForRed(const char* data, int width, int height, int pixel) {
    centerX = width / 2;
    centerY = height / 2;

    for (int y = centerY - 5; y <= centerY + 1; ++y) {
        for (int x = centerX - pixel; x <= centerX + pixel; ++x) {
            int base = (x + y * width) * 4;
            unsigned char red = data[base + 2];
            unsigned char green = data[base + 1];
            unsigned char blue = data[base];
            if (isRed(red, green, blue)|| blackColor(red, green, blue, data, width, height, isRed(red, green, blue)) || permissionShot) {
                if (permissionShot && moveShoot())
                {
                    std::cout << "sparo1: " << pixel << endl;
                    Sleep(110);
                    MouseClick();
                    Sleep(3);
                    pixel = 2;
                    permissionShot = false;
                    return;
                }
                if (moveShoot()) {
                    if (delayShoting && !crouchControl) {
                        MouseClick();
                        std::cout << "sparo2: " << pixel << endl;
                        delayShoting = false;
                        Sleep(3);
                        pixel = 2;
                        return;
                    }
                    if (crouchControl) {
                        MouseClick();
                        Sleep(3);
                        crouchControl = false;
                        return;
                    }
                }
                if (!moveShoot()) {
                    permissionShot = true;
                }
                // std::cout << "1_ALGOVALUE: " << algoValue << endl;
               // std::cout << "2_PIXEL: " << pixel << endl;
            }
        }
    }
}

void checkColorSelected(const char* data, int width, int height, int pixel) {
    if (colorNumber == 1) {
        CheckForPurple(data, width, height, pixel);
    }
    if (colorNumber == 2) {
        CheckForYellow(data, width, height, pixel);
    }
    if (colorNumber == 3) {
        CheckForRed(data, width, height, pixel);
    }
    else
    {
        return;
    }

}

void SetVolume(WORD volume) {
    volume = min(max(volume, (WORD)0), (WORD)65535);
    DWORD dwVolume = ((DWORD)volume << 16) | (DWORD)volume;
    waveOutSetVolume(0, dwVolume);
}


Button button1(35.f, 43, 115, 35.f, { "STATUS: ON", "STATUS: OFF" }); //x,y,lunghezza,altezza
Button button2(460.f, 43, 118, 35.f, { "RED", "YELLOW", "PURPLE" });
Button button4(165.f, 43, 138, 35.f, { "Move&Shot: ON", "Move&Shot: OFF" });
Button button14(319.f, 43, 125, 35.f, { "LOCKED!", "LOCKED!" });//AIM ASSIST 170.f, 60
Button button5(457, 290, 118, 33.f, { "" });//SETTINGS NEW WINDOW BUTTON 
Button button6(15, 15, 125, 33.f, { "" });//GET KEY VALUE SETTINGS  58 distance Y
Button button7(15, 60, 125, 33.f, { "" });//PIXEL WRITE 
Button button15(15, 105, 125, 33.f, { "" });//NEW HANDLE
Button button8(15, 105, 125, 33.f, { "" });//RESOLUTION BUTTON
Button button9(10, 290, 125, 33.f, { "" });//NEW WINDOW PROFILES POP UP
Button button10(165, 290, 33, 33.f, { "" });//#1 PROFILE
Button button11(205, 290, 33, 33.f, { "" });//#2 PROFILE
Button button12(245, 290, 33, 33.f, { "" });//#3 PROFILE
Button button13(35.f, 290, 115, 33.f, { "" });//SAVE PROFILE
Button button3(325.f, 43, 115, 35.f, { "HOLD BUTTON", "PRESS BUTTON" });
bool buttonPressed = false;

int barWidth = 190;
int barHeight = 2;
int handleSize = 20;
int handleRadius = handleSize / 2;
int numPoints = 8;
int spacing = barWidth / (numPoints - 1);

int selectedPoint = 1;
bool isDraggingHandle = false;
int newBarPosX = 157;
int newBarPosY = 116;
//------------------------------------------------------- second bar
int barWidth2 = 190;
int barHeight2 = 2;
int handleSize2 = 20;
int handleRadius2 = handleSize / 2;
int numPoints2 = 8;
int spacing2 = barWidth / (numPoints - 1);

int selectedPoint2 = 1;
bool isDraggingHandle2 = false;
int newBarPosX2 = 157;
int newBarPosY2 = 116;

bool programStart = true;
bool programStart2 = true;

double pixel = getVariableFromFile("settings2", 0);
bool isMouseMoved() {
    static POINT lastPos = { 0 };
    POINT currentPos;
    GetCursorPos(&currentPos);

    if (lastPos.x != currentPos.x || lastPos.y != currentPos.y) {
        lastPos = currentPos;
        return true;
    }

    return false;
}
int algoInt = 0;
int isMouseMoved2() {
    static POINT lastPos = { 0 };
    POINT currentPos;
    GetCursorPos(&currentPos);

    algoInt = currentPos.x - lastPos.x;
    if (algoInt < 0) {
        algoInt *=-1;

    }


        lastPos = currentPos;
        return algoInt;
    
    return algoInt;

}

void centerConsoleWindow() {
    HWND consoleWindow = GetConsoleWindow();
    if (consoleWindow != NULL) {
        RECT rect;
        GetWindowRect(consoleWindow, &rect);
        int consoleWidth = rect.right - rect.left;
        int consoleHeight = rect.bottom - rect.top;

        // Get screen width and height
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);

        // Calculate the position of the console window
        int consoleX = (screenWidth - consoleWidth) / 2;
        int consoleY = (screenHeight - consoleHeight) / 2;

        // Move the console window to the calculated position
        MoveWindow(consoleWindow, consoleX, consoleY, consoleWidth, consoleHeight, TRUE);
    }
}
void setConsoleResolution(int width, int height) {
    HWND console = GetConsoleWindow();
    if (console == NULL) {
        return; // Failed to get console window handle
    }
    RECT rect;
    GetWindowRect(console, &rect);

    // Calculate the required width and height of the window
    rect.right = rect.left + width;
    rect.bottom = rect.top + height;

    // Resize the console window
    MoveWindow(console, rect.left, rect.top, width, height, TRUE);
}
bool mouseMOVED3 = true;
bool mouseMOVED4 = true;

void hideConsole() {
    HWND hWnd = GetConsoleWindow();
    if (hWnd != NULL) {
        ShowWindow(hWnd, SW_HIDE);
    }
}

void showConsole() {
    // setConsoleResolution(400, 200);
    HWND hWnd = GetConsoleWindow();
    if (hWnd != NULL) {
        ShowWindow(hWnd, SW_SHOW);
    }
}
bool IsDebugged()
{
    return IsDebuggerPresent();
}


int close = 0;
bool close2 = false;

const std::string compilation_date = (std::string)skCrypt(__DATE__);
const std::string compilation_time = (std::string)skCrypt(__TIME__);

using namespace KeyAuth;
void introConsole() {
    centerConsoleWindow();
    setConsoleResolution(550, 300);
    std::cout << "              ____________________________________   " << endl;
    std::cout << "             |                                    |  " << endl;
    std::cout << "             |   EXODUS AMD AIMLOCK VERSION 6.5.0 |  "    <<endl;
    std::cout << "             |         dev. MrRobot1259           |  " << endl;
    std::cout << "             |  PLEASE ENTER YOUR LICENSE BELOW!  |  " << endl;
    std::cout << "             |____________________________________|  " << endl;
}

void outroConsole() {
    std::cout << endl << " Key Authentication... " << endl;
    Sleep(2000);
    std::cout << endl << " LOGIN CONFIRMED ";
    Sleep(2000);
}

std::string version = skCrypt("2.6").decrypt();
std::string url = skCrypt("https://keyauth.win/api/1.2/").decrypt(); // change if you're self-hosting
std::string path = skCrypt("").decrypt();

api KeyAuthApp(name, ownerid, secret, version, url, path);

void licenseCheck() {

    KeyAuthApp.init();
    if (!KeyAuthApp.response.success)
    {
        std::cout << skCrypt("\n Status: ") << KeyAuthApp.response.message;
        Sleep(1500);
        exit(1);
    }
   std::string filename = "license.txt"; // Name of the license file
    // Check if the file exists
    std::ifstream checkFile(filename);
    if (checkFile.good()) {
        std::string license = readLicenseFromFile(filename); // Call the function to read the license text
        if (!license.empty()) {
            std::cout <<std::endl << " License read from file: license.txt" << "\n";
            Sleep(1000);
            KeyAuthApp.license(license);
        }
    }
    else {
        std::string key;
        std::cout << skCrypt("\n Enter license: ");
        std::cin >> key;
        KeyAuthApp.license(key);
        createLicenseFile(filename, key);
    }


    if (!KeyAuthApp.response.success)
    {
        std::cout << skCrypt("\n Status: ") << KeyAuthApp.response.message;
        if (!KeyAuthApp.response.success)
        {
            Sleep(1000);
            std::string key;
            cout << std::endl;
            std::cout << skCrypt("\n Enter New license: ");
            std::cin >> key;
            KeyAuthApp.license(key);
            Sleep(1000);
            std::cout << skCrypt("\n Status: ") << KeyAuthApp.response.message <<endl;
            Sleep(1000);
            if (!KeyAuthApp.response.success)
            {
                Sleep(3000);
                exit(1);
            }
            createLicenseFile(filename, key);
        }
    }
    licenseGood = false;
   // std::cout << "LOGIN GOOD";
}
void sessionCheck() {
    KeyAuthApp.check();
    if (!KeyAuthApp.response.success)
    {
        Sleep(1000);
        exit(1);
    }
}

static const auto startTime = std::chrono::steady_clock::now();
auto currentTime = std::chrono::steady_clock::now();
void HideWindow(sf::RenderWindow& window) {
    HWND hwnd = window.getSystemHandle(); // Get the handle of the SFML window
    ShowWindow(hwnd, SW_HIDE); // Hide the SFML window
}
void ShowWindow(sf::RenderWindow& window) {
    HWND hwnd = window.getSystemHandle(); // Get the handle of the SFML window
    ShowWindow(hwnd, SW_SHOW); // Hide the SFML window
}

std::string generateRandomString() {
    const std::string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const int length = 15;
    std::string randomString;
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator

    for (int i = 0; i < length; ++i) {
        randomString += charset[rand() % charset.length()];
    }

    return randomString;
}


int main(){
    introConsole();
    showConsole();
    mainprotect();
    licenseCheck();
    outroConsole();
    sessionCheck();
    hideConsole();
    std::string randomStr = generateRandomString();
    sf::RenderWindow window(sf::VideoMode(600, 338), randomStr, sf::Style::Titlebar | sf::Style::Close);
    HWND hwnd = window.getSystemHandle();

    window.setFramerateLimit(10);
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("backGroundNONAME.jpg")) {
        std::cerr << "Failed to load background image!" << std::endl;
        return 1;
    } //settingss.png
    sf::Sprite background(backgroundTexture);
    sf::Image icon;
    if (!icon.loadFromFile("prova11.jpg")) {
        // Handle error if the ICO file failed to load
        std::cerr << "Failed to load ICON!" << std::endl;
        return 1;
    }

    // Set the loaded image as the window icon
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    button1.updateText("STATUS: OFF"); // Set the button text
    button2.updateText("Select a Color");
    button3.updateText("Shot Mode");
    button4.updateText("Move&Shot: OFF");
    button5.updateText("SETTINGS");
    button5.changeBackgroundColor(sf::Color(140, 140, 140, 255));
    // button5.changeBackgroundColor(sf::Color(128, 128, 128));
    button6.updateText("CHANGE KEY");
    button6.changeBackgroundColor(sf::Color(0, 204, 204, 150));
    button7.updateText("PIXEL RANGE");
    button7.highlightable = false;
    button7.updateOutlineColor(sf::Color(204, 204, 255, 0));
    button15.updateText("AIM ASSIST");
    button15.highlightable = false;
    button15.updateOutlineColor(sf::Color(204, 204, 255, 0));
    button8.updateText("RES. DETECTED");
    button8.highlightable = false;
    button8.updateOutlineColor(sf::Color(204, 204, 255, 0));
    button9.updateText("SAVE CONFIG");
    button10.updateText("#1");
    button11.updateText("#2");
    button12.updateText("#3");
    button13.updateText("SAVE CONFIG");
    button13.changeBackgroundColor(sf::Color(255, 255, 255, 150));
    button14.updateText("AIM LOCK: OFF");

    MyWindow myWindow;
    myWindow.setLabelText("PRESS THE BUTTON");
    myWindow.setLabelCharacterSize(16);
    myWindow.setLabelPosition(147, 21);

    HDC hdc_target;
    RECT rect;
    GetClientRect(GetDesktopWindow(), &rect);
    HDC monitor = GetDC(GetDesktopWindow());
    int current = GetDeviceCaps(monitor, VERTRES);
    int total = GetDeviceCaps(monitor, DESKTOPVERTRES);

    uint32_t screenWidth = rect.right - rect.left;
    uint32_t screenHeight = rect.bottom - rect.top;
    uint32_t captureWidth = 30;
    uint32_t captureHeight = 30;
    uint32_t width = screenWidth < captureWidth ? screenWidth : captureWidth;
    uint32_t height = screenHeight < captureHeight ? screenHeight : captureHeight;

    int startX = (screenWidth - width) / 2;
    int startY = (screenHeight - height) / 2;
    int startXoriginal = startX;
    int startXaltered = startX -= 8;
    int startXaltered2 = startXaltered;



    ComPtr<IDXGISurface1> gdiSurface;
    ComPtr<ID3D11Texture2D> texture;
    HRESULT hr(E_FAIL);
    D3D_FEATURE_LEVEL lFeatureLevel;
    for (UINT DriverTypeIndex = 0; DriverTypeIndex < gNumDriverTypes; ++DriverTypeIndex)
    {
        hr = D3D11CreateDevice(
            nullptr,
            gDriverTypes[DriverTypeIndex],
            nullptr,
            0,
            gFeatureLevels,
            gNumFeatureLevels,
            D3D11_SDK_VERSION,
            &lDevice,
            &lFeatureLevel,
            &lImmediateContext);
        if (SUCCEEDED(hr))
        {
            break;
        }
        lDevice.Reset();
        lImmediateContext.Reset();
    }
    desc.Width = width;
    desc.Height = height;
    desc.ArraySize = 1;
    desc.MipLevels = 1;
    desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = 40;
    desc.MiscFlags = D3D11_RESOURCE_MISC_GDI_COMPATIBLE;
    desc.CPUAccessFlags = 0;
    hr = lDevice->CreateTexture2D(&desc, NULL, &texture);
    if (FAILED(hr)) {

        return 0;
    }

    hr = texture->QueryInterface(__uuidof(IDXGISurface1), (void**)&gdiSurface);
    if (FAILED(hr)) {
        return 0;
    }
    std::string yellowText2 = "     " + std::to_string(screenWidth) + "x" + std::to_string(screenHeight);
    sf::Text label;
    label.setCharacterSize(13);
    label.setFont(Button::font);
    label.setFillColor(sf::Color(200, 200, 200, 128));
    label.setString("Dev_MrRobot1259");
    label.setPosition(250, window.getSize().y - label.getLocalBounds().height - 13);

    MyWindow myWindow2;
    myWindow2.setLabelText(yellowText2);
    myWindow2.setLabelCharacterSize(16);
    myWindow2.setLabelPosition(147, 110);

    desc.BindFlags = 0;
    desc.MiscFlags &= D3D11_RESOURCE_MISC_TEXTURECUBE;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    desc.Usage = D3D11_USAGE_STAGING;
    int userKey = GetPreferredKeyFromFileSettings(nameFile);
    bool isFocused = true;
    bool changes = false;


    if (!backgroundTexture.loadFromFile("backGroundNONAME.jpg")) {
        std::cerr << "Failed to load background image!" << std::endl;
        return 1;
    }

    // Create the transparent background rectangle shape
    sf::RectangleShape background2(sf::Vector2f(barWidth + 26, barHeight + 32));
    background2.setPosition(newBarPosX - 13, newBarPosY - 56);
    background2.setFillColor(sf::Color(200, 200, 200, 128)); // White with alpha 100 for transparency


    // Create the progress bar
    sf::RectangleShape bar(sf::Vector2f(barWidth, barHeight));
    bar.setPosition(newBarPosX, newBarPosY - 40);
    bar.setFillColor(sf::Color::White);

    // Create the handle
    sf::RectangleShape handle(sf::Vector2f(handleSize, handleSize));
    handle.setFillColor(sf::Color::White);
    handle.setOrigin(handleSize / 2, handleSize / 2);
    handle.setPosition(newBarPosX, (newBarPosY - 40) - handleRadius + 10);
    //--------------------------------------------------------------------------------SECOND HANDLE
    sf::RectangleShape background4(sf::Vector2f(barWidth2 + 26, barHeight2 + 32));
    background4.setPosition(newBarPosX2 - 13, newBarPosY2 - 11);
    background4.setFillColor(sf::Color(200, 200, 200, 128)); // White with alpha 100 for transparency

    // Create the progress bar
    sf::RectangleShape bar2(sf::Vector2f(barWidth2, barHeight2));
    bar2.setPosition(newBarPosX2, newBarPosY2 + 6);
    bar2.setFillColor(sf::Color::White);

    // Create the handle
    sf::RectangleShape handle2(sf::Vector2f(handleSize2, handleSize2));
    handle2.setFillColor(sf::Color::White);
    handle2.setOrigin(handleSize2 / 2, handleSize2 / 2);
    handle2.setPosition(newBarPosX2, (newBarPosY2 + 6) - handleRadius2 + 10);


    sf::Text positionText;
    positionText.setCharacterSize(16);
    positionText.setFont(Button::font);
    positionText.setFillColor(sf::Color::Black);

    sf::Text positionText2;
    positionText2.setCharacterSize(16);
    positionText2.setFont(Button::font);
    positionText2.setFillColor(sf::Color::Black);
    bool aimLock = false;
    pixel = getVariableFromFile("settings2", 0);
    aimValue = getVariableFromFile("settings3", 0)- 1;
    pixelOriginal = pixel;
    unsigned short last_r = 0;
    unsigned short last_g = 0;
    unsigned short last_b = 0;
    auto start = std::chrono::high_resolution_clock::now();
    Timer timer1;
    Timer timer2;
    Timer timer3;

    while (window.isOpen()) {

        if (programStart2) {
            // updateTextButton.updateText2();
            std::cout << "prova";
            if (licenseGood) {
                exit(0);
            }
           // sessionCheck();
            programStart2 = false;
        }
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::LostFocus) {
                isFocused = false;
                window.setFramerateLimit(1); // framerate finestra background
            }
            else if (event.type == sf::Event::GainedFocus) {
                isFocused = true;
                window.setFramerateLimit(60); // framerate finestra attiva
            }
            if (isFocused) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        // aprimento del menu controll cursore
                        if (button1.contains(mousePos)) {
                            button1.toggleMenu();
                        }
                        else if (button2.contains(mousePos)) {
                            button2.toggleMenu();
                        }
                        else if (button3.contains(mousePos)) {
                            button3.toggleMenu();
                        }
                        else if (button4.contains(mousePos)) {
                            button4.toggleMenu();
                        }
                        else if (button14.contains(mousePos)) {
                            button14.toggleMenu();
                        }
                        if (button5.contains(mousePos) && !newWindowOpened) {
                            newWindowOpened = true;

                            sf::RenderWindow smallWindow(sf::VideoMode(370, 150), "Settings", sf::Style::Titlebar | sf::Style::Close);
                            smallWindow.setFramerateLimit(10);
                            sf::Texture backgroundTexture2;
                            if (!backgroundTexture2.loadFromFile("backGroundNONAME2.jpg")) {
                                std::cerr << "Failed to load background image!" << std::endl;
                                return 1;
                            }
                            sf::Sprite background3(backgroundTexture2);
                            sf::Image icon2;
                            if (!icon2.loadFromFile("settingss.png")) {
                                // Handle error if the ICO file failed to load
                                std::cerr << "Failed to load ICON!" << std::endl;
                                return 1;
                            }
                            smallWindow.setIcon(icon2.getSize().x, icon2.getSize().y, icon2.getPixelsPtr());
                            HWND hwnd = smallWindow.getSystemHandle();
                            LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
                            SetWindowLongPtr(hwnd, GWL_STYLE, style & ~WS_MINIMIZEBOX);
                           // SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                            sf::Text label2;
                            label2.setCharacterSize(16);
                            label2.setFont(Button::font);
                            label2.setFillColor(sf::Color::Black);
                            label2.setString(yellowText2);
                            label2.setPosition(10, smallWindow.getSize().y - label2.getLocalBounds().height - 10);
                            while (smallWindow.isOpen()) {
                                if (programStart) { //load pixel parameters
                                    float snapX = getVariableFromFile("settings2", 3);
                                    float handlePosY = getVariableFromFile("settings2", 4);
                                    if (getVariableFromFile("settings2", 4) == 0) {
                                        handlePosY = 1;
                                    }
                                    int textX = getVariableFromFile("settings2", 1);
                                    int textY = getVariableFromFile("settings2", 2);
                                    sf::Vector2f handlePosition = handle.getPosition(); // Get the current position
                                    handlePosition.y = handlePosY; // Update the y coordinate
                                    handle.setPosition(snapX, handle.getPosition().y);
                                    int value = getVariableFromFile("settings2", 0);
                                    std::string valueString = std::to_string(value);
                                    positionText.setString(valueString); // Set the text to the value string
                                    positionText.setPosition(textX - 4, textY - 11); // Set the position of the text to match the handle
                                    //------------------------------------------------------------------------------------------------------SECOND HANDLE
                                    float snapX2 = getVariableFromFile("settings3", 3);
                                    float handlePosY2 = getVariableFromFile("settings3", 4);
                                    if (getVariableFromFile("settings3", 4) == 0) {
                                        handlePosY2 = 1;
                                    }
                                    int textX2 = getVariableFromFile("settings3", 1);
                                    int textY2 = getVariableFromFile("settings3", 2);
                                    sf::Vector2f handlePosition2 = handle2.getPosition(); // Get the current position
                                    handlePosition2.y = handlePosY2; // Update the y coordinate
                                    handle2.setPosition(snapX2, handle2.getPosition().y);
                                    int value2 = getVariableFromFile("settings3", 0);
                                    std::string valueString2 = std::to_string(value2);
                                    positionText2.setString(valueString2); // Set the text to the value string
                                    positionText2.setPosition(textX2 - 4, textY2 - 11); // Set the position of the text to match the handle

                                    programStart = false;
                                }
                                sf::Event event;
                                while (smallWindow.pollEvent(event)) {
                                    if (event.type == sf::Event::Closed) {
                                        smallWindow.close();
                                        newWindowOpened = false;
                                    }
                                    else if (event.type == sf::Event::MouseButtonPressed) {
                                        if (event.mouseButton.button == sf::Mouse::Left) {
                                            sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                                            if (handle.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                                isDraggingHandle = true;
                                            }
                                            if (handle2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                                isDraggingHandle2 = true;
                                            }

                                            // Check if the button was pressed
                                            if (button6.contains(mousePos)) {
                                                myWindow.label.setString("PRESS A KEY!");
                                                buttonPressed = true;
                                            }

                                        }

                                    }
                                    if (event.type == sf::Event::MouseButtonPressed && buttonPressed) {
                                        if (event.mouseButton.button != sf::Mouse::Left) {
                                            // Get the name of the mouse button pressed
                                            MouseButton button = static_cast<MouseButton>(event.mouseButton.button);
                                            std::string buttonName = getMouseButtonString(button);
                                            CreateFileSettings(nameFile, getMouseButtonString2(button));
                                            userKey = GetPreferredKeyFromFileSettings(nameFile);
                                            myWindow.label.setString("Key Selected: " + buttonName);
                                            buttonPressed = false;
                                        }
                                    }
                                    else if (event.type == sf::Event::KeyPressed && buttonPressed) {
                                        // Get the name of the key pressed
                                        Key key = static_cast<Key>(event.key.code);
                                        std::string keyName = getKeyString2(key);
                                        CreateFileSettings(nameFile, getKeyString3(key));
                                        userKey = GetPreferredKeyFromFileSettings(nameFile);
                                        myWindow.label.setString("Key Selected: " + keyName);
        
                                        buttonPressed = false;

                                    }
                                    else if (event.type == sf::Event::MouseButtonReleased) {
                                        if (event.mouseButton.button == sf::Mouse::Left) {
                                            isDraggingHandle = false;
                                            isDraggingHandle2 = false;
                                        }
                                    }
                                    else if (event.type == sf::Event::MouseMoved) {

                                        if (isDraggingHandle) {
                                            sf::Vector2f mousePos = smallWindow.mapPixelToCoords(sf::Mouse::getPosition(smallWindow));
                                            float mouseX = std::min(std::max(mousePos.x, bar.getPosition().x), bar.getPosition().x + barWidth);

                                            // Calculate the closest point to the mouse position
                                            int closestPoint = std::round((mouseX - bar.getPosition().x) / spacing);
                                            float snapX = bar.getPosition().x + closestPoint * spacing;
                                            int affermazione = selectedPoint;
                                            // Snap the handle to the closest point
                                            handle.setPosition(snapX, handle.getPosition().y);
                                            selectedPoint = closestPoint + 1;
                                            // Calculate the value based on the handle position
                                            int value = selectedPoint;
                                            std::string valueString = std::to_string(value);
                                            positionText.setString(valueString); // Set the text to the value string
                                            positionText.setPosition((handle.getPosition().x) - 4, (handle.getPosition().y) - 11); // Set the position of the text to match the handle
                                            int textX = static_cast<int>(handle.getPosition().x);
                                            int textY = static_cast<int>(handle.getPosition().y);
                                            if (selectedPoint = !affermazione) {
                                                saveToFile2("settings2", value, textX, textY, snapX, textY);
                                                pixel = value;
                                                pixelOriginal = pixel;
                                            }
                                        }
                                        //----------------------------------------------------------------------------------- second bar 
                                        else if (event.type == sf::Event::MouseMoved) {

                                            if (isDraggingHandle2) {
                                                sf::Vector2f mousePos = smallWindow.mapPixelToCoords(sf::Mouse::getPosition(smallWindow));
                                                float mouseX = std::min(std::max(mousePos.x, bar2.getPosition().x), bar2.getPosition().x + barWidth2);

                                                // Calculate the closest point to the mouse position
                                                int closestPoint2 = std::round((mouseX - bar2.getPosition().x) / spacing2);
                                                float snapX2 = bar2.getPosition().x + closestPoint2 * spacing2;
                                                int affermazione2 = selectedPoint2;
                                                // Snap the handle to the closest point
                                                handle2.setPosition(snapX2, handle2.getPosition().y);
                                                selectedPoint2 = closestPoint2 + 1;
                                                // Calculate the value based on the handle position
                                                int value = selectedPoint2;
                                                std::string valueString2 = std::to_string(value);
                                                positionText2.setString(valueString2); // Set the text to the value string
                                                positionText2.setPosition((handle2.getPosition().x) - 4, (handle2.getPosition().y) - 11); // Set the position of the text to match the handle
                                                int textX = static_cast<int>(handle2.getPosition().x);
                                                int textY = static_cast<int>(handle2.getPosition().y);
                                                if (selectedPoint2 = !affermazione2) {
                                                    saveToFile2("settings3",value, textX, textY, snapX2, textY);
                                                    value -= 1;
                                                    aimValue = value;
                                                }
                                            }
                                        }
                                    }
                                }

                                smallWindow.clear();
                                smallWindow.draw(background3);
                                smallWindow.draw(background2);
                          //      smallWindow.draw(background4);

                                button6.draw(smallWindow);
                                button7.draw(smallWindow);
                                button8.draw(smallWindow);
                               // button15.draw(smallWindow);
                                myWindow.draw(smallWindow);
                                // smallWindow.draw(label2);
                                myWindow2.draw(smallWindow);
                                smallWindow.draw(bar);
                               // smallWindow.draw(bar2);

                                // Draw the handles
                                for (int i = 0; i < numPoints; ++i) {
                                    sf::RectangleShape point(sf::Vector2f(2, 10));
                                    point.setFillColor(sf::Color::White);
                                    point.setPosition(bar.getPosition().x + i * spacing - 1, bar.getPosition().y - 5);
                                    smallWindow.draw(point);
                                }
                         /*       // Draw the handles
                                for (int i = 0; i < numPoints; ++i) {
                                    sf::RectangleShape point2(sf::Vector2f(2, 10));
                                    point2.setFillColor(sf::Color::White);
                                    point2.setPosition(bar2.getPosition().x + i * spacing2 - 1, bar2.getPosition().y - 5);
                                    smallWindow.draw(point2);
                                }*/
                                // Draw the handle
                                smallWindow.draw(handle);
                               // smallWindow.draw(handle2);
                                smallWindow.draw(positionText);
                              //  smallWindow.draw(positionText2);
                                smallWindow.display();
                            }
                        }
                        // aggiornamento del tasto e controllo cursore
                        else if (button1.isMenuVisible()) {
                            std::string option = button1.getOption(mousePos);
                            if (!option.empty()) {
                                button1.updateText(option);
                                button1.toggleMenu();
                                status1++;
                                changes = true;
                            }
                        }
                        else if (button2.isMenuVisible()) {
                            std::string option = button2.getOption(mousePos);
                            if (!option.empty()) {
                                if (option == "RED") {
                                    colorNumber = 3;
                                    button2.updateText("RED");
                                }
                                if (option == "YELLOW") {
                                    colorNumber = 2;
                                    button2.updateText("YELLOW");
                                }
                                if (option == "PURPLE") {
                                    colorNumber = 1;
                                    button2.updateText(option);
                                }
                                button2.toggleMenu();
                            }
                        }
                        else if (button3.isMenuVisible()) {
                            std::string option = button3.getOption(mousePos);
                            if (!option.empty()) {
                                button3.updateText(option);

                                if (option == "HOLD BUTTON") {
                                    toggleShot = 2;
                                    status2 = toggleShot;
                                }
                                if (option == "PRESS BUTTON") {
                                    toggleShot = 1;
                                    status2 = toggleShot;
                                }

                                button3.toggleMenu();
                            }
                        }
                        else if (button4.isMenuVisible()) {
                            std::string option = button4.getOption(mousePos);
                            if (!option.empty()) {
                                button4.updateText(option);
                                if (option == "Move&Shot: OFF") {
                                    shotMove = 2;
                                }
                                if (option == "Move&Shot: ON") {
                                    shotMove = 1;
                                }
                                button4.toggleMenu();
                            }
                        }
                        else if (button14.isMenuVisible()) {
                            std::string option = button14.getOption(mousePos);
                            if (!option.empty()) {
                                button14.updateText(option);

                                if (option == "LOCKED!") {
                                //    aimLock = true;
                                  //  aimLockInt = 2;
                                }
                                if (option == "LOCKED!") {
                                  //  aimLock = false;
                                   // aimLockInt = 1;
                                }

                                button14.toggleMenu();
                            }
                        }
                        //chiude i menu
                        if (button1.isMenuVisible() && !button1.contains(mousePos)) {
                            button1.toggleMenu();
                        }
                        if (button2.isMenuVisible() && !button2.contains(mousePos)) {
                            button2.toggleMenu();
                        }
                        if (button3.isMenuVisible() && !button3.contains(mousePos)) {
                            button3.toggleMenu();
                        }
                        if (button4.isMenuVisible() && !button4.contains(mousePos)) {
                            button4.toggleMenu();
                        }
                        if (button14.isMenuVisible() && !button14.contains(mousePos)) {
                            button14.toggleMenu();
                        }
                        if (button13.contains(mousePos)) {
                            button13.updateText("SELECT ONE");
                            optionFile = true;
                            optionButton = false;
                            button10.changeBackgroundColor(sf::Color(224, 224, 224, 125));
                            button11.changeBackgroundColor(sf::Color(224, 224, 224, 125));
                            button12.changeBackgroundColor(sf::Color(224, 224, 224, 125));
                        }
                        if (optionFile) {
                            if (button10.contains(mousePos)) {
                                button13.updateText("SAVE CONFIG");
                                saveToFile("profile1", colorNumber, toggleShot, shotMove, status1, aimLockInt);//0-colore, 1, toggleshot, 2-shotMove, 3-AIMBOT
                                button10.changeBackgroundColor(sf::Color(224, 224, 224, 125));
                                button11.changeBackgroundColor(sf::Color(114, 85, 85, 175));
                                button12.changeBackgroundColor(sf::Color(114, 85, 85, 175));
                                optionFile = false;
                                optionButton = true;
                            }
                            if (button11.contains(mousePos)) {
                                button13.updateText("SAVE CONFIG");
                                saveToFile("profile2", colorNumber, toggleShot, shotMove, toggleShot, aimLockInt);//0-colore, 1, toggleshot, 2-shotMove, 3-AIMBOT
                                button10.changeBackgroundColor(sf::Color(114, 85, 85, 175));
                                button11.changeBackgroundColor(sf::Color(224, 224, 224, 125));
                                button12.changeBackgroundColor(sf::Color(114, 85, 85, 175));
                                optionFile = false;
                                optionButton = true;
                            }
                            if (button12.contains(mousePos)) {
                                button13.updateText("SAVE CONFIG");
                                saveToFile("profile3", colorNumber, toggleShot, shotMove, toggleShot, aimLockInt);//0-colore, 1, toggleshot, 2-shotMove, 3-AIMBOT
                                button10.changeBackgroundColor(sf::Color(114, 85, 85, 175));
                                button11.changeBackgroundColor(sf::Color(114, 85, 85, 175));
                                button12.changeBackgroundColor(sf::Color(224, 224, 224, 125));//(153, 153, 255, 175)
                                optionFile = false;
                                optionButton = true;

                            }
                        }
                        //----------------------------------------------------------------------------------------------PROFILE 1
                        if (button10.contains(mousePos)) {
                            //-------------------------------------colore import
                            int colorr = getVariableFromFile("profile1", 0);
                            if (colorr == 3) {
                                colorNumber = 3;
                                button2.updateText("RED");
                            }
                            if (colorr == 2) {
                                colorNumber = 2;
                                button2.updateText("YELLOW");
                            }
                            if (colorr == 1) {
                                colorNumber = 1;
                                button2.updateText("PURPLE");
                            }
                            button10.changeBackgroundColor(sf::Color(224, 224, 224, 125));
                            button11.changeBackgroundColor(sf::Color(114, 85, 85, 175));
                            button12.changeBackgroundColor(sf::Color(114, 85, 85, 175));

                            //-------------------------------------toggle shot import
                            int togglee = getVariableFromFile("profile1", 1);
                            if (togglee == 2) {
                                toggleShot = 2;
                                status2 = toggleShot;
                                button3.updateText("HOLD BUTTON");
                            }
                            if (togglee == 1) {
                                toggleShot = 1;
                                status2 = toggleShot;
                                button3.updateText("PRESS BUTTON");
                            }
                            //-------------------------------------toggle shot import
                            int shotMovee = getVariableFromFile("profile1", 2);
                            if (shotMovee == 2) {
                                shotMove = 2;
                                button4.updateText("Move&Shot: OFF");
                            }
                            if (shotMovee == 1) {
                                shotMove = 1;
                                button4.updateText("Move&Shot: ON");
                            }
                            int aimLockInt2 = getVariableFromFile("profile1", 4);
                            if (aimLockInt2 == 2) {
                             //   aimLock = true;
                             //   aimLockInt = 2;
                                button14.updateText("LOCKED!");
                            }
                            if (aimLockInt2 == 1) {
                             //   aimLock = false;
                            //    aimLockInt = 1;
                                button14.updateText("LOCKED!");
                            }
                            changes = true;
                            status1 = 2;
                            button1.updateText("STATUS: ON");
                            button10.changeBackgroundColor(sf::Color(224, 224, 224, 125));
                            button11.changeBackgroundColor(sf::Color(114, 85, 85, 175));
                            button12.changeBackgroundColor(sf::Color(114, 85, 85, 175));
                            //----------------------------------------------------------------------------------------------PROFILE 2 
                        }
                        if (button11.contains(mousePos)) {
                            //-------------------------------------colore import
                            int colorr = getVariableFromFile("profile2", 0);
                            if (colorr == 3) {
                                colorNumber = 3;
                                button2.updateText("RED");
                            }
                            if (colorr == 2) {
                                colorNumber = 2;
                                button2.updateText("YELLOW");
                            }
                            if (colorr == 1) {
                                colorNumber = 1;
                                button2.updateText("PURPLE");
                            }
                            //-------------------------------------toggle shot import
                            int togglee = getVariableFromFile("profile2", 1);
                            if (togglee == 2) {
                                toggleShot = 2;
                                status2 = toggleShot;
                                button3.updateText("HOLD BUTTON");
                            }
                            if (togglee == 1) {
                                toggleShot = 1;
                                status2 = toggleShot;
                                button3.updateText("PRESS BUTTON");
                            }
                            //-------------------------------------toggle shot import
                            int shotMovee = getVariableFromFile("profile2", 2);
                            if (shotMovee == 2) {
                                shotMove = 2;
                                button4.updateText("Move&Shot: OFF");
                            }
                            if (shotMovee == 1) {
                                shotMove = 1;
                                button4.updateText("Move&Shot: ON");
                            }
                            int aimLockInt2 = getVariableFromFile("profile2", 4);
                            if (aimLockInt2 == 2) {
                                //aimLock = true;
                               // aimLockInt = 2;
                                button14.updateText("LOCKED!");
                            }
                            if (aimLockInt2 == 1) {
                               // aimLock = false;
                               // aimLockInt = 1;
                                button14.updateText("LOCKED!");
                            }
                            changes = true;
                            status1 = 2;
                            button1.updateText("STATUS: ON");
                            button10.changeBackgroundColor(sf::Color(114, 85, 85, 175));
                            button11.changeBackgroundColor(sf::Color(224, 224, 224, 125));
                            button12.changeBackgroundColor(sf::Color(114, 85, 85, 175));
                        }
                        //----------------------------------------------------------------------------------------------PROFILE 3
                        if (button12.contains(mousePos)) {
                            //-------------------------------------colore import
                            int colorr = getVariableFromFile("profile3", 0);
                            if (colorr == 3) {
                                colorNumber = 3;
                                button2.updateText("RED");
                            }
                            if (colorr == 2) {
                                colorNumber = 2;
                                button2.updateText("YELLOW");
                            }
                            if (colorr == 1) {
                                colorNumber = 1;
                                button2.updateText("PURPLE");
                            }
                            //-------------------------------------toggle shot import
                            int togglee = getVariableFromFile("profile3", 1);
                            if (togglee == 2) {
                                toggleShot = 2;
                                status2 = toggleShot;
                                button3.updateText("HOLD BUTTON");
                            }
                            if (togglee == 1) {
                                toggleShot = 1;
                                status2 = toggleShot;
                                button3.updateText("PRESS BUTTON");
                            }
                            //-------------------------------------toggle shot import
                            int shotMovee = getVariableFromFile("profile3", 2);
                            if (shotMovee == 2) {
                                shotMove = 2;
                                button4.updateText("Move&Shot: OFF");
                            }
                            if (shotMovee == 1) {
                                shotMove = 1;
                                button4.updateText("Move&Shot: ON");
                            }
                            int aimLockInt2 = getVariableFromFile("profile3", 4);
                            if (aimLockInt2 == 2) {
                               // aimLock = true;
                               // aimLockInt = 2;
                                button14.updateText("LOCKED!");
                            }
                            if (aimLockInt2 == 1) {
                              //  aimLock = false;
                               // aimLockInt = 1;
                                button14.updateText("LOCKED!");
                            }
                            changes = true;
                            status1 = 2;

                            button1.updateText("STATUS: ON");

                            button10.changeBackgroundColor(sf::Color(114, 85, 85, 175));
                            button11.changeBackgroundColor(sf::Color(114, 85, 85, 175));
                            button12.changeBackgroundColor(sf::Color(224, 224, 224, 125));//(153, 153, 255, 175)
                        }
                    }

                }

                if (event.type == sf::Event::MouseMoved) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    button1.setHighlightedOption(mousePos);
                    button2.setHighlightedOption(mousePos);
                    button3.setHighlightedOption(mousePos);
                    button4.setHighlightedOption(mousePos);
                    button14.setHighlightedOption(mousePos);
                }
            }
        }

        if (isFocused) {
            window.clear(sf::Color::White);
            window.draw(background);
            button1.draw(window);
            button2.draw(window);
            button3.draw(window);
            button4.draw(window);
            button5.draw(window);
            //button9.draw(window);
            button10.draw(window);
            button11.draw(window);
            button12.draw(window);
            button13.draw(window);
         // button14.draw(window);
            // window.draw(label);
            window.display();
            // Clear the window with black color
        }

        {//trigger funzionalità
            HDC hDC = nullptr;
            gdiSurface->GetDC(true, &hDC);
            hdc_target = GetDC(GetDesktopWindow());
            if (mouseMOVED3) { //mouseMOVED3
                algoValue = isMouseMoved2();
                if (algoValue >= 0 && algoValue <= 2) {
                    startXaltered = startXaltered2;
                    pixel = 1;
                }
                if (algoValue >= 3 && algoValue <= 4) {
                    startXaltered = startXaltered2;
                    pixel = 3;
                }
                if (algoValue >= 5 && algoValue <= 7) {
                    startXaltered = startXaltered2 + 4;
                    pixel = 5;
                }
                if (algoValue >= 8 && algoValue <= 13) {
                    startXaltered = startXaltered2 + 7;
                    pixel = 7;
                }
                if (algoValue >= 14 && algoValue <= 100) {
                    startXaltered = startXaltered2 + 8;
                    pixel = 10;
                }
                // std::cout << "MOUSE MOVEMENT: " << algoValue << std::endl;
                // std::cout << "pixel: " << pixel << std::endl;
            }
            if (GetAsyncKeyState(VK_F6) & 0x8000) {
                isFocused = false;
                window.setFramerateLimit(1);
                HideWindow(window);
            }
            if (GetAsyncKeyState(VK_F5) & 0x8000) {
                isFocused = true;
                window.setFramerateLimit(60);
                ShowWindow(window);
            }

            if (isMouseMoved()) {
                if (mouseMOVED4) {
                    mouseMOVED4 = false;
                    mouseMOVED3 = true;
                    //std::cerr <<"PIXEL MOUSE MOVIMENTO: "<<pixel << std::endl;
                }
            }
            else
            {
                if (mouseMOVED3) {
                    startXaltered = startXaltered2;
                    pixel = 4;
                    mouseMOVED3 = false;
                    mouseMOVED4 = true;
                    // std::cerr << "PIXEL MOUSE FERMO: " << pixel << std::endl;
                }
            }

            if (timer3.moreThanOneSecondPassed(1000) && mouseMOVED4) {
                startXaltered = startXaltered2 + 7;
                permissionShot = false;
                pixel = 7;
                //cout << "pixel; " << pixel << endl;
            }
            if (timer1.moreThanOneSecondPassed(200)) {
                permissionShot = false;
            }

            if (timer2.moreThanOneSecondPassed(150) && !delayShoting) {
                delayShoting = true;
                //cout << "pixel; " << pixel << endl;
            }
            if (GetAsyncKeyState(VK_LCONTROL)) {
                crouchControl = true;
                startXaltered = startXaltered2 + 9;
                pixel = 15;

            }
            ID3D11Texture2D* pFrameCopy = nullptr;
            HRESULT hr = lDevice->CreateTexture2D(&desc, nullptr, &pFrameCopy);
            if (FAILED(hr)) {
                continue;
            }
            if (BitBlt(hDC, 0, 0, captureWidth, captureHeight, hdc_target, startXaltered, startY, SRCCOPY)) {
                ReleaseDC(NULL, hdc_target);
                gdiSurface->ReleaseDC(nullptr);

                lImmediateContext->CopyResource(pFrameCopy, texture.Get());

                D3D11_MAPPED_SUBRESOURCE tempsubsource;
                hr = lImmediateContext->Map(pFrameCopy, 0, D3D11_MAP_READ, 0, &tempsubsource);
                if (SUCCEEDED(hr)) {
                    void* d = tempsubsource.pData;
                    char* data = reinterpret_cast<char*>(d);

                    if (toggleShot == 1) {
                        if (GetAsyncKeyState(userKey) || changes) {
                            if (!changes) {
                                status1++;
                            }
                            if (status1 % 2 == 0) {
                                //text.setString("STATUS: OFF");
                                if (!changes) {
                                    button1.toggleOption();
                                    bool played = PlaySound(TEXT("ON"), NULL, SND_ASYNC);
                                }
                                //bool played = PlaySound(TEXT("ON"), NULL, SND_ASYNC);
                            }
                            else {

                                if (!changes) {
                                    button1.toggleOption();
                                    bool played = PlaySound(TEXT("OFF"), NULL, SND_ASYNC);
                                }
                                //bool played = PlaySound(TEXT("OFF"), NULL, SND_ASYNC);
                            }
                            SetVolume(0x3999);
                            changes = false;
                            Sleep(400);
                        }
                    }

                    if (toggleShot == 2 && status1 % 2 == 0 && GetAsyncKeyState(userKey) && !GetAsyncKeyState(0x001)) {
                        checkColorSelected(data, captureWidth, captureHeight, pixel);
                    }

                    if (toggleShot == 1 && status1 % 2 == 0 && !GetAsyncKeyState(0x001)) {
                        checkColorSelected(data, captureWidth, captureHeight, pixel);
                    }                
                }
            }
            lImmediateContext->Unmap(pFrameCopy, 0);
            lImmediateContext->Flush();
            pFrameCopy->Release();
       
               
        }
    }
    return 0;
}

