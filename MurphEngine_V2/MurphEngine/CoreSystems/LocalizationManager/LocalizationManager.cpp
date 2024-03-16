#include "LocalizationManager.h"

#include <ranges>

#include "../../LoggingSystem/Logging.h"
#include "Bleach_New/BleachNew.h"


LocalizationManager::LocalizationManager()
	:m_currentLocalizationLanguage("English")
{
	
}

LocalizationManager::~LocalizationManager()
{
	// clear the map of arrays of strings.
	for (auto& language : m_languageLocalizationMap | std::views::values)
		language.clear();
	// clean the map
	m_languageLocalizationMap.clear();

	// clean the english map.
	m_englishLocalizationAssociationMap.clear();
}


void LocalizationManager::AddStringToLocalization(const std::string& string)
{
	static size_t stringIndex = 0;

	// if the localization hasn't processed this string yet
	if (!m_englishLocalizationAssociationMap.contains(string))
	{
		// add it to the list, and increment the index.
		m_englishLocalizationAssociationMap.emplace(string, stringIndex);

		for (auto& language : m_languageLocalizationMap)
		{
			std::string defaultText = "Default";
			language.second.emplace_back(defaultText);
		}

		++stringIndex;
	}
}


void LocalizationManager::AddLanguageToLocalization(const std::string& newLanguageName)
{
	if (m_languageLocalizationMap.contains(newLanguageName))
	{
		LOG_TO_CONSOLE(kError, "Language already added.");
		return;
	}
	m_languageLocalizationMap.try_emplace(newLanguageName);
}


void LocalizationManager::AddLanguageLocalizedString(const std::string& language, const std::string& englishString, const std::string& translatedString)
{
	// if our map doesn't contain the language we request
	if (!m_languageLocalizationMap.contains(language))
	{
		LOG_TO_CONSOLE(kError, "Unable to Add Localized String. Input Language not found.");
		return;
	}

	// if our english association map doesn't contain the string, report an error, and add to the map.
	if (!m_englishLocalizationAssociationMap.contains(englishString))
	{
		LOG_TO_CONSOLE(kError, "Index for new localized string not found.");
		return;
	}

	// Get the language map we are going to add the translation to.

	// Get the index we have associated with the english translation
	const size_t localizedIndex = m_englishLocalizationAssociationMap.at(englishString);
	m_languageLocalizationMap.at(language)[localizedIndex] = translatedString;
}

std::string LocalizationManager::Localize(const std::string& string)
{
	// if we are using default language settings, then we don't localize.
	if (m_currentLocalizationLanguage == "English")
		return string;

	// if the string we are searching for is NOT within our localization map
	if (!m_englishLocalizationAssociationMap.contains(string))
		return string; // push it through without translation.

	// get index from map
	const auto index = m_englishLocalizationAssociationMap.at(string);
	return m_languageLocalizationMap.at(m_currentLocalizationLanguage).at(index);
}
