
namespace BtnUtils {

	namespace BtnInstantinator {
		
		Unity::CGameObject* GetQuickMenu() {
			auto objbuf = Unity::GameObject::Find("Canvas_QuickMenu(Clone)");
			if (objbuf)
				return objbuf;
			else
				return nullptr;
		}

		Unity::CGameObject* GetDevToolsGrid() {
			auto QM = GetQuickMenu();
			if (QM)
			{
				//printf("QM Valid\n");
				auto QMTrans = (Unity::CComponent*)QM->GetTransform();
				if (QMTrans)
				{
					auto DevToolsButtonsMenu = QMTrans->CallMethodSafe<Unity::CComponent*>("FindChild", IL2CPP::String::New("CanvasGroup/Container/Window/QMParent/Menu_DevTools/Scrollrect/Viewport/VerticalLayoutGroup/Buttons"))->GetGameObject();
					if (DevToolsButtonsMenu) {
						return DevToolsButtonsMenu;
					}

				}
			}
			return nullptr;
		}

		Unity::CGameObject* GetButtonTemplate() {
			auto QM = GetQuickMenu();
			if (QM)
			{
				auto QMTrans = (Unity::CComponent*)QM->GetTransform();
				if (QMTrans)
				{
					auto RespawnButtonTrans = QMTrans->CallMethodSafe<Unity::CComponent*>("FindChild", IL2CPP::String::New("CanvasGroup/Container/Window/QMParent/Menu_Dashboard/ScrollRect/Viewport/VerticalLayoutGroup/Buttons_QuickActions/Button_Respawn"));
					if (RespawnButtonTrans)
					{
						Unity::CGameObject* GridToPlaceButton = GetDevToolsGrid();
						if (GridToPlaceButton)
						{
							auto GridToPlaceButtonTrans = GridToPlaceButton->GetTransform();
							if (GridToPlaceButtonTrans)
							{
								auto RespawnButtonCopy = RespawnButtonTrans->GetGameObject()->Instantiate(GridToPlaceButtonTrans);
								if (RespawnButtonTrans->GetGameObject())
								{			
									auto ButtonComp = RespawnButtonCopy->GetComponent("Button");
									if (ButtonComp)
									{
										auto onclick = ButtonComp->GetPropertyValue<Unity::CComponent*>("onClick");
										if (onclick) {
											onclick->CallMethodSafe<void*>("RemoveAllListeners");

										}
									}
									return RespawnButtonCopy;
								}
							}
						}
					}
				}
			}
			return nullptr;
		}

		bool SetupPanel(std::string title) {
			auto QM = GetQuickMenu();
			if (QM)
			{
				auto QMTrans = (Unity::CComponent*)QM->GetTransform();
				if (QMTrans)
				{
					auto DevToolsText = QMTrans->CallMethodSafe<Unity::CComponent*>("FindChild", IL2CPP::String::New("CanvasGroup/Container/Window/QMParent/Menu_DevTools/Header_DevTools/LeftItemContainer/Text_Title"))->GetGameObject();
					if (DevToolsText)
					{
						auto CompTest = DevToolsText->GetComponentByIndex(UNITY_COMPONENT_CLASS, 2);
						if (CompTest) {
							CompTest->CallMethodSafe<void*>("SetText", IL2CPP::String::New(title.c_str()), false);
						}
					}
				}
			}

			auto DevToolsButtonscomp = QM->GetTransform()->CallMethodSafe<Unity::CComponent*>("FindChild", IL2CPP::String::New("CanvasGroup/Container/Window/QMParent/Menu_DevTools/Scrollrect/Viewport/VerticalLayoutGroup/Buttons"));
			if (DevToolsButtonscomp)
			{
				auto DevToolsButtonsTrans = DevToolsButtonscomp->GetGameObject()->GetTransform();
				auto DevToolsChildren = DevToolsButtonsTrans->GetChildCount();
				
				for (int j = 0; j < DevToolsChildren; j++)
				{
					auto child = (Unity::CComponent*)DevToolsButtonsTrans->GetChild(j);
					if (child)
					{
						child->GetGameObject()->Destroy();
					}
				}
			}

			return true;
		}

		Unity::CGameObject* GetDevToolsButton() {
			auto QM = GetQuickMenu();
			if (QM) {
				auto QMTrans = (Unity::CComponent*)QM->GetTransform();
				if (QMTrans)
				{
					auto DTButton = QMTrans->CallMethodSafe<Unity::CComponent*>("FindChild", IL2CPP::String::New("CanvasGroup/Container/Window/Page_Buttons_QM/HorizontalLayoutGroup/Page_DevTools"))->GetGameObject();
					if (DTButton)
					{
						return DTButton;
					}
				}
			}
			return nullptr;
		}
	}
	

	struct BaseConstructor {
	private:
		std::string CachedText;
	public:
		Unity::CGameObject* Obj;
		Unity::CComponent* Button;
		Unity::CComponent* Text;
		std::vector<std::function<void()>> OnClick;

		bool SetText(std::string text) {
			CachedText = text;

			if (Text) {
				Text->CallMethodSafe<void*>("SetText", IL2CPP::String::New(text.c_str()));
				return true;
			}
			return false;
		}

		bool CenterText() {
			if (Text) {
				auto obj = Text->GetGameObject();

				auto pos = obj->GetTransform()->GetLocalPosition();
				obj->GetTransform()->SetLocalPosition(Unity::Vector3(pos.x, pos.y + 50.f, pos.z));
				return true;
			}

			return false;
		}

		bool SetColor(Unity::Color Color) {
			if (Text) {
				Text->CallMethodSafe<void*>("set_color", Color);
				return true;
			}

			return false;
		}

		bool RemoveIcon() {
			auto buttontransform = (Unity::CComponent*)this->Obj->GetTransform();
			if (buttontransform)
			{
				auto ButtonIcon = buttontransform->CallMethodSafe<Unity::CComponent*>("FindChild", IL2CPP::String::New("Icon"))->GetGameObject();
				if (ButtonIcon) {
					ButtonIcon->Destroy();
					return true;
				}
			}
			return false;
		}

		void SetActive(bool state) {
			Obj->SetActive(state);

			if (state) {
				SetText(CachedText);
			}
		}

		void SetOnClick(std::function<void()> Action) {
			OnClick.push_back(Action);
		}
	};
}