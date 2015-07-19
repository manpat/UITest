#ifndef UI_H
#define UI_H

#include <vector>
#include "vec2.h"
#include "gfx.h"

namespace ui {
	class Element;
	class Panel;

	enum class ElementType {
		Panel,
		Button,
	};

	namespace {
		std::vector<Element*> elements;
	}

	void Render();
	Panel* CreatePanel(const vec2& pos, const vec2& size);
	Element* GetElementAt(const vec2&);

	class Element {
	public:
		// virtual ~Element() {};
		virtual ElementType GetType() const = 0;

		virtual void Render() {};

		virtual void OnClick(uint button) {};
		virtual void OnDrag(const vec2&) {};
	};

	class Panel : public Element {
	protected:
		vec2 pos, size;
		gfx::VBO quad;
	public:
		Panel(const vec2& pos, const vec2& size);
		ElementType GetType() const override { return ElementType::Panel; }

		void Render() override;
		void OnDrag(const vec2&) override;
	};
}

#endif