#pragma once

#include "Control.h"

class Button : public Control
{

    friend class ControlCreation;

public:

    virtual ~Button();

private:

    Button(Rect rectangle, bool anchored, bool dragOutside, Point scale, SDL_RendererFlip flip);

    bool Update() override;

    bool Draw() const override;

    bool Manipulate() override;

public:
    
    // Set the key to interact with the button when selected
    KeyCode submitKey = KeyCode::RETURN;
    // Calls when the user releases the click button
    Action<> onRelease;
    // Calls when the user removes the pointer from the button while clicking. This won't call if DGSO enabled
    Action<> onRemove;
    // Calls when the user puts the mouse on the button
    Action<> onFocus;
    // Calls when the user puts the mouse on the button
    Action<> onUnfocus;
    // Calls when the user clicks on the button.
    Action<> onClick;
    // Calls when the user submits the click on the button when checkbox selected.
    Action<> onSubmit;

    Texture* texDisabled = nullptr;
    Texture* texNormal   = nullptr;
    Texture* texFocused  = nullptr;
    Texture* texPressed  = nullptr;
    Texture* texSelected = nullptr;
};
