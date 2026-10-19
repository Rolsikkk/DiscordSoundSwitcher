# 🎧 Discord Sound Theme Switcher

<p align="center">
  <img src="https://img.shields.io/github/v/release/Rolsikkk/DiscordSoundSwitcher?color=7289da&style=for-the-badge" alt="Release" />
  <img src="https://img.shields.io/badge/Platform-Windows-0078d7?style=for-the-badge&logo=windows" alt="Platform" />
  <img src="https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=c%2B%2B" alt="C++17" />
  <img src="https://img.shields.io/badge/License-MIT-success?style=for-the-badge" alt="License" />
</p>

Утилита на **C++17** для мгновенного переключения звуковых тем и рингтонов в **Discord** на Windows в один клик.

Позволяет принудительно отключить сезонные хэллоуинские звуки, включить новогодний пак **Snowsgiving**, активировать редкую мемную пасхалку **Snow Halation** (1 к 1000) или выбрать Nitro-звуки (Retro 8-bit, Lo-Fi, Уточка, Bubble).

---

## ❄️ Доступные режимы звука

| Номер | Режим | Описание |
| :---: | :--- | :--- |
| `[1]` | **Классический (Default)** | Стандартные звуки Discord. Полностью отключает Хэллоуин. |
| `[2]` | **Новогодний (Winter Holiday)** | Официальный зимний пак (бубенцы, зимний звонок, праздничный войс). |
| `[3]` | **Новогодний Snowsgiving** | Зимний пак + легендарный рождественский рингтон Snowsgiving. |
| `[4]` | **Новогодний Snow Halation** | Зимний пак + секретная пасхалка (аниме-ремикс Love Live, шанс 1/1000). |
| `[5]` | **Хэллоуин (Halloween)** | Сезонный пак с призрачным сообщением и ведьминским смехом. |
| `[6]` | **Ретро 8-Бит (Retro Beat)** | 8-битный звук сообщений + битовый рингтон вызова. |
| `[7]` | **Lo-Fi Chill** | Мягкий и расслабляющий звук сообщений. |
| `[8]` | **Уточка (Ducky)** | Забавное кряканье уточки на входящие сообщения. |
| `[9]` | **Пузырьки (Bubble / Bop)** | Звонкие всплывающие пузырьки. |
| `[0]` | **Сбросить все патчи** | Полный возврат к оригинальному состоянию Discord. |

---

## ⚡ Особенности

- 🔍 **Умный автопоиск Discord:** сам находит запущенный процесс, стандартные пути (`Discord`, `DiscordCanary`, `DiscordPTB`), а если Discord установлен в нестандартную папку — запросит путь один раз и запомнит его.
- 🚀 **Безопасно и надежно:** не трогает и не ломает `.asar`-архивы и бинарники. Использует сетевой хук Electron (`webRequest`), поэтому звуки переключаются со 100% надежностью и не сбрасываются при перезапусках.
- 🔄 **Проверка обновлений:** при запуске проверяет наличие новых версий на GitHub и предлагает обновиться.
- 🧹 **Откат в 1 клик:** пункт `[0]` полностью удаляет хуки и возвращает Discord к чистому заводскому виду.

---

## 📥 Установка и запуск

1. Скачайте последний релиз **`DiscordSoundSwitcher.exe`** из раздела **[Releases](https://github.com/Rolsikkk/DiscordSoundSwitcher/releases/latest)**.
2. Запустите файл.
3. Введите номер желаемого звукового режима и нажмите `Enter`.
4. Подтвердите перезапуск Discord (`Enter` или `Y`).

---

## 🛠️ Сборка из исходников

Для компиляции потребуется любой современный компилятор C++17 (MinGW-w64 GCC, Clang или MSVC):

```cmd
git clone https://github.com/Rolsikkk/DiscordSoundSwitcher.git
cd DiscordSoundSwitcher
g++ -std=c++17 -O2 main.cpp -o DiscordSoundSwitcher.exe -lshell32 -lwininet
```

Или просто запустите `build.bat`.

---

## 📜 Лицензия

Проект распространяется под лицензией MIT. Подробности в файле [LICENSE](LICENSE).

---

## ⭐ Star History

[![Star History Chart](https://api.star-history.com/svg?repos=Rolsikkk/DiscordSoundSwitcher&type=Date)](https://star-history.com/#Rolsikkk/DiscordSoundSwitcher&Date)
