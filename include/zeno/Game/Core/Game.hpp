#ifndef ZENO_GAME_CORE_GAME_HPP
#define ZENO_GAME_CORE_GAME_HPP

#include <string>
#include <functional>

#include <zeno/Graphics/Colour.hpp>
#include <zeno/System/Clock.hpp>
#include <zeno/Window/Window.hpp>

///////////////////////////////////////////////////////////////////////////////
///
/// \namespace zeno
///
///////////////////////////////////////////////////////////////////////////////
namespace zeno {

///////////////////////////////////////////////////////////////////////////////
///
/// \brief  Game class that contains basic application
///
///////////////////////////////////////////////////////////////////////////////
class Game
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief Constructor, creates a Game with the given window options
    ///
    /// \param  _title  Window title to set
    /// \param  _width  Width of window to set
    /// \param  _height Height of window to set
    ///
    ///////////////////////////////////////////////////////////////////////////////
    Game(const std::string _title, unsigned int _width, unsigned int _height);


    ///////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief  Starts the game running
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void start(void);

    ///////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief  Stops the game
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void stop(void);

    ///////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief  Sets the desired number of frames to be rendered per second
    ///
    /// \param  _FPS    Desired frame rate
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void setDesiredFPS(unsigned int _FPS);
    ///////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief  Returns the current desired number of frames to be rendered per second
    ///
    /// \return unsigned int representing current desired FPS
    ///
    ///////////////////////////////////////////////////////////////////////////////
    unsigned int getDesiredFPS(void) const;
    ///////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief  Sets the desired number of updates to be processed per second
    ///
    /// \param  _UPS    Desired update rate
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void setDesiredUPS(unsigned int _UPS);
    ///////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief  Returns the current desired number of updates to be processed per second
    ///
    /// \return unsigned int representing current desired UPS
    ///
    ///////////////////////////////////////////////////////////////////////////////
    unsigned int getDesiredUPS(void) const;

    ///////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief  Sets the Colour used to clear the screen
    ///
    /// \param  _colour Colour to set the screen when clearing
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void setClearColour(const zeno::Colour& _colour);
    ///////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief  Gets the Colour used to clear the screen
    ///
    /// \return Colour that the screen is being cleared to
    ///
    ///////////////////////////////////////////////////////////////////////////////
    zeno::Colour getClearColour(void) const;

    ///////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief  Assigns the method to call when the window is resized
    ///
    /// \param  _resizeMethod   Method to call
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void setResizeMethod(std::function<void(unsigned int, unsigned int)> _resizeMethod);

    ///////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief  Assigns the method to call when the close button is pressed
    ///         If it returns true or is not set, the Game will be closed
    ///         when the close button is pressed
    ///
    /// \param  _closeMethod    Method to call
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void setOnCloseButtonMethod(std::function<bool(void)> _closeMethod);

private:
    ///////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief  Updates the Game
    ///
    /// \param  _delta  Time elapsed to update the game with
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void update(float _delta);

    ///////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief  Renders the Game
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void render(void) const;

    ///////////////////////////////////////////////////////////////////////////////
    ///
    /// \brief  Exits the Game and frees all resources
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void exit(void);

private:
    bool                                                m_Running;          ///~ Whether the game is running or not

    unsigned int                                        m_DesiredFPS;       ///~ The desired Frames to be rendered per second
    unsigned int                                        m_DesiredUPS;       ///~ The desired Updates to process per second

    zeno::Colour                                        m_ClearColour;      ///~ Colour to use when clearing the screen

    zeno::Time                                          m_SceneTime;        ///~ Time associated with the age of the scene

    zeno::Window                                        m_Window;           ///~ Window that the game will use to render

    //~ Event methods
    std::function<void(unsigned int, unsigned int)>     m_OnWindowResize;   ///~ Method to call when window is resized
    std::function<bool(void)>                           m_OnCloseButton;    ///~ Method to call when close button is pressed;
};

} //~ namespace zeno

#endif //~ ZENO_GAME_CORE_GAME_HPP