/**
* Copyright 2017 BitTorrent Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#pragma once

#include <okui/config.h>

#include <okui/ml/Context.h>
#include <okui/ml/elements/View.h>
#include <okui/views/LabeledPopoutButton.h>

namespace okui::ml::elements {

class LabeledPopoutButton : public View {
public:
    virtual std::unique_ptr<ElementInterface> create() const override {
        return std::make_unique<Element>();
    }

protected:
    class Element : public View::Element<views::LabeledPopoutButton> {
    public:
        virtual void setAttribute(stdts::string_view name, stdts::string_view value) override {
            if (name == "command") {
                _command = strtoull(std::string(value).c_str(), nullptr, 0);
                if (!_command) {
                    _command = scraps::FNV1A64(value.data(), value.size());
                }
                setAction(_command, _commandContext);
            } else if (name == "command-context") {
                auto cc = context()->get(std::string(value));
                _commandContext = cc ? *cc : CommandContext{};
                setAction(_command, _commandContext);
            } else if (name == "icon") {
                setIcon(value.to_string());
            } else if (name == "label-font") {
                setLabelStyle(views::TextView::Style{focusedLabelStyle()}.font(std::string(value) + ".png", std::string(value) + ".fnt"));
            } else {
                elements::View::Element<views::LabeledPopoutButton>::setAttribute(name, value);
            }
        }

        virtual void setAttribute(stdts::string_view name, std::vector<ValueComponent> components) override {
            if (name == "icon-color") {
                if (auto color = SumColorComponents(components)) {
                    setIconColor(*color);
                }
            } else if (name == "label-text-size") {
                setLabelStyle(views::TextView::Style{focusedLabelStyle()}.textSize(SumNumberComponents(components).value_or(0.0)));
            } else if (name == "label-text-color") {
                setLabelStyle(views::TextView::Style{focusedLabelStyle()}.textColor(SumColorComponents(components).value_or(Color::kBlack)));
            } else {
                elements::View::Element<views::LabeledPopoutButton>::setAttribute(name, components);
            }
        }

        virtual void setText(stdts::string_view text) override {
            setLabelText(text.to_string());
        }

    private:
        Command        _command;
        CommandContext _commandContext;
    };
};

} // namespace okui::ml::elements
