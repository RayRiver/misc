#include "Display.h"

USING_NS_CC;

DisplayHelper *DisplayHelper::s_instance = nullptr;

DisplayHelper * DisplayHelper::getInstance()
{
	if (!s_instance)
	{
		s_instance = new DisplayHelper;
	}
	return s_instance;
}

DisplayHelper::DisplayHelper()
{
	m_rect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	m_size = m_rect.size;
	m_width = m_rect.size.width;
	m_height = m_rect.size.height;

	m_sizeInPixels = Director::getInstance()->getOpenGLView()->getFrameSize();
	m_widthInPixels = m_sizeInPixels.width;
	m_heightInPixels = m_sizeInPixels.height;

	m_left = m_rect.origin.x;
	m_right = m_rect.origin.x + m_rect.size.width;
	m_top = m_rect.origin.y + m_rect.size.height;
	m_bottom = m_rect.origin.y;

	m_cx = m_left + m_width / 2;
	m_cy = m_bottom + m_height / 2;

	m_pointCenter = Vec2(m_cx, m_cy);
	m_pointLeftTop = Vec2(m_left, m_top);
	m_pointLeftBottom = Vec2(m_left, m_bottom);
	m_pointRightTop = Vec2(m_right, m_top);
	m_pointRightBottom = Vec2(m_right, m_bottom);
	m_pointLeftCenter = Vec2(m_left, m_cy);
	m_pointRightCenter = Vec2(m_right, m_cy);
	m_pointTopCenter = Vec2(m_cx, m_top);
	m_pointBottomCenter = Vec2(m_cx, m_bottom);
}

DisplayHelper::~DisplayHelper()
{

}
