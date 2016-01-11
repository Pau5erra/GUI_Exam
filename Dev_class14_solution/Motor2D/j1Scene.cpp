#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "Gui.h"
#include "j1Scene.h"
#include "j1Fonts.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	/*Gui* window = App->gui->CreateImage({0, 512, 483, 512});
	window->Center();
	window->draggable = true;
	window->interactive = true;
	window->cut_childs = false;

	Gui* input = App->gui->CreateInput({488, 569, 344, 61}, "Your name", 315, {-13,-14});
	input->parent = window;
	input->interactive = true;
	input->Center();
	input->SetLocalPos(input->GetLocalPos().x, 150);
	input->can_focus = true;

	button = App->gui->CreateImage({642, 169, 229, 69});
	button->SetListener(this);
	button->interactive = true;
	button->can_focus = true;
	
	Gui* text = App->gui->CreateLabel("Button");

	text->parent = button;
	button->parent = window;

	text->Center();
	button->Center();

	Gui* title = App->gui->CreateLabel("Window Title");
	title->parent = window;
	title->Center();
	iPoint p = title->GetLocalPos();
	title->SetLocalPos(p.x, 50);
	*/
	/*
	Gui* fondo = App->gui->CreateImage("UI/WOW00.png");

	_TTF_Font* wow_font = App->font->Load("UI/LemonMilk.otf");
	SDL_Color color = { (255), (255), (0), (0) };
	GuiLabel* account_name_text = App->gui->CreateLabel("Account Name:");
	account_name_text->SetFont(wow_font);
	account_name_text->SetColor(color);
	account_name_text->SetLocalPos(470, 550);
	
	GuiLabel* account_password = App->gui->CreateLabel("Account Password:");
	account_password->SetFont(wow_font);
	account_password->SetColor(color);
	account_password->SetLocalPos(470, 670);

	Gui* name_window = App->gui->CreateImage("UI/UI-SILVER-BUTTON-UP.png");
	name_window->SetLocalPos(470, 580);
	name_window->interactive = true;
	name_window->cut_childs = false;

	Gui* input_name = App->gui->CreateInput({ (0), (0), (0), (0) }, "Your Name", 79, { 0, 0 }, false, 10 );
	input_name->SetParent(name_window);
	input_name->interactive = true;
	input_name->can_focus = true;

	login_button = App->gui->CreateImage("UI/UI-DialogBox-Button-Down.png");
	login_button->SetLocalPos(470, 750);
	login_button->SetListener(this);
	login_button->interactive = true;
	login_button->can_focus = true;
	//login_button->SetImage();

	GuiLabel* login_text = App->gui->CreateLabel("Login");
	login_text->SetFont(wow_font);
	login_text->SetColor(color);
	login_text->SetParent(login_button);
	login_text->Center();

	Gui* password_window = App->gui->CreateImage("UI/UI-SILVER-BUTTON-UP.png");
	password_window->SetLocalPos(470, 700);
	password_window->interactive = true;
	password_window->cut_childs = false;

	Gui* input_password = App->gui->CreateInput({ (0), (0), (0), (0) }, "Your Password", 79, { 0, 0 }, true, 10);
	input_password->SetParent(password_window);
	input_password->interactive = true;
	input_password->can_focus = true;

	Gui* prova_window = App->gui->CreateImage("UI/UI-SILVER-BUTTON-UP.png");
	prova_window->SetLocalPos(0, 0);
	prova_window->interactive = true;
	prova_window->cut_childs = false;

	Gui* input_prova = App->gui->CreateInput({ (0), (0), (0), (0) }, "Your Prova", 79, { 0, 0 }, false, 10);
	input_prova->SetParent(prova_window);
	input_prova->interactive = true;
	input_prova->can_focus = true;

	App->gui->DisableGuiElement(prova_window);
	*/
	Gui* slider_prova = App->gui->CreateSlideBar({ 0, 11, 307, 11 }, { 805, 318, 26, 15 });
	slider_prova->Center();
	slider_prova->interactive = true;
	slider_prova->can_focus = true;

	value = 0.0f;

	sprintf_s(value_string, "%f", value);
	value_text = App->gui->CreateLabel("Value:");
	value_text->SetLocalPos(200, 100);

	value_char = App->gui->CreateLabel(value_string);
	value_char->SetParent(value_text);
	value_char->SetLocalPos(75, 2);

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	// Gui ---
	
	// -------
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		if (login_button)
		{
			if (login_button->active == true)
				App->gui->DisableGuiElement(login_button);
			else
				App->gui->EnableGuiElement(login_button);
		}
	}
	p2SString title();

	sprintf_s(value_string, "%f", value);

	value_char->SetText(value_string);

	//App->win->SetTitle(title.GetString());

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

// Called when UI event is raised
void j1Scene::OnGui(Gui* ui, GuiEvents event)
{

/*Normal Button coords are {0,111,229,69} - hover state
Bright Button coords are {410,169,229,69} - click state
Dark Button coords are {645,165,229,69} - normal state
*/
	if(ui == login_button)
	{
		switch(event)
		{
			case GuiEvents::mouse_enters:
			case GuiEvents::gain_focus:{
				login_button->SetImage("UI/UI-DialogBox-Button-Up.png");
				break;
			}
			case GuiEvents::mouse_leaves:
			case GuiEvents::lost_focus:
				login_button->SetImage("UI/UI-DialogBox-Button-Down.png");
			break;

			case GuiEvents::mouse_lclick_down:
				login_button->SetImage("UI/UI-DialogBox-Button-Disabled.png");
			break;

			case GuiEvents::mouse_lclick_up :
				login_button->SetImage("UI/UI-DialogBox-Button-Down.png");
			break;

			case GuiEvents::mouse_rclick_down:
				login_button->SetImage("UI/UI-DialogBox-Button-Disabled.png");
			break;

			case GuiEvents::mouse_rclick_up:
				login_button->SetImage("UI/UI-DialogBox-Button-Down.png");
			break;
		}
	}
}