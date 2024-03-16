#include "EngineParser.h"
#include "../../LoggingSystem/Logging.h" 
#include "Bleach_New/BleachNew.h"

///////////////////////////////////////
/////// ENGINE COMPONENT INCLUDES /////
///////////////////////////////////////
#include "../MurphEngine.h"
#include "../../../DemoProject/GameApplication/GameApplication.h"
#include "../CoreConcepts/Component/EngineLevelComponents/ButtonComponent/ButtonComponent.h"
#include "../CoreConcepts/Component/EngineLevelComponents/ButtonComponent/CheckBoxComponent/CheckBoxComponent.h"
#include "../CoreConcepts/Component/EngineLevelComponents/ButtonComponent/DynamicBarComponent/DynamicBarComponent.h"
#include "../CoreConcepts/Component/EngineLevelComponents/ButtonComponent/SliderComponent/SliderComponent.h"
#include "../CoreConcepts/Component/EngineLevelComponents/ButtonComponent/ToggleComponent/ToggleComponent.h"
#include "../CoreConcepts/Component/EngineLevelComponents/CollisionComponent/CollisionComponent.h"
#include "../CoreConcepts/Component/EngineLevelComponents/MovementComponent/MovementComponent.h"
#include "../CoreConcepts/Component/EngineLevelComponents/PositionComponent/PositionComponent.h"
#include "../CoreConcepts/Component/EngineLevelComponents/SpriteComponent/SpriteComponent.h"
#include "../CoreConcepts/Component/EngineLevelComponents/TextComponent/TextComponent.h"

#include "../SceneManager/Scene/Scene.h"

class GameApplication;


bool EngineParser::ParseFile(tinyxml2::XMLElement* element, Entity* pEntity)
{
    if (!pEntity) // if no entity was entered, we cannot add an element, so we cannot parse the file.
        return false;

    if (const auto elementName = element->Name(); std::strcmp(elementName, "PositionComponent") == 0)
    {
        auto positionX = static_cast<float>(std::atof(element->Attribute("x")));
        auto positionY = static_cast<float>(std::atof(element->Attribute("y")));
        auto positionWidth = static_cast<float>(std::atof(element->Attribute("width")));
        auto positionHeight = static_cast<float>(std::atof(element->Attribute("height")));
    	auto instance = MurphEngine::GetInstance()->GetGraphicsManager();

        if (positionWidth <= 0.f)
            positionWidth = static_cast<float>(instance->GetWindowWidth());
        if (positionHeight <= 0.f)
            positionHeight = static_cast<float>(instance->GetWindowHeight());
        pEntity->AddComponent(BLEACH_NEW(PositionComponent(positionX, positionY, positionWidth, positionHeight)));
    }
    else if (std::strcmp(elementName, "TextComponent") == 0)
    {
        auto fontPath = element->Attribute("fontLocation");
        auto fontSize = std::atoi(element->Attribute("fontSize"));
        auto contents = "test";
        auto component = static_cast<TextComponent*>(pEntity->AddComponent(BLEACH_NEW(TextComponent(fontPath, fontSize, contents))));
        component->Initialize();

        for (tinyxml2::XMLElement* actorElement = element->FirstChildElement();
            actorElement != nullptr;
            actorElement = actorElement->NextSiblingElement())
        {
            auto textElementName = actorElement->Name();
            if (strcmp(textElementName, "Text") == 0)
            {
                auto displayText = actorElement->Attribute("outputText");
                component->UpdateText(displayText);

                //TODO: parse justification, like we do in button.
            }
            else if (strcmp(textElementName, "TextColor") == 0)
            {
                auto redTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("redTint")));
                auto greenTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("greenTint")));
                auto blueTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("blueTint")));
                auto alphaTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("alphaTint")));

                component->SetTextColor({ redTint, greenTint, blueTint, alphaTint });
            }
        }

        auto button = pEntity->GetComponent("PositionComponent");
        if (button != nullptr)
        {
            auto var = static_cast<PositionComponent*>(button)->GetPosition();
            auto size = static_cast<PositionComponent*>(button)->GetPosition();
            component->SetParentPos({ var.x, var.y, size.x, size.y});
        }
    }
    else if (std::strcmp(elementName, "ButtonComponent") == 0)
    {
        auto spritePath = element->Attribute("Sprite");
        auto component = static_cast<ButtonComponent*>(pEntity->AddComponent(BLEACH_NEW(ButtonComponent(spritePath))));

        //component->SetCallback([]()-> void
        //    {
        //        
        //        LOG_TO_CONSOLE(kDefault, "Default Callback! (Does Nothing.)");
        //    });
        for (tinyxml2::XMLElement* actorElement = element->FirstChildElement();
            actorElement != nullptr;
            actorElement = actorElement->NextSiblingElement())
        {
            auto buttonElementName = actorElement->Name();
            if (strcmp(buttonElementName, "ButtonAnchorPosition") == 0)
            {
                //auto inputJustification = actorElement->Attribute("justification");
                // parse justification string into the enum.
            	component->SetJustification(ButtonComponent::ButtonJustification::kCenter);
            }
            //TODO: This should be at game level, not engine level. pull this out one level.
            //TODO:  (cont.) This will be accomplished by making game level components, and using the game level parser to parse them.
            else if (strcmp(buttonElementName, "ButtonCallback") == 0)
            {
                //auto buttonCallback = actorElement->Attribute("callback");
                ParseButtonCallback(component, actorElement->Attribute("callback"));
			}
            else if (strcmp(buttonElementName, "ButtonTextCallback") == 0)
            {
                //auto buttonOutput = actorElement->Attribute("TextOutput");
            	component->SetCallbackAsDebugLogText(actorElement->Attribute("TextOutput"));
            } 
            else if (strcmp(buttonElementName, "WidgetName") == 0)
            {
                auto widgetName = actorElement->Attribute("name");
                static_cast<InterfaceEntity*>(pEntity)->SetName(widgetName);
                component->SetwidgetName(widgetName);
            }
            else if (strcmp(buttonElementName, "ButtonTint") == 0)
            {
                auto redTint =   static_cast<uint8_t>(std::atoi(actorElement->Attribute("redTint")));
                auto greenTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("greenTint")));
                auto blueTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("blueTint")));
                auto alphaTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("alphaTint")));

                component->SetImageTintColor(redTint, greenTint, blueTint, alphaTint);
            }
            else if (strcmp(buttonElementName, "ButtonHighlightTint") == 0)
            {
                auto redTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("redTint")));
                auto greenTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("greenTint")));
                auto blueTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("blueTint")));
                auto alphaTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("alphaTint")));

                component->SetHighlightTintColor(redTint, greenTint, blueTint, alphaTint);
            }
            else
            {
                LOG_TO_CONSOLE(kError, "UN-IMPLEMENTED element input.");
            }
        }

    }
    else if (std::strcmp(elementName, "SpriteComponent") == 0)
    {
        //LOG_TO_CONSOLE(kDebug, elementName);

        auto positionComponent = static_cast<PositionComponent*>(pEntity->GetComponent("PositionComponent"));
        auto position = positionComponent->GetRect();

        auto spritePath = element->Attribute("Sprite");
        if (std::strlen(spritePath) <= 1)
        {
            spritePath = "no image. defaulting to pixel.";
            pEntity->AddComponent(BLEACH_NEW(SpriteComponent(position.GetWidth(), position.GetHeight())));
            // call sprite component no image.
        }
        else
        {
            // add sprite component with image.
            auto spriteComp = pEntity->AddComponent(BLEACH_NEW(SpriteComponent(position.GetWidth(), position.GetHeight())));
            static_cast<SpriteComponent*>(spriteComp)->AddTexture(spritePath);
        }
    }
    else if (std::strcmp(elementName, "CheckBoxComponent") == 0)
    {
        //LOG_TO_CONSOLE(kDebug, elementName);

        auto boxPath = element->Attribute("boxSprite");
        auto checkPath = element->Attribute("checkMarkSprite");
        auto component = static_cast<CheckBoxComponent*>(pEntity->AddComponent(BLEACH_NEW(CheckBoxComponent(boxPath, checkPath))));


        for (tinyxml2::XMLElement* actorElement = element->FirstChildElement();
            actorElement != nullptr;
            actorElement = actorElement->NextSiblingElement())
        {
            auto buttonElementName = actorElement->Name();
            if (strcmp(buttonElementName, "checkBoxBackgroundTint") == 0)
            {
                auto redTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("redTint")));
                auto greenTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("greenTint")));
                auto blueTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("blueTint")));
                auto alphaTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("alphaTint")));

                component->SetImageTintColor(redTint, greenTint, blueTint, alphaTint);
            }
            else if (strcmp(buttonElementName, "WidgetName") == 0)
            {
                auto widgetName = actorElement->Attribute("name");
                static_cast<InterfaceEntity*>(pEntity)->SetName(widgetName);
                component->SetwidgetName(widgetName);
            }
            else if (strcmp(buttonElementName, "checkBoxSelectTint") == 0)
            {
                auto redTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("redTint")));
                auto greenTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("greenTint")));
                auto blueTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("blueTint")));
                auto alphaTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("alphaTint")));

                component->SetBoxHighlightTintColor(redTint, greenTint, blueTint, alphaTint);
            }
            else if (strcmp(buttonElementName, "checkTint") == 0)
            {
                auto redTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("redTint")));
                auto greenTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("greenTint")));
                auto blueTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("blueTint")));
                auto alphaTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("alphaTint")));

                component->SetMarkTintColor(redTint, greenTint, blueTint, alphaTint);
            }
        }
    }
    else if (std::strcmp(elementName, "ToggleComponent") == 0)
    {
        //LOG_TO_CONSOLE(kDebug, elementName);

        auto boxPath = element->Attribute("boxSprite");
        auto toggleKnobSpritePath = element->Attribute("toggleKnobSprite");
        auto component = static_cast<ToggleComponent*>(pEntity->AddComponent(BLEACH_NEW(ToggleComponent(boxPath, toggleKnobSpritePath))));


        for (tinyxml2::XMLElement* actorElement = element->FirstChildElement();
            actorElement != nullptr;
            actorElement = actorElement->NextSiblingElement())
        {
            auto buttonElementName = actorElement->Name();
            if (strcmp(buttonElementName, "ToggleBackgroundTint") == 0)
            {
                auto redTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("redTint")));
                auto greenTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("greenTint")));
                auto blueTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("blueTint")));
                auto alphaTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("alphaTint")));

                component->SetImageTintColor(redTint, greenTint, blueTint, alphaTint);
            }
            else if (strcmp(buttonElementName, "WidgetName") == 0)
            {
                auto widgetName = actorElement->Attribute("name");
                static_cast<InterfaceEntity*>(pEntity)->SetName(widgetName);
                component->SetwidgetName(widgetName);
            }
            else if (strcmp(buttonElementName, "ToggleSelectTint") == 0)
            {
                auto redTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("redTint")));
                auto greenTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("greenTint")));
                auto blueTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("blueTint")));
                auto alphaTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("alphaTint")));

                component->SetHighlightTintColor(redTint, greenTint, blueTint, alphaTint);
            }
            else if (strcmp(buttonElementName, "ToggleTint") == 0)
            {
                auto redTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("redTint")));
                auto greenTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("greenTint")));
                auto blueTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("blueTint")));
                auto alphaTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("alphaTint")));

                component->SetToggleTintColor(redTint, greenTint, blueTint, alphaTint);
            }
        }
    }
    else if (std::strcmp(elementName, "SliderComponent") == 0)
    {
        //LOG_TO_CONSOLE(kDebug, elementName);

        auto trayPath = element->Attribute("sliderTraySprite");
        auto sliderKnobSpritePath = element->Attribute("sliderKnobSprite");

        auto component = dynamic_cast<SliderComponent*>(pEntity->AddComponent(BLEACH_NEW(SliderComponent(trayPath, sliderKnobSpritePath))));
        for (tinyxml2::XMLElement* actorElement = element->FirstChildElement();
            actorElement != nullptr;
            actorElement = actorElement->NextSiblingElement())
        {
            auto buttonElementName = actorElement->Name();
            if (strcmp(buttonElementName, "SliderTrayTint") == 0)
            {
                auto redTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("redTint")));
                auto greenTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("greenTint")));
                auto blueTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("blueTint")));
                auto alphaTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("alphaTint")));

                component->SetImageTintColor(redTint, greenTint, blueTint, alphaTint);
            }
            else if (strcmp(buttonElementName, "WidgetName") == 0)
            {
                auto widgetName = actorElement->Attribute("name");
                static_cast<InterfaceEntity*>(pEntity)->SetName(widgetName);
                component->SetwidgetName(widgetName);
            }
            else if (strcmp(buttonElementName, "SliderKnobTint") == 0)
            {
                auto redTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("redTint")));
                auto greenTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("greenTint")));
                auto blueTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("blueTint")));
                auto alphaTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("alphaTint")));

                component->SetKnobTintColor(redTint, greenTint, blueTint, alphaTint);
            }
            else if (strcmp(buttonElementName, "SliderValues") == 0)
            {
                auto minSliderVal = static_cast<uint8_t>(std::atoi(actorElement->Attribute("min")));
                auto maxSliderVal = static_cast<uint8_t>(std::atoi(actorElement->Attribute("max")));

                component->SetMinimumSliderValue(minSliderVal);
                component->SetMaximumSliderValue(maxSliderVal);
            }
            else if (strcmp(buttonElementName, "SliderKnobSize") == 0)
            {
                auto knobWidth = static_cast<uint8_t>(std::atoi(actorElement->Attribute("width")));
                auto knobHeight = static_cast<uint8_t>(std::atoi(actorElement->Attribute("height")));

                component->SetKnobSize(knobWidth, knobHeight);
            }
        }
    }
    else if (std::strcmp(elementName, "MovementComponent") == 0)
    {
        auto moveSpeed = static_cast<float>(std::atof(element->Attribute("moveSpeed")));


        auto component = static_cast<MovementComponent*>(pEntity->AddComponent(BLEACH_NEW(MovementComponent())));
        component->SetMovementSpeed(moveSpeed);
    }
    else if (std::strcmp(elementName, "DynamicBarComponent") == 0)
    {
        //LOG_TO_CONSOLE(kDebug, elementName);

        auto trayPath = element->Attribute("traySprite");
        auto barPath = element->Attribute("barSprite");

        auto component = dynamic_cast<DynamicBarComponent*>(pEntity->AddComponent(BLEACH_NEW(DynamicBarComponent(trayPath, barPath))));
        for (tinyxml2::XMLElement* actorElement = element->FirstChildElement();
            actorElement != nullptr;
            actorElement = actorElement->NextSiblingElement())
        {
            auto buttonElementName = actorElement->Name();
            if (strcmp(buttonElementName, "WidgetName") == 0)
            {
                auto widgetName = actorElement->Attribute("name");
                static_cast<InterfaceEntity*>(pEntity)->SetName(widgetName);
                component->SetwidgetName(widgetName);
            }
            else if (strcmp(buttonElementName, "TrayTint") == 0)
            {
                auto redTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("redTint")));
                auto greenTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("greenTint")));
                auto blueTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("blueTint")));
                auto alphaTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("alphaTint")));

                component->SetImageTintColor(redTint, greenTint, blueTint, alphaTint);
            }
            else if (strcmp(buttonElementName, "BarTint") == 0)
            {
                auto redTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("redTint")));
                auto greenTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("greenTint")));
                auto blueTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("blueTint")));
                auto alphaTint = static_cast<uint8_t>(std::atoi(actorElement->Attribute("alphaTint")));

                component->SetKnobTintColor(redTint, greenTint, blueTint, alphaTint);
            }
            else if (strcmp(buttonElementName, "Values") == 0)
            {
                auto minSliderVal = static_cast<uint8_t>(std::atoi(actorElement->Attribute("min")));
                auto maxSliderVal = static_cast<uint8_t>(std::atoi(actorElement->Attribute("max")));

                component->SetMinimumBarValue(minSliderVal);
                component->SetMaximumBarValue(maxSliderVal);

                component->SetNewBarValue(5.f);
            }
            else if (strcmp(buttonElementName, "KnobSize") == 0)
            {
                auto knobWidth = static_cast<uint8_t>(std::atoi(actorElement->Attribute("width")));
                auto knobHeight = static_cast<uint8_t>(std::atoi(actorElement->Attribute("height")));

                component->SetBarSize(knobWidth, knobHeight);
            }
        }
        }
    else if (std::strcmp(elementName, "CollisionComponent") == 0)
    {
        auto isBlockingInput = element->Attribute("Blocking");
        bool isBlocking = false;
        if (strcmp(isBlockingInput, "true") == 0)
        {
            isBlocking = true;
        }
        else if (strcmp(isBlockingInput, "false") == 0)
        {
            isBlocking = false;
        }
        else
        {
            LOG_TO_CONSOLE(kError, "Invalid blocking input true/false input. Defaulting to false.");
        }


        auto component = static_cast<CollisionComponent*>(pEntity->AddComponent(BLEACH_NEW(CollisionComponent())));
        component->SetBlockingCollision(isBlocking);
    }
    else
    {
        LOG_TO_CONSOLE(kError, " cannot be found. Please Add, or check spelling");
        return false;
    }

    return true;
}

/// <summary>
/// Parse Button Callback (TODO: split engine and game level callbacks)
/// </summary>
/// <param name="component"> current button component</param>
/// <param name="callback">Requested callback from XML</param>
void EngineParser::ParseButtonCallback(ButtonComponent* component, const char* callback)
{
    if (strcmp(callback, "QuitApplication") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetSceneManager()->GetCurrentScene()->QuitScene();
                LOG_TO_CONSOLE(kDefault, "Quit Called");
            });
    }
    //TODO: Move the below callbacks to game level via Game level components. (see above TODO)
    else if (strcmp(callback, "PlayButton") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("Level_1");
                LOG_TO_CONSOLE(kSystem, "Pressed Play!");
            });
    }
    else if (strcmp(callback, "OptionsMenu") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("OptionsMenu");
                LOG_TO_CONSOLE(kDefault, "Opening Options Menu");
            });
    }
    else if (strcmp(callback, "DifficultyMenu") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("DifficultyMenu");
                LOG_TO_CONSOLE(kDefault, "Opening Difficulty Menu");
            });
    }
    else if (strcmp(callback, "VolumeMenu") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("VolumeMenu");
                LOG_TO_CONSOLE(kDefault, "Opening Volume Menu");
            });
    }
    else if (strcmp(callback, "MainMenu") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("MainMenu");
                LOG_TO_CONSOLE(kDefault, "Opening Main Menu");
            });
    }
    else if (strcmp(callback, "InventoryMenu") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("InventoryMenu");
                LOG_TO_CONSOLE(kDefault, "Opening Inventory Menu");
            });
    }
    else if (strcmp(callback, "SongSelectionMenu") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("SongSelectionMenu");
                LOG_TO_CONSOLE(kDefault, "Opening Song Select Menu");
            });
    }
    else if (strcmp(callback, "PreviousScene") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetSceneManager()->ActivatePreviousScene();
                LOG_TO_CONSOLE(kDefault, "Opening Previous Scene");
            });
    }
    else if (strcmp(callback, "Start") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("MainMenu");
                LOG_TO_CONSOLE(kDefault, "Opening Main Menu");
            });
    }
    else if (strcmp(callback, "CharacterSelectMenu") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("CharacterSelectMenu");
                LOG_TO_CONSOLE(kDefault, "Opening Character Select Menu");
            });
    }
    else if (strcmp(callback, "LanguageSelectMenu") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("LanguageSelectMenu");
                LOG_TO_CONSOLE(kDefault, "Opening Character Select Menu");
            });
    }
    else if (strcmp(callback, "CosmeticVerificationMenu") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("CosmeticVerificationMenu");
                LOG_TO_CONSOLE(kDefault, "Opening Cosmetic Verification");
            });
    }
    else if (strcmp(callback, "MaxOutfit") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("MaxOutfitSelectMenu");
                LOG_TO_CONSOLE(kDefault, "Opening Max Outfit Select Menu");
            });
    }
    else if (strcmp(callback, "SamOutfit") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("SamOutfitSelectMenu");
                LOG_TO_CONSOLE(kDefault, "Opening Sam Outfit Select Menu");
            });
    }
    else if (strcmp(callback, "SamOutfitPajamas") == 0)
    {
        component->SetCallback([]()-> void
            {
                auto instance = MurphEngine::GetInstance();
                static_cast<GameApplication*>(instance->GetApplication())->GetCosmeticSystem()->GetPlayerCosmeticManager()
                    ->SetPlayerCosmeticTexture("Assets/Characters/Sam/SamPajamas.png");
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("CosmeticVerificationMenu");
                LOG_TO_CONSOLE(kDefault, "Selected Outfit.");
            });
    }
    else if (strcmp(callback, "SamOutfitScrubs") == 0)
    {
        component->SetCallback([]()-> void
            {
                auto instance = MurphEngine::GetInstance();
                static_cast<GameApplication*>(instance->GetApplication())->GetCosmeticSystem()->GetPlayerCosmeticManager()
                    ->SetPlayerCosmeticTexture("Assets/Characters/Sam/SamScrubs.png");
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("CosmeticVerificationMenu");
                LOG_TO_CONSOLE(kDefault, "Selected Outfit.");
            });
    }
    else if (strcmp(callback, "SamOutfitTuxedo") == 0)
    {
        component->SetCallback([]()-> void
            {
                auto instance = MurphEngine::GetInstance();
                static_cast<GameApplication*>(instance->GetApplication())->GetCosmeticSystem()->GetPlayerCosmeticManager()
                    ->SetPlayerCosmeticTexture("Assets/Characters/Sam/SamTuxedo.png");
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("CosmeticVerificationMenu");
                LOG_TO_CONSOLE(kDefault, "Selected Outfit.");
            });
    }
    else if (strcmp(callback, "SamOutfitDuster") == 0)
    {
        component->SetCallback([]()-> void
            {
                auto instance = MurphEngine::GetInstance();
                static_cast<GameApplication*>(instance->GetApplication())->GetCosmeticSystem()->GetPlayerCosmeticManager()
                    ->SetPlayerCosmeticTexture("Assets/Characters/Sam/SamDuster.png");
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("CosmeticVerificationMenu");
                LOG_TO_CONSOLE(kDefault, "Selected Outfit.");
            });
    }
    else if (strcmp(callback, "MaxOutfitPajamas") == 0)
    {
        component->SetCallback([]()-> void
            {
                auto instance = MurphEngine::GetInstance();
                static_cast<GameApplication*>(instance->GetApplication())->GetCosmeticSystem()->GetPlayerCosmeticManager()
                    ->SetPlayerCosmeticTexture("Assets/Characters/Max/MaxPajamas.png");
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("CosmeticVerificationMenu");
                LOG_TO_CONSOLE(kDefault, "Selected Outfit.");
            });
    }
    else if (strcmp(callback, "MaxOutfitBoyScout") == 0)
    {
        component->SetCallback([]()-> void
            {
                auto instance = MurphEngine::GetInstance();
                static_cast<GameApplication*>(instance->GetApplication())->GetCosmeticSystem()->GetPlayerCosmeticManager()
                    ->SetPlayerCosmeticTexture("Assets/Characters/Max/MaxBoyscout.png");
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("CosmeticVerificationMenu");
                LOG_TO_CONSOLE(kDefault, "Selected Outfit.");
            });
    }
    else if (strcmp(callback, "MaxOutfitOpera") == 0)
    {
        component->SetCallback([]()-> void
            {
                auto instance = MurphEngine::GetInstance();
                static_cast<GameApplication*>(instance->GetApplication())->GetCosmeticSystem()->GetPlayerCosmeticManager()
                    ->SetPlayerCosmeticTexture("Assets/Characters/Max/MaxOpera.png");
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("CosmeticVerificationMenu");
                LOG_TO_CONSOLE(kDefault, "Selected Outfit.");
            });
    }
    else if (strcmp(callback, "MaxOutfitWedding") == 0)
    {
        component->SetCallback([]()-> void
            {
                auto instance = MurphEngine::GetInstance();
                static_cast<GameApplication*>(instance->GetApplication())->GetCosmeticSystem()
                    ->GetPlayerCosmeticManager()
                    ->SetPlayerCosmeticTexture("Assets/Characters/Max/MaxWedding.png");
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("CosmeticVerificationMenu");
                LOG_TO_CONSOLE(kDefault, "Selected Outfit.");
            });
    }
    else if (strcmp(callback, "SetLanguage_English") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetLocalizationManager()->SetLocalizationLanguage("English");
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("MainMenu");
                LOG_TO_CONSOLE(kDefault, "Setting Language to English");
            });
    }
    else if (strcmp(callback, "SetLanguage_French") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetLocalizationManager()->SetLocalizationLanguage("French");
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("MainMenu");
                LOG_TO_CONSOLE(kDefault, "Setting Language to French");
            });
            }
    else if (strcmp(callback, "SetLanguage_German") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetLocalizationManager()->SetLocalizationLanguage("German");
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("MainMenu");
                LOG_TO_CONSOLE(kDefault, "Setting Language to German");
            });
            }
    else if (strcmp(callback, "SetLanguage_Italian") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetLocalizationManager()->SetLocalizationLanguage("Italian");
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("MainMenu");
                LOG_TO_CONSOLE(kDefault, "Setting Language to Italian");
            });
    }
    else if (strcmp(callback, "SetLanguage_Spanish") == 0)
    {
        component->SetCallback([]()-> void
            {
                MurphEngine::GetInstance()->GetLocalizationManager()->SetLocalizationLanguage("Spanish");
                MurphEngine::GetInstance()->GetSceneManager()->LoadScene("MainMenu");
                LOG_TO_CONSOLE(kDefault, "Setting Language to Spanish");
            });
            }
    else
    {
        LOG_TO_CONSOLE(kError, "UN-IMPLEMENTED element input.");
    }
}

