#ifndef BUTTON_API_H
#define BUTTON_API_H

#include <vector>
#include <string>

#include "BtnUtils.h"

namespace ButtonAPI {
    struct MenuTab : BtnUtils::BaseConstructor {
    public:
        static std::vector<MenuTab*> MenuTabs;
        std::vector<BaseConstructor*> Buttons;
        static MenuTab* SelectedTab;
        bool IsInsideTab = false;

        MenuTab(const std::string& text) : BaseConstructor() {
            auto OnClickM = [this]() {
                for (MenuTab* tab : MenuTabs) {
                    tab->SetActive(false);

                    for (BaseConstructor* tb : tab->Buttons) {
                        tb->SetActive(true);
                    }
                }

                for (BaseConstructor* tb : Buttons) {
                    tb->SetActive(true);
                }

                SelectedTab = this;
            };

            OnClick.push_back(OnClickM);
            MenuTabs.push_back(this);

            this->Obj = BtnUtils::BtnInstantinator::GetButtonTemplate();

            auto ButtonComp = this->Obj->GetComponent("Button");
            if (ButtonComp) {
                this->Button;
            }

            auto BtnT = (Unity::CComponent*)this->Obj->GetTransform();
            if (BtnT)
            {
                auto ButtonText = BtnT->CallMethodSafe<Unity::CComponent*>("FindChild", IL2CPP::String::New("Text_H4"))->GetGameObject();
                if (ButtonText) {
                    auto CompTest = ButtonText->GetComponentByIndex(UNITY_COMPONENT_CLASS, 2);
                    if (CompTest) {
                        this->Text = CompTest;
                    }
                }
            }

            CenterText();
            RemoveIcon();
            SetText(text);
        }
    };

    struct SimpleButton : BtnUtils::BaseConstructor {
    public:
        SimpleButton(const std::string& text, bool TextCentered = true, bool ShouldRemoveIcon = true) : BaseConstructor() {
            if (TextCentered) {
                CenterText();
            }
            if (ShouldRemoveIcon) {
                RemoveIcon();
            }

            SetText(text);
        }

        SimpleButton(const std::string& text, bool TextCentered, bool ShouldRemoveIcon, MenuTab* Parent) : BaseConstructor() {
            if (TextCentered) {
                CenterText();
            }
            if (ShouldRemoveIcon) {
                RemoveIcon();
            }

            SetText(text);

            if (Parent) {
                Parent->Buttons.push_back(static_cast<BaseConstructor*>(this));

                this->Obj = BtnUtils::BtnInstantinator::GetButtonTemplate();

                auto ButtonComp = this->Obj->GetComponent("Button"); 
                if (ButtonComp) {
                    this->Button;
                }

                auto BtnT = (Unity::CComponent*)this->Obj->GetTransform();
                if (BtnT)
                {
                    auto ButtonText = BtnT->CallMethodSafe<Unity::CComponent*>("FindChild", IL2CPP::String::New("Text_H4"))->GetGameObject();
                    if (ButtonText) {
                        auto CompTest = ButtonText->GetComponentByIndex(UNITY_COMPONENT_CLASS, 2);
                        if (CompTest) {
                            this->Text = CompTest;
                        }
                    }
                }
            }
        }
    };

    struct ToggleButton : BtnUtils::BaseConstructor {
    public:
        bool Enabled = false;

        ToggleButton(const std::string& text, bool TextCentered = true, bool ShouldRemoveIcon = true, MenuTab* Parent = nullptr) : BaseConstructor() {
            auto StateChange = [&]() {
                Enabled = !Enabled;
                SetColor(Enabled ? Unity::Color(0.f, 1.f, 0.f, 1.f) : Unity::Color(1.f, 0.f, 0.f, 1.f));
                };

            if (TextCentered) {
                CenterText();
            }
            if (ShouldRemoveIcon) {
                RemoveIcon();
            }

            SetText(text);

            OnClick.push_back(StateChange);

            if (Parent) {
                Parent->Buttons.push_back(static_cast<BaseConstructor*>(this));

                this->Obj = BtnUtils::BtnInstantinator::GetButtonTemplate();

                auto ButtonComp = this->Obj->GetComponent("Button");
                if (ButtonComp) {
                    this->Button;
                }

                auto BtnT = (Unity::CComponent*)this->Obj->GetTransform();
                if (BtnT)
                {
                    auto ButtonText = BtnT->CallMethodSafe<Unity::CComponent*>("FindChild", IL2CPP::String::New("Text_H4"))->GetGameObject();
                    if (ButtonText) {
                        auto CompTest = ButtonText->GetComponentByIndex(UNITY_COMPONENT_CLASS, 2);
                        if (CompTest) {
                            this->Text = CompTest;
                        }
                    }
                }
            }
        }
        

        ToggleButton(const std::string& text, bool* v, bool TextCentered = true, bool ShouldRemoveIcon = true, MenuTab* Parent = nullptr) : BaseConstructor() {
            auto StateChange = [&]() { 
                *v = !*v;
                SetColor(*v ? Unity::Color(0.f, 1.f, 0.f, 1.f) : Unity::Color(1.f, 0.f, 0.f, 1.f));
                };

            if (TextCentered) {
                CenterText();
            }
            if (ShouldRemoveIcon) {
                RemoveIcon();
            }

            SetText(text);

            OnClick.push_back(StateChange);

            if (Parent) {
                Parent->Buttons.push_back(static_cast<BaseConstructor*>(this));

                this->Obj = BtnUtils::BtnInstantinator::GetButtonTemplate();

                auto ButtonComp = this->Obj->GetComponent("Button");
                if (ButtonComp) {
                    this->Button;
                }

                auto BtnT = (Unity::CComponent*)this->Obj->GetTransform();
                if (BtnT)
                {
                    auto ButtonText = BtnT->CallMethodSafe<Unity::CComponent*>("FindChild", IL2CPP::String::New("Text_H4"))->GetGameObject();
                    if (ButtonText) {
                        auto CompTest = ButtonText->GetComponentByIndex(UNITY_COMPONENT_CLASS, 2);
                        if (CompTest) {
                            this->Text = CompTest;
                        }
                    }
                }
            }
        }
    };
}

#endif // BUTTON_API_H
