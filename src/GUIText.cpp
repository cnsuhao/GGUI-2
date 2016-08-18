#include "GUIText.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

GUIText::GUIText(string fontname)
{

    _fontname = fontname;
    _characters = map<int, Character>();
    _mode = DYNAMIC;
}

GUIText::GUIText()
{
    _characters = map<int, Character>();
    _mode = DYNAMIC;
}

GUIText::~GUIText()
{
    //_characterMesh.Unload();
}

void GUIText::Load()
{

    _characterMesh.RectangleDrawMode = TEXTURELESS;

    // Apply default font to unspecifed font objects
    if (_fontname == "")
       _fontname = "CMUSerif";

    // Parse path to font information
    stringstream path;
    path << "Content/Fonts/" << _fontname << "/" << _fontname << ".fnt";

    // Create font information reader
    ifstream fontreader(path.str().c_str());

    // Check if the font reader was opened
    if (!fontreader)
    {
        cout << "Error opening file: " << path.str() << "!" << endl;
        return;
    }
    else
    {

        string      line;
        Character   charBuffer;

        while ( getline (fontreader, line) )
        {
            vector<string> lineinfo = split(line, ' ');
            if (lineinfo[0] == "char")
            {
                // Construct a character from current line
                //x and y: x=xyz
                charBuffer.x = stof((lineinfo[2]).substr(2,lineinfo[2].size()) );
                charBuffer.y = stof((lineinfo[3]).substr(2,lineinfo[3].size()) );
                //width and height: width=xyz / height=xyz
                charBuffer.width = stof((lineinfo[4]).substr(6,lineinfo[4].size()) );
                charBuffer.height = stof((lineinfo[5]).substr(7,lineinfo[5].size()) );
                charBuffer.xoffset = stof((lineinfo[6]).substr(8,lineinfo[6].size()) );
                charBuffer.yoffset = stof((lineinfo[7]).substr(8,lineinfo[7].size()) );
                charBuffer.xadvance = stof((lineinfo[8]).substr(9,lineinfo[8].size()) );
                //Save the character to the vector
                _characters[stoi((lineinfo[1]).substr(3,lineinfo[1].size()))] = (charBuffer);
            } else if (lineinfo[0] == "page")
            {
                // Parse path to font information
                path.str("");
                path << "Content/Fonts/" << _fontname << "/" << (lineinfo[2]).substr(6,(lineinfo[2].size())-7);
                //_textureAtlas.Load(path.str(), true);
                _characterMesh.SpecialPath = path.str();
                _characterMesh.Load();
            } else if (lineinfo[0] == "common")
            {
                _textureWidth = stof(lineinfo[3].substr(7, lineinfo[3].size()));
                _textureHeight = stof(lineinfo[4].substr(7, lineinfo[4].size()));
            } else if (lineinfo[0] == "info")
            {
                _loadedFontSize = stof(lineinfo[3].substr(5, lineinfo[3].size()));
            } else if (lineinfo[0] == "kernings")
            {
                break;
            }

        }

        // Close the font reader
        fontreader.close();

        _fontSizeMultiplier = 1.0f;
        _fontSize = _loadedFontSize;
        _lineSpacing = _loadedFontSize;
        // Rectangle settings
        //_characterMesh.setSize(_fontSizeMultiplier);
        //_characterMesh.extendedDraw = true;


    }


}

void GUIText::Draw(Camera* camera, ShaderOptions* shader)
{

    if (_mode == DYNAMIC)
    {

        shader->Color = _color;
        shader->FontRendering = true;
        shader->TextureWidth = _textureWidth;
        shader->TextureHeight = _textureHeight;
        shader->CharacterInfoChanged = true;
        shader->FontInfoChanged = true;

        _characterMesh.setPosition(this->_position);
        _characterMesh.Update();

        int currentLine = 0;

        // Draw each character
		_characterMesh.BindTexture();
        for (int i = 0; i < _text.size(); i++) {
            if((int)_text[i] != 10) {
                // Send composition information to the shader
                shader->FontX = _characters[(int)_text[i]].x;
                shader->FontY = _characters[(int)_text[i]].y;
                shader->FontWidth = _characters[(int)_text[i]].width;
                shader->FontHeight = _characters[(int)_text[i]].height;

                //Offset
                _characterMesh.setPosition(
                    _characterMesh.getPosition().x + (_characters[(int)_text[i]].xoffset)*_fontSizeMultiplier,
                    _characterMesh.getPosition().y + (_characters[(int)_text[i]].yoffset)*_fontSizeMultiplier + (currentLine*_lineSpacing)
                );

                _characterMesh.setWidth(
                    _characters[(int)_text[i]].width *_fontSizeMultiplier
                );

                _characterMesh.setHeight(
                    _characters[(int)_text[i]].height*_fontSizeMultiplier
                );

                _characterMesh.Update();

                //Draw the current character
                _characterMesh.Draw(camera, shader);

                //Advance the cursor
                _characterMesh.setPositionX(_characterMesh.getPosition().x
                    + (_characters[(int)_text[i]].xadvance)*_fontSizeMultiplier);
                  //  - (_characters[(int)_text[i]].xoffset));
                _characterMesh.setPositionY(this->_position.y);
            } else {
                currentLine++;
                _characterMesh.setPositionX(this->_position.x);
            }
            _characterMesh.Update();
        }

        shader->CharacterInfoChanged = false;
        shader->FontRendering = false;
        shader->Color = glm::vec3(1.0);
    }
    else if (_mode == STATIC)
    {

    }
}

void GUIText::Update()
{

    //_characterMesh.Update();
}


