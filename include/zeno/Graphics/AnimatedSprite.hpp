#ifndef INCLUDED_ZENO_GRAPHICS_ANIMATEDSPRITE_HPP
#define INCLUDED_ZENO_GRAPHICS_ANIMATEDSPRITE_HPP

#include <zeno/Graphics/Colour.hpp>

#include <zeno/System/Rect.hpp>
#include <zeno/System/Mat4x4.hpp>
#include <zeno/System/Transformable3D.hpp>

namespace zeno {
    class Texture;

class AnimatedSprite : public zeno::Transformable3D
{
private:
    struct Animation {
        std::string                         name;
        float                               duration;
        std::vector<zeno::FloatRect>        frames;
        unsigned int                        currentFrame;
    };

public:
    AnimatedSprite(zeno::Texture& _texture);
    ~AnimatedSprite(void);

    void addAnimation(const std::string& _name, const std::vector<zeno::FloatRect>& _frames, float _duration, bool _repeat, unsigned int _startingIndex = 0);

    void playAnimation(const std::string& _name);

    void update(float _delta);

    void render(const zeno::Mat4x4& _projection, const zeno::Mat4x4& _view) const;

    void setColour(const zeno::Colour& _colour);
    const zeno::Colour& getColour(void) const;

private:
    void changeAnimation(Animation *_animation);

    void incrementCurrentAnimation(void);

    void populateLastAnimation(void);

private:
    zeno::Colour                m_Colour;

    zeno::Texture&              m_Texture;

    Animation *                 m_CurrentAnimation;

    std::vector<Animation>      m_Animations;
    std::vector<unsigned int>   m_VAOs;
    std::vector<unsigned int>   m_VBOPositions;
    std::vector<unsigned int>   m_VBOTextures;

    unsigned int                m_CurrentAnimationIndex;

    float                       m_ElapsedTime;
};

} //~ namespace zeno


#endif //~ INCLUDED_ZENO_GRAPHICS_ANIMATEDSPRITE_HPP
