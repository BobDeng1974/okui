#include <okui/ml/Environment.h>

#include <okui/ml/elements/Button.h>
#include <okui/ml/elements/FocusBorder.h>
#include <okui/ml/elements/Image.h>
#include <okui/ml/elements/LabeledPopoutButton.h>
#include <okui/ml/elements/Popout.h>
#include <okui/ml/elements/StateMachine.h>
#include <okui/ml/elements/Text.h>
#include <okui/ml/elements/View.h>

namespace okui::ml {

Environment::Environment() {
    defineElementType<elements::Button>("button");
    defineElementType<elements::FocusBorder>("focusborder");
    defineElementType<elements::Image>("image");
    defineElementType<elements::LabeledPopoutButton>("labeledpopoutbutton");
    defineElementType<elements::Popout>("popout");
    defineElementType<elements::StateMachine>("statemachine");
    defineElementType<elements::Text>("text");
    defineElementType<elements::View>("view");
}

} // namespace okui::ml
