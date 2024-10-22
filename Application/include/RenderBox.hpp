#include "Rect.hpp"

#include <SDL3/SDL.h>
#include <vector>

class Texture;
class Font;
class RenderWindow;

struct RenderBox {
public:
	RenderBox();

	void Render(const Texture& texture, const FloatRect& rect, const UIntRect& area = UIntRect());

	void Render(const Font& font, uint8_t alignment, const char* text, const FloatRect& rect, const UIntRect& area = UIntRect());

	FloatRect m_Rect;
	FloatRect m_InsideDimensions;
	Color	  m_OutlineColor;
	Color	  m_BackgroundColor;

	friend class RenderWindow;

private:
	struct RenderQueueElement {
		enum class Type {
			Texture,
			Font,
			None
		};

		Type		type		= Type::None;
		Texture*	texture		= nullptr;
		Font*		font		= nullptr;
		uint8_t		alignment	= 0;
		const char*	text		= nullptr;
		FloatRect	rect;
		UIntRect				area;
	};

	std::vector<RenderQueueElement> m_RenderQueue;
};