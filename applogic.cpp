#include "app.h"
#include "input.h"
#include "debug.h"
#include "ui.h"
#include "gfx.h"
#include "states.h"

namespace App {
	void Update(){
		Action::GetCurrentAction()->Update();
	}

	void Render(){
		glClearColor(Input::GetButton(2)?1:0.5, 0.6+Input::GetMousePosition().y*0.5, 0.6, 1);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glEnableVertexAttribArray(0 /*pos*/);
		GetShader()->SetFloat("aspect", GetAspect());
		ui::Render();
	}
}