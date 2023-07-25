#pragma once

enum class ControlType
{
    EMPTY_CONTROL = -1,
    BUTTON,
    TOGGLE,
    CHECKBOX,
    SLIDER,
    SLIDERBAR,
    COMBOBOX,
    DROPDOWNBOX,
    INPUTBOX,
    VALUEBOX,
    SPINNER,
    TEXT,
    IMAGE
};

enum class ControlState
{
    DISABLED,
    NORMAL,
    FOCUSED,
    PRESSED,
    SELECTED
};
