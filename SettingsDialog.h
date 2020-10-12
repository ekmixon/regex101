/*
 * Copyright (C) 2020 Adrian Carpenter
 *
 * This file is part of a regex101.com offline application.
 *
 * https://github.com/fizzyade/regex101
 *
 * =====================================================================
 * The regex101 web content is owned and used with permission from
 * Firas Dib at regex101.com.  This application is an unofficial
 * tool to provide an offline application version of the website.
 * =====================================================================
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QIcon>
#include <QMap>
#include <QWidget>

#if defined(Q_OS_MACOS)
class QMacToolBar;
#endif

class QHBoxLayout;
class QVBoxLayout;
class QStackedWidget;
class QTreeWidget;
class QLabel;
class QMacToolBarItem;
class QParallelAnimationGroup;

namespace Nedrysoft {
    class TransparentWidget;

    /**
     * @brief               Settings page class
     *
     * @details             Describes an individual page of the application settings
     */
    class SettingsPage
    {
        public:
            enum Icon {
                General,
                Database
            };

        public:
            QString m_name;                     //! display name of the settings category page
            QString m_description;              //! description of the settings category page
#if defined(Q_OS_MACOS)
            TransparentWidget *m_widget;        //! the widget that contains the settings for this category
#else
            QWidget *m_widget;                  //! the widget that contains the settings for this category
#endif
            Icon m_icon;                        //! the icon of the page
            QMacToolBarItem *m_toolBarItem;     //! toolbar item
    };

    /**
     * @brief               Settings dialog class
     *
     * @details             Provides the settings dialog to modify preferences.  On macOS the dialog
     *                      is presented in a native style, under Windows & Linux the dialog uses a
     *                      format which is consistent and has a standard appearance for those OS's.
     */
    class SettingsDialog : public QWidget
    {
        Q_OBJECT

        public:
            /**
             * @brief           Constructs a settings window
             *
             * @param[in]       parent is the the owner of the window.
             */
            explicit SettingsDialog(QWidget *parent=nullptr);

            /**
             * @brief           Destroys a settings window
             */
            ~SettingsDialog();

        private:
            /**
             * @brief           Returns the QWindow handle from native widget
             *
             * @returns         The QWindow handle of the native window
             */
            QWindow *nativeWindowHandle();

            /**
             * @brief           Returns the platform specific icon for the given icon type
             *
             * @param[in]       icon the icon to get
             * @returns         the requested icon
             */
            QIcon getIcon(SettingsPage::Icon icon);

        protected:
            /**
             * @brief           Window resize event
             *
             * @details         Called when the widget is resized, allows child widgets to be manually resized
             *
             * @params[in]      event is the event containing the resize information
             */
            virtual void resizeEvent(QResizeEvent *event);

            /**
             * @brief           Adds a setting page
             *
             * @details         Adds the given page to the settings dialog
             *
             * @params[in]      name is the displayed name of the page
             * @params[in]      description is the description of the purpose of the page
             * @params[in]      icon is the icon of the page
             * @params[in]      widget is the widget containing the page content
             * @params[in]      defaultPage true if page is the default shown page; otherwise false
             *
             * @returns         the settings page structure
             */
            Nedrysoft::SettingsPage *addPage(QString name, QString description, SettingsPage::Icon icon, QWidget *widget, bool defaultPage=false);

        private:
#if defined(Q_OS_MACOS)
            QMacToolBar *m_toolBar;                             //! A native macOS toolbar (unified style)
            SettingsPage *m_currentPage;                        //! current widget
            int m_toolbarHeight;                                //! the height of the unified toolbar
            QParallelAnimationGroup *m_animationGroup;          //! the currently active animation
#else
            QHBoxLayout *m_layout;                              //! box layout
            QVBoxLayout *m_detailLayout;                        //! detail layout
            QTreeWidget *m_treeWidget;                          //! tree widget for categories
            QStackedWidget *m_stackedWidget;                    //! stacked widget for page content
            QLabel *m_categoryLabel;                            //! category label
#endif
            QMap<QMacToolBarItem *, SettingsPage *> m_pages;    //! The list of settings widgets
    };
}

#endif // SETTINGSDIALOG_H
