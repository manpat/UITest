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

	Element* GetElementAt(const vec2& p){
		for(auto e: elements){
			if(e->CollisionTest(p)) return e;
		}

		return nullptr;
	}

	Panel::Panel(const vec2& pos, const vec2& size): pos(pos), size(size) {
		std::vector<vec2> points{
			{-size.x/2.f,-size.y/2.f},
			{ size.x/2.f,-size.y/2.f},
			{ size.x/2.f, size.y/2.f},
			{-size.x/2.f, size.y/2.f},
		};

		quad.Bind();
		quad.Upload(points);
		quad.Unbind();
		debug::log("Panel created");
	}

	bool Panel::CollisionTest(const vec2& v) {
		auto diff = v-pos;
		diff.x = std::abs(diff.x);
		diff.y = std::abs(diff.y);

		return !(diff.x > size.x/2.f || diff.y > size.y/2.f);
	}

	void Panel::Render() {
		App::GetShader()->SetVec2("pos", pos);
		quad.Draw(GL_TRIANGLE_FAN);
	}

	void Panel::OnDrag(const vec2& npos){
		pos = npos;
	}
}