#ifndef __ctHondaStageScene_H__
#define __ctHondaStageScene_H__

#include "ctModule.h"
#include "ctAnimation.h"

class ctHondaStageScene : public ctModule
{
public:

	ctHondaStageScene();

	// Destructor
	virtual ~ctHondaStageScene();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool Load(pugi::xml_node&);

	bool Save(pugi::xml_node&) const;

	void OnUITrigger(UIElement* elementTriggered, UI_State ui_state);

private:
	void LoadAnimation(pugi::xml_node animation_node, ctAnimation* animation);
	void LoadRect(pugi::xml_node rect_node, SDL_Rect rect);

private:

	bool quit_pressed = false;

	std::string atlas_name;
	SDL_Texture* atlas_tex = nullptr;

	SDL_Rect ground = { 0,0,0,0 };
	SDL_Rect foreground = { 0,0,0,0 };
	SDL_Rect background = { 0,0,0,0 };

	ctAnimation girl = ctAnimation();
	ctAnimation flag = ctAnimation();

};


#endif // __ctHondaStageScene_H__