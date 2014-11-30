#ifndef NEWKEYCOMMAND_HPP
#define NEWKEYCOMMAND_HPP

#include <QUndoCommand>
#include "treeviewmodel.hpp"

class NewKeyCommand : public QUndoCommand
{

public:
	explicit NewKeyCommand(ConfigNodePtr parentNode, const QString& path, const QString& value, const QVariantMap& metaData, QUndoCommand* parent = 0);

	virtual void undo();
	virtual void redo();

private:

	ConfigNodePtr m_parentNode;
	ConfigNodePtr m_newNode;
	QString       m_path;
	QString       m_name;
	QString       m_value;
	QVariantMap   m_metaData;
};

#endif // NEWKEYCOMMAND_HPP
