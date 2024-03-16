#pragma once
#include <string>
#include <unordered_map>

class LocalizationManager
{
	/// <summary>
	/// Current Language we are using as a "default"
	/// </summary>
	std::string m_currentLocalizationLanguage;

	/// <summary>
	/// English association map
	/// </summary>
	std::unordered_map<std::string, size_t> m_englishLocalizationAssociationMap;

	/// <summary>
	/// Map of Localized languages. Accessed via index found in englishAssociationMap
	/// </summary>
	std::unordered_map<std::string, std::vector<std::string>> m_languageLocalizationMap;

public:
	LocalizationManager();
	~LocalizationManager();

	/// <summary>
	/// Specify which language is the "default"
	/// </summary>
	/// <param name="localizedLanguage">which is the new default language</param>
	void SetLocalizationLanguage(const std::string& localizedLanguage) { m_currentLocalizationLanguage = localizedLanguage; }

	/// <summary>
	/// Get set default language
	/// </summary>
	/// <returns>current default language name</returns>
	std::string GetLocalizationLanguage() const { return m_currentLocalizationLanguage; }

	/// <summary>
	/// Add String to English map for localization
	/// </summary>
	/// <param name="string">string to localize</param>
	void AddStringToLocalization(const std::string& string);

	/// <summary>
	/// Add Specified language for translation storage
	/// </summary>
	/// <param name="newLanguageName">new language name</param>
	void AddLanguageToLocalization(const std::string& newLanguageName);

	/// <summary>
	/// add translated string to map of localized languages
	/// </summary>
	/// <param name="language">Specified Language of translated string</param>
	/// <param name="englishString">english translation for correlation</param>
	/// <param name="translatedString">translation to store</param>
	/// <returns>if string was added successfully</returns>
	void AddLanguageLocalizedString(const std::string& language, const std::string& englishString, const std::string& translatedString);

	/// <summary>
	/// Get Translated string from english.
	/// </summary>
	/// <param name="string">Requested string we want translated</param>
	/// <returns>translated string based on set value.</returns>
	std::string Localize(const std::string& string);
};
