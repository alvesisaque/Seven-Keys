#Class object

##public:

·string ObjectID
·string ActionID
·string MessageID
·string Parameters
·const list<Object * >& children() const → list of object in a specifc parameter.

###Object::set_walkable()

·bool walkable → set if the object is walkable or not

###Object::set_mass()

·double mass → set the object's mass

###Object::set_position()

·double x → size x of object colision box
·double y → size y of object colision box

###Object::set_dimensions()

·double w → object dimensions width
·double h → object dimensions height

###Object::set_parent()

·Object * parent
·enum { NONE, LEFT, CENTER, RIGHT, TOP, MIDDLE, BOTTOM }
·Alignment

###Object::align_to()

·const Object* object
·Alignment xaxis
·Alignment yaxis

###Object::add_child()

·Object * child

###Object::remove_child()

·Object * child

###Object::send_message()

·Object * receiver
·MessageID id
·Parameters parameters

###Object::on_message()

·Object * sender
·MessageID id
·Parameters p

###Object::add_observer()

·Object * observer

###Object::remove_observer()

·Object * observer

###Object::notify()

·ActionID action → object actions in the game
·Parameters parameters → object parameters

###Object::update()

·unsigned long elapsed
·auto child → iterator of list of object childrens.

##private:

###Object::update_self()

·unsigned long elapsed
·unique_ptr<Impl> m_impl
·Object * m_base
·Object * m_parent
·ObjectID m_id
·Rect m_box
·bool m_visible
·bool m_walkable
·double m_mass
·list<Object * > m_children
·list<Object * > m_observers
