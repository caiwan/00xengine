#include "Settings.hpp"
#include "Utils/String.hpp"
#include "Debug/Debug.hpp"

namespace engine{
    Settings::Settings(){
    }

    bool Settings::Parse(){
        bool ret = true;
		mSettingsFile.Open(settingsFileName, RWM_ReadOnly, FP_Top);
        if(mSettingsFile.IsOpened()){
            std::string line;
            while(!mSettingsFile.End()){
                line = mSettingsFile.GetLine();
				if(!line.empty())
					if(line[0] != '[' && line[0] != '\0'){
						Setting set;
						if(FindKey(line, set.Key, set.Value)){
							set.Key = StringUtils::ToLower(set.Key);
							AddSetting(set);
						}else{
							ret = false;
							break;
						}
					}
            }
            mSettingsFile.Close();
        }else{
			OmniLog << "Settings Manager : Settings File not found. Creating default one" << eol;
			// Creation de fichier par defaut au cas ou l'on ne trouverai pas de fichier utilisateur
			Setting set;
			mSettingsFile.Open(settingsFileName, RWM_Write, FP_Top);
			mSettingsFile << "[Video]" << eol;
			mSettingsFile << "WindowWidth=800" << eol;
			set.Key = "WindowWidth"; set.Value = "800";
			AddSetting(set);
			mSettingsFile << "WindowHeight=600" << eol;
			set.Key = "WindowHeight"; set.Value = "600";
			AddSetting(set);
			mSettingsFile << "MultiSamples=0" << eol;
			set.Key = "MultiSamples"; set.Value = "0";
			AddSetting(set);
			mSettingsFile << "CullFace=CCW" << eol;
			set.Key = "CullFace"; set.Value = "CCW";
			AddSetting(set);
			mSettingsFile << "Anisotropy=1" << eol;
			set.Key = "Anisotropy"; set.Value = "1";
			AddSetting(set);
			mSettingsFile << "VSync=on" << eol;
			set.Key = "VSync"; set.Value = "on";
			AddSetting(set);
			mSettingsFile << "FOV=45" << eol;
			set.Key = "FOV"; set.Value = "45";
			AddSetting(set);
			mSettingsFile << "NearPlane=0.1" << eol;
			set.Key = "NearPlane"; set.Value = "0.1";
			AddSetting(set);
			mSettingsFile << "FarPlane=500.0" << eol;
			set.Key = "FarPlane"; set.Value = "500.0";
			AddSetting(set);
			mSettingsFile << "AmbientColor=0.5,0.5,0.5" << eol;
			set.Key = "AmbientColor"; set.Value = "0.5,0.5,0.5";
			AddSetting(set);
			mSettingsFile.Close();
		}
        return ret;
    }

    void Settings::AddSetting(const Setting &set){
        if(!set.Key.empty() && !set.Value.empty())
            mSettings.push_back(set);
    }

    bool Settings::FindKey(std::string line, std::string &key, std::string &val) const {
		bool ret = true;
        size_t pos = line.find_first_of("=");

        if(pos <= 256){
            key = line.substr(0,pos);
            val = line.substr(pos+1);
        }else{
            ret = false;
            OmniLog << "Setting Manager : " << line << " is not a Valid Setting!" << eol;
        }
        return ret;
    }

    const std::string Settings::getSetting(const std::string key) const{
		std::string lowered = StringUtils::ToLower(key);
        for(std::vector<Setting>::const_iterator it = mSettings.begin(); it != mSettings.end(); it++)
            if((*it).Key == lowered)
                return (*it).Value;
        OmniLog << "Setting Manager : The \"" << key << "\" does not exist in the configuration file." << eol;
        return "";
    }

    const std::string Settings::GetSettingStr(const std::string key){
        std::string ret = Settings::Call().getSetting(key);
        return ret;
    }

    const s32 Settings::GetSettingInt(const std::string key){
        s32 ret = atoi(Settings::Call().getSetting(key).c_str());
        return ret;
    }

	const f32 Settings::GetSettingFloat(const std::string key){
		f32 ret = (f32)atof(Settings::Call().getSetting(key).c_str());
        return ret;
	}

    const bool Settings::GetSettingBool(const std::string key){
        bool ret = (Settings::Call().getSetting(key) == "yes" || Settings::Call().getSetting(key) == "on") ? true : false;
        return ret;
    }

	const Vector2F Settings::GetSettingVec2(const std::string key){
		std::string all = Settings::Call().getSetting(key);
		Vector2F vec2 = StringConverter::ToVector2(all);
		return vec2;
	}

	const Vector3F Settings::GetSettingVec3(const std::string key){
		std::string all = Settings::Call().getSetting(key);
		Vector3F vec3 = StringConverter::ToVector3(all);
		return vec3;
	}

	const Color Settings::GetSettingColor(const std::string key){
		std::string all = Settings::Call().getSetting(key);
		Color col = StringConverter::ToColor(all);
		return col;
	}
}
