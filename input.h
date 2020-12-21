#pragma once
#include <vector>


class input_handler_delegate 
{
public: virtual void input_handler_did_finish(bool update_graphics) = 0;
};


class input_handler 
{ 
protected:
	input_handler_delegate* _input_delegate = nullptr;
public:
	virtual const input_handler_delegate* get_input_delegate() { return _input_delegate; }
	virtual void set_input_delegate(input_handler_delegate* input_delegate) { _input_delegate = input_delegate; }
};


class keyboard_handler : public input_handler
{
public:
	inline virtual void keyboard(unsigned char key, int x, int y) {}
	inline virtual void special(int key, int x, int y) {}
};


class mouse_handler : public input_handler
{
public:
	inline virtual void mouse(int button, int state, int x, int y) {}
	inline virtual void motion(int x, int y, bool is_active) {}
};

class window_state_handler : public input_handler
{
public:
	inline virtual void visibility(int state) {}
	inline virtual void entry(int state) {}
};

class idle_handler : public input_handler
{
public:	inline virtual void update() {}
};

class close_handler : public input_handler
{
public:	inline virtual void close() {}
};

class input_manager 
{
protected:
	input_handler_delegate* _default_delegate;
	std::vector<keyboard_handler*> keyboard_handlers;
	std::vector<mouse_handler*> mouse_handlers;
	std::vector<window_state_handler*> window_state_handlers;
	std::vector<idle_handler*> idle_handlers;
	std::vector<close_handler*> close_handlers;
public:
	input_manager(input_handler_delegate* default_d);
	void add_handler(input_handler* handler);

	virtual void keyboard(unsigned char key, int x, int y);
	virtual void special(int key, int x, int y);

	virtual void mouse(int button, int state, int x, int y);
	virtual void motion(int x, int y, bool is_active);

	virtual void visibility(int state);
	virtual void entry(int state);

	virtual void idle();
	
	virtual void close();
};

