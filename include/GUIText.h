#ifndef GUITEXT_H
#define GUITEXT_H

#include <string>
#include <Drawable.h>
#include <map>
#include <glm/common.hpp>

#include "Camera.h"
#include "Rectangle.h"
//#include "Texture.h"
//#include "FontShader.h"
//#include "Transform.h"

struct Character
{
    float x;
    float y;
    float width;
    float height;
    float xoffset;
    float yoffset;
    float xadvance;
};

enum Mode {DYNAMIC, STATIC};

class GUIText : public Drawable
{
    public:
        GUIText(string fontname);
        GUIText();
        virtual ~GUIText();

        void Load();
        void Draw(Camera* camera, ShaderOptions* shader);
        void Update();

        void SetText(string Text) {
            _text = Text;
        }

        string GetText() {
            return _text;
        }

        void SetFontSize(float fontSize)
        {
            _fontSize = fontSize;
            _fontSizeMultiplier = fontSize / _loadedFontSize;
            _lineSpacing = fontSize;
        }

        float GetFontSize() {
            return _fontSize;
        }

    protected:

    private:

        map<int, Character> _characters;
        glm::vec3           _color = glm::vec3(0,0,0);
        string              _fontname;
        string              _text = "I'm cool. \nHello World!";
        float               _fontSize;
        float               _fontSizeMultiplier;
        float               _lineSpacing;
        int                 _mode;
        float               _textureWidth;
        float               _textureHeight;
        float               _loadedFontSize;
        Rectangle           _characterMesh = Rectangle();


};

#endif // GUITEXT_H
