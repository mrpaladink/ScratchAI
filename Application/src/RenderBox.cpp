#include "RenderBox.hpp"

#include "Texture.hpp"
#include "Font.hpp"

RenderBox::RenderBox() {
	m_RenderQueue.reserve(64);
}

void RenderBox::Render(const Texture& texture, const FloatRect& rect, const UIntRect& area) {
	RenderQueueElement rqe = {};
	rqe.type = RenderQueueElement::Type::Texture;
	rqe.texture = (Texture*) & texture;
	rqe.rect = rect;
	rqe.area = area;

	m_RenderQueue.push_back(rqe);
}

void RenderBox::Render(const Font& font, uint8_t alignment, const char* text, const FloatRect& rect, const UIntRect& area) {
	RenderQueueElement rqe = {};
	rqe.type = RenderQueueElement::Type::Font;
	rqe.font = (Font*)&font;
	rqe.alignment = alignment;
	rqe.text = text;
	rqe.rect = rect;
	rqe.area = area;

	m_RenderQueue.push_back(rqe);
}