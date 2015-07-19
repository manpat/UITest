#include "ui.h"
#include "debug.h"
#include "app.h"

namespace ui {
	Panel* CreatePanel(const vec2& pos, const vec2& size){
		auto p = new Panel(pos, size);
		elements.push_back(p);
		return p;
	}

	void Render() {
		for(auto e: elements){
			e->Render();
		}
	}

	Element* GetElementAt(const vec2&){
		return nullptr;
	}

	Panel::Panel(const vec2& pos, const vec2& size): pos(pos), size(size) {
		std::vector<vec2> points{
			{-size.x,-size.y},
			{ size.x,-size.y},
			{ size.x, size.y},
			{-size.x, size.y},
		};

		quad.Bind();
		quad.Upload(points);
		quad.Unbind();
		debug::log("Panel created");
	}

	void Panel::Render() {
		App::GetShader()->SetVec2("pos", pos);
		quad.Draw(GL_TRIANGLE_FAN);
	}

	void Panel::OnDrag(const vec2& npos){
		pos = npos;
	}
}