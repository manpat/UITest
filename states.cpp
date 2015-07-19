#include "states.h"
#include "debug.h"
#include "vec2.h"

namespace {
	Action* currentAction = nullptr;
}

Action* Action::GetCurrentAction(){
	return currentAction;
}

void Action::GotoState(Action* naction, bool complete){
	if(currentAction) {
		if(complete){
			currentAction->Complete();
		}else{
			currentAction->Cancel();
		}

		delete currentAction;
	}

	currentAction = naction;
	currentAction->Enter();
}

/*
	                                        
	88888888ba,                         88  
	88      `"8b                        88  
	88        `8b                       88  
	88         88  ,adPPYba,  ,adPPYba, 88  
	88         88 a8P_____88 a8"     "" 88  
	88         8P 8PP""""""" 8b         88  
	88      .a8P  "8b,   ,aa "8a,   ,aa 88  
	88888888Y"'    `"Ybbd8"'  `"Ybbd8"' 88  
	                                        
	                                        
*/
#include "input.h"
#include "app.h"
#include "ui.h"

namespace {
	ui::Element* element;
}

struct Idle : Action {
	void Update() override;
};

struct Click : Action {
	Click(uint b = 0) : button(b) {}
	void Enter() override;
	void Update() override;
	void Cancel() override;
	void Complete() override;

	uint button;
};

struct Drag : Action {
	Drag(uint b = 0) : button(b) {}
	void Enter() override;
	void Update() override;
	void Cancel() override;
	void Complete() override;

	uint button;
	vec2 start;
	vec2 end;
};

void Action::InitSystem(){
	GotoState(new Idle);
}

/*
	                                  
	88888888ba,                 ad88  
	88      `"8b               d8"    
	88        `8b              88     
	88         88  ,adPPYba, MM88MMM  
	88         88 a8P_____88   88     
	88         8P 8PP"""""""   88     
	88      .a8P  "8b,   ,aa   88     
	88888888Y"'    `"Ybbd8"'   88     
	                                  
	                                  
*/
void Idle::Update() {
	if(Input::GetButtonDown(0)){
		GotoState(new Click{0});
		return;
	}
	if(Input::GetButtonDown(1)){
		GotoState(new Click{1});
		return;
	}
	if(Input::GetButtonDown(2)){
		GotoState(new Click{2});
		return;
	}
}

void Click::Enter() {
	debug::log("Click enter ", button);

	if(button == 2){
		auto mpos = Input::GetMousePosition()*App::GetAspectVec();
		if(!(element = ui::GetElementAt(mpos))){
			element = ui::CreatePanel(mpos, {0.2, 0.2});
		}
	}
}
void Click::Update() {
	if(Input::GetButtonUp(button)){
		GotoState(new Idle);
		return;
	}

	if(Input::GetMouseDelta().magnitude() > 0.001){
		GotoState(new Drag(button), false);
		return;
	}
}
void Click::Cancel() {
	debug::log("Click cancel");
}
void Click::Complete() {
	debug::log("Click complete");
	if(element) element->OnClick(button);
}

void Drag::Enter() {
	debug::log("Drag begin ", button);
	start = Input::GetMousePosition()*App::GetAspectVec();
}
void Drag::Update() {
	end = Input::GetMousePosition()*App::GetAspectVec();

	if(Input::GetButtonUp(button)){
		GotoState(new Idle);
		return;
	}

	if(element) element->OnDrag(end);

}
void Drag::Cancel() {
	debug::log("Drag cancel");
}
void Drag::Complete() {
	debug::log("Drag complete");
	element = nullptr;
}