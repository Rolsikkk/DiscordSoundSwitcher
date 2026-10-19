(function() {
    if (window.__dssInterval) {
        clearInterval(window.__dssInterval);
    }
    window.__dssInjected = true;

    function remoteLog(msg) {
        try {
            fetch('https://discord.com/__sound_switcher_api?action=log&msg=' + encodeURIComponent(msg)).catch(() => {});
        } catch(e) {}
    }

    try {
        remoteLog('sound_ui: init on ' + window.location.href);

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
        let activeModeId = 'winter_holiday';
        try {
            if (typeof window !== 'undefined' && window.localStorage) {
                activeModeId = window.localStorage.getItem('dss_active_mode') || 'winter_holiday';
            }
        } catch(e) {}

        function playPreview(url) {
            try {
                if (currentAudio) {
                    currentAudio.pause();
                    currentAudio.currentTime = 0;
                }
                currentAudio = new Audio(url);
                currentAudio.volume = 0.85;
                currentAudio.play().catch(e => console.log('Audio preview:', e));
            } catch(e) {}
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
            } catch (e) {}
        }

        function applyMode(mode) {
            activeModeId = mode.id;
            try {
                if (window.localStorage) window.localStorage.setItem('dss_active_mode', mode.id);
            } catch(e) {}

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

            renderThemesList('dss-panel');
            renderThemesList('dss-inline-panel');
            renderThemesList('dss-modal-content');
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
                    z-index: 9999999;
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

        function renderThemesList(targetId) {
            const container = document.getElementById(targetId);
            if (!container) return;

            container.innerHTML = `
                <div style="margin-bottom: 20px;">
                    <div style="display: flex; align-items: center; justify-content: space-between;">
                        <h2 style="color: #f2f3f5; font-size: 20px; font-weight: 700; margin: 0 0 6px 0;">Звуковые темы Discord</h2>
                        <span style="color: #23a55a; font-size: 12px; font-weight: 600; background: rgba(35,165,90,0.15); border: 1px solid rgba(35,165,90,0.3); border-radius: 4px; padding: 4px 8px;">Работает в реальном времени</span>
                    </div>
                    <p style="color: #949ba4; font-size: 14px; margin: 0;">Выберите тему для рингтонов и уведомлений. Звуки применяются моментально без перезапуска.</p>
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
                                transition: background 0.15s ease, border-color 0.15s ease;
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
        function getVoiceSidebarItem() {
            const all = Array.from(document.querySelectorAll('[class*="item_"], [role="tab"], div, button, a'));
            for (const el of all) {
                const text = el.textContent.trim();
                if ((text === 'Голос и видео' || text === 'Voice & Video' || text.startsWith('Голос и видео')) && el.children.length <= 2) {
                    let row = el;
                    while (row && row.parentElement) {
                        if (row.parentElement.children.length > 5) {
                            return row;
                        }
                        row = row.parentElement;
                    }
                    return el;
                }
            }
            return null;
        }

        function injectSidebarTab() {
            if (document.getElementById('dss-sidebar-tab')) return;

            const voiceItem = getVoiceSidebarItem();
            if (!voiceItem || !voiceItem.parentElement) return;

            const parent = voiceItem.parentElement;
            const myTab = voiceItem.cloneNode(true);
            myTab.id = 'dss-sidebar-tab';
            myTab.setAttribute('role', 'tab');
            myTab.setAttribute('aria-selected', 'false');

            myTab.classList.forEach(cls => {
                if (cls.includes('selected')) myTab.classList.remove(cls);
            });

            const textElem = Array.from(myTab.querySelectorAll('*')).find(c => 
                c.children.length === 0 && (c.textContent.trim() === 'Голос и видео' || c.textContent.trim() === 'Voice & Video' || c.textContent.trim().startsWith('Голос и видео'))
            ) || myTab;
            textElem.textContent = '🎵 Звуковые темы';

            parent.insertBefore(myTab, voiceItem.nextSibling);
            remoteLog('Sidebar tab successfully injected!');

            myTab.addEventListener('click', (e) => {
                e.preventDefault();
                e.stopPropagation();

                parent.querySelectorAll('[role="tab"], [class*="item_"]').forEach(el => {
                    el.setAttribute('aria-selected', 'false');
                    el.classList.forEach(cls => {
                        if (cls.includes('selected')) el.classList.remove(cls);
                    });
                });

                myTab.setAttribute('aria-selected', 'true');
                voiceItem.classList.forEach(cls => {
                    if (cls.includes('selected')) myTab.classList.add(cls);
                });
                myTab.style.backgroundColor = 'var(--background-modifier-selected, rgba(255,255,255,0.07))';
                myTab.style.color = '#ffffff';

                showSettingsPanel();
            });

            Array.from(parent.children).forEach(sibling => {
                if (sibling === myTab || sibling.__dssListener) return;
                sibling.__dssListener = true;
                sibling.addEventListener('click', () => {
                    hideSettingsPanel();
                    myTab.setAttribute('aria-selected', 'false');
                    myTab.classList.forEach(cls => {
                        if (cls.includes('selected')) myTab.classList.remove(cls);
                    });
                    myTab.style.backgroundColor = '';
                    myTab.style.color = '';
                });
            });
        }

        function showSettingsPanel() {
            const contentRegion = document.querySelector('[class*="contentRegion_"]') || 
                                  document.querySelector('[class*="contentRegionScroller_"]') ||
                                  document.querySelector('main')?.parentElement;
            if (!contentRegion) return;

            Array.from(contentRegion.children).forEach(child => {
                if (child.id !== 'dss-panel') {
                    child.__dssPrevDisplay = child.style.display;
                    child.style.display = 'none';
                }
            });

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
                    font-family: var(--font-primary, "gg sans", sans-serif);
                    color: #dbdee1;
                `;
                contentRegion.appendChild(panel);
            }
            panel.style.display = 'block';
            renderThemesList('dss-panel');
        }

        function hideSettingsPanel() {
            const panel = document.getElementById('dss-panel');
            if (panel) panel.style.display = 'none';

            const contentRegion = document.querySelector('[class*="contentRegion_"]') || 
                                  document.querySelector('[class*="contentRegionScroller_"]') ||
                                  document.querySelector('main')?.parentElement;
            if (contentRegion) {
                Array.from(contentRegion.children).forEach(child => {
                    if (child.id !== 'dss-panel') {
                        child.style.display = child.__dssPrevDisplay !== undefined ? child.__dssPrevDisplay : '';
                    }
                });
            }
        }

        // 2. INJECT INLINE VOICE SECTION
        function injectInlineVoiceSection() {
            if (document.getElementById('dss-inline-card')) return;

            const all = Array.from(document.querySelectorAll('button, h2, h3, div'));
            const micTest = all.find(el => el.textContent.trim() === 'Проверка микрофона' || el.textContent.trim() === "Let's Check");
            if (!micTest) return;

            let container = micTest;
            while (container && container.parentElement && container !== document.body) {
                if (container.parentElement.className.includes('contentColumn_') || 
                    container.parentElement.className.includes('contentRegion_') ||
                    container.parentElement.children.length > 8) {
                    break;
                }
                container = container.parentElement;
            }

            if (!container || !container.parentElement) return;

            const inlineCard = document.createElement('div');
            inlineCard.id = 'dss-inline-card';
            inlineCard.style.cssText = `
                margin: 0 0 24px 0;
                padding: 20px 24px;
                background: #2b2d31;
                border: 1px solid #383a40;
                border-radius: 8px;
                font-family: var(--font-primary, "gg sans", sans-serif);
                box-shadow: 0 2px 10px rgba(0,0,0,0.2);
            `;

            inlineCard.innerHTML = `
                <div style="display: flex; align-items: center; justify-content: space-between; margin-bottom: 14px;">
                    <div>
                        <div style="display: flex; align-items: center; gap: 8px;">
                            <span style="font-size: 20px;">🎵</span>
                            <h3 style="color: #f2f3f5; font-size: 16px; font-weight: 700; margin: 0;">Звуковые темы Discord</h3>
                            <span style="background: #5865f2; color: #fff; font-size: 10px; font-weight: 700; padding: 2px 6px; border-radius: 4px; text-transform: uppercase;">Switcher</span>
                        </div>
                        <p style="color: #949ba4; font-size: 13px; margin: 4px 0 0 0;">Переключайте новогодние, хэллоуинские и ретро звуки в один клик прямо здесь.</p>
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
                        transition: background 0.15s ease;
                    ">
                        Сменить тему звуков
                    </button>
                </div>
                <div id="dss-inline-panel" style="display: none; margin-top: 16px; border-top: 1px solid #383a40; padding-top: 16px;"></div>
            `;

            container.parentElement.insertBefore(inlineCard, container);
            remoteLog('Inline Voice Card successfully injected!');

            const toggleBtn = inlineCard.querySelector('#dss-toggle-btn');
            const inlinePanel = inlineCard.querySelector('#dss-inline-panel');

            toggleBtn.addEventListener('click', () => {
                if (inlinePanel.style.display === 'none') {
                    inlinePanel.style.display = 'block';
                    toggleBtn.textContent = 'Скрыть';
                    toggleBtn.style.background = '#4e5058';
                    renderThemesList('dss-inline-panel');
                } else {
                    inlinePanel.style.display = 'none';
                    toggleBtn.textContent = 'Сменить тему звуков';
                    toggleBtn.style.background = '#5865f2';
                }
            });
        }

        // 3. INJECT SEARCH HELPER
        function injectSearchHelper() {
            const notFound = Array.from(document.querySelectorAll('div, h3, p')).find(el => 
                el.textContent.includes('Ничего не найдено') || el.textContent.includes('No results found')
            );
            if (notFound && notFound.parentElement && !document.getElementById('dss-search-helper')) {
                const helper = document.createElement('div');
                helper.id = 'dss-search-helper';
                helper.style.cssText = `
                    margin-top: 20px;
                    padding: 16px 20px;
                    background: #2b2d31;
                    border: 1px solid #5865f2;
                    border-radius: 8px;
                    cursor: pointer;
                    display: flex;
                    align-items: center;
                    justify-content: space-between;
                    box-shadow: 0 4px 16px rgba(0,0,0,0.3);
                `;
                helper.innerHTML = `
                    <div style="display: flex; align-items: center; gap: 12px;">
                        <span style="font-size: 24px;">🎵</span>
                        <div>
                            <div style="color: #f2f3f5; font-size: 15px; font-weight: 700;">Открыть Звуковые темы</div>
                            <div style="color: #949ba4; font-size: 13px;">Нажмите здесь, чтобы выбрать новогодний, хэллоуинский или ретро режим</div>
                        </div>
                    </div>
                    <button style="
                        background: #5865f2;
                        color: #ffffff;
                        border: none;
                        border-radius: 4px;
                        padding: 8px 16px;
                        font-weight: 600;
                        font-size: 13px;
                        cursor: pointer;
                    ">Открыть</button>
                `;
                helper.onclick = (e) => {
                    e.stopPropagation();
                    openModal();
                };
                notFound.parentElement.appendChild(helper);
            }
        }

        // 4. INJECT QUICK MODAL / BUTTON (Available from anywhere in Discord)
        function injectQuickButton() {
            let quickBtn = document.getElementById('dss-quick-btn');

            // Find Discord bottom-left panel
            const panel = document.querySelector('section[class*="panels_"], div[class*="panels_"]');
            let targetContainer = null;
            let targetRef = null;

            if (panel) {
                const buttons = Array.from(panel.querySelectorAll('button'));
                if (buttons.length >= 3) {
                    // The last button in the user controls group is the Settings button
                    targetRef = buttons[buttons.length - 1];
                    targetContainer = targetRef.parentElement;
                }
            }

            if (!targetContainer) {
                targetRef = document.querySelector('button[aria-label*="астройки"], button[aria-label*="Settings"], button[aria-label*="settings"]');
                if (targetRef) targetContainer = targetRef.parentElement;
            }

            if (targetContainer && targetRef) {
                // If button already exists in body, move it to the user panel
                if (quickBtn && quickBtn.parentElement !== targetContainer) {
                    quickBtn.remove();
                    quickBtn = null;
                }

                if (!quickBtn) {
                    quickBtn = document.createElement('button');
                    quickBtn.id = 'dss-quick-btn';
                    quickBtn.title = 'Звуковые темы Discord (Discord Sound Switcher)';
                    quickBtn.setAttribute('aria-label', 'Звуковые темы Discord');
                    quickBtn.style.cssText = `
                        display: flex;
                        align-items: center;
                        justify-content: center;
                        width: 32px;
                        height: 32px;
                        border-radius: 4px;
                        border: none;
                        background: transparent;
                        color: #b5bac1;
                        cursor: pointer;
                        font-size: 16px;
                        margin: 0 2px;
                        transition: background 0.15s ease, color 0.15s ease;
                    `;
                    quickBtn.innerHTML = '🎵';
                    quickBtn.onmouseenter = () => { quickBtn.style.background = 'rgba(255,255,255,0.08)'; quickBtn.style.color = '#ffffff'; };
                    quickBtn.onmouseleave = () => { quickBtn.style.background = 'transparent'; quickBtn.style.color = '#b5bac1'; };
                    targetContainer.insertBefore(quickBtn, targetRef);
                    quickBtn.addEventListener('click', (e) => {
                        e.preventDefault();
                        e.stopPropagation();
                        openModal();
                    });
                    remoteLog('Quick Button attached next to Settings Gear in bottom panel!');
                }
            } else if (!quickBtn) {
                // Floating fallback in bottom-right
                quickBtn = document.createElement('button');
                quickBtn.id = 'dss-quick-btn';
                quickBtn.title = 'Звуковые темы Discord (Discord Sound Switcher)';
                quickBtn.setAttribute('aria-label', 'Звуковые темы Discord');
                quickBtn.style.cssText = `
                    position: fixed;
                    bottom: 24px;
                    right: 24px;
                    width: 44px;
                    height: 44px;
                    border-radius: 50%;
                    border: none;
                    background: #5865f2;
                    color: #ffffff;
                    font-size: 20px;
                    cursor: pointer;
                    box-shadow: 0 4px 16px rgba(0,0,0,0.5);
                    z-index: 999999;
                    display: flex;
                    align-items: center;
                    justify-content: center;
                    transition: transform 0.2s ease, background 0.2s ease;
                `;
                quickBtn.innerHTML = '🎵';
                quickBtn.onmouseenter = () => { quickBtn.style.transform = 'scale(1.08)'; quickBtn.style.background = '#4752c4'; };
                quickBtn.onmouseleave = () => { quickBtn.style.transform = 'scale(1)'; quickBtn.style.background = '#5865f2'; };
                document.body.appendChild(quickBtn);
                quickBtn.addEventListener('click', (e) => {
                    e.preventDefault();
                    e.stopPropagation();
                    openModal();
                });
            }
        }

        function openModal() {
            let modal = document.getElementById('dss-modal');
            if (!modal) {
                modal = document.createElement('div');
                modal.id = 'dss-modal';
                modal.style.cssText = `
                    position: fixed;
                    top: 0;
                    left: 0;
                    width: 100vw;
                    height: 100vh;
                    background: rgba(0,0,0,0.7);
                    backdrop-filter: blur(4px);
                    z-index: 99999999;
                    display: flex;
                    align-items: center;
                    justify-content: center;
                    font-family: var(--font-primary, "gg sans", sans-serif);
                `;

                modal.innerHTML = `
                    <div style="
                        background: #313338;
                        width: 620px;
                        max-width: 90vw;
                        max-height: 85vh;
                        border-radius: 10px;
                        box-shadow: 0 8px 32px rgba(0,0,0,0.6);
                        display: flex;
                        flex-direction: column;
                        overflow: hidden;
                    ">
                        <div style="
                            padding: 18px 24px;
                            border-bottom: 1px solid #383a40;
                            display: flex;
                            align-items: center;
                            justify-content: space-between;
                        ">
                            <div style="display: flex; align-items: center; gap: 10px;">
                                <span style="font-size: 22px;">🎵</span>
                                <span style="color: #f2f3f5; font-size: 18px; font-weight: 700;">Звуковые темы Discord</span>
                            </div>
                            <button id="dss-modal-close" style="
                                background: transparent;
                                border: none;
                                color: #b5bac1;
                                font-size: 20px;
                                cursor: pointer;
                                padding: 4px 8px;
                                border-radius: 4px;
                            ">✕</button>
                        </div>
                        <div id="dss-modal-content" style="
                            padding: 24px;
                            overflow-y: auto;
                            flex: 1 1 auto;
                        "></div>
                    </div>
                `;

                document.body.appendChild(modal);

                modal.addEventListener('click', (e) => {
                    if (e.target === modal) modal.style.display = 'none';
                });

                modal.querySelector('#dss-modal-close').addEventListener('click', () => {
                    modal.style.display = 'none';
                });
            }

            modal.style.display = 'flex';
            renderThemesList('dss-modal-content');
        }

        // Run UI check cycle
        window.__dssInterval = setInterval(() => {
            try {
                injectSidebarTab();
                injectInlineVoiceSection();
                injectQuickButton();
                injectSearchHelper();
            } catch(e) {}
        }, 500);

        remoteLog('sound_ui: loaded successfully');

    } catch(err) {
        remoteLog('sound_ui CRITICAL ERROR: ' + (err ? (err.stack || err.message || err) : 'unknown'));
    }
})();
