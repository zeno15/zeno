#include <zeno/Graphics/AnimatedSprite.hpp>

#include <zeno/Graphics/Texture.hpp>

#include <iostream>
#include <GL/glew.h>
#include <zeno/Graphics/ShaderManager.hpp>

namespace zeno {

AnimatedSprite::AnimatedSprite(zeno::Texture &_texture) :
        m_Texture(_texture),
        m_CurrentAnimation(nullptr),
        m_ElapsedTime(0.0f) {
}

AnimatedSprite::~AnimatedSprite(void) {

}

void AnimatedSprite::addAnimation(const std::string &_name, const std::vector<zeno::FloatRect> &_frames,
                                  float _duration, bool _repeat, unsigned int _startingIndex /*= 0*/) {
    Animation a;

    a.name = _name;
    a.duration = _duration;
    a.frames = _frames;
    a.currentFrame = _startingIndex;

    m_Animations.push_back(a);

    populateLastAnimation();
}

void AnimatedSprite::playAnimation(const std::string &_name) {
    for (unsigned int i = 0; i < m_Animations.size(); i += 1) {
        auto &a = m_Animations.at(i);

        if (_name == a.name) {
            m_CurrentAnimationIndex = i;

            changeAnimation(&a);

            return;
        }
    }
}

void AnimatedSprite::update(float _delta) {
    m_ElapsedTime += _delta;

    if (m_CurrentAnimation == nullptr) {
        return;
    }

    if (m_ElapsedTime > m_CurrentAnimation->duration) {
        m_ElapsedTime -= m_CurrentAnimation->duration;

        incrementCurrentAnimation();
    }
}

void AnimatedSprite::render(const zeno::Mat4x4 &_projection, const zeno::Mat4x4 &_view) const {
    if (m_CurrentAnimation != nullptr) {
        m_Texture.bind();

        zeno::ShaderManager::getInstance().getShader("AnimatedSprite").bind();

        zeno::ShaderManager::getInstance().getShader("AnimatedSprite").passUniform("projection", _projection);
        zeno::ShaderManager::getInstance().getShader("AnimatedSprite").passUniform("model",
                                                                                   zeno::Mat4x4::createTranslation(
                                                                                           getPosition()));
        zeno::ShaderManager::getInstance().getShader("AnimatedSprite").passUniform("view", _view);

        glBindVertexArray(m_VAOs.at(m_CurrentAnimationIndex));
        glDrawArrays(GL_TRIANGLES, m_CurrentAnimation->currentFrame * 6, 6);
        glBindVertexArray(0);

        zeno::ShaderManager::getInstance().getShader("AnimatedSprite").unbind();

        m_Texture.unbind();
    }
}

void AnimatedSprite::setColour(const zeno::Colour &_colour) {
    m_Colour = _colour;
}

const zeno::Colour &AnimatedSprite::getColour(void) const {
    return m_Colour;
}

void AnimatedSprite::changeAnimation(Animation *_animation) {
    m_ElapsedTime = 0.0f;

    if (m_CurrentAnimation == _animation) {
        return;
    }

    m_CurrentAnimation = _animation;
}

void AnimatedSprite::incrementCurrentAnimation(void) {
    m_CurrentAnimation->currentFrame += 1;

    if (m_CurrentAnimation->currentFrame >= m_CurrentAnimation->frames.size()) {
        m_CurrentAnimation->currentFrame = 0;
    }
}

void AnimatedSprite::populateLastAnimation(void) {
    m_VAOs.push_back(0);
    glGenVertexArrays(1, &m_VAOs.back());
    glBindVertexArray(m_VAOs.back());

    //~ Positions
    m_VBOPositions.push_back(0);
    glGenBuffers(1, &m_VBOPositions.back());

    glBindBuffer(GL_ARRAY_BUFFER, m_VBOPositions.back());

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_Animations.back().frames.size() * 6 * 3, nullptr,
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    std::vector<float> positions;

    positions.resize(m_Animations.back().frames.size() * 3 * 6);

    for (unsigned int i = 0; i < m_Animations.back().frames.size(); i += 1) {
        //~ Bottom Left
        positions[(i * 3 * 6) + 0] = 0.0f;
        positions[(i * 3 * 6) + 1] = 0.0f;
        positions[(i * 3 * 6) + 2] = 0.0f;

        //~ Bottom Right
        positions[(i * 3 * 6) + 3] = 0.0f + m_Animations.back().frames.at(i).width;
        positions[(i * 3 * 6) + 4] = 0.0f;
        positions[(i * 3 * 6) + 5] = 0.0f;

        //~ Top Right
        positions[(i * 3 * 6) + 6] = 0.0f + m_Animations.back().frames.at(i).width;
        positions[(i * 3 * 6) + 7] = 0.0f + m_Animations.back().frames.at(i).height;
        positions[(i * 3 * 6) + 8] = 0.0f;

        //~ Bottom Left
        positions[(i * 3 * 6) + 9] = 0.0f;
        positions[(i * 3 * 6) + 10] = 0.0f;
        positions[(i * 3 * 6) + 11] = 0.0f;

        //~ Top Right
        positions[(i * 3 * 6) + 12] = 0.0f + m_Animations.back().frames.at(i).width;
        positions[(i * 3 * 6) + 13] = 0.0f + m_Animations.back().frames.at(i).height;
        positions[(i * 3 * 6) + 14] = 0.0f;

        //~ Top Left
        positions[(i * 3 * 6) + 15] = 0.0f;
        positions[(i * 3 * 6) + 16] = 0.0f + m_Animations.back().frames.at(i).height;
        positions[(i * 3 * 6) + 17] = 0.0f;


    }


    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * positions.size(), positions.data());

    //~ Textures
    m_VBOTextures.push_back(0);
    glGenBuffers(1, &m_VBOTextures.back());

    glBindBuffer(GL_ARRAY_BUFFER, m_VBOTextures.back());

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_Animations.back().frames.size() * 6 * 2, nullptr,
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    std::vector<float> textures = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,

            0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
    };

    textures.resize(m_Animations.back().frames.size() * 2 * 6);

    zeno::Vector2f texSize = m_Texture.getSize();

    for (unsigned int i = 0; i < m_Animations.back().frames.size(); i += 1) {
        //~ Bottom Left
        textures[(i * 2 * 6) + 0] = (m_Animations.back().frames.at(i).left) / texSize.x;
        textures[(i * 2 * 6) + 1] = (m_Animations.back().frames.at(i).bot) / texSize.y;

        //~ Bottom Right
        textures[(i * 2 * 6) + 2] =
                (m_Animations.back().frames.at(i).left + m_Animations.back().frames.at(i).width) / texSize.x;
        textures[(i * 2 * 6) + 3] = (m_Animations.back().frames.at(i).bot) / texSize.y;

        //~ Top Right
        textures[(i * 2 * 6) + 4] =
                (m_Animations.back().frames.at(i).left + m_Animations.back().frames.at(i).width) / texSize.x;
        textures[(i * 2 * 6) + 5] =
                (m_Animations.back().frames.at(i).bot + m_Animations.back().frames.at(i).height) / texSize.y;

        //~ Bottom Left
        textures[(i * 2 * 6) + 6] = (m_Animations.back().frames.at(i).left) / texSize.x;
        textures[(i * 2 * 6) + 7] = (m_Animations.back().frames.at(i).bot) / texSize.y;

        //~ Top Right
        textures[(i * 2 * 6) + 8] =
                (m_Animations.back().frames.at(i).left + m_Animations.back().frames.at(i).width) / texSize.x;
        textures[(i * 2 * 6) + 9] =
                (m_Animations.back().frames.at(i).bot + m_Animations.back().frames.at(i).height) / texSize.y;

        //~ Top Left
        textures[(i * 2 * 6) + 10] = (m_Animations.back().frames.at(i).left) / texSize.x;
        textures[(i * 2 * 6) + 11] =
                (m_Animations.back().frames.at(i).bot + m_Animations.back().frames.at(i).height) / texSize.y;
    }

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * textures.size(), textures.data());
}

} //~ namespace zeno