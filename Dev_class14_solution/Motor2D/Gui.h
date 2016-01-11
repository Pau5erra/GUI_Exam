#ifndef __GUI_H__
#define __GUI_H__

#include "p2Point.h"

#define CURSOR_WIDTH 2

enum GuiEvents
{
	listening_ends,
	mouse_enters,
	mouse_leaves,
	mouse_lclick_down,
	mouse_lclick_up,
	mouse_rclick_down,
	mouse_rclick_up,
	gain_focus,
	lost_focus,
	input_changed,
	input_submit
};

enum GuiTypes
{
	unknown,
	image,
	label,
	button,
	input_text,
	slide_bar
};

// ---------------------------------------------------
class Gui
{
public:
	Gui();
	virtual ~Gui()
	{}

	virtual void Draw() const
	{}
	virtual void DebugDraw() const;
	virtual void Update(const Gui* mouse_hover, const Gui* focus)
	{}
	virtual void Update()
	{}
	void CheckInput(const Gui* mouse_hover, const Gui* focus);
	void SetLocalPos(int x, int y);
	void Center();
	rectangle GetScreenRect() const;
	rectangle GetLocalRect() const;
	iPoint GetScreenPos() const;
	iPoint GetLocalPos() const;
	void SetListener(j1Module* module);
	void SetParent(Gui* dad);
	void SetSize(int w, int h);

protected:
	

public:
	bool draggable = false;
	bool interactive = false;
	bool cut_childs = false;
	bool can_focus = false;
	bool active = true;
	p2List<Gui*> childs;
	GuiTypes type = GuiTypes::unknown;
	Gui* parent = nullptr;
protected:
	
	j1Module* listener = nullptr;
	bool have_focus = false;
private:
	bool mouse_inside = false;
	rectangle rect;
};

// ---------------------------------------------------
class GuiImage : public Gui
{
public:
	GuiImage(const SDL_Texture* texture);
	GuiImage(const SDL_Texture* texture, const rectangle& section);
	~GuiImage();

	void SetSection(const rectangle& section);
	void SetImage(const char* path);
	void SetImage(const char*path, const rectangle& section);
	void Draw() const;

private:

	rectangle section;
	const SDL_Texture* texture = nullptr;
};

// ---------------------------------------------------
class GuiLabel : public Gui
{
public:
	GuiLabel(const char* text, _TTF_Font* font = NULL, SDL_Color color = { (255), (255), (255), (255) });
	~GuiLabel();

	void SetText(const char* text);
	void SetFont(_TTF_Font* font = NULL);
	void SetColor(SDL_Color color = { (255), (255), (255), (255) });
	const SDL_Texture* GetTexture() const;
	void Draw() const;

private:

	SDL_Texture* texture = nullptr;
	_TTF_Font* font = NULL;
	SDL_Color color;
	const char* text;
	bool is_password = false;
};

// ---------------------------------------------------
// TODO 1: Create a new InputText UI element with it's own label and image
// and draw it
class GuiInputText : public Gui
{
public:
	GuiInputText(const char* default_text, uint width, const SDL_Texture* texture, const rectangle& section, const iPoint& offset = { 0, 0 },
		bool password = false, int _max_quantity = 0);
	~GuiInputText();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw() const;

private:

	GuiLabel text;
	int max_quantity;
	bool password;
	GuiImage image;
	p2SString input;
	iPoint cursor_coords = { 0, 0 };
	int last_cursor = 0;
	bool had_focus = false;
	const char* def_text;
	bool show_def_text;
};


class SlideBar : public Gui{
public:
	SlideBar(const SDL_Texture* texture, const rectangle& bar_section, const rectangle& thumb_section);
	~SlideBar();

	void Update(const Gui* mouse_hover, const Gui* focus);
	void Draw() const;

private:

	GuiImage bar;
	GuiImage thumb;
};


#endif // __GUI_H__
