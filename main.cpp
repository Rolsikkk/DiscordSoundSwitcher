#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <filesystem>
#include <algorithm>
#include <cstdlib>
#include <windows.h>
#include <shellapi.h>
#include <wininet.h>
#include <tlhelp32.h>

namespace fs = std::filesystem;

// Version & Repository
const std::string CURRENT_VERSION = "v1.1.0";
const std::string GITHUB_REPO     = "Rolsikkk/DiscordSoundSwitcher";

// ANSI colors for clean CLI styling
const std::string RESET   = "\033[0m";
const std::string BOLD    = "\033[1m";
const std::string RED     = "\033[31m";
const std::string GREEN   = "\033[32m";
const std::string YELLOW  = "\033[33m";
const std::string BLUE    = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN    = "\033[36m";
const std::string WHITE   = "\033[37m";
const std::string GRAY    = "\033[90m";

// Audio Hashes in Discord CDN
// Classic (Default):
const std::string HASH_CLASSIC_MSG        = "3ed22d14f3c30bc4.mp3";
const std::string HASH_CLASSIC_CALLING    = "5146737af413d88e.mp3";
const std::string HASH_CLASSIC_RINGING    = "c2a7111bb44b8da0.mp3";
const std::string HASH_CLASSIC_DEAFEN     = "529ff198eac567af.mp3";
const std::string HASH_CLASSIC_UNDEAFEN   = "b150f03c89944403.mp3";
const std::string HASH_CLASSIC_MUTE       = "2d3b4ba32c34c862.mp3";
const std::string HASH_CLASSIC_UNMUTE     = "e74c4a06134a20e4.mp3";
const std::string HASH_CLASSIC_DISCONNECT = "dd0911025fe00b2e.mp3";
const std::string HASH_CLASSIC_USER_JOIN  = "b135ff6c8e091b43.mp3";
const std::string HASH_CLASSIC_USER_LEAVE = "7b9a183742515fc2.mp3";

// Halloween:
const std::string HASH_HW_MSG        = "c269de500ca3cb7b.mp3";
const std::string HASH_HW_CALLING    = "ef24e229a3413c8a.mp3";
const std::string HASH_HW_RINGING    = "7a287e2f88531f25.mp3";
const std::string HASH_HW_DEAFEN     = "514663b657bc4c7d.mp3";
const std::string HASH_HW_UNDEAFEN   = "4dfa756a71484219.mp3";
const std::string HASH_HW_MUTE       = "d5e69d2c2aac0a27.mp3";
const std::string HASH_HW_UNMUTE     = "6f0d538ed066a1a6.mp3";
const std::string HASH_HW_DISCONNECT = "9b8ef0a59d731dd6.mp3";
const std::string HASH_HW_USER_JOIN  = "00b48ea9fc787786.mp3";
const std::string HASH_HW_USER_LEAVE = "c9b6b9d1ef992f1b.mp3";

// Winter Holiday / New Year:
const std::string HASH_WINTER_CALLING    = "a07935fe464c324c.mp3";
const std::string HASH_WINTER_RINGING    = "daf6c21d9f92979a.mp3";
const std::string HASH_WINTER_DEAFEN     = "70fe5e248588bb13.mp3";
const std::string HASH_WINTER_UNDEAFEN   = "5b518eba0a73ec4a.mp3";
const std::string HASH_WINTER_MUTE       = "81034fa14558e50f.mp3";
const std::string HASH_WINTER_UNMUTE     = "b2c49178b1a4e3d9.mp3";
const std::string HASH_WINTER_DISCONNECT = "600991ad4560f288.mp3";
const std::string HASH_WINTER_USER_JOIN  = "b766ee70384a56ce.mp3";
const std::string HASH_WINTER_USER_LEAVE = "cf2c36fde50eb05d.mp3";

// Special Holiday Ringtones:
const std::string HASH_SNOWSGIVING_RINGING   = "4261355196740dab.mp3";
const std::string HASH_SNOW_HALATION_RINGING = "82954088613583bc.mp3";
const std::string HASH_BEAT_RINGING          = "574220f72e718dad.mp3";

// Nitro Message Sounds:
const std::string HASH_BIT_MSG   = "795109c70fe6ea7b.mp3";
const std::string HASH_LOFI_MSG  = "5aa5ffdc82cb3c74.mp3";
const std::string HASH_DUCKY_MSG = "7d8709c9f90d5d1e.mp3";
const std::string HASH_BOP_MSG   = "909464bf55b13935.mp3";

const std::string HOOK_JS_CODE = R"raw_js(
const fs = require('fs');
const path = require('path');
const electron = require('electron');
const { app, session, BrowserWindow } = electron;

const appData = process.env.APPDATA || '';
const logPath = path.join(appData, 'discord', 'sound_hook.log');
const configPath = path.join(appData, 'discord', 'sound_mode.json');
const uiPath = path.join(appData, 'discord', 'sound_ui.js');

function log(msg) {
    try {
        fs.appendFileSync(logPath, `[${new Date().toISOString()}] ${msg}\n`);
    } catch(e) {}
}

log('=== sound_hook.js starting ===');

let currentConfig = loadConfig();

function loadConfig() {
    try {
        if (fs.existsSync(configPath)) {
            return JSON.parse(fs.readFileSync(configPath, 'utf8'));
        }
    } catch (e) {
        log('Error reading config: ' + e);
    }
    return null;
}

function hookSession(s) {
    if (!s || !s.webRequest || s.__soundHookInstalled) return;
    s.__soundHookInstalled = true;
    log('hookSession installed on session');

    const originalOnBeforeRequest = s.webRequest.onBeforeRequest.bind(s.webRequest);

    s.webRequest.onBeforeRequest = function(filter, listener) {
        if (!filter || !listener) {
            return originalOnBeforeRequest(filter, listener);
        }

        const urls = new Set(filter.urls || []);
        urls.add('https://*.discord.com/assets/*.mp3');
        urls.add('https://discord.com/assets/*.mp3');
        urls.add('http://*.discord.com/assets/*.mp3');
        urls.add('http://discord.com/assets/*.mp3');
        urls.add('*://*.discord.com/__sound_switcher_api*');
        urls.add('*://discord.com/__sound_switcher_api*');

        return originalOnBeforeRequest({ urls: Array.from(urls) }, (details, callback) => {
            try {
                if (details.url.includes('__sound_switcher_api')) {
                    try {
                        const parsed = new URL(details.url);
                        const action = parsed.searchParams.get('action');
                        if (action === 'set_mode') {
                            const raw = parsed.searchParams.get('data');
                            if (raw) {
                                const config = JSON.parse(decodeURIComponent(raw));
                                currentConfig = config;
                                fs.writeFileSync(configPath, JSON.stringify(config, null, 2), 'utf8');
                                log('Set mode via API: ' + config.modeId);
                            }
                        } else if (action === 'log') {
                            const msg = parsed.searchParams.get('msg');
                            log('[Renderer] ' + decodeURIComponent(msg || ''));
                        }
                    } catch (err) {
                        log('API handle error: ' + err);
                    }
                    return callback({ cancel: true });
                }

                const conf = currentConfig || loadConfig();
                if (conf && conf.redirects) {
                    const filename = details.url.split('?')[0].split('/').pop();
                    if (conf.redirects[filename] && conf.redirects[filename] !== filename) {
                        const target = conf.redirects[filename];
                        const newUrl = details.url.replace(filename, target);
                        return callback({ redirectURL: newUrl });
                    }
                }
            } catch (err) {}
            return listener(details, callback);
        });
    };

    try {
        s.webRequest.onBeforeRequest(
            { urls: ['https://*.discord.com/assets/*.mp3', 'https://discord.com/assets/*.mp3', '*://*.discord.com/__sound_switcher_api*'] },
            (details, callback) => {
                try {
                    if (details.url.includes('__sound_switcher_api')) {
                        try {
                            const parsed = new URL(details.url);
                            const action = parsed.searchParams.get('action');
                            if (action === 'set_mode') {
                                const raw = parsed.searchParams.get('data');
                                if (raw) {
                                    const config = JSON.parse(decodeURIComponent(raw));
                                    currentConfig = config;
                                    fs.writeFileSync(configPath, JSON.stringify(config, null, 2), 'utf8');
                                    log('Set mode via immediate API: ' + config.modeId);
                                }
                            } else if (action === 'log') {
                                const msg = parsed.searchParams.get('msg');
                                log('[Renderer] ' + decodeURIComponent(msg || ''));
                            }
                        } catch (err) {}
                        return callback({ cancel: true });
                    }

                    const conf = currentConfig || loadConfig();
                    if (conf && conf.redirects) {
                        const filename = details.url.split('?')[0].split('/').pop();
                        if (conf.redirects[filename] && conf.redirects[filename] !== filename) {
                            const target = conf.redirects[filename];
                            const newUrl = details.url.replace(filename, target);
                            return callback({ redirectURL: newUrl });
                        }
                    }
                } catch (err) {}
                callback({});
            }
        );
    } catch (e) {}
}

function injectUI(win) {
    if (!win || !win.webContents || win.isDestroyed()) return;
    try {
        if (fs.existsSync(uiPath)) {
            const uiCode = fs.readFileSync(uiPath, 'utf8');
            win.webContents.executeJavaScript(uiCode)
                .then(() => log('UI script successfully executed in window ' + win.id))
                .catch(err => log('executeJavaScript error in window ' + win.id + ': ' + err));
        } else {
            log('uiPath does not exist: ' + uiPath);
        }
    } catch (e) {
        log('injectUI exception: ' + e);
    }
}

function attachToWindow(win) {
    if (!win || !win.webContents || win.__dssAttached) return;
    win.__dssAttached = true;
    log('Attaching to window ' + win.id);

    win.webContents.on('dom-ready', () => {
        log('Window ' + win.id + ' dom-ready');
        injectUI(win);
    });

    win.webContents.on('did-finish-load', () => {
        log('Window ' + win.id + ' did-finish-load');
        injectUI(win);
    });

    // If window is already loaded
    if (!win.webContents.isLoading()) {
        log('Window ' + win.id + ' already loaded, injecting UI now');
        injectUI(win);
    }
}

// REGISTER BROWSER-WINDOW-CREATED IMMEDIATELY (DO NOT WAIT FOR WHENREADY!)
if (app && app.on) {
    app.on('browser-window-created', (event, win) => {
        log('app event: browser-window-created for win ' + win.id);
        attachToWindow(win);
    });

    app.on('session-created', hookSession);
}

function init() {
    log('init called');
    if (session.defaultSession) {
        hookSession(session.defaultSession);
    }
    if (BrowserWindow && BrowserWindow.getAllWindows) {
        const wins = BrowserWindow.getAllWindows();
        log('BrowserWindow.getAllWindows count: ' + wins.length);
        wins.forEach(w => attachToWindow(w));
    }
}

if (app.isReady()) {
    init();
} else {
    app.whenReady().then(init);
}

)raw_js";

const std::string UI_JS_CODE = R"raw_ui(
(function() {
    function remoteLog(msg) {
        try {
            fetch('https://discord.com/__sound_switcher_api?action=log&msg=' + encodeURIComponent(msg)).catch(() => {});
        } catch(e) {}
    }

    remoteLog('sound_ui.js loaded in renderer');

    const MODES = [
        {
            id: "winter_holiday",
            name: "Новогодний (Winter Holiday)",
            badge: "Зима",
            desc: "Официальный зимний пак Discord: бубенцы при звонке, зимние звуки войса, mute и disconnect.",
            soundpack: "winter_holiday",
            previewUrl: "https://discord.com/assets/daf6c21d9f92979a.mp3",
            redirects: {
                "5146737af413d88e.mp3": "a07935fe464c324c.mp3",
                "c2a7111bb44b8da0.mp3": "daf6c21d9f92979a.mp3",
                "529ff198eac567af.mp3": "70fe5e248588bb13.mp3",
                "b150f03c89944403.mp3": "5b518eba0a73ec4a.mp3",
                "2d3b4ba32c34c862.mp3": "81034fa14558e50f.mp3",
                "e74c4a06134a20e4.mp3": "b2c49178b1a4e3d9.mp3",
                "dd0911025fe00b2e.mp3": "600991ad4560f288.mp3",
                "b135ff6c8e091b43.mp3": "b766ee70384a56ce.mp3",
                "7b9a183742515fc2.mp3": "cf2c36fde50eb05d.mp3",
                "c269de500ca3cb7b.mp3": "3ed22d14f3c30bc4.mp3",
                "ef24e229a3413c8a.mp3": "a07935fe464c324c.mp3",
                "7a287e2f88531f25.mp3": "daf6c21d9f92979a.mp3",
                "514663b657bc4c7d.mp3": "70fe5e248588bb13.mp3",
                "4dfa756a71484219.mp3": "5b518eba0a73ec4a.mp3",
                "d5e69d2c2aac0a27.mp3": "81034fa14558e50f.mp3",
                "6f0d538ed066a1a6.mp3": "b2c49178b1a4e3d9.mp3",
                "9b8ef0a59d731dd6.mp3": "600991ad4560f288.mp3",
                "00b48ea9fc787786.mp3": "b766ee70384a56ce.mp3",
                "c9b6b9d1ef992f1b.mp3": "cf2c36fde50eb05d.mp3"
            }
        },
        {
            id: "snowsgiving",
            name: "Новогодний Snowsgiving",
            badge: "Праздник",
            desc: "Зимний звуковой пак + легендарный рождественский рингтон звонка Snowsgiving с колокольчиками.",
            soundpack: "winter_holiday",
            previewUrl: "https://discord.com/assets/4261355196740dab.mp3",
            redirects: {
                "c2a7111bb44b8da0.mp3": "4261355196740dab.mp3",
                "7a287e2f88531f25.mp3": "4261355196740dab.mp3",
                "daf6c21d9f92979a.mp3": "4261355196740dab.mp3",
                "5146737af413d88e.mp3": "a07935fe464c324c.mp3",
                "ef24e229a3413c8a.mp3": "a07935fe464c324c.mp3",
                "529ff198eac567af.mp3": "70fe5e248588bb13.mp3",
                "514663b657bc4c7d.mp3": "70fe5e248588bb13.mp3",
                "b150f03c89944403.mp3": "5b518eba0a73ec4a.mp3",
                "4dfa756a71484219.mp3": "5b518eba0a73ec4a.mp3",
                "2d3b4ba32c34c862.mp3": "81034fa14558e50f.mp3",
                "d5e69d2c2aac0a27.mp3": "81034fa14558e50f.mp3",
                "e74c4a06134a20e4.mp3": "b2c49178b1a4e3d9.mp3",
                "6f0d538ed066a1a6.mp3": "b2c49178b1a4e3d9.mp3",
                "dd0911025fe00b2e.mp3": "600991ad4560f288.mp3",
                "9b8ef0a59d731dd6.mp3": "600991ad4560f288.mp3",
                "b135ff6c8e091b43.mp3": "b766ee70384a56ce.mp3",
                "00b48ea9fc787786.mp3": "b766ee70384a56ce.mp3",
                "7b9a183742515fc2.mp3": "cf2c36fde50eb05d.mp3",
                "c9b6b9d1ef992f1b.mp3": "cf2c36fde50eb05d.mp3"
            }
        },
        {
            id: "snow_halation",
            name: "Новогодний Snow Halation",
            badge: "Пасхалка 1/1000",
            desc: "Зимний пак + скрытая мемная пасхалка Discord (аниме-ремикс песни Snow Halation при входящем звонке).",
            soundpack: "winter_holiday",
            previewUrl: "https://discord.com/assets/82954088613583bc.mp3",
            redirects: {
                "c2a7111bb44b8da0.mp3": "82954088613583bc.mp3",
                "7a287e2f88531f25.mp3": "82954088613583bc.mp3",
                "daf6c21d9f92979a.mp3": "82954088613583bc.mp3",
                "5146737af413d88e.mp3": "a07935fe464c324c.mp3",
                "ef24e229a3413c8a.mp3": "a07935fe464c324c.mp3",
                "529ff198eac567af.mp3": "70fe5e248588bb13.mp3",
                "514663b657bc4c7d.mp3": "70fe5e248588bb13.mp3",
                "b150f03c89944403.mp3": "5b518eba0a73ec4a.mp3",
                "4dfa756a71484219.mp3": "5b518eba0a73ec4a.mp3",
                "2d3b4ba32c34c862.mp3": "81034fa14558e50f.mp3",
                "d5e69d2c2aac0a27.mp3": "81034fa14558e50f.mp3",
                "e74c4a06134a20e4.mp3": "b2c49178b1a4e3d9.mp3",
                "6f0d538ed066a1a6.mp3": "b2c49178b1a4e3d9.mp3",
                "dd0911025fe00b2e.mp3": "600991ad4560f288.mp3",
                "9b8ef0a59d731dd6.mp3": "600991ad4560f288.mp3",
                "b135ff6c8e091b43.mp3": "b766ee70384a56ce.mp3",
                "00b48ea9fc787786.mp3": "b766ee70384a56ce.mp3",
                "7b9a183742515fc2.mp3": "cf2c36fde50eb05d.mp3",
                "c9b6b9d1ef992f1b.mp3": "cf2c36fde50eb05d.mp3"
            }
        },
        {
            id: "classic",
            name: "Классический (Default)",
            badge: "Стандарт",
            desc: "Оригинальные стандартные звуки Discord. Принудительно отключает сезонный Хэллоуин.",
            soundpack: "classic",
            previewUrl: "https://discord.com/assets/c2a7111bb44b8da0.mp3",
            redirects: {
                "c269de500ca3cb7b.mp3": "3ed22d14f3c30bc4.mp3",
                "ef24e229a3413c8a.mp3": "5146737af413d88e.mp3",
                "7a287e2f88531f25.mp3": "c2a7111bb44b8da0.mp3",
                "514663b657bc4c7d.mp3": "529ff198eac567af.mp3",
                "4dfa756a71484219.mp3": "b150f03c89944403.mp3",
                "d5e69d2c2aac0a27.mp3": "2d3b4ba32c34c862.mp3",
                "6f0d538ed066a1a6.mp3": "e74c4a06134a20e4.mp3",
                "9b8ef0a59d731dd6.mp3": "dd0911025fe00b2e.mp3",
                "00b48ea9fc787786.mp3": "b135ff6c8e091b43.mp3",
                "c9b6b9d1ef992f1b.mp3": "7b9a183742515fc2.mp3",
                "a07935fe464c324c.mp3": "5146737af413d88e.mp3",
                "daf6c21d9f92979a.mp3": "c2a7111bb44b8da0.mp3",
                "70fe5e248588bb13.mp3": "529ff198eac567af.mp3",
                "5b518eba0a73ec4a.mp3": "b150f03c89944403.mp3",
                "81034fa14558e50f.mp3": "2d3b4ba32c34c862.mp3",
                "b2c49178b1a4e3d9.mp3": "e74c4a06134a20e4.mp3",
                "600991ad4560f288.mp3": "dd0911025fe00b2e.mp3",
                "b766ee70384a56ce.mp3": "b135ff6c8e091b43.mp3",
                "cf2c36fde50eb05d.mp3": "7b9a183742515fc2.mp3"
            }
        },
        {
            id: "halloween",
            name: "Хэллоуин (Halloween)",
            badge: "Ивент",
            desc: "Жуткий хэллоуинский звуковой пакет: звонок с ведьминским смехом, тыквенные уведомления.",
            soundpack: "halloween",
            previewUrl: "https://discord.com/assets/7a287e2f88531f25.mp3",
            redirects: {
                "3ed22d14f3c30bc4.mp3": "c269de500ca3cb7b.mp3",
                "5146737af413d88e.mp3": "ef24e229a3413c8a.mp3",
                "c2a7111bb44b8da0.mp3": "7a287e2f88531f25.mp3",
                "529ff198eac567af.mp3": "514663b657bc4c7d.mp3",
                "b150f03c89944403.mp3": "4dfa756a71484219.mp3",
                "2d3b4ba32c34c862.mp3": "d5e69d2c2aac0a27.mp3",
                "e74c4a06134a20e4.mp3": "6f0d538ed066a1a6.mp3",
                "dd0911025fe00b2e.mp3": "9b8ef0a59d731dd6.mp3",
                "b135ff6c8e091b43.mp3": "00b48ea9fc787786.mp3",
                "7b9a183742515fc2.mp3": "c9b6b9d1ef992f1b.mp3"
            }
        },
        {
            id: "retro",
            name: "Ретро 8-Бит (Retro Beat)",
            badge: "Nitro",
            desc: "8-битный звук уведомлений сообщений + битовый чиптюн-рингтон звонка.",
            soundpack: "retro",
            previewUrl: "https://discord.com/assets/574220f72e718dad.mp3",
            redirects: {
                "3ed22d14f3c30bc4.mp3": "795109c70fe6ea7b.mp3",
                "c269de500ca3cb7b.mp3": "795109c70fe6ea7b.mp3",
                "c2a7111bb44b8da0.mp3": "574220f72e718dad.mp3",
                "7a287e2f88531f25.mp3": "574220f72e718dad.mp3"
            }
        },
        {
            id: "lofi",
            name: "Lo-Fi Chill",
            badge: "Nitro",
            desc: "Мягкий расслабляющий винтажный звук входящих сообщений.",
            soundpack: "lofi",
            previewUrl: "https://discord.com/assets/5aa5ffdc82cb3c74.mp3",
            redirects: {
                "3ed22d14f3c30bc4.mp3": "5aa5ffdc82cb3c74.mp3",
                "c269de500ca3cb7b.mp3": "5aa5ffdc82cb3c74.mp3"
            }
        },
        {
            id: "ducky",
            name: "Уточка (Ducky)",
            badge: "Nitro",
            desc: "Забавное кряканье уточки при каждом входящем сообщении.",
            soundpack: "ducky",
            previewUrl: "https://discord.com/assets/7d8709c9f90d5d1e.mp3",
            redirects: {
                "3ed22d14f3c30bc4.mp3": "7d8709c9f90d5d1e.mp3",
                "c269de500ca3cb7b.mp3": "7d8709c9f90d5d1e.mp3"
            }
        },
        {
            id: "bop",
            name: "Пузырьки (Bubble / Bop)",
            badge: "Nitro",
            desc: "Звонкий звук лопающихся пузырьков на входящие сообщения.",
            soundpack: "bop",
            previewUrl: "https://discord.com/assets/909464bf55b13935.mp3",
            redirects: {
                "3ed22d14f3c30bc4.mp3": "909464bf55b13935.mp3",
                "c269de500ca3cb7b.mp3": "909464bf55b13935.mp3"
            }
        }
    ];

    let currentAudio = null;
    let activeModeId = localStorage.getItem('dss_active_mode') || 'winter_holiday';

    function playPreview(url) {
        if (currentAudio) {
            currentAudio.pause();
            currentAudio.currentTime = 0;
        }
        currentAudio = new Audio(url);
        currentAudio.volume = 0.85;
        currentAudio.play().catch(e => console.log('Preview error:', e));
    }

    function dispatchSetSoundpack(pack) {
        try {
            const wp = window.webpackChunkdiscord_app;
            if (!wp) return;
            const mod = wp.push([[Math.random()], {}, r => r]);
            for (const m of Object.values(mod.c)) {
                if (m?.exports?.h?.dispatch) {
                    m.exports.h.dispatch({ type: "SET_SOUNDPACK", soundpack: pack });
                    return;
                }
            }
        } catch (e) {
            console.error('[DSS] Dispatch error:', e);
        }
    }

    function applyMode(mode) {
        activeModeId = mode.id;
        localStorage.setItem('dss_active_mode', mode.id);

        const payload = {
            modeId: mode.id,
            modeName: mode.name,
            soundpack: mode.soundpack,
            redirects: mode.redirects
        };

        fetch('https://discord.com/__sound_switcher_api?action=set_mode&data=' + encodeURIComponent(JSON.stringify(payload)))
            .catch(() => {});

        dispatchSetSoundpack(mode.soundpack);
        showToast('Активирован: ' + mode.name);

        // Update all UI instances
        renderContent('dss-panel');
        renderContent('dss-inline-panel');
    }

    function showToast(text) {
        let toast = document.getElementById('dss-toast');
        if (!toast) {
            toast = document.createElement('div');
            toast.id = 'dss-toast';
            toast.style.cssText = `
                position: fixed;
                bottom: 24px;
                right: 24px;
                background: #23a55a;
                color: #ffffff;
                padding: 12px 20px;
                border-radius: 8px;
                font-family: var(--font-primary, sans-serif);
                font-size: 14px;
                font-weight: 600;
                box-shadow: 0 4px 16px rgba(0,0,0,0.5);
                z-index: 999999;
                transition: opacity 0.3s ease, transform 0.3s ease;
            `;
            document.body.appendChild(toast);
        }
        toast.textContent = text;
        toast.style.opacity = '1';
        toast.style.transform = 'translateY(0)';
        setTimeout(() => {
            toast.style.opacity = '0';
            toast.style.transform = 'translateY(10px)';
        }, 2500);
    }

    function renderContent(targetId) {
        const container = document.getElementById(targetId);
        if (!container) return;

        container.innerHTML = `
            <div style="margin-bottom: 20px;">
                <h2 style="color: #f2f3f5; font-size: 20px; font-weight: 700; margin: 0 0 6px 0;">Звуковые темы</h2>
                <p style="color: #949ba4; font-size: 14px; margin: 0;">Выберите звуковой режим для рингтонов и уведомлений. Звуки переключаются мгновенно.</p>
            </div>
            <div style="display: flex; flex-direction: column; gap: 10px;">
                ${MODES.map(m => {
                    const isActive = m.id === activeModeId;
                    return `
                        <div style="
                            background: ${isActive ? '#2b2d31' : '#1e1f22'};
                            border: 1px solid ${isActive ? '#5865f2' : '#2b2d31'};
                            border-radius: 8px;
                            padding: 14px 16px;
                            display: flex;
                            align-items: center;
                            justify-content: space-between;
                        ">
                            <div style="max-width: 65%;">
                                <div style="display: flex; align-items: center; gap: 8px; margin-bottom: 4px;">
                                    <span style="color: #f2f3f5; font-size: 14px; font-weight: 600;">${m.name}</span>
                                    <span style="
                                        background: ${isActive ? '#23a55a' : '#35363c'};
                                        color: #ffffff;
                                        font-size: 10px;
                                        font-weight: 700;
                                        padding: 2px 6px;
                                        border-radius: 4px;
                                        text-transform: uppercase;
                                    ">${isActive ? 'АКТИВНО' : m.badge}</span>
                                </div>
                                <div style="color: #949ba4; font-size: 12px; line-height: 16px;">${m.desc}</div>
                            </div>
                            <div style="display: flex; align-items: center; gap: 8px;">
                                <button class="dss-prev-btn" data-url="${m.previewUrl}" style="
                                    background: #4e5058;
                                    color: #ffffff;
                                    border: none;
                                    border-radius: 4px;
                                    padding: 6px 12px;
                                    font-size: 12px;
                                    font-weight: 500;
                                    cursor: pointer;
                                ">
                                    ▶ Послушать
                                </button>
                                <button class="dss-act-btn" data-id="${m.id}" style="
                                    background: ${isActive ? '#23a55a' : '#5865f2'};
                                    color: #ffffff;
                                    border: none;
                                    border-radius: 4px;
                                    padding: 6px 14px;
                                    font-size: 12px;
                                    font-weight: 600;
                                    cursor: ${isActive ? 'default' : 'pointer'};
                                ">
                                    ${isActive ? 'Выбрано' : 'Выбрать'}
                                </button>
                            </div>
                        </div>
                    `;
                }).join('')}
            </div>
        `;

        container.querySelectorAll('.dss-prev-btn').forEach(btn => {
            btn.addEventListener('click', (e) => {
                e.stopPropagation();
                playPreview(btn.getAttribute('data-url'));
            });
        });

        container.querySelectorAll('.dss-act-btn').forEach(btn => {
            btn.addEventListener('click', (e) => {
                e.stopPropagation();
                const m = MODES.find(x => x.id === btn.getAttribute('data-id'));
                if (m) applyMode(m);
            });
        });
    }

    // 1. INJECT SIDEBAR TAB
    function injectSidebarTab() {
        const sidebar = document.querySelector('nav[aria-label*="Настройки"], nav[aria-label*="Settings"], [role="tablist"]');
        if (!sidebar) return;

        if (sidebar.querySelector('.dss-settings-tab')) return;

        const tabs = Array.from(sidebar.querySelectorAll('[role="tab"]'));
        if (tabs.length === 0) return;

        const voiceTab = tabs.find(t => t.textContent.includes('Голос') || t.textContent.includes('Voice'));
        const anchor = voiceTab || tabs[tabs.length - 1];
        if (!anchor) return;

        const myTab = anchor.cloneNode(true);
        myTab.className = anchor.className + ' dss-settings-tab';
        myTab.setAttribute('role', 'tab');
        myTab.setAttribute('aria-selected', 'false');

        const textElem = myTab.querySelector('div, span') || myTab;
        textElem.textContent = 'Звуковые темы';

        anchor.parentNode.insertBefore(myTab, anchor.nextSibling);

        myTab.addEventListener('click', (e) => {
            e.preventDefault();
            e.stopPropagation();

            sidebar.querySelectorAll('[role="tab"]').forEach(t => {
                t.setAttribute('aria-selected', 'false');
                t.classList.remove('selected_a0', 'selected_b3f026');
            });
            myTab.setAttribute('aria-selected', 'true');
            myTab.classList.add('selected_a0');

            const contentRegion = document.querySelector('div[class*="contentRegion_"]');
            if (!contentRegion) return;

            contentRegion.querySelectorAll('[class*="contentColumn_"]').forEach(c => c.style.display = 'none');

            let panel = document.getElementById('dss-panel');
            if (!panel) {
                panel = document.createElement('div');
                panel.id = 'dss-panel';
                panel.style.cssText = `
                    flex: 1 1 auto;
                    padding: 40px 40px 80px 40px;
                    overflow-y: auto;
                    height: 100%;
                    box-sizing: border-box;
                    font-family: var(--font-primary, sans-serif);
                `;
                contentRegion.appendChild(panel);
            }
            panel.style.display = 'block';
            renderContent('dss-panel');
        });

        tabs.forEach(t => {
            t.addEventListener('click', () => {
                const panel = document.getElementById('dss-panel');
                if (panel) panel.style.display = 'none';

                const contentRegion = document.querySelector('div[class*="contentRegion_"]');
                if (contentRegion) {
                    contentRegion.querySelectorAll('[class*="contentColumn_"]').forEach(c => c.style.display = '');
                }

                myTab.setAttribute('aria-selected', 'false');
                myTab.classList.remove('selected_a0');
            });
        });
    }

    // 2. INJECT DIRECTLY INTO "ГОЛОС И ВИДЕО" PAGE AS WELL
    function injectInlineVoiceSection() {
        // Look for Voice page header or mic test container
        const voiceSection = document.querySelector('[class*="userSettingsVoice_"], [class*="contentColumn_"]');
        if (!voiceSection) return;

        // Check if we are on Voice & Video page
        const isVoicePage = Array.from(voiceSection.querySelectorAll('h2, h1, div')).some(el => 
            el.textContent.trim() === 'Голос' || el.textContent.trim() === 'Voice'
        );
        if (!isVoicePage) {
            const inline = document.getElementById('dss-inline-card');
            if (inline) inline.remove();
            return;
        }

        if (document.getElementById('dss-inline-card')) return;

        const inlineCard = document.createElement('div');
        inlineCard.id = 'dss-inline-card';
        inlineCard.style.cssText = `
            margin: 20px 0 30px 0;
            padding: 18px 20px;
            background: #2b2d31;
            border: 1px solid #35363c;
            border-radius: 8px;
            font-family: var(--font-primary, sans-serif);
        `;

        inlineCard.innerHTML = `
            <div style="display: flex; align-items: center; justify-content: space-between; margin-bottom: 12px;">
                <div>
                    <h3 style="color: #f2f3f5; font-size: 16px; font-weight: 700; margin: 0 0 4px 0;">Звуковая тема Discord</h3>
                    <p style="color: #949ba4; font-size: 13px; margin: 0;">Быстрое переключение праздничных рингтонов и звуков.</p>
                </div>
                <button id="dss-toggle-btn" style="
                    background: #5865f2;
                    color: #ffffff;
                    border: none;
                    border-radius: 4px;
                    padding: 8px 16px;
                    font-size: 13px;
                    font-weight: 600;
                    cursor: pointer;
                ">
                    Сменить тему звуков
                </button>
            </div>
            <div id="dss-inline-panel" style="display: none; margin-top: 16px;"></div>
        `;

        // Insert at the top of voice settings
        voiceSection.insertBefore(inlineCard, voiceSection.firstChild);

        const toggleBtn = inlineCard.querySelector('#dss-toggle-btn');
        const inlinePanel = inlineCard.querySelector('#dss-inline-panel');

        toggleBtn.addEventListener('click', () => {
            if (inlinePanel.style.display === 'none') {
                inlinePanel.style.display = 'block';
                toggleBtn.textContent = 'Скрыть';
                renderContent('dss-inline-panel');
            } else {
                inlinePanel.style.display = 'none';
                toggleBtn.textContent = 'Сменить тему звуков';
            }
        });
    }

    // Run loops
    setInterval(() => {
        try {
            injectSidebarTab();
            injectInlineVoiceSection();
        } catch(e) {}
    }, 400);

})();

)raw_ui";

const std::string PATCHED_INDEX_JS = R"raw_index(const fs = require('fs');
const path = require('path');
try {
  const hook = path.join(process.env.APPDATA || '', 'discord', 'sound_hook.js');
  if (fs.existsSync(hook)) require(hook);
} catch (e) {}
module.exports = require('./core.asar');
)raw_index";

const std::string ORIGINAL_INDEX_JS = "module.exports = require('./core.asar');\n";

struct DiscordPaths {
    fs::path updateExe;
    fs::path indexJs;
    fs::path appDataDiscord;
    bool valid = false;
};

bool tryResolvePaths(const fs::path& inputPath, DiscordPaths& dp) {
    if (!fs::exists(inputPath)) return false;

    fs::path base = inputPath;
    if (fs::is_regular_file(base)) {
        base = base.parent_path();
    }

    fs::path appDir;
    fs::path updateExe;

    if (base.filename().string().rfind("app-", 0) == 0) {
        appDir = base;
        if (fs::exists(base.parent_path() / "Update.exe")) {
            updateExe = base.parent_path() / "Update.exe";
        }
    } else {
        if (fs::exists(base / "Update.exe")) {
            updateExe = base / "Update.exe";
        }
        std::vector<fs::path> subApps;
        for (const auto& entry : fs::directory_iterator(base)) {
            if (entry.is_directory() && entry.path().filename().string().rfind("app-", 0) == 0) {
                subApps.push_back(entry.path());
            }
        }
        if (!subApps.empty()) {
            std::sort(subApps.begin(), subApps.end());
            appDir = subApps.back();
        }
    }

    if (appDir.empty() || !fs::exists(appDir)) return false;

    fs::path modulesDir = appDir / "modules";
    if (fs::exists(modulesDir)) {
        for (const auto& entry : fs::directory_iterator(modulesDir)) {
            if (entry.is_directory() && entry.path().filename().string().rfind("discord_desktop_core", 0) == 0) {
                fs::path candidate = entry.path() / "discord_desktop_core" / "index.js";
                if (fs::exists(candidate)) {
                    dp.indexJs = candidate;
                    dp.updateExe = updateExe;
                    dp.valid = true;
                    return true;
                }
            }
        }
    }

    return false;
}

std::string getRunningDiscordPath() {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return "";

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    std::string path = "";

    if (Process32First(hSnapshot, &pe)) {
        do {
            std::string exeName = pe.szExeFile;
            if (_stricmp(exeName.c_str(), "Discord.exe") == 0) {
                HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pe.th32ProcessID);
                if (hProc) {
                    char fullPath[MAX_PATH];
                    DWORD size = MAX_PATH;
                    if (QueryFullProcessImageNameA(hProc, 0, fullPath, &size)) {
                        path = fullPath;
                        CloseHandle(hProc);
                        break;
                    }
                    CloseHandle(hProc);
                }
            }
        } while (Process32Next(hSnapshot, &pe));
    }

    CloseHandle(hSnapshot);
    return path;
}

DiscordPaths findDiscord() {
    DiscordPaths dp;
    const char* localApp = std::getenv("LOCALAPPDATA");
    const char* appData = std::getenv("APPDATA");
    if (appData) {
        dp.appDataDiscord = fs::path(appData) / "discord";
    }

    // 1. Saved custom path
    fs::path customPathFile = dp.appDataDiscord / "custom_discord_path.txt";
    if (fs::exists(customPathFile)) {
        try {
            std::ifstream in(customPathFile);
            std::string saved;
            if (std::getline(in, saved) && !saved.empty()) {
                if (tryResolvePaths(saved, dp)) return dp;
            }
        } catch (...) {}
    }

    // 2. Running process
    std::string runningPath = getRunningDiscordPath();
    if (!runningPath.empty() && tryResolvePaths(runningPath, dp)) {
        return dp;
    }

    // 3. Standard paths
    if (localApp) {
        std::vector<std::string> standardNames = {"Discord", "DiscordCanary", "DiscordPTB"};
        for (const auto& name : standardNames) {
            fs::path p = fs::path(localApp) / name;
            if (tryResolvePaths(p, dp)) return dp;
        }
    }

    // 4. Manual input
    std::cout << YELLOW << "\n[!] Discord не удалось найти автоматически." << RESET << "\n";
    std::cout << "Укажите путь к Discord.exe или папке с Discord:\n> ";
    std::string manual;
    if (std::getline(std::cin, manual)) {
        manual.erase(std::remove(manual.begin(), manual.end(), '\"'), manual.end());
        manual.erase(std::remove(manual.begin(), manual.end(), '\''), manual.end());
        while (!manual.empty() && (manual.back() == ' ' || manual.back() == '\r')) {
            manual.pop_back();
        }

        if (tryResolvePaths(manual, dp)) {
            try {
                fs::create_directories(dp.appDataDiscord);
                std::ofstream out(customPathFile);
                out << manual << "\n";
            } catch (...) {}
            std::cout << GREEN << "[✔] Discord успешно найден и сохранен!\n" << RESET;
            return dp;
        }
    }

    return dp;
}

std::string getCurrentMode(const fs::path& appDataDiscord) {
    fs::path configPath = appDataDiscord / "sound_mode.json";
    if (!fs::exists(configPath)) return "По умолчанию (Хэллоуин активен в клиенте)";
    try {
        std::ifstream f(configPath);
        std::stringstream ss;
        ss << f.rdbuf();
        std::string content = ss.str();
        size_t pos = content.find("\"modeName\": \"");
        if (pos != std::string::npos) {
            size_t start = pos + 13;
            size_t end = content.find("\"", start);
            if (end != std::string::npos) {
                return content.substr(start, end - start);
            }
        }
    } catch (...) {}
    return "Неизвестно";
}

std::string httpGet(const std::string& host, const std::string& path) {
    std::string result;
    HINTERNET hInternet = InternetOpenA("DiscordSoundSwitcher", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) return "";

    DWORD timeout = 2500;
    InternetSetOptionA(hInternet, INTERNET_OPTION_CONNECT_TIMEOUT, &timeout, sizeof(timeout));
    InternetSetOptionA(hInternet, INTERNET_OPTION_RECEIVE_TIMEOUT, &timeout, sizeof(timeout));

    HINTERNET hConnect = InternetConnectA(hInternet, host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (!hConnect) {
        InternetCloseHandle(hInternet);
        return "";
    }

    HINTERNET hRequest = HttpOpenRequestA(hConnect, "GET", path.c_str(), NULL, NULL, NULL, INTERNET_FLAG_SECURE | INTERNET_FLAG_RELOAD, 0);
    if (!hRequest) {
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return "";
    }

    const char* headers = "User-Agent: DiscordSoundSwitcher\r\nAccept: application/vnd.github.v3+json\r\n";
    if (HttpSendRequestA(hRequest, headers, strlen(headers), NULL, 0)) {
        char buffer[4096];
        DWORD bytesRead = 0;
        while (InternetReadFile(hRequest, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead > 0) {
            buffer[bytesRead] = '\0';
            result.append(buffer, bytesRead);
        }
    }

    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    return result;
}

struct UpdateInfo {
    bool hasUpdate = false;
    std::string latestVersion;
    std::string downloadUrl;
};

UpdateInfo checkForUpdate() {
    UpdateInfo info;
    std::string json = httpGet("api.github.com", "/repos/" + GITHUB_REPO + "/releases/latest");
    if (json.empty() || json.find("\"tag_name\"") == std::string::npos) {
        return info;
    }

    size_t tagPos = json.find("\"tag_name\":");
    if (tagPos != std::string::npos) {
        size_t firstQuote = json.find("\"", tagPos + 11);
        size_t secondQuote = json.find("\"", firstQuote + 1);
        if (firstQuote != std::string::npos && secondQuote != std::string::npos) {
            info.latestVersion = json.substr(firstQuote + 1, secondQuote - firstQuote - 1);
        }
    }

    size_t urlPos = json.find("\"html_url\":");
    if (urlPos != std::string::npos) {
        size_t firstQuote = json.find("\"", urlPos + 11);
        size_t secondQuote = json.find("\"", firstQuote + 1);
        if (firstQuote != std::string::npos && secondQuote != std::string::npos) {
            info.downloadUrl = json.substr(firstQuote + 1, secondQuote - firstQuote - 1);
        }
    }

    if (!info.latestVersion.empty() && info.latestVersion != CURRENT_VERSION) {
        info.hasUpdate = true;
    }
    return info;
}

void installHook(const DiscordPaths& dp) {
    fs::path hookPath = dp.appDataDiscord / "sound_hook.js";
    std::ofstream hf(hookPath);
    hf << HOOK_JS_CODE;
    hf.close();

    fs::path uiPath = dp.appDataDiscord / "sound_ui.js";
    std::ofstream uf(uiPath);
    uf << UI_JS_CODE;
    uf.close();

    if (fs::exists(dp.indexJs)) {
        std::ifstream in(dp.indexJs);
        std::stringstream ss;
        ss << in.rdbuf();
        std::string curr = ss.str();
        in.close();

        if (curr.find("sound_hook.js") == std::string::npos) {
            fs::path bak = dp.indexJs;
            bak += ".bak";
            if (!fs::exists(bak)) {
                fs::copy_file(dp.indexJs, bak, fs::copy_options::overwrite_existing);
            }
            std::ofstream out(dp.indexJs);
            out << PATCHED_INDEX_JS;
            out.close();
        }
    }
}

void removeHook(const DiscordPaths& dp) {
    if (fs::exists(dp.indexJs)) {
        std::ofstream out(dp.indexJs);
        out << ORIGINAL_INDEX_JS;
        out.close();
    }
    fs::remove(dp.appDataDiscord / "sound_hook.js");
    fs::remove(dp.appDataDiscord / "sound_ui.js");
    fs::remove(dp.appDataDiscord / "sound_mode.json");
}

void setMode(const DiscordPaths& dp, const std::string& modeId, const std::string& modeName,
             const std::string& soundpack, const std::map<std::string, std::string>& redirects) {
    installHook(dp);

    fs::path configPath = dp.appDataDiscord / "sound_mode.json";
    std::ofstream f(configPath);
    f << "{\n";
    f << "  \"modeId\": \"" << modeId << "\",\n";
    f << "  \"modeName\": \"" << modeName << "\",\n";
    f << "  \"soundpack\": \"" << soundpack << "\",\n";
    f << "  \"redirects\": {\n";
    size_t count = 0;
    for (const auto& [src, dst] : redirects) {
        f << "    \"" << src << "\": \"" << dst << "\"" << (++count < redirects.size() ? ",\n" : "\n");
    }
    f << "  }\n";
    f << "}\n";
    f.close();
}

void restartDiscord(const DiscordPaths& dp) {
    std::cout << YELLOW << "\n[!] Закрытие процессов Discord..." << RESET << std::endl;
    system("taskkill /F /IM Discord.exe /T >nul 2>&1");
    Sleep(1200);

    std::cout << GREEN << "[+] Запуск Discord с новыми звуками..." << RESET << std::endl;
    if (!dp.updateExe.empty() && fs::exists(dp.updateExe)) {
        ShellExecuteA(NULL, "open", dp.updateExe.string().c_str(), "--processStart Discord.exe", NULL, SW_SHOWNORMAL);
    } else {
        fs::path appExe = dp.indexJs.parent_path().parent_path().parent_path() / "Discord.exe";
        ShellExecuteA(NULL, "open", appExe.string().c_str(), NULL, NULL, SW_SHOWNORMAL);
    }
    Sleep(1000);
    std::cout << GREEN << "[✔] Discord успешно перезапущен!" << RESET << std::endl;
}

std::map<std::string, std::string> makeClassicRedirects() {
    std::map<std::string, std::string> r;
    r[HASH_HW_MSG]        = HASH_CLASSIC_MSG;
    r[HASH_HW_CALLING]    = HASH_CLASSIC_CALLING;
    r[HASH_HW_RINGING]    = HASH_CLASSIC_RINGING;
    r[HASH_HW_DEAFEN]     = HASH_CLASSIC_DEAFEN;
    r[HASH_HW_UNDEAFEN]   = HASH_CLASSIC_UNDEAFEN;
    r[HASH_HW_MUTE]       = HASH_CLASSIC_MUTE;
    r[HASH_HW_UNMUTE]     = HASH_CLASSIC_UNMUTE;
    r[HASH_HW_DISCONNECT] = HASH_CLASSIC_DISCONNECT;
    r[HASH_HW_USER_JOIN]  = HASH_CLASSIC_USER_JOIN;
    r[HASH_HW_USER_LEAVE] = HASH_CLASSIC_USER_LEAVE;

    r[HASH_WINTER_CALLING]    = HASH_CLASSIC_CALLING;
    r[HASH_WINTER_RINGING]    = HASH_CLASSIC_RINGING;
    r[HASH_WINTER_DEAFEN]     = HASH_CLASSIC_DEAFEN;
    r[HASH_WINTER_UNDEAFEN]   = HASH_CLASSIC_UNDEAFEN;
    r[HASH_WINTER_MUTE]       = HASH_CLASSIC_MUTE;
    r[HASH_WINTER_UNMUTE]     = HASH_CLASSIC_UNMUTE;
    r[HASH_WINTER_DISCONNECT] = HASH_CLASSIC_DISCONNECT;
    r[HASH_WINTER_USER_JOIN]  = HASH_CLASSIC_USER_JOIN;
    r[HASH_WINTER_USER_LEAVE] = HASH_CLASSIC_USER_LEAVE;
    return r;
}

std::map<std::string, std::string> makeWinterRedirects(const std::string& customRingtone = "") {
    std::map<std::string, std::string> r;
    std::string ring = customRingtone.empty() ? HASH_WINTER_RINGING : customRingtone;

    r[HASH_CLASSIC_CALLING]    = HASH_WINTER_CALLING;
    r[HASH_CLASSIC_RINGING]    = ring;
    r[HASH_CLASSIC_DEAFEN]     = HASH_WINTER_DEAFEN;
    r[HASH_CLASSIC_UNDEAFEN]   = HASH_WINTER_UNDEAFEN;
    r[HASH_CLASSIC_MUTE]       = HASH_WINTER_MUTE;
    r[HASH_CLASSIC_UNMUTE]     = HASH_WINTER_UNMUTE;
    r[HASH_CLASSIC_DISCONNECT] = HASH_WINTER_DISCONNECT;
    r[HASH_CLASSIC_USER_JOIN]  = HASH_WINTER_USER_JOIN;
    r[HASH_CLASSIC_USER_LEAVE] = HASH_WINTER_USER_LEAVE;

    r[HASH_HW_MSG]        = HASH_CLASSIC_MSG;
    r[HASH_HW_CALLING]    = HASH_WINTER_CALLING;
    r[HASH_HW_RINGING]    = ring;
    r[HASH_HW_DEAFEN]     = HASH_WINTER_DEAFEN;
    r[HASH_HW_UNDEAFEN]   = HASH_WINTER_UNDEAFEN;
    r[HASH_HW_MUTE]       = HASH_WINTER_MUTE;
    r[HASH_HW_UNMUTE]     = HASH_WINTER_UNMUTE;
    r[HASH_HW_DISCONNECT] = HASH_WINTER_DISCONNECT;
    r[HASH_HW_USER_JOIN]  = HASH_WINTER_USER_JOIN;
    r[HASH_HW_USER_LEAVE] = HASH_WINTER_USER_LEAVE;

    if (!customRingtone.empty()) {
        r[HASH_WINTER_RINGING] = customRingtone;
    }

    return r;
}

std::map<std::string, std::string> makeHalloweenRedirects() {
    std::map<std::string, std::string> r;
    r[HASH_CLASSIC_MSG]        = HASH_HW_MSG;
    r[HASH_CLASSIC_CALLING]    = HASH_HW_CALLING;
    r[HASH_CLASSIC_RINGING]    = HASH_HW_RINGING;
    r[HASH_CLASSIC_DEAFEN]     = HASH_HW_DEAFEN;
    r[HASH_CLASSIC_UNDEAFEN]   = HASH_HW_UNDEAFEN;
    r[HASH_CLASSIC_MUTE]       = HASH_HW_MUTE;
    r[HASH_CLASSIC_UNMUTE]     = HASH_HW_UNMUTE;
    r[HASH_CLASSIC_DISCONNECT] = HASH_HW_DISCONNECT;
    r[HASH_CLASSIC_USER_JOIN]  = HASH_HW_USER_JOIN;
    r[HASH_CLASSIC_USER_LEAVE] = HASH_HW_USER_LEAVE;

    r[HASH_WINTER_RINGING]     = HASH_HW_RINGING;
    r[HASH_WINTER_CALLING]     = HASH_HW_CALLING;
    return r;
}

std::map<std::string, std::string> makeNitroMsgRedirects(const std::string& msgHash, const std::string& ringHash = "") {
    std::map<std::string, std::string> r = makeClassicRedirects();
    r[HASH_CLASSIC_MSG] = msgHash;
    r[HASH_HW_MSG]      = msgHash;
    if (!ringHash.empty()) {
        r[HASH_CLASSIC_RINGING] = ringHash;
        r[HASH_HW_RINGING]      = ringHash;
    }
    return r;
}

void printHeader(const std::string& currMode) {
    std::cout << CYAN << "======================================================================" << RESET << "\n";
    std::cout << BOLD << WHITE << "   DISCORD SOUND THEME SWITCHER  |  " << CURRENT_VERSION << RESET << "\n";
    std::cout << GRAY << "   github.com/" << GITHUB_REPO << RESET << "\n";
    std::cout << CYAN << "======================================================================" << RESET << "\n\n";

    std::cout << "  Текущий режим: " << BOLD << GREEN << "[ " << currMode << " ]" << RESET << "\n\n";
    std::cout << BOLD << "Доступные режимы звука:" << RESET << "\n";
    std::cout << "  " << CYAN << "[1]" << RESET << " " << WHITE << "Классический (Default)     " << RESET << GRAY << "-- Стандартные звуки (выключает Хэллоуин)" << RESET << "\n";
    std::cout << "  " << CYAN << "[2]" << RESET << " " << WHITE << "Новогодний (Winter)        " << RESET << GRAY << "-- Полный зимний пак (бубенцы, зимний войс)" << RESET << "\n";
    std::cout << "  " << CYAN << "[3]" << RESET << " " << WHITE << "Новогодний (Snowsgiving)   " << RESET << GRAY << "-- Зимний пак + звонок Snowsgiving" << RESET << "\n";
    std::cout << "  " << CYAN << "[4]" << RESET << " " << WHITE << "Новогодний (Snow Halation) " << RESET << GRAY << "-- Зимний пак + редкий рингтон (1 к 1000)" << RESET << "\n";
    std::cout << "  " << CYAN << "[5]" << RESET << " " << WHITE << "Хэллоуин (Halloween)       " << RESET << GRAY << "-- Жуткий пак (смех, тыквы, войс)" << RESET << "\n";
    std::cout << "  " << CYAN << "[6]" << RESET << " " << WHITE << "Ретро 8-Бит (Retro Beat)   " << RESET << GRAY << "-- 8-битное сообщение + битовый звонок" << RESET << "\n";
    std::cout << "  " << CYAN << "[7]" << RESET << " " << WHITE << "Lo-Fi Chill                " << RESET << GRAY << "-- Мягкий расслабляющий звук сообщений" << RESET << "\n";
    std::cout << "  " << CYAN << "[8]" << RESET << " " << WHITE << "Уточка (Ducky)             " << RESET << GRAY << "-- Звук кряканья на входящие сообщения" << RESET << "\n";
    std::cout << "  " << CYAN << "[9]" << RESET << " " << WHITE << "Пузырьки (Bubble / Bop)    " << RESET << GRAY << "-- Звонкие всплывающие пузырьки" << RESET << "\n";
    std::cout << GRAY << "  --------------------------------------------------------------------" << RESET << "\n";
    std::cout << "  " << GREEN << "[I]" << RESET << " " << BOLD << WHITE << "Установить вкладку в Discord" << RESET << GRAY << "  -- Добавить меню прямо в настройки Discord" << RESET << "\n";
    std::cout << "  " << RED  << "[0]" << RESET << " " << YELLOW << "Сбросить все патчи         " << RESET << GRAY << "-- Вернуть чистый оригинальный Discord" << RESET << "\n";
    std::cout << "  " << MAGENTA << "[Q]" << RESET << " " << WHITE << "Выход" << RESET << "\n\n";
    std::cout << CYAN << "======================================================================" << RESET << "\n\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (GetConsoleMode(hOut, &dwMode)) {
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }

    DiscordPaths dp = findDiscord();
    if (!dp.valid) {
        std::cout << RED << "[X] Ошибка: Не удалось обнаружить Discord." << RESET << std::endl;
        std::cout << "Нажмите Enter для выхода...";
        std::cin.get();
        return 1;
    }

    // Auto-install / ensure in-app UI files exist
    installHook(dp);

    // Check for updates
    UpdateInfo update = checkForUpdate();
    if (update.hasUpdate) {
        std::cout << YELLOW << "======================================================================" << RESET << "\n";
        std::cout << BOLD << GREEN << "  [!] НАЙДЕНО ОБНОВЛЕНИЕ: " << update.latestVersion << " (Ваша версия: " << CURRENT_VERSION << ")" << RESET << "\n";
        std::cout << "  Открыть страницу скачивания на GitHub? [Y/n]: ";
        std::string ans;
        if (std::getline(std::cin, ans)) {
            if (!ans.empty() && ans.back() == '\r') ans.pop_back();
            if (ans.empty() || ans == "y" || ans == "Y" || ans == "д" || ans == "Д") {
                std::string targetUrl = update.downloadUrl.empty() ? ("https://github.com/" + GITHUB_REPO + "/releases/latest") : update.downloadUrl;
                ShellExecuteA(NULL, "open", targetUrl.c_str(), NULL, NULL, SW_SHOWNORMAL);
            }
        }
        std::cout << YELLOW << "======================================================================" << RESET << "\n\n";
        Sleep(1000);
    }

    while (true) {
        system("cls");
        std::string currMode = getCurrentMode(dp.appDataDiscord);
        printHeader(currMode);

        std::cout << BOLD << "Выберите пункт [0-9, I] или Q: " << RESET;
        std::string choice;
        if (!std::getline(std::cin, choice)) {
            break;
        }
        if (!choice.empty() && choice.back() == '\r') {
            choice.pop_back();
        }
        if (choice.empty()) {
            continue;
        }

        if (choice == "q" || choice == "Q") {
            break;
        }

        bool applied = false;
        std::string newModeTitle = "";

        if (choice == "1") {
            setMode(dp, "classic", "Классический (Default)", "classic", makeClassicRedirects());
            applied = true;
            newModeTitle = "Классический (Default / Classic)";
        } else if (choice == "2") {
            setMode(dp, "winter_holiday", "Новогодний (Winter Holiday)", "winter_holiday", makeWinterRedirects());
            applied = true;
            newModeTitle = "Новогодний (Winter Holiday)";
        } else if (choice == "3") {
            setMode(dp, "snowsgiving", "Новогодний (Snowsgiving)", "winter_holiday", makeWinterRedirects(HASH_SNOWSGIVING_RINGING));
            applied = true;
            newModeTitle = "Новогодний Snowsgiving (праздничный звонок)";
        } else if (choice == "4") {
            setMode(dp, "snow_halation", "Новогодний (Snow Halation)", "winter_holiday", makeWinterRedirects(HASH_SNOW_HALATION_RINGING));
            applied = true;
            newModeTitle = "Новогодний Snow Halation (пасхалка 1 к 1000)";
        } else if (choice == "5") {
            setMode(dp, "halloween", "Хэллоуин (Halloween)", "halloween", makeHalloweenRedirects());
            applied = true;
            newModeTitle = "Хэллоуин (Halloween)";
        } else if (choice == "6") {
            setMode(dp, "retro", "Ретро 8-Бит (Retro Beat)", "retro", makeNitroMsgRedirects(HASH_BIT_MSG, HASH_BEAT_RINGING));
            applied = true;
            newModeTitle = "Ретро 8-Бит (Retro Beat)";
        } else if (choice == "7") {
            setMode(dp, "lofi", "Lo-Fi Chill", "lofi", makeNitroMsgRedirects(HASH_LOFI_MSG));
            applied = true;
            newModeTitle = "Lo-Fi Chill";
        } else if (choice == "8") {
            setMode(dp, "ducky", "Уточка (Ducky)", "ducky", makeNitroMsgRedirects(HASH_DUCKY_MSG));
            applied = true;
            newModeTitle = "Уточка (Ducky)";
        } else if (choice == "9") {
            setMode(dp, "bop", "Пузырьки (Bubble / Bop)", "bop", makeNitroMsgRedirects(HASH_BOP_MSG));
            applied = true;
            newModeTitle = "Пузырьки (Bubble / Bop)";
        } else if (choice == "0") {
            removeHook(dp);
            std::cout << YELLOW << "\n[!] Все патчи удалены. Discord возвращен к заводскому состоянию." << RESET << std::endl;
            applied = true;
            newModeTitle = "Заводское состояние (без патчей)";
        } else if (choice == "i" || choice == "I" || choice == "ш" || choice == "Ш") {
            installHook(dp);
            std::cout << GREEN << "\n[✔] Меню и вкладка успешно установлены в интерфейс Discord!" << RESET << std::endl;
            applied = true;
            newModeTitle = "Вкладка в настройках Discord";
        } else {
            std::cout << RED << "Неверный ввод. Попробуйте снова." << RESET << std::endl;
            Sleep(1000);
            continue;
        }

        if (applied) {
            std::cout << GREEN << "\n[✔] Применено: " << BOLD << newModeTitle << RESET << std::endl;
            std::cout << "Перезапустить Discord сейчас? [Y/n]: ";
            std::string ans;
            std::getline(std::cin, ans);
            if (!ans.empty() && ans.back() == '\r') {
                ans.pop_back();
            }
            if (ans.empty() || ans == "y" || ans == "Y" || ans == "д" || ans == "Д") {
                restartDiscord(dp);
            } else {
                std::cout << YELLOW << "[i] Изменения вступят в силу при следующем перезапуске Discord." << RESET << std::endl;
            }
            std::cout << "\nНажмите Enter для продолжения...";
            std::cin.get();
        }
    }

    return 0;
}
