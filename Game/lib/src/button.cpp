#include "core/color.hpp"
#include "core/rect.hpp"
#include "core/text.hpp"
#include "core/texture.hpp"
#include "util/button.hpp"
#include "core/environment.hpp"
#include "core/mousebuttonevent.hpp"
#include "core/mousemotionevent.hpp"

#include <cstdio>

class Button::Impl
{
public:
    typedef enum { IDLE, ACTIVE } State;

    Impl(Button *button)
    {
        this->m_button = button;
        this->m_text = nullptr;
        this->m_idle = Color::GREEN;
        this->m_active = Color::BLUE;
        this->m_border = Color::BLACK;
        this->m_thickness = 1;
        this->m_state = IDLE;
        this->m_idle_texture = nullptr;
        this->m_active_texture = nullptr;
    }

    Impl(Button *button, const string& idle_image_id,
        const string& active_image_id)
    {
        this->m_button = button;
        this->m_text = nullptr;
        this->m_idle = Color::GREEN;
        this->m_active = Color::BLUE;
        this->m_border = Color::BLACK;
        this->m_thickness = 1;
        this->m_state = IDLE;

        Environment *env = Environment::get_instance();

        this->m_idle_texture = env->resources_manager->get_texture(idle_image_id);
        this->m_active_texture = env->resources_manager->get_texture(active_image_id);

        this->m_button->set_position(0.0, 0.0);
        this->m_button->set_dimensions(m_idle_texture->width(), m_idle_texture->height());
    }


    ~Impl()
    {
        delete m_text;
    }

    void set_text(const string& text, const Color& color)
    {
        if (text.size() > 0)
        {
            delete m_text;
            m_text = new Text(m_button, text, color);
        }
    }

    void set_color(const Color& idle, const Color& active)
    {
        m_idle = idle;
        m_active = active;
    }

    void set_border(int thickness, const Color& color)
    {
        m_border = color;
        m_thickness = thickness;
    }

    bool on_event(const MouseButtonEvent& event)
    {
        if (event.state() == MouseButtonEvent::PRESSED and
            event.button() == MouseButtonEvent::LEFT and
            m_button->bounding_box().contains(event.horizontal_position(), event.vertical_position()))
        {
            char coords[64];
            sprintf(coords, "%.2f,%.2f", event.horizontal_position(), event.vertical_position());
            m_button->notify(clickedID, coords);
            return true;
        }else{
            //do nothing
        }

        return false;
    }

    bool on_event(const MouseMotionEvent& event)
    {
        if (m_button->bounding_box().contains(event.horizontal_position(), event.vertical_position()))
        {
            m_state = ACTIVE;
            if (m_active_texture.get())
            {
                m_button->set_dimensions(m_active_texture->width(), m_active_texture->height());
            }else{
                //do nothing
            }
            return true;
        }else
        {
            m_state = IDLE;
            if (m_idle_texture.get())
            {
                m_button->set_dimensions(m_idle_texture->width(), m_idle_texture->height());
            }else{
                //do nothing
            }
        }
        return false;
    }

    void draw_self()
    {
        Environment *env = Environment::get_instance();
        shared_ptr<Texture> image;
        Color color;

        switch (m_state)
        {
            case IDLE:
                image = m_idle_texture;
                color = m_idle;
            break;

            case ACTIVE:
                image = m_active_texture;
                color = m_active;
            break;
        }

        if (image.get())
        {
            env->canvas->draw(image.get(), m_button->horizontal_position(), m_button->vertical_position());
        }else
        {
            env->canvas->set_blend_mode(Canvas::BLEND);
            Rect r = m_button->bounding_box();

            for (int i = 0; i < m_thickness; ++i)
            {
                env->canvas->draw(r, m_border);

                r.set_position(r.horizontal_position() + 1, r.vertical_position() + 1);
                r.set_dimensions(r.width() - 2, r.height() - 2);
            }

            env->canvas->fill(r, color);
            env->canvas->set_blend_mode(Canvas::NONE);
        }

        if (m_text)
        {
            m_text->align_to(m_button, Object::CENTER, Object::MIDDLE);
            m_text->draw();
        }else{
            //do nothing
        }
    }

    private:
        Button *m_button;
        Text *m_text;
        Color m_idle, m_active, m_border;
        int m_thickness;
        State m_state;
        shared_ptr<Texture> m_idle_texture, m_active_texture;
    };

ActionID Button::clickedID = "clicked()";

Button::Button(Object *parent, ObjectID id, double width, double height)
              : Object(parent, id, 0, 0, width, height), m_impl(new Impl(this))
{
    Environment *env = Environment::get_instance();
    env->events_manager->register_listener(this);
}

Button::Button(Object *parent, ObjectID id, const string& idle_image_id,
               const string& active_image_id)
               : Object(parent, id), m_impl(new Impl(this, idle_image_id, active_image_id))
{
    Environment *env = Environment::get_instance();
    env->events_manager->register_listener(this);
}

Button::~Button()
{
    Environment *env = Environment::get_instance();
    env->events_manager->unregister_listener(this);
}

void Button::draw_self()
{
    m_impl->draw_self();
}

bool Button::on_event(const MouseButtonEvent& event)
{
    return m_impl->on_event(event);
}

bool Button::on_event(const MouseMotionEvent& event)
{
    return m_impl->on_event(event);
}

void Button::set_text(const string& text, const Color& color)
{
    return m_impl->set_text(text, color);
}

void Button::set_color(const Color& idle, const Color& active)
{
    return m_impl->set_color(idle, active);
}

void Button::set_border(int thickness, const Color& color)
{
    return m_impl->set_border(thickness, color);
}
