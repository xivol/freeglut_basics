#include "input.h"

input_manager::input_manager(input_handler_delegate* default_d)
{
    _default_delegate = default_d;
}

void input_manager::add_handler(input_handler* handler)
{
    if (!handler) return;

    if (auto kh = dynamic_cast<keyboard_handler*>(handler))
        keyboard_handlers.push_back(kh);
    if (auto mh = dynamic_cast<mouse_handler*>(handler))
        mouse_handlers.push_back(mh);
    if (auto wh = dynamic_cast<window_state_handler*>(handler))
        window_state_handlers.push_back(wh);
    if (auto ih = dynamic_cast<idle_handler*>(handler))
        idle_handlers.push_back(ih);
    if (auto ch = dynamic_cast<close_handler*>(handler))
        close_handlers.push_back(ch);

    if (!handler->get_input_delegate())
        handler->set_input_delegate(_default_delegate);
}

void input_manager::keyboard(unsigned char key, int x, int y)
{
    for (auto handler : keyboard_handlers)
        handler->keyboard(key, x, y);
}

void input_manager::special(int key, int x, int y)
{
    for (auto handler : keyboard_handlers)
        handler->special(key, x, y);
}

void input_manager::mouse(int button, int state, int x, int y)
{
    for (auto handler : mouse_handlers)
        handler->mouse(button, state, x, y);
}

void input_manager::motion(int x, int y, bool is_active)
{
    for (auto handler : mouse_handlers)
        handler->motion(x, y, is_active);
}

void input_manager::visibility(int state)
{
    for (auto handler : window_state_handlers)
        handler->visibility(state);
}

void input_manager::entry(int state)
{
    for (auto handler : window_state_handlers)
        handler->entry(state);
}

void input_manager::idle()
{
    for (auto handler : idle_handlers)
        handler->update();
}

void input_manager::close()
{
    for (auto handler : close_handlers)
        handler->close();
}
