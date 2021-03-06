/**
 * @file
 *
 * @brief
 *
 * @copyright BSD License (see doc/COPYING or http://www.libelektra.org)
 */

#ifndef EDITKEYCOMMAND_HPP
#define EDITKEYCOMMAND_HPP

#include <QUndoCommand>
#include "treeviewmodel.hpp"
#include "datacontainer.hpp"

/**
 * @brief The EditKeyCommand class. Remembers a node for redo/undo.
 */
class EditKeyCommand : public QUndoCommand
{

public:
	/**
	 * @brief The command to edit a ConfigNode.
	 *
	 * @param model The TreeViewModel that contains the ConfigNode to edit.
	 * @param index The index of the ConfigNode to edit.
	 * @param data The data needed to undo/redo the edit.
	 * @param parent An optional parent command.
	 */
	explicit        EditKeyCommand(TreeViewModel* model, int index, DataContainer* data, QUndoCommand* parent = nullptr);

	virtual void    undo() override;
	virtual void    redo() override;

private:

	TreeViewModel*  m_model;
	int             m_index;

	QString         m_oldName;
	QString			m_oldValue;
	QVariantMap     m_oldMetaData;

	QString         m_newName;
	QString			m_newValue;
	QVariantMap     m_newMetaData;
};

#endif // EDITKEYCOMMAND_HPP
