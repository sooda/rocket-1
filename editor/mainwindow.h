#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QLabel;
class QAction;

extern "C" {
#include "../lib/track.h"
}
class SyncDocument;
class TrackView;
class ClientSocket;

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(SOCKET serverSocket);
	void createMenuBar();
	void createStatusBar();
	void updateRecentFiles();
	void setCurrentFileName(const QString &fileName);
	void setWindowFileName(const QString &fileName);
	void loadDocument(const QString &path);
	void setDocument(SyncDocument *newDoc);

	void processCommand(ClientSocket &sock);

	void setStatusPosition(int row, int col);
	void setStatusText(const QString &text);
	void setStatusValue(double val, bool valid);
	void setStatusKeyType(enum key_type keyType, bool valid);

	void timerEvent(QTimerEvent *event);
	bool guiConnected;
	SOCKET serverSocket;
	size_t clientIndex;

	TrackView *trackView;
	QLabel *statusText, *statusRow, *statusCol, *statusValue, *statusKeyType;
	QMenu *fileMenu, *recentFilesMenu, *editMenu;
	QAction *recentFileActions[5];

public slots:
	void fileNew();
	void fileOpen();
	void fileSave();
	void fileSaveAs();
	void fileRemoteExport();
	void openRecentFile();
	void fileQuit();

	void editBiasSelection();

	void editSetRows();

	void editPreviousBookmark();
	void editNextBookmark();

	void onPosChanged();
	void onCurrValDirty();
};

#endif // MAINWINDOW_H
