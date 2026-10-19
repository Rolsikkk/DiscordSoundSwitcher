(function() {
    if (window.__soundSwitcherLoaded) return;
    window.__soundSwitcherLoaded = true;

    const MODES = [
        {
            id: "winter_holiday",
            name: "Новогодний (Winter Holiday)",
            badge: "Зима",
            desc: "Официальный зимний пак Discord: бубенцы при звонке, зимние звуки входа/выхода в войс, mute и disconnect.",
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
                "7b9a183742515fc2.mp3": "c9b6b9d1ef992f1b.mp3",
                "daf6c21d9f92979a.mp3": "7a287e2f88531f25.mp3"
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
        currentAudio.play().catch(e => console.log('Preview playback error:', e));
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

        // Notify main process to update sound_mode.json and webRequest redirects
        const payload = {
            modeId: mode.id,
            modeName: mode.name,
            soundpack: mode.soundpack,
            redirects: mode.redirects
        };

        fetch('https://discord.com/__sound_switcher_api?action=set_mode&data=' + encodeURIComponent(JSON.stringify(payload)))
            .catch(() => {});

        dispatchSetSoundpack(mode.soundpack);

        // Show banner / toast
        showToast('Активирован режим: ' + mode.name);
        renderContent();
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
                box-shadow: 0 4px 16px rgba(0,0,0,0.4);
                z-index: 10000;
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

    function renderContent() {
        const panel = document.getElementById('dss-panel');
        if (!panel) return;

        panel.innerHTML = `
            <div style="margin-bottom: 24px;">
                <h2 style="color: #f2f3f5; font-size: 20px; font-weight: 700; margin: 0 0 6px 0;">Звуковые темы</h2>
                <p style="color: #949ba4; font-size: 14px; margin: 0;">Выберите звуковой режим для рингтонов и уведомлений. Звуки применяются моментально.</p>
            </div>
            <div style="display: flex; flex-direction: column; gap: 12px;">
                ${MODES.map(m => {
                    const isActive = m.id === activeModeId;
                    return `
                        <div style="
                            background: ${isActive ? '#2b2d31' : '#1e1f22'};
                            border: 1px solid ${isActive ? '#5865f2' : '#2b2d31'};
                            border-radius: 8px;
                            padding: 16px;
                            display: flex;
                            align-items: center;
                            justify-content: space-between;
                            transition: border-color 0.2s;
                        ">
                            <div style="max-width: 65%;">
                                <div style="display: flex; align-items: center; gap: 8px; margin-bottom: 4px;">
                                    <span style="color: #f2f3f5; font-size: 15px; font-weight: 600;">${m.name}</span>
                                    <span style="
                                        background: ${isActive ? '#23a55a' : '#35363c'};
                                        color: #ffffff;
                                        font-size: 11px;
                                        font-weight: 700;
                                        padding: 2px 6px;
                                        border-radius: 4px;
                                        text-transform: uppercase;
                                    ">${isActive ? 'АКТИВНО' : m.badge}</span>
                                </div>
                                <div style="color: #949ba4; font-size: 13px; line-height: 18px;">${m.desc}</div>
                            </div>
                            <div style="display: flex; align-items: center; gap: 10px;">
                                <button class="dss-preview-btn" data-url="${m.previewUrl}" style="
                                    background: #4e5058;
                                    color: #ffffff;
                                    border: none;
                                    border-radius: 4px;
                                    padding: 8px 12px;
                                    font-size: 13px;
                                    font-weight: 500;
                                    cursor: pointer;
                                    display: flex;
                                    align-items: center;
                                    gap: 6px;
                                ">
                                    ▶ Послушать
                                </button>
                                <button class="dss-apply-btn" data-id="${m.id}" style="
                                    background: ${isActive ? '#23a55a' : '#5865f2'};
                                    color: #ffffff;
                                    border: none;
                                    border-radius: 4px;
                                    padding: 8px 16px;
                                    font-size: 13px;
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

        // Bind preview buttons
        panel.querySelectorAll('.dss-preview-btn').forEach(btn => {
            btn.addEventListener('click', (e) => {
                e.stopPropagation();
                playPreview(btn.getAttribute('data-url'));
            });
        });

        // Bind apply buttons
        panel.querySelectorAll('.dss-apply-btn').forEach(btn => {
            btn.addEventListener('click', (e) => {
                e.stopPropagation();
                const m = MODES.find(x => x.id === btn.getAttribute('data-id'));
                if (m) applyMode(m);
            });
        });
    }

    function openCustomTab() {
        const sidebar = document.querySelector('nav[aria-label="Настройки пользователя"], [role="tablist"]');
        if (!sidebar) return;

        // Deselect standard tabs
        sidebar.querySelectorAll('[role="tab"]').forEach(t => {
            t.setAttribute('aria-selected', 'false');
            t.classList.remove('selected_a0', 'selected_b3f026');
        });

        // Select our tab
        const myTab = sidebar.querySelector('.dss-settings-tab');
        if (myTab) {
            myTab.setAttribute('aria-selected', 'true');
            myTab.classList.add('selected_a0');
        }

        // Hide standard contentColumn
        const contentRegion = document.querySelector('div[class*="contentRegion_"]');
        if (!contentRegion) return;

        const standardColumns = contentRegion.querySelectorAll('[class*="contentColumn_"]');
        standardColumns.forEach(c => c.style.display = 'none');

        // Create or show our panel
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
            `;
            contentRegion.appendChild(panel);
        }
        panel.style.display = 'block';
        renderContent();
    }

    function closeCustomTab() {
        const panel = document.getElementById('dss-panel');
        if (panel) panel.style.display = 'none';

        const contentRegion = document.querySelector('div[class*="contentRegion_"]');
        if (contentRegion) {
            const standardColumns = contentRegion.querySelectorAll('[class*="contentColumn_"]');
            standardColumns.forEach(c => c.style.display = '');
        }

        const myTab = document.querySelector('.dss-settings-tab');
        if (myTab) {
            myTab.setAttribute('aria-selected', 'false');
            myTab.classList.remove('selected_a0', 'selected_b3f026');
        }
    }

    // Main observer loop
    setInterval(() => {
        const sidebar = document.querySelector('nav[aria-label="Настройки пользователя"], [role="tablist"]');
        if (!sidebar) {
            closeCustomTab();
            return;
        }

        if (sidebar.querySelector('.dss-settings-tab')) return;

        const tabs = Array.from(sidebar.querySelectorAll('[role="tab"]'));
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
            openCustomTab();
        });

        // Whenever standard tabs are clicked, hide our panel
        tabs.forEach(t => {
            t.addEventListener('click', () => {
                closeCustomTab();
            });
        });
    }, 400);

})();
