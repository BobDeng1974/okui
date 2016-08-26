#pragma once

#include "okui/config.h"

#include "okui/views/Button.h"
#include "okui/views/ImageView.h"

#include <unordered_map>

namespace okui {
namespace views {

class ImageButton : public Button<View> {
public:
    TextureHandle& texture(State state = State::kNormal) { return _imageViews[state].texture(); }
    ImageView& image(State state = State::kNormal) { return _imageViews[state]; }

    void setTextureResource(std::string resource, State state = State::kNormal);
    void setTextureFromURL(std::string url, State state = State::kNormal);
    void setTextureFromURL(std::string url, std::string placeholderResource, State state = State::kNormal);
    void setTextureColor(Color color, State state = State::kNormal);
    void setTextureDistanceField(double edge = 0.5, State state = State::kNormal);

    void load();
    void unload();

    virtual void layout() override;
    virtual void stateChanged() override;

private:
    ImageView& _stateImageView(State state);

    std::unordered_map<State, ImageView> _imageViews;
    Color                                _normalColor = Color::kWhite;
};

} } // namespace okui::views