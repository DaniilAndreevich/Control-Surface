#pragma once

#include "Selector.hpp"
#include <Hardware/IncrementButton.hpp>

template <setting_t N>
class IncrementSelector_Base : virtual public Selector<N> {
  public:
    IncrementSelector_Base(const IncrementButton &button, bool wrap = true)
        : button(button), wrap(wrap) {}

    IncrementSelector_Base(const Button &button, bool wrap = true)
        : button{button}, wrap(wrap) {}

    void beginInput() override { button.begin(); }

    void update() override {
        if (button.getState() == IncrementButton::Increment)
            this->increment(wrap);
    }

  private:
    IncrementButton button;
    bool wrap;
};

// -------------------------------------------------------------------------- //

template <setting_t N>
class IncrementSelector : virtual public IncrementSelector_Base<N> {
  public:
    IncrementSelector(Selectable<N> &selectable, const IncrementButton &button,
                      bool wrap = true)
        : Selector<N>(selectable), IncrementSelector_Base<N>(button, wrap) {}

    IncrementSelector(Selectable<N> &selectable, const Button &button,
                      bool wrap = true)
        : Selector<N>(selectable), IncrementSelector_Base<N>(button, wrap) {}

    void beginOutput() override {}
    void updateOutput(UNUSED_PARAM setting_t oldSetting,
                      UNUSED_PARAM setting_t newSetting) override {}
};