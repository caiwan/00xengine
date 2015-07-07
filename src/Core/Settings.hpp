#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <vector>
#include <string>
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Utils/Color.hpp"
#include "Utils/File.hpp"
#include "Utils/Singleton.hpp"

namespace engine{
	/// \brief Default config file
    const char settingsFileName[] = "Options.cfg";

	/// \brief Structure conaining a key and its mapped value
    struct Setting{
        Setting() : Key(""), Value(""){
		}

		Setting(std::string key, std::string val) : Key(key), Value(val){
		}

		std::string Key;
		std::string Value;
    };

	/// \brief Class parsing and keeping in memory the settings of the engine. Singleton class, Parse function must be called early. Kill Singleton function must be called in the end of execution
    class OOXAPI Settings : public Singleton<Settings>{
        friend class Singleton<Settings>;
    	public:
    		Settings();
    		~Settings(){}

    		/// \brief Parse the Option.cfg to store options. Or create it if it doesn't exist
            bool Parse();

            /// \brief Returns one setting value from specified key
            /// \param key : Key of the asked value
            /// \return String
			static const std::string GetSettingStr(const std::string key);

            /// \brief Returns one setting value from specified key
            /// \param key : Key of the asked value
            /// \return Int
            static const s32 GetSettingInt(const std::string key);

            /// \brief Returns one setting value from specified key
            /// \param key : Key of the asked value
            /// \return Float
            static const f32 GetSettingFloat(const std::string key);

            /// \brief Returns one setting value from specified key
            /// \param key : Key of the asked value
            /// \return Bool
            static const bool GetSettingBool(const std::string key);

            /// \brief Returns one setting value from specified key
            /// \param key : Key of the asked value
            /// \return Vector2
			static const Vector2F GetSettingVec2(const std::string key);

            /// \brief Returns one setting value from specified key
            /// \param key : Key of the asked value
            /// \return Vector3
			static const Vector3F GetSettingVec3(const std::string key);

            /// \brief Returns one setting value from specified key
            /// \param key : Key of the asked value
            /// \return Color
			static const Color GetSettingColor(const std::string key);

    	private:

            /// \brief Add a setting to the vector
            // \param set : Setting to be added
    		void AddSetting(const Setting &set);

            /// \brief Function used by parse to parse one line and get a key and its value
            /// \param line : Complete Line
            /// \param key  : Left Part of the line (Key)
            /// \param val  : Right Part of the line (Value)
            bool FindKey(std::string line, std::string &key, std::string &val) const;

            /// \brief Function used by specific GetSetting*** public function
            /// \param key : Key of the asked value
            const std::string getSetting(const std::string key) const;

            std::vector<Setting> mSettings;
            File mSettingsFile;
    };

}

#endif // SETTINGS_HPP
