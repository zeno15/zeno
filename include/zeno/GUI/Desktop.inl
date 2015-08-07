template <typename T>
T& Desktop::getElement(const std::string& _element)
{
    GuiBase *returnElement = m_DesktopPane.getChild(_element);

    T& element = *dynamic_cast<T *>(returnElement);

    return element;
}

template <typename T>
void Desktop::addToElement(const std::string& _id, const std::string& _parent /*= std::string()*/)
{
    GuiBase *parent = nullptr;

    if (_parent.empty())
    {
        //~ We are adding the element to the root pane
        parent = &m_DesktopPane;
    }
    else
    {
        //~ We are adding the element to a non root pane
        parent = m_DesktopPane.getChild(_parent);
    }



    if (std::find(m_InvalidIds.begin(), m_InvalidIds.end(), _id) != m_InvalidIds.end())
    {
        throw std::runtime_error("Element id: '" + _id + "' already exists in the GUI Desktop");
    }

    if (!parent)
    {
        throw std::runtime_error("Parent Element: '" + _parent + "' does not exist in the GUI Desktop");
    }

    m_InvalidIds.push_back(_id);

    T *newElement = T::createElement(_id, parent, *this);

    parent->addChild(newElement);

    newElement->initialise();

}