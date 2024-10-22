#include "../TextInput.hpp"
#include "Rect.hpp"
#include "Font.hpp"

class Edit {
public:
	Edit(const Keyboard& keyboard);

	void SetFont(const Font& font);

	void SetSize(const FloatRect& size);

	void Update();

private:

};