#ifndef __ctKenStageScene_H__
#define __ctKenStageScene_H__

#include "ctModule.h"
#include "ctAnimation.h"
#include "ctGui.h"

class ctKenStageScene : public ctModule
{
public:

	ctKenStageScene();

	// Destructor
	virtual ~ctKenStageScene();

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
	void LoadRect(pugi::xml_node rect_node, SDL_Rect* rect);

	void SetSceneAnimationsSpeed(float dt);
	void SetEntitiesSpeed(float dt);

private:

	bool quit_pressed = false;

	float foreground_pos = 0.0f;
	bool forward_foreground = false;

	std::string atlas_name;
	SDL_Texture* atlas_tex = nullptr;

	SDL_Rect ground = { 0,0,0,0 };
	SDL_Rect foreground = { 0,0,0,0 };
	SDL_Rect background = { 0,0,0,0 };

	//animations
	ctAnimation flag = ctAnimation();
	ctAnimation girl = ctAnimation();
	ctAnimation two_guys = ctAnimation();
	ctAnimation green_guy = ctAnimation();
	ctAnimation blue_guy = ctAnimation();
	ctAnimation fedora_guy = ctAnimation();
	ctAnimation pink_guy = ctAnimation();

	//animations velocity
	uint girl_vel = 0u, flag_vel = 0u, two_guys_vel = 0u, green_guy_vel = 0u, blue_guy_vel = 0u, fedora_guy_vel = 0u, pink_guy_vel = 0u;

	bool key_speed = false;

};


#endif // __ctKenStageScene_H__