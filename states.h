#ifndef STATES_H
#define STATES_H

struct Action {
protected:
	static void GotoState(Action*, bool complete = true);

public:
	static void InitSystem();
	static Action* GetCurrentAction();

	virtual void Enter() {};
	virtual void Update() {};
	virtual void Cancel() {};
	virtual void Complete() {};
};

#endif