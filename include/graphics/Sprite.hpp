#include "graphics/RenderObject.hpp"

#include "core/MethResult.hpp"

namespace Pneumatic {

namespace Graphics {

class Sprite : public Pneumatic::Graphics::RenderObject {
public:
	Sprite(void);
	~Sprite(void) = default;

	auto load(const std::string& file_name) -> MethResult;
};

} // namespace Graphics

} // namespace Pneumatic
