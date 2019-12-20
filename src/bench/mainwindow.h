/****************************************************************************
**
** Copyright (C) 2019 Luxoft Sweden AB
** Copyright (C) 2018 Pelagicore AG
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QML Live tool.
**
** $QT_BEGIN_LICENSE:GPL-QTAS$
** Commercial License Usage
** Licensees holding valid commercial Qt Automotive Suite licenses may use
** this file in accordance with the commercial license agreement provided
** with the Software or, alternatively, in accordance with the terms
** contained in a written agreement between you and The Qt Company.  For
** licensing terms and conditions see https://www.qt.io/terms-conditions.
** For further information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
** SPDX-License-Identifier: GPL-3.0
**
****************************************************************************/

#pragma once

#include <QtCore>
#include <QtWidgets>
#include <QtQuick>


class BenchQuickView;
class WorkspaceView;
class LogView;
class LiveDocument;
class LiveRuntime;
class LiveHubEngine;
class BenchLiveNodeEngine;
class HostModel;
class HostManager;
class AllHostsWidget;
class Host;
class HostDiscoveryManager;
class Options;
class NewProjectWizard;
class ProjectManager;
class RuntimeManager;

QT_FORWARD_DECLARE_CLASS(QToolBar);

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void activateDocument(const LiveDocument &path);
    void setWorkspace(const QString& path, bool activateRootPath = true);
    void setPluginPath(const QString& path);
    void setStaysOnTop(bool enabled);
    void setWorkspaceConfig(const QString& projectFile);
    void init();
    bool isInitialized() const { return m_initialized; }

    HostModel *hostModel() const { return m_hostModel; }
    HostManager *hostManager() const { return m_hostManager; }

public slots:
    void setImportPaths(const QStringList& pathList);

signals:
    void quitEvent();

protected:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);

private:
    void setupContent();
    void setupWorkspaceView();
    void setupHostView();
    void setupLogView();
    void setupToolBar();
    void setupMenuBar();
    void writeSettings();
    void restoreImportPathsFromSettings();
    void openWorkspaceConfigFile(const QString& path);
    void saveImportPathToSettings(const QString& path);

private slots:
    void takeSnapshot();
    void slowDownAnimations(bool enable);
    void openFolder();
    void logQuitEvent();
    void updateWindowTitle();
    void openPreferences(Host *host = nullptr);
    void openRecentFolder();
    void clearRecentFolder();
    void stayOnTop();
    void openWorkspaceConfig();
    void newWorkspaceConfigWizard();
    void newWorkspaceConfig();
    void onLogWidgetAdded(QDockWidget* logDock);
    void onLogWidgetRemoved(QDockWidget* logDock);

private:
    void updateRecentFolder(const QString &path = QString());

private:
    bool m_initialized;
    WorkspaceView *m_workspaceView;
    QString m_workspacePath;
    LogView *m_log;
    QUrl m_currentSource;
    QDockWidget *m_logDock;
    QDockWidget *m_hostDock;
    HostManager *m_hostManager;
    HostModel *m_hostModel;
    HostDiscoveryManager *m_discoveryManager;
    AllHostsWidget* m_allHosts;
    LiveHubEngine *m_hub;
    BenchLiveNodeEngine *m_node;
    QStringList m_recentFolder;
    QMenu* m_recentMenu;
    QMenu* m_logDockMenu;
    QAction *m_stayOnTop;
    QAction *m_openFolder;
    QAction *m_refresh;
    QAction *m_clipRootObject;
    QToolBar* m_toolBar;
    QStringList m_qmlDefaultimportList;
    QAction *m_openWorkspaceConfig;
    QAction *m_createWorkspaceConfig;
    NewProjectWizard *m_newWorkspaceConfigWizard;
    ProjectManager *m_projectManager;
    QSet<QString> *m_imports;
    RuntimeManager *m_runtimeManager;
    bool m_closeEvent;
};
