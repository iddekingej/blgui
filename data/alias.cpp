#include "alias.h"
#include <QDir>
#include <QDirIterator>
#include <QHash>
#include <QFile>

/**
 * Start with a file follows symlinks until it reaches a non symlink (endpoint)
 * All symlinks as stored as (symlink,endpoint)
 * 
 * \param p_file - Start point for following symlinks
 */
void TAlias::processAlias(const QString &p_file)
{
	QString l_currentFile=p_file;
	QString l_target;
	QStringList l_paths;	
	bool l_linked=false;
	while(true){			
		if(aliasses.contains(l_currentFile)){
			l_currentFile=aliasses.value(l_currentFile);
			break;
		}
		l_target=QFile::symLinkTarget(l_currentFile);
		if(l_target=="") break;
		l_paths << l_currentFile;
		l_currentFile=l_target;
		l_linked=true;
	}
	if(l_linked){
		foreach(QString l_found, l_paths){
			aliasses.insert(l_found,l_currentFile);
		}
			
	}
}
/**Scans all files in a folder "p_path" , if it is a symlink the 
 * links are followed until a non symlink is found(endpoint)
 * 
 * \param p_path - process all symlinks in this directory
*/
void TAlias::procesAliasses(const QString &p_path)
{	
	QDirIterator l_iter(p_path,QDirIterator::NoIteratorFlags);
	while(l_iter.hasNext()){
		l_iter.next();
		if(l_iter.fileInfo().isSymLink()){
			processAlias(l_iter.filePath());
		}
	}
}

/**
 *   Convert alias (=symlink) to device
 * 
 *  \param p_path alias.
 */

const QString TAlias::getDeviceNameFromAliasPath(const QString &p_path){
	QString l_path=aliasses.value(p_path);
	QFileInfo l_info(l_path);
	return l_info.fileName();
}


/**
 *  Proces all 'aliases' symlinks from a list of folders.
 */
void TAlias::readInfo()
{
	procesAliasses(QStringLiteral("/dev/disk/by-id"));
	procesAliasses(QStringLiteral("/dev/disk/by-label"));
	procesAliasses(QStringLiteral("/dev/disk/by-partlabel"));
	procesAliasses(QStringLiteral("/dev/disk/by-partuid"));
	procesAliasses(QStringLiteral("/dev/disk/by-path"));
	procesAliasses(QStringLiteral("/dev/disk/by-uuid"));
	procesAliasses(QStringLiteral("/dev/mapper"));
}
