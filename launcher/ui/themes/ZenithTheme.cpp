// SPDX-License-Identifier: GPL-3.0-only
/*
 *  Zenith Launcher - Next-Gen Gaming Minecraft Launcher
 *  Copyright (C) 2026 Zenith Launcher Contributors
 */
#include "ZenithTheme.h"

#include <QObject>

QString ZenithTheme::id()
{
    return "zenith_gamer";
}

QString ZenithTheme::name()
{
    return QObject::tr("Zenith Cyber (Gamer Edition)");
}

QString ZenithTheme::tooltip()
{
    return QObject::tr("High-contrast cyber gamer theme with neon cyan & purple accents and smooth cards");
}

QPalette ZenithTheme::colorScheme()
{
    QPalette cyberPalette;
    cyberPalette.setColor(QPalette::Window, QColor(13, 15, 23));          // #0d0f17
    cyberPalette.setColor(QPalette::WindowText, QColor(240, 243, 248));   // #f0f3f8
    cyberPalette.setColor(QPalette::Base, QColor(19, 23, 34));            // #131722
    cyberPalette.setColor(QPalette::AlternateBase, QColor(26, 31, 46));   // #1a1f2e
    cyberPalette.setColor(QPalette::ToolTipBase, QColor(19, 23, 34));
    cyberPalette.setColor(QPalette::ToolTipText, QColor(240, 243, 248));
    cyberPalette.setColor(QPalette::Text, QColor(240, 243, 248));
    cyberPalette.setColor(QPalette::Button, QColor(24, 28, 43));          // #181c2b
    cyberPalette.setColor(QPalette::ButtonText, Qt::white);
    cyberPalette.setColor(QPalette::BrightText, QColor(255, 68, 102));    // Neon red
    cyberPalette.setColor(QPalette::Link, QColor(0, 242, 254));           // Electric Cyan
    cyberPalette.setColor(QPalette::Highlight, QColor(0, 242, 254));      // Electric Cyan
    cyberPalette.setColor(QPalette::HighlightedText, QColor(10, 11, 16)); // Dark text on cyan
    cyberPalette.setColor(QPalette::PlaceholderText, QColor(120, 130, 155));
    cyberPalette.setColor(QPalette::Mid, QColor(37, 43, 64));             // #252b40
    return fadeInactive(cyberPalette, fadeAmount(), fadeColor());
}

double ZenithTheme::fadeAmount()
{
    return 0.45;
}

QColor ZenithTheme::fadeColor()
{
    return QColor(13, 15, 23);
}

bool ZenithTheme::hasStyleSheet()
{
    return true;
}

QString ZenithTheme::appStyleSheet()
{
    return QStringLiteral(
        "/* =================================================== */\n"
        "/*  Zenith Cyber (Gamer Edition) - Custom Stylesheet  */\n"
        "/* =================================================== */\n\n"

        "QWidget {\n"
        "    font-family: 'Segoe UI Variable Display', 'Segoe UI', 'Inter', -apple-system, sans-serif;\n"
        "}\n\n"

        "QToolTip {\n"
        "    color: #ffffff;\n"
        "    background-color: #131722;\n"
        "    border: 1px solid #00f2fe;\n"
        "    border-radius: 6px;\n"
        "    padding: 6px 10px;\n"
        "    font-size: 12px;\n"
        "}\n\n"

        "QMainWindow, QDialog {\n"
        "    background-color: #0d0f17;\n"
        "}\n\n"

        "/* --- Buttons --- */\n"
        "QPushButton {\n"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #1e2437, stop:1 #141724);\n"
        "    border: 1px solid #2b334d;\n"
        "    border-radius: 7px;\n"
        "    padding: 7px 16px;\n"
        "    color: #f0f3f8;\n"
        "    font-weight: 600;\n"
        "    min-height: 20px;\n"
        "}\n\n"
        "QPushButton:hover {\n"
        "    border: 1px solid #00f2fe;\n"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #252d44, stop:1 #181d2e);\n"
        "    color: #ffffff;\n"
        "}\n\n"
        "QPushButton:pressed {\n"
        "    background: #0f121d;\n"
        "    border: 1px solid #00b4bf;\n"
        "}\n\n"
        "QPushButton:disabled {\n"
        "    background: #11131c;\n"
        "    border: 1px solid #1a1e2b;\n"
        "    color: #555e75;\n"
        "}\n\n"

        "/* --- Inputs & Combos --- */\n"
        "QLineEdit, QSpinBox, QDoubleSpinBox, QComboBox {\n"
        "    background-color: #131722;\n"
        "    border: 1px solid #252b40;\n"
        "    border-radius: 7px;\n"
        "    padding: 6px 10px;\n"
        "    color: #f0f3f8;\n"
        "    selection-background-color: #00f2fe;\n"
        "    selection-color: #0a0b10;\n"
        "}\n\n"
        "QLineEdit:focus, QSpinBox:focus, QDoubleSpinBox:focus, QComboBox:focus {\n"
        "    border: 1px solid #00f2fe;\n"
        "    background-color: #161b28;\n"
        "}\n\n"
        "QComboBox::drop-down {\n"
        "    subcontrol-origin: padding;\n"
        "    subcontrol-position: top right;\n"
        "    width: 24px;\n"
        "    border-left-width: 0px;\n"
        "    border-top-right-radius: 7px;\n"
        "    border-bottom-right-radius: 7px;\n"
        "}\n\n"

        "/* --- ScrollBars --- */\n"
        "QScrollBar:vertical {\n"
        "    border: none;\n"
        "    background: #0d0f17;\n"
        "    width: 10px;\n"
        "    margin: 0px;\n"
        "    border-radius: 5px;\n"
        "}\n\n"
        "QScrollBar::handle:vertical {\n"
        "    background: #252b40;\n"
        "    min-height: 25px;\n"
        "    border-radius: 5px;\n"
        "}\n\n"
        "QScrollBar::handle:vertical:hover {\n"
        "    background: #00f2fe;\n"
        "}\n\n"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
        "    height: 0px;\n"
        "}\n\n"
        "QScrollBar:horizontal {\n"
        "    border: none;\n"
        "    background: #0d0f17;\n"
        "    height: 10px;\n"
        "    margin: 0px;\n"
        "    border-radius: 5px;\n"
        "}\n\n"
        "QScrollBar::handle:horizontal {\n"
        "    background: #252b40;\n"
        "    min-width: 25px;\n"
        "    border-radius: 5px;\n"
        "}\n\n"
        "QScrollBar::handle:horizontal:hover {\n"
        "    background: #00f2fe;\n"
        "}\n\n"

        "/* --- Progress Bar --- */\n"
        "QProgressBar {\n"
        "    border: 1px solid #252b40;\n"
        "    border-radius: 7px;\n"
        "    background-color: #131722;\n"
        "    text-align: center;\n"
        "    color: #ffffff;\n"
        "    font-weight: bold;\n"
        "    height: 18px;\n"
        "}\n\n"
        "QProgressBar::chunk {\n"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #00f2fe, stop:1 #7f00ff);\n"
        "    border-radius: 6px;\n"
        "}\n\n"

        "/* --- Tabs --- */\n"
        "QTabBar::tab {\n"
        "    background: transparent;\n"
        "    color: #8f9bb3;\n"
        "    padding: 9px 18px;\n"
        "    border-bottom: 2px solid transparent;\n"
        "    font-weight: 600;\n"
        "}\n\n"
        "QTabBar::tab:selected {\n"
        "    color: #00f2fe;\n"
        "    border-bottom: 2px solid #00f2fe;\n"
        "}\n\n"
        "QTabBar::tab:hover:!selected {\n"
        "    color: #ffffff;\n"
        "}\n\n"

        "/* --- Menus & Context --- */\n"
        "QMenu {\n"
        "    background-color: #141724;\n"
        "    border: 1px solid #283049;\n"
        "    border-radius: 8px;\n"
        "    padding: 6px;\n"
        "}\n\n"
        "QMenu::item {\n"
        "    padding: 7px 22px;\n"
        "    border-radius: 6px;\n"
        "    color: #f0f3f8;\n"
        "}\n\n"
        "QMenu::item:selected {\n"
        "    background-color: #20273c;\n"
        "    color: #00f2fe;\n"
        "}\n\n"
        "QMenu::separator {\n"
        "    height: 1px;\n"
        "    background: #252b40;\n"
        "    margin: 4px 8px;\n"
        "}\n\n"

        "/* --- ToolBars & Navigation --- */\n"
        "QToolBar {\n"
        "    background-color: #0d0f17;\n"
        "    border: none;\n"
        "    spacing: 5px;\n"
        "    padding: 4px;\n"
        "}\n\n"
        "QToolButton {\n"
        "    background: transparent;\n"
        "    border: 1px solid transparent;\n"
        "    border-radius: 7px;\n"
        "    padding: 6px 12px;\n"
        "    color: #f0f3f8;\n"
        "    font-weight: 500;\n"
        "}\n\n"
        "QToolButton:hover {\n"
        "    background-color: #1a1f30;\n"
        "    border: 1px solid #2f3854;\n"
        "    color: #00f2fe;\n"
        "}\n\n"
        "QToolButton:pressed, QToolButton:checked {\n"
        "    background-color: #222940;\n"
        "    border: 1px solid #00f2fe;\n"
        "    color: #00f2fe;\n"
        "}\n\n"

        "/* --- Primary Play Button (Zenith Neon Style) --- */\n"
        "QToolButton#zenithPlayButton {\n"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #00f2fe, stop:1 #4facfe);\n"
        "    color: #0b0d14;\n"
        "    font-size: 13px;\n"
        "    font-weight: 800;\n"
        "    border: 1px solid #00f2fe;\n"
        "    border-radius: 8px;\n"
        "    padding: 8px 16px;\n"
        "    min-height: 24px;\n"
        "}\n\n"
        "QToolButton#zenithPlayButton:hover {\n"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #1effff, stop:1 #67b7ff);\n"
        "    color: #000000;\n"
        "}\n\n"
        "QToolButton#zenithPlayButton:pressed {\n"
        "    background: #00bcd4;\n"
        "}\n"
    );
}
