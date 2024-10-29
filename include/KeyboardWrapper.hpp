#include "keyboard/Keyboard.hpp"
#include "BleKeyboard.h"
#include <memory>

class KeyboardWrapper
{
private:
    static const MediaKeyReport *toMediaKeyReport(const MediaKeyCode &mediaKey);

    struct BleKey
    {
        virtual std::string asText() = 0;
        virtual void writeKey(BleKeyboard &keyboard) = 0;
        virtual void holdKey(BleKeyboard &keyboard) = 0;
        virtual void releaseKey(BleKeyboard &keyboard) = 0;
    };
    struct MediaReportKey : BleKey
    {
        MediaReportKey(const MediaKeyCode &mediaKey, const std::string text)
            :report(toMediaKeyReport(mediaKey)), text(text){} 

        const MediaKeyReport *report;
        const std::string text;

        std::string asText() override;
        void writeKey(BleKeyboard &keyboard) override;
        void holdKey(BleKeyboard &keyboard) override;
        void releaseKey(BleKeyboard &keyboard) override;
    };
    struct CharKey : BleKey
    {
        CharKey(const char character)
            : character(character), text(std::string(1, character)) {}
        const char character;
        const std::string text;

        std::string asText() override;
        void writeKey(BleKeyboard &keyboard) override;
        void holdKey(BleKeyboard &keyboard) override;
        void releaseKey(BleKeyboard &keyboard) override;
    };

    BleKeyboard bleKeyboard = BleKeyboard("NavigationButtons", "jodoll", 100);

    std::shared_ptr<BleKey> toBleKey(const Keyboard::Key &key);

public:
    void connect();
    void writeKey(const Keyboard::Key &key);
    void holdKey(Keyboard::Key &key);
    void releaseKey(Keyboard::Key &key);
    void releaseAll();
};
