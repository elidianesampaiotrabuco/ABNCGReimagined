#pragma once
#include <_main.hpp>

#include <Geode/loader/SettingEvent.hpp>

#define mod(id) Loader::get()->getInstalledMod(id)

template <class T>
inline std::monostate listenForSettingChanges(
    std::string modID, std::string const& settingKey, void (*callback)(T)
) {
    (void)new EventListener(
        callback, GeodeSettingChangedFilter<T>(modID, settingKey)
    );
    return std::monostate();
}

inline auto settingIsForcedPopup(auto settingName = "thats") {
    return createQuickPopup(
        "Warning",
        fmt::format(
            "{} will be disabled by ABNCG: Reimagined every time the game starts.",
            settingName
        ),
        "Ok", nullptr,
        [](auto, auto) {}, false);
}

#define setListenerToNtfyForcedSetting(id, key) listenForSettingChanges(id, key,+[](bool value) {    settingIsForcedPopup(key)->show();    });

$execute{
	mod("geode.loader")->setSettingValue("disable-last-crashed-popup", true);
    setListenerToNtfyForcedSetting("geode.loader", "disable-last-crashed-popup");
	mod("geode.loader")->setSettingValue("enable-geode-theme", false);
    setListenerToNtfyForcedSetting("geode.loader", "enable-geode-theme");
}