#ifndef DisplayHelper_h__
#define DisplayHelper_h__

#include "cocos2d.h"

class DisplayHelper
{
public:
	static DisplayHelper *getInstance();
	~DisplayHelper();

	// visible rect
	inline const cocos2d::Size &size() { return m_size; }
	inline const cocos2d::Size &sizeInPixels() { return m_sizeInPixels; }
	inline const cocos2d::Rect &rect() { return m_rect; }
	inline float width() { return m_width; }
	inline float height() { return m_height; }
	inline float widthInPixels() { return m_widthInPixels; }
	inline float heightInPixels() { return m_heightInPixels; }

	// coordinate
	inline float left() { return m_left; }
	inline float right() { return m_right; }
	inline float top() { return m_top; }
	inline float bottom() { return m_bottom; }
	inline float cx() { return m_cx; }
	inline float cy() { return m_cy; }
	inline float nx(float n) { return m_left + m_width * n; }
	inline float ny(float n) { return m_bottom + m_height * n; }

	// point
	inline const cocos2d::Vec2 &pointCenter() { return m_pointCenter; }
	inline const cocos2d::Vec2 &pointLeftTop() { return m_pointLeftTop; }
	inline const cocos2d::Vec2 &pointTopLeft() { return m_pointLeftTop; }
	inline const cocos2d::Vec2 &pointLeftBottom() { return m_pointLeftBottom; }
	inline const cocos2d::Vec2 &pointBottomLeft() { return m_pointLeftBottom; }
	inline const cocos2d::Vec2 &pointRightTop() { return m_pointRightTop; }
	inline const cocos2d::Vec2 &pointTopRight() { return m_pointRightTop; }
	inline const cocos2d::Vec2 &pointRightBottom() { return m_pointRightBottom; }
	inline const cocos2d::Vec2 &pointBottomRight() { return m_pointRightBottom; }
	inline const cocos2d::Vec2 &pointTopCenter() { return m_pointTopCenter; }
	inline const cocos2d::Vec2 &pointBottomCenter() { return m_pointBottomCenter; }
	inline const cocos2d::Vec2 &pointLeftCenter() { return m_pointLeftCenter; }
	inline const cocos2d::Vec2 &pointRightCenter() { return m_pointRightCenter; }

	// CCNode
	inline cocos2d::Rect getContentRect(cocos2d::Node *node) 
	{
		const cocos2d::Vec2 &_pos = node->getPosition();
		const cocos2d::Size &_size = node->getContentSize();
		const cocos2d::Vec2 &_anchorPoint = node->getAnchorPoint();
		auto x = _pos.x-_size.width*_anchorPoint.x;
		auto y = _pos.y-_size.height*_anchorPoint.y;
		return cocos2d::Rect(x, y, _size.width, _size.height);
	}

	inline cocos2d::Rect getCenterContentRect(cocos2d::Node *node) 
	{
		const cocos2d::Vec2 &_pos = node->getPosition();
		const cocos2d::Size &_size = node->getContentSize();
		auto x = _pos.x-_size.width*0.5;
		auto y = _pos.y-_size.height*0.5;
		return cocos2d::Rect(x, y, _size.width, _size.height);
	}

	inline void rect2points(const cocos2d::Rect &r, cocos2d::Vec2 *points)
	{
		points[0].x = r.origin.x;
		points[0].y = r.origin.y;
		points[1].x = r.origin.x + r.size.width;
		points[1].y = r.origin.y;
		points[2].x = r.origin.x + r.size.width;
		points[2].y = r.origin.y + r.size.height;
		points[3].x = r.origin.x;
		points[3].y = r.origin.y + r.size.height;
	}

private:
	float m_left, m_right, m_top, m_bottom;
	float m_cx, m_cy;
	float m_width, m_height;
	float m_widthInPixels, m_heightInPixels;
	cocos2d::Size m_size;
	cocos2d::Size m_sizeInPixels;
	cocos2d::Rect m_rect;

	cocos2d::Vec2 m_pointCenter;
	cocos2d::Vec2 m_pointLeftTop, m_pointLeftBottom, m_pointRightTop, m_pointRightBottom;
	cocos2d::Vec2 m_pointTopCenter, m_pointBottomCenter, m_pointLeftCenter, m_pointRightCenter;

private:
	DisplayHelper();
	static DisplayHelper *s_instance;

};

#define DISPLAY (DisplayHelper::getInstance())

#endif // DisplayHelper_h__
