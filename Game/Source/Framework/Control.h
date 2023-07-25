#pragma once

#include "Input.h"
#include "Render.h"

#include "Rect.h"
#include "Flag.h"
#include "Action.h"
#include "ID.h"
#include "ControlEnums.h"

class Control
{

    friend class ControlCreation;
    friend class GuiManager;

public:

    virtual ~Control() {}

    void Disable(bool disable)
    {
        if (!disable && state == ControlState::DISABLED)
        {
            state = ControlState::NORMAL;
            onEnable.Invoke();
        }
        else if (disable && state != ControlState::DISABLED)
        {
            state = ControlState::DISABLED;
            onDisable.Invoke();
        }
    }

    ID Id() const
    {
        return id;
    }

    bool operator==(Control* control)
    {
        return this->id == control->id;
    }

    bool operator==(Control control)
    {
        return this->id == control.id;
    }

    bool IsSelected()
    {
        return id == *selectID;
    }

    bool IsEnabled() const
    {
        return state != ControlState::DISABLED;
    }

    bool IsState(ControlState state) const
    {
        return this->state == state;
    }

    ControlType Type() const
    {
        return type;
    }

    void Layer(int layer)
    {
        if (this->layer == layer) return;
        this->layer = layer;
        onNewLayerSet->Invoke();
    }

    int Layer()
    {
        return layer;
    }

protected:

    Control(ControlType type, Rect rectangle, bool anchored, bool dragOutside, Point scale, SDL_RendererFlip flip)
    {
        this->type = type;
        this->rectangle = rectangle;
        this->anchored = anchored;
        this->dragOutside = dragOutside;
        this->scale = scale;
        this->state = ControlState::NORMAL;
        this->flip = flip;
    }

    virtual bool Update()
    {
        return true;
    }

    virtual bool Draw() const
    {
        return true;
    }

    virtual bool Manipulate() 
    { 
        return true;
    }

    void SetModules(Flag* config, ID* selectID, float* dt, Input* input, Render* render)
    {
        this->config = config;
        this->input = input;
        this->render = render;
        this->selectID = selectID;
        this->dt = dt;
    }

public:

    // Calls when the button is selected throught GUI Navigation
    Action<> onSelect;    
    // Calls when the button is diselected throught GUI Navigation
    Action<> onDiselect;
    // Calls when the button is disabled
    Action<> onDisable;
    // Calls when the button is enabled
    Action<> onEnable;

    SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;

protected:

    ControlType type = ControlType::EMPTY_CONTROL;
    ControlState state = ControlState::NORMAL;
    Rect rectangle = {};
    bool anchored = false;
    bool dragOutside = false;
    Point scale = {};
    Flag* config = nullptr;
    ID id = ID();
    ID* selectID = nullptr;
    float* dt = nullptr;

    Input* input = nullptr;
    Render* render = nullptr;

private:

    Action<>* onNewLayerSet = nullptr;
    int layer = -1;

};