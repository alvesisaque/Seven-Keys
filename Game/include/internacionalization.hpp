#ifndef INTERNACIONALIZATION
#define INTERNACIONALIZATION

#include "core/level.hpp"
#include <string>

#define DEFAULT_LANGUAGE_PATH "EN-US"
#define LANGUAGE_PATH "language"
class Image;

class Internacionalization : public Level
{
public:
    /*static string load_string(const string& language, const string& source_to_translate);*/
    Internacionalization();

    static string load_string(const string& source_to_translate);
    virtual ~Internacionalization();

    bool on_message(Object *object, MessageID id, Parameters);

private:
    void set_language(const string& language);
    static string get_language();
    static const string GAME_RESOURCE_PATH;
    string game_language;
    void draw_self();
};

#endif
