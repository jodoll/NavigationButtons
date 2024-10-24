class KeyMap
{
private:
public:
    static KeyMap &idle()
    {
        static KeyMap instance;
        return instance;
    }

    KeyMap(/* args */){}
    ~KeyMap(){}
};

