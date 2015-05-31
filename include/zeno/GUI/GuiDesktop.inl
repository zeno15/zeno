template <typename T>
T *GuiDesktop::getElementFromPane(const std::string& _pane, const std::string& _element)
{
    return dynamic_cast<T *>(getPane(_pane).getChild(_element));
}