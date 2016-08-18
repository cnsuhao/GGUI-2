// Copyright Candfa 2016
#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <glm/glm.hpp>

class Drawable {
 public:
	 Drawable(){ };
	virtual ~Drawable(){};
    // Functions to inherit
	virtual void Load(){};
	virtual void Update(){};
	virtual void Draw(){};
    // Getters
    float getDistance() {
        return _distance;
    }
    float getOpacity() {
        return _opacity;
    }
    glm::vec2 getPosition() {
        return _position;
    }
    glm::vec2 getSize() {
        return _size;
    }
    // Setters
    void setDistance(float Distance) {
        _distance = Distance;
        _distanceChanged = true;
    }
    void setOpacity(float Opacity) {
        _opacity = Opacity;
       // _opacityChanged = true;
    }
    void setPosition(glm::vec2 Position) {
        _position = Position;
		_positionChanged = true;
    }
    void setPosition(float x, float y) {
        _position = glm::vec2(x, y);
		_positionChanged = true;
	}
    void setPositionX(float x) {
        _position.x = x;
		_positionChanged = true;
    }
    void setPositionY(float y) {
        _position.y = y;
		_positionChanged = true;
    }
    void setSize(glm::vec2 Size) {
        _size = Size;
		_sizeChanged = true;
    }
	void setSize(float Width, float Height) {
		_size = glm::vec2(Width, Height);
		_sizeChanged = true;
	}
	void setSize(float WidthHeight) {
		_size = glm::vec2(WidthHeight);
		_sizeChanged = true;
	}
    void setWidth(float Width) {
        _size.x = Width;
		_sizeChanged = true;
    }
    void setHeight(float Height) {
		_size.y = Height;
		_sizeChanged = true;
    }

 protected:
    glm::vec2 _position = glm::vec2(10, 10);
	glm::vec2 _size = glm::vec2(300.0f, 300.0f);
    float _distance = 1.0f;
    float _opacity = 1.0f;
	bool _positionChanged = true;
	bool _sizeChanged = true;
    bool _distanceChanged = true;
    //bool _opacityChanged = true;
};

#endif