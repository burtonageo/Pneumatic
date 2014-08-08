#include "graphics/RenderObject.hpp"

#include "core/MethResult.hpp"

namespace pneu {

namespace graphics {

class Sprite : public pneu::graphics::RenderObject {
public:
	Sprite(void);
	~Sprite(void) = default;

	auto load(const std::string& file_name) -> MethResult;
};

} // namespace graphics

} // namespace pneu
